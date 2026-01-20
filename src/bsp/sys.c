#include <bsp/sys.h>

__attribute__((__weak__))
void bsp_init(void) {
    return;
}

__attribute__((__weak__))
__attribute__((__noreturn__))
void halt(int code) {
    while (true);
}

__attribute__((__weak__))
__attribute__((__noreturn__))
void reset(int code) {
    while (true);
}
