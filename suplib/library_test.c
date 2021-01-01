// This is a nearly identical test program from liburing, but changed to use the wrapper functions rather than the inline static ones.

#include <stdio.h>
//#include <linux/fcntl.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <liburing.h>
#include "library.h"

// I don't know why this is happening, but it's not getting defined for me from fcntl.h
#ifndef O_DIRECT
#define O_DIRECT 00040000 
#endif

const int queue_depth = 4;

int main() {
	struct io_uring ring;
	int i, fd, ret, pending, done;
	struct io_uring_sqe *sqe;
	struct io_uring_cqe *cqe;
	struct iovec *iovecs;
	struct stat sb;
	ssize_t fsize;
	off_t offset;
	void *buf;

	ret = io_uring_queue_init(queue_depth, &ring, 0);

	if (ret < 0) {
		fprintf(stderr, "queue_init: %s\n", strerror(-ret));
		return 1;
	}

	// with a new enough kernel, this could use the io_uring openat2 op
	fd = open("testfile.txt", O_RDONLY | O_DIRECT);
	if (fd < 0) {
		perror("open");
		return 1;
	}

	if (fstat(fd, &sb) < 0) {
		perror("fstat");
		return 1;
	}



	fsize = 0;
	iovecs = calloc(queue_depth, sizeof(struct iovec));
	for (i = 0; i < queue_depth; i++) {
		if (posix_memalign(&buf, 4096, 4096))
			return 1;
		iovecs[i].iov_base = buf;
		iovecs[i].iov_len = 4096;
		fsize += 4096;
	}

	offset = 0;
	i = 0;
	do {
		sqe = io_uring_get_sqe(&ring);
		if (!sqe)
			break;
		MY_io_uring_prep_readv(sqe, fd, &iovecs[i], 1, offset);
		offset += iovecs[i].iov_len;
		i++;
		if (offset > sb.st_size)
			break;
	} while (1);

	ret = io_uring_submit(&ring);
	if (ret < 0) {
		fprintf(stderr, "io_uring_submit: %s\n", strerror(-ret));
		return 1;
	} else if (ret != i) {
		fprintf(stderr, "io_uring_submit submitted less %d\n", ret);
		return 1;
	}

	done = 0;
	pending = ret;
	fsize = 0;
	for (i = 0; i < pending; i++) {
		ret = MY_io_uring_wait_cqe(&ring, &cqe);
		if (ret < 0) {
			fprintf(stderr, "io_uring_wait_cqe: %s\n", strerror(-ret));
			return 1;
		}

		done++;
		ret = 0;
		if (cqe->res != 4096 && cqe->res + fsize != sb.st_size) {
			fprintf(stderr, "ret=%d, wanted 4096\n", cqe->res);
			ret = 1;
		}
		fsize += cqe->res;
		MY_io_uring_cqe_seen(&ring, cqe);
		if (ret)
			break;
	}

	printf("Submitted=%d, completed=%d, bytes=%lu\n", pending, done,
						(unsigned long) fsize);
	close(fd);
	io_uring_queue_exit(&ring);
	return 0;


	return 0;
}
