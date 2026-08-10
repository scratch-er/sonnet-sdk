#ifndef __BSP_SYS_H
#define __BSP_SYS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Heap */

/**
 * @brief Memory area descriptor
 * 
 * Describes a contiguous memory region with start and end addresses.
 * Used to define heap and other memory areas.
 */
typedef struct {
    void* start;    /**< Pointer to start of memory area */
    void* end;      /**< Pointer to end of memory area (exclusive) */
} area_t;

/**
 * @brief Global heap memory area
 * 
 * Externally defined heap area that can be used by memory allocators.
 * The actual definition must be provided in the board-specific implementation.
 */
extern const area_t heap;

/* Initialization and Shutting Down */

/**
 * @brief Initialize the Board Support Package
 * 
 * Performs hardware initialization including clocks, GPIO, UART, and other
 * board-specific peripherals. This function must be called before `main`.
 */
void bsp_init(void);

/**
 * @brief Halt the system with an error code
 * 
 * @param code Exit code indicating reason for halt (0 = normal, non-zero = error)
 * @note If shutting down is not supported by hardware, this should be implemenented
 * as a reset or a forever loop.
 */
__attribute__((__noreturn__))
void halt(int code);

/**
 * @brief Reset the system with a status code
 * 
 * @param code Reset code indicating reason for reset
 * @note If restting is not supported by hardware, this should be implemenented
 * as shutting down or a forever loop.
 */
__attribute__((__noreturn__))
void reset(int code);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_SYS_H */
