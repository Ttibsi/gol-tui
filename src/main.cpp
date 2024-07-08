#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include <rawterm/core.h>
#include <rawterm/color.h>
#include <rawterm/cursor.h>

#include "game.h"

int main() {
    using namespace std::chrono_literals;

    rawterm::enable_raw_mode();
    rawterm::enter_alt_screen();
    rawterm::enable_signals();

    rawterm::Cursor c = rawterm::Cursor();
    rawterm::Cursor::cursor_hide();
    c.reset();

    board_t initial_cells = generate_initial_cells();

    while (true) {
        initial_cells = redraw_board(c, initial_cells);
        auto k = rawterm::process_keypress();

        if (k.has_value()) {
            if (k.value() == rawterm::Key('q')) {
                break; 
            } else if (k.value() == rawterm::Key(' ', rawterm::Mod::Space)) {
                rawterm::wait_for_input();
            }
        }

        std::this_thread::sleep_for(330ms);
    }

    rawterm::exit_alt_screen();
    rawterm::Cursor::cursor_show();
    return 0;
}
