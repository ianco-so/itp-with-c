#include <stdio.h>
#include <stdarg.h>
#include <select.h>
#include <time.h>
#include <types.h>
#include <unistd.h>

int sync_scanf(time_t sec, const char *format, ...);

int main(int argc, char **argv) {

    int i;
    int value;
    int ret;

    for (i = 0 ; i < 10 ; i++ ) {
        ret = sync_scanf(3, "%d", &value);

        if( ret > 0 ) {
            printf("OK %d\n", value);
        } else if( ret == -2 ) {
            printf("3 seconds passed and you typed nothing!\n");
            break;
        } else {
            printf("No enough arguments\n");
            break;
        }
    }

    return 0;
}

int sync_scanf(time_t sec, const char *format, ...) {
    int re;
    va_list arg;
    fd_set readfds;
    struct timeval timeout = {0};

    timeout.tv_sec = sec;

    FD_ZERO(&readfds);
    FD_SET(0, &readfds);

    re = select(1, &readfds, NULL, NULL, &timeout);

    if( re == -1 ) {
        perror("Error");
        return -1;
    }
    else if( re == 0 ) {
        return -2;
    }

    va_start(arg, format);
    re = vfscanf(stdin, format, arg);
    va_end(arg);

    return re;
}