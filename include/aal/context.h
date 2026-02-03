#ifndef __AAL_CONTEXT_H
#define __AAL_CONTEXT_H

#include <stdint.h>

struct context_t;
typedef struct context_t context_t;

void* get_stack_pointer(void);

context_t* create_context(void* (*entry)(void*), void (*exit)(void*), void* stack_pointer, void* arg);

void switch_to_context(context_t* context, context_t** save);

#endif // __AAL_CONTEXT_H
