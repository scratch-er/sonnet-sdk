#ifndef __minefield_H
#define __minefield_H
#include <stdint.h>
#include <stdbool.h>

typedef struct block_t {
    bool is_mine;
    bool is_opened; 
    bool is_marked;
    uint8_t nearby_mines;
} block_t;

typedef struct minefield_t {
    uint16_t height;
    uint16_t width;
    uint32_t num_of_mines;
    block_t *blocks;
    uint32_t opened_blocks;
    bool is_lost;
} minefield_t;

/**
 * * @brief Initialize the minefield.
 *
 * Note that the `height`, `width`, `num_of_mines` and `blocks` fields of the `minefield` structure must be corectly set
 * before calling this function.
 * 
 * @param minefield The minefield to initialize.
 * @param num_of_mines The number of mines in the minefield.
 */
void init_minefield(minefield_t *minefield);

/**
 * @brief Retrieve a block from the minefield.
 *
 * This function retrieves a pointer to the block located at the given row and column in the minefield. It
 * returns NULL if the row or column is out of bounds.
 *
 * @param minefield The minefield containing the block.
 * @param row The row index of the block.
 * @param col The column index of the block.
 * @return A pointer to the block at the specified row and column, or NULL if the row or column is out of
 * bounds.
 */
block_t *get_block(minefield_t *minefield, uint16_t row, uint16_t col);

/**
 * @brief Opens a block in the minefield.
 *
 * This function attempts to open a block at the specified row and column.
 * If the opened block has no nearby mines, all adjacent blocks are also opened recursively.
 * If the block is a mine, the game is lost.
 *
 * @param minefield The minefield to open a block in.
 * @param row The row index of the block to open.
 * @param col The column index of the block to open.
 */
void open_block(minefield_t *minefield, uint16_t row, uint16_t col);

/**
 * @brief Marks a block in the minefield.
 *
 * This function attempts to mark a block at the specified row and column. 
 * If out of bound, nothing will happen.
 *
 * @param minefield The minefield to mark a block in.
 * @param row The row index of the block to mark.
 * @param col The column index of the block to mark.
 */
void mark_block(minefield_t *minefield, uint16_t row, uint16_t col);

/**
 * @brief Unmarks a block in the minefield.
 *
 * This function attempts to unmark a block at the specified row and column. 
 * If out of bound, nothing will happen.
 *
 * @param minefield The minefield to unmark a block in.
 * @param row The row index of the block to unmark.
 * @param col The column index of the block to unmark.
 */
void unmark_block(minefield_t *minefield, uint16_t row, uint16_t col);

/**
 * @brief Whether the game is beaten.
 */
bool is_beaten(minefield_t *minefield);

/**
 * @brief Whether the game is lost.
 */
bool is_lost(minefield_t *minefield);

#endif
