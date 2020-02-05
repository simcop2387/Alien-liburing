use Test::More;
use Test::Alien;
use Alien::liburing;

alien_ok 'Alien::liburing';
ffi_ok { symbols => ['io_uring_get_probe_ring'] };

done_testing;
