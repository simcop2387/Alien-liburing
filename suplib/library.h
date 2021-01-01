// This header should only ever be used for tests

// bare struct definitions for prototypes
struct statx;
struct epoll_event;

int MY_io_uring_opcode_supported(struct io_uring_probe *p, int op);
void MY_io_uring_cq_advance(struct io_uring *ring, unsigned nr);
void MY_io_uring_cqe_seen(struct io_uring *ring, struct io_uring_cqe *cqe);
void MY_io_uring_sqe_set_data(struct io_uring_sqe *sqe, void *data);
void *MY_io_uring_cqe_get_data(const struct io_uring_cqe *cqe);
void MY_io_uring_sqe_set_flags(struct io_uring_sqe *sqe, unsigned flags);
void MY_io_uring_prep_rw(int op, struct io_uring_sqe *sqe, int fd, const void *addr, unsigned len, __u64 offset);
void MY_io_uring_prep_splice(struct io_uring_sqe *sqe, int fd_in, int64_t off_in, int fd_out, int64_t off_out, unsigned int nbytes, unsigned int splice_flags);
void MY_io_uring_prep_tee(struct io_uring_sqe *sqe, int fd_in, int fd_out, unsigned int nbytes, unsigned int splice_flags);
void MY_io_uring_prep_readv(struct io_uring_sqe *sqe, int fd, const struct iovec *iovecs,unsigned nr_vecs, off_t offset);
void MY_io_uring_prep_read_fixed(struct io_uring_sqe *sqe, int fd, void *buf, unsigned nbytes, off_t offset, int buf_index);
void MY_io_uring_prep_writev(struct io_uring_sqe *sqe, int fd,const struct iovec *iovecs, unsigned nr_vecs, off_t offset);
void MY_io_uring_prep_write_fixed(struct io_uring_sqe *sqe, int fd, const void *buf, unsigned nbytes, off_t offset, int buf_index);
void MY_io_uring_prep_recvmsg(struct io_uring_sqe *sqe, int fd, struct msghdr *msg, unsigned flags);
void MY_io_uring_prep_sendmsg(struct io_uring_sqe *sqe, int fd, const struct msghdr *msg, unsigned flags);
void MY_io_uring_prep_poll_add(struct io_uring_sqe *sqe, int fd, unsigned poll_mask);
void MY_io_uring_prep_poll_remove(struct io_uring_sqe *sqe, void *user_data);
void MY_io_uring_prep_fsync(struct io_uring_sqe *sqe, int fd, unsigned fsync_flags);
void MY_io_uring_prep_nop(struct io_uring_sqe *sqe);
void MY_io_uring_prep_timeout(struct io_uring_sqe *sqe, struct __kernel_timespec *ts, unsigned count, unsigned flags);
void MY_io_uring_prep_timeout_remove(struct io_uring_sqe *sqe, __u64 user_data, unsigned flags);
void MY_io_uring_prep_timeout_update(struct io_uring_sqe *sqe, struct __kernel_timespec *ts,__u64 user_data, unsigned flags);
void MY_io_uring_prep_accept(struct io_uring_sqe *sqe, int fd, struct sockaddr *addr, socklen_t *addrlen, int flags);
void MY_io_uring_prep_cancel(struct io_uring_sqe *sqe, void *user_data, int flags);
void MY_io_uring_prep_link_timeout(struct io_uring_sqe *sqe, struct __kernel_timespec *ts, unsigned flags);
void MY_io_uring_prep_connect(struct io_uring_sqe *sqe, int fd, const struct sockaddr *addr, socklen_t addrlen);
void MY_io_uring_prep_files_update(struct io_uring_sqe *sqe, int *fds, unsigned nr_fds, int offset);
void MY_io_uring_prep_fallocate(struct io_uring_sqe *sqe, int fd, int mode, off_t offset, off_t len);
void MY_io_uring_prep_openat(struct io_uring_sqe *sqe, int dfd, const char *path, int flags, mode_t mode);
void MY_io_uring_prep_close(struct io_uring_sqe *sqe, int fd);
void MY_io_uring_prep_read(struct io_uring_sqe *sqe, int fd, void *buf, unsigned nbytes, off_t offset);
void MY_io_uring_prep_write(struct io_uring_sqe *sqe, int fd, const void *buf, unsigned nbytes, off_t offset);
void MY_io_uring_prep_statx(struct io_uring_sqe *sqe, int dfd, const char *path, int flags, unsigned mask, struct statx *statxbuf);
void MY_io_uring_prep_fadvise(struct io_uring_sqe *sqe, int fd, off_t offset, off_t len, int advice);
void MY_io_uring_prep_madvise(struct io_uring_sqe *sqe, void *addr, off_t length, int advice);
void MY_io_uring_prep_send(struct io_uring_sqe *sqe, int sockfd, const void *buf, size_t len, int flags);
void MY_io_uring_prep_recv(struct io_uring_sqe *sqe, int sockfd, void *buf, size_t len, int flags);
void MY_io_uring_prep_openat2(struct io_uring_sqe *sqe, int dfd, const char *path, struct open_how *how);
void MY_io_uring_prep_epoll_ctl(struct io_uring_sqe *sqe, int epfd, int fd, int op, struct epoll_event *ev);
void MY_io_uring_prep_provide_buffers(struct io_uring_sqe *sqe, void *addr, int len, int nr, int bgid, int bid);
void MY_io_uring_prep_remove_buffers(struct io_uring_sqe *sqe, int nr, int bgid);
void MY_io_uring_prep_shutdown(struct io_uring_sqe *sqe, int fd, int how);
void MY_io_uring_prep_unlinkat(struct io_uring_sqe *sqe, int dfd, const char *path, int flags);
void MY_io_uring_prep_renameat(struct io_uring_sqe *sqe, int olddfd, const char *oldpath, int newdfd, const char *newpath, int flags);
unsigned MY_io_uring_sq_ready(struct io_uring *ring);
unsigned MY_io_uring_sq_space_left(struct io_uring *ring);
int MY_io_uring_sqring_wait(struct io_uring *ring);
unsigned MY_io_uring_cq_ready(struct io_uring *ring);
bool MY_io_uring_cq_eventfd_enabled(struct io_uring *ring);
int MY_io_uring_cq_eventfd_toggle(struct io_uring *ring, bool enabled);
int MY_io_uring_wait_cqe_nr(struct io_uring *ring, struct io_uring_cqe **cqe_ptr, unsigned wait_nr);
int MY_io_uring_peek_cqe(struct io_uring *ring, struct io_uring_cqe **cqe_ptr);
int MY_io_uring_wait_cqe(struct io_uring *ring, struct io_uring_cqe **cqe_ptr);