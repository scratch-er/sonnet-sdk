#include <bsp/io.h>
#include <stddef.h>

__attribute__((__weak__))
void putch(char ch) {
    return;
}

__attribute__((__weak__))
char getch(void) {
    while (true);
}
