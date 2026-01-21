#include "minefield.h"
#include <lightio.h>
#include <stdint.h>

typedef enum state_t {NEW_GAME, IN_GAME, GAME_OVER} state_t;

void output_minefield(minefield_t *minefield);
void print_help(void);

#define MAX_BLOCKS 128u

int main() {
    state_t state = GAME_OVER;
    state_t next_state;
    // user input
    uint8_t command;
    bool new_game = false;
    unsigned height, width, num_of_mines;

    minefield_t minefield;
    block_t blocks[MAX_BLOCKS];

    print_help();

    while (true) {
        switch (state) {
            case NEW_GAME:
                minefield.height = height;
                minefield.width = width;
                minefield.num_of_mines = num_of_mines;
                minefield.blocks = blocks;
                init_minefield(&minefield);
                new_game = false;
                output_minefield(&minefield);
                break;
            case IN_GAME:
                switch (command) {
                    case 'o':
                        open_block(&minefield, height, width);
                        break;
                    case 'm':
                        mark_block(&minefield, height, width);
                        break;
                    case 'u':
                        unmark_block(&minefield, height, width);
                        break;
                    default:
                        break;
                }
                output_minefield(&minefield);
                break;
            case GAME_OVER:
                output_str("use command `n` to start a new game, or use command `q` to quite game.\n", 0);
                break;
        }

        // parse user input
        output_str("> ", 0);
        command = getch();
        switch (command) {
            case 'n':
                height = input_uint32_dec();
                width = input_uint32_dec();
                num_of_mines = input_uint32_dec();
                if (width*height > MAX_BLOCKS) {
                    output_str("Maximum number of blocks is ", 0);
                    output_uint32_dec(MAX_BLOCKS, 0);
                    output_str(".\n", 0);
                    new_game = false;
                } else if (num_of_mines > width*height/2) {
                    output_str("Number of mines cannot exceed half of the number of blocks.\n", 0);
                    new_game = false;
                } else {
                    new_game = true;
                }
                break;
            case 'o':
            case 'm':
            case 'u':
                new_game = false;
                height = input_uint32_dec();
                width = input_uint32_dec();
                break;
            case 'q':
                return 0;
                break;
            default:
                break;
        }

        // decide the next state
        switch (state) {
            case NEW_GAME:
                next_state = IN_GAME;
                break;
            case IN_GAME:
                if (is_beaten(&minefield) || is_lost(&minefield)) {
                    next_state = GAME_OVER;
                } else if (new_game) {
                    next_state = NEW_GAME;
                } else {
                    next_state = IN_GAME;
                }
                break;
            case GAME_OVER:
                if (new_game) {
                    next_state = NEW_GAME;
                } else {
                    next_state = GAME_OVER;
                }
                break;
        }
        state = next_state;
    }

    return 0;
}

void print_help(void) {
    output_str("Welcome to minesweeper!\n", 0);
    output_str("n <height> <width> <n_mines>: start a new game\n", 0);
    output_str("o <row> <col>: open a block\n", 0);
    output_str("m <row> <col>: mark a block\n", 0);
    output_str("u <row> <col>: unmark a block\n", 0);
    output_str("q: quite game\n", 0);
}

void output_minefield(minefield_t *minefield) {
    output_str("\n   ", 0);
    for (uint16_t c=0; c<minefield->width; ++c) {
        output_str("", 3 - output_uint32_dec(c, 0));
    }
    putch('\n');
    for (uint16_t r=0; r<minefield->height; ++r) {
        output_str("", 3 - output_uint32_dec(r, 0));;
        for (uint16_t c=0; c<minefield->width; ++c) {
            block_t *block = get_block(minefield, r, c);
            if (block->is_opened) {
                if (block->is_mine) {
                    output_str("*", 3);
                } else {
                    output_str("", 3 - output_uint32_dec(block->nearby_mines, 0));
                }
            } else if (block->is_marked) {
                output_str("!", 3);
            } else {
                output_str("-", 3);
            }
        }
        putch('\n');
    }

    if (is_beaten(minefield)) {
        output_str("You win!\n", 0);
    }
    if (is_lost(minefield)) {
        output_str("You lost!\n", 0);
    }
}
