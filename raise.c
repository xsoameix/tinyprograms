#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void
catch(int signo) {
    int a = 1;
}

int
main(void) {
    if(signal(SIGINT, catch) == SIG_ERR) {
        return EXIT_FAILURE;
    }
    return 0;
}
