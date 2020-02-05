use Test::More;
use Test::Alien;
use Alien::liburing;

alien_ok 'Alien::liburing';
#ffi_ok { symbols => ['cmark_version_string','cmark_markdown_to_html'] };
#run_ok(['cmark', '--version'])->exit_is(0);

done_testing;
