#ifndef BOARDS_H
#define BOARDS_H

#define BOARD_UNKNOWN -1

#define BOARD_DEFAULT               1    
#define BOARD_FABSCAN               2

#define MB(board) (MOTHERBOARD==BOARD_##board)

#endif
