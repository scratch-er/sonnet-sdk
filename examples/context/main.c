#include <aal/context.h>
#include <lightio.h>
#include <stdint.h>

uint32_t stack[1024];
context_t* main_context;

void* hello(void* arg) {
    output_str("Hello, world from new context!\r\n", 0);
    return (void*)(0xdeadbeef);
}

void context_exit(void* arg) {
    output_str("Context exited with code ", 0);
    output_uint32_hex((uint32_t)arg, 8);
    output_str(".\r\n", 0);
    switch_to_context(main_context, NULL);
}

int main() {
    output_str("Switching to new context.\r\n", 0);
    context_t* new_context = create_context(hello, context_exit, stack+1024, &main_context);
    switch_to_context(new_context, &main_context);
    output_str("Switched back.\r\n", 0);
    return 0;
}
