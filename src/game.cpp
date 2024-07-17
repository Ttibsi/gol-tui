#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <vector>

#include <nlohmann/json.h>
#include <rawterm/color.h>
#include <rawterm/core.h>
#include <rawterm/screen.h>
#include <rawterm/text.h>

#include "game.h"

using json = nlohmann::json;

// TODO: handle off the screen

board_t generate_initial_cells() {
  board_t ret;
  auto term_size = rawterm::get_term_size();
  for (int i = 1; i < term_size.vertical; i++) {
    for (int j = 1; j < term_size.horizontal; j++) {
      ret.emplace(rawterm::Pos(i, j), false);
    }
  }

  std::ifstream f("config.json");
  json data = json::parse(f);

  for (auto &&d : data) {
    ret[rawterm::Pos(d["y"], d["x"])] = true;
  }

  return ret;
}

board_t get_cells(board_t current_cells) {
  board_t ret;

  const std::array<rawterm::Pos, 8> relative_cords = {
      rawterm::Pos(-1, -1), rawterm::Pos(-1, 0),  rawterm::Pos(-1, 1),
      rawterm::Pos(0, -1),  rawterm::Pos(0, +1),  rawterm::Pos(+1, -1),
      rawterm::Pos(+1, 0),  rawterm::Pos(+1, +1),
  };

  for (auto &&cell : current_cells) {
    int living_neighbors = 0;

    for (const rawterm::Pos &i : relative_cords) {
      auto tmp = rawterm::Pos(i.vertical + cell.first.vertical,
                              i.horizontal + cell.first.horizontal);

      try {
        if (current_cells.at(tmp)) {
          living_neighbors++;
        }
      } catch (const std::out_of_range &) {
        continue;
      }
    }

    // Any live cell with two or three live neighbours lives on to the next
    // generation. Any live cell with fewer than two live neighbours dies, as if
    // by underpopulation. Any live cell with more than three live neighbours
    // dies, as if by overpopulation. Any dead cell with exactly three live
    // neighbours becomes a live cell, as if by reproduction.

    if (current_cells[cell.first]) {
      ret[cell.first] = (living_neighbors == 2 || living_neighbors == 3);
    } else {
      ret[cell.first] = (living_neighbors == 3);
    }
  }

  return ret;
}

board_t redraw_board(rawterm::Cursor &c, board_t cells) {
  for (auto &&[pos, alive] : cells) {
    c.move(pos);
    if (alive) {
      std::cout << rawterm::set_background(" ", rawterm::Colors::orange);
    } else {
      std::cout << rawterm::set_background(" ", rawterm::Colors::gray);
    }
  }

  return get_cells(cells);
}
