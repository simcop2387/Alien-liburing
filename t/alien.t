use Test::More;
use Test::Alien;
use Alien::liburing;

alien_ok 'Alien::liburing';

ffi_ok { symbols => [qw/
    io_uring_get_probe io_uring_get_probe_ring io_uring_get_sqe io_uring_peek_batch_cqe 
    io_uring_queue_exit io_uring_queue_init io_uring_queue_init_params io_uring_queue_mmap
    io_uring_register_buffers io_uring_register_eventfd io_uring_register_files 
    io_uring_register_files_update io_uring_register_personality io_uring_register_probe 
    io_uring_ring_dontfork io_uring_submit io_uring_submit_and_wait io_uring_unregister_buffers 
    io_uring_unregister_files io_uring_unregister_personality io_uring_wait_cqes io_uring_wait_cqe_timeout/] };

done_testing;
