#ifndef GAME_H
#define GAME_H

#include <unordered_map>
#include <rawterm/cursor.h>

using board_t = std::unordered_map<rawterm::Pos, bool>;

board_t generate_initial_cells();
board_t redraw_board(rawterm::Cursor&, board_t);

#endif // GAME_H
