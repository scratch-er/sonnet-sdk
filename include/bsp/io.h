#ifndef __BSP_IO_H
#define __BSP_IO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Note: do not mix direct use of functions in this header with stdio functions,
 * as stdio functions can have buffering
*/

/**
 * @brief Output a character to the default console
 * 
 * Writes a single character to the system console (typically UART).
 * 
 * @param ch Character to output
 * @note If the system has no console, this should do nothing.
 */
void putch(char ch);

/**
 * @brief Read a character from the default console
 * 
 * Reads a single character from the system console (typically UART).
 * This function may block until a character is available.
 * 
 * @return Character read from console
 * @note If the system has no console, this should block forever.
 */
char getch(void);

#ifdef __cplusplus
}
#endif

#endif
