#include <bsp/time.h>
#include <bsp/io.h>
#include <stddef.h>

const char* msg = "Hello, world!\r\n";

int main() {
    for (int i=0; i<16; ++i) {
        for (size_t i=0; msg[i]; ++i) {
            putch(msg[i]);
        }
        spin_delay(500000);
    }
    return 0;
}
