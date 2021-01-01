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



	return 0;
}
