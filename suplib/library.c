#include <stdio.h>
#include <liburing.h>

void hello() {
	io_uring_prep_splice(NULL, 0, 0, 0, 0, 1, 0);

	printf("Hello world!\n");
}
