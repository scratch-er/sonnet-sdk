#ifndef __BSP_TIME_H
#define __BSP_TIME_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Note:
 * 
 * Althoght `uptime_us()` and `cycle_count()` are both time related functions,
 * they serve slightly different purposes. 
 *
 * `uptime_us()` gets the "real world" time, and `cycle_count()` gets the performance counter.
 * The time calculated from them can be different when, for example, the CPU enters sleep.
 *
 * It is recommended that `uptime_us()` uses system timer or RTC as time source.
 * And on simplest hardware (e.g. no RTC or even no system timer),
 * it is reasonable for `uptime_us` to use cycle counter as time source.
 */

/**
 * @brief Get system uptime in microseconds
 * 
 * Returns the time elapsed since system initialization in microseconds.
 * The counter may wrap around depending on implementation.
 * 
 * @return Uptime in microseconds
 * @note If the system has no time source, this should return zero.
 */
uint64_t uptime_us(void);

/**
 * @brief Get CPU time in cycles
 * 
 * Returns the CPU cycles consumed since system initialization.
 * The counter may wrap around depending on implementation.
 * 
 * @return CPU cycle count
 * @note If the system has no cycle counter, this should return zero.
 */
uint64_t cycle_count(void);

/**
 * @brief Get CPU instruction count
 * 
 * @return CPU instruction count
 * @note If the system has no instruction counter, this should return zero.
 */
uint64_t instr_count(void);

/**
 * @brief Busy-wait delay in microseconds
 * 
 * Performs a busy-wait delay for the specified number of microseconds.
 * This function spins in a loop and does not yield to other tasks.
 * 
 * @param us Number of microseconds to delay
 * @note Do not use this in an RTOS.
 */
void spin_delay(uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_TIME_H */
