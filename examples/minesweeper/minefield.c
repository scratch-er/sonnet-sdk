#include <stddef.h>
#include <limits.h>
#include "minefield.h"

int gen_rand(void) {
    static unsigned int _random_seed;
    if (_random_seed == 0) {
        _random_seed = 0x7a2d5eed;
    }
    unsigned int feedback = 0;
    feedback ^= (_random_seed>>31) | 1;
    feedback ^= (_random_seed>>21) | 1;
    feedback ^= (_random_seed>>1) | 1;
    feedback ^= (_random_seed>>0) | 1;
    _random_seed >>= 1;
    _random_seed |= feedback<<31;
    return (_random_seed >> 1) % INT_MAX;
}

void init_minefield(minefield_t *minefield) {
    // make it empty
    uint32_t num_of_blocks = minefield->width * minefield->height;
    minefield->opened_blocks = 0;
    minefield->is_lost = false;
    for (uint32_t i=0; i<num_of_blocks; ++i) {
        minefield->blocks[i].is_mine = false;
        minefield->blocks[i].is_opened = false;
        minefield->blocks[i].is_marked = false;
        minefield->blocks[i].nearby_mines = 0;
    }

    // genetate mines
    uint32_t current_num_of_mines = 0;
    while (current_num_of_mines < minefield->num_of_mines) {
        block_t *block = minefield->blocks + gen_rand()%num_of_blocks;
        if (!block->is_mine) {
            block->is_mine = true;
            current_num_of_mines += 1;
        }
    }
    
    // count the nearby mines of all blocks
    for (int r=0; r<minefield->height; ++r) {
        for (int c=0; c<minefield->width; ++c) {
            block_t *current_block = get_block(minefield, r, c);
            for (int i=-1; i<=1; ++i) {
                for (int j=-1; j<=1; ++j) {
                    block_t *neighbor = get_block(minefield, r+i, c+j);
                    if (neighbor != NULL) {
                        if (neighbor->is_mine) {
                            current_block->nearby_mines += 1;
                        }
                    }
                }
            }
        }
    }
}

block_t *get_block(minefield_t *minefield, uint16_t row, uint16_t col) {
    // in C, overflow behavior of unsigned values are defined
    if (row>=minefield->height || col>=minefield->width) {
        return NULL;
    }
    uint32_t offset = row*minefield->width + col;
    return minefield->blocks + offset;
}

void open_block(minefield_t *minefield, uint16_t row, uint16_t col) {
    block_t *block = get_block(minefield, row, col);
    if (block == NULL) {
        return;
    }
    if (block->is_opened) {
        return;
    }
    block->is_opened = true;
    if (block->nearby_mines == 0) {
        for (int i=-1; i<=1; ++i) {
            for (int j=-1; j<=1; ++j) {
                open_block(minefield, row+i, col+j);
            }
        }
    }
    if (block->is_mine) {
        minefield->is_lost = true;
    }
    minefield->opened_blocks += 1;
}

void mark_block(minefield_t *minefield, uint16_t row, uint16_t col) {
    block_t *block = get_block(minefield, row, col);
    if (block != NULL) {
        block->is_marked = true;
    }
}

void unmark_block(minefield_t *minefield, uint16_t row, uint16_t col) {
    block_t *block = get_block(minefield, row, col);
    if (block != NULL) {
        block->is_marked = false;
    }
}

bool is_beaten(minefield_t *minefield) {
    uint32_t num_of_blockes = minefield->height*minefield->width;
    if (minefield->is_lost || num_of_blockes==0) {
        return false;
    } else {
        return minefield->opened_blocks + minefield->num_of_mines == num_of_blockes;
    }
}

bool is_lost(minefield_t *minefield) {
    return minefield->is_lost;
}