#include "spritesheet.hpp"

namespace sprite {

const char GAMETILES_FILE[] = "assets/game-tiles.png";
const char BUTTON_FILE[] = "assets/buttons.png";
const char DOODLE_FILE[] = "assets/doodle.png";

Tile::Tile() : x(0),
                       y(0),
                       w(0),
                       h(0) {}
Tile::Tile(int x_, int y_, int w_, int h_)
    : x(x_),
      y(y_),
      w(w_),
      h(h_) {}
Tile::Tile(const Rectangle& xywh)
    : x(xywh.x),
      y(xywh.y),
      w(xywh.w),
      h(xywh.h) {}

const Tile doodle[6] {
    {0, 0, 58, 57},
    {58, 0, 58, 57},
    {2 * 58, 0, 58, 57},
    {3 * 58, 0, 58, 57},
    {0, 60, 58, 78},
    {58, 60, 58, 78}
};

const Tile button[5] {
    {0, 0, 140, 50},
    {140, 0, 140, 50},
    {2 * 140, 0, 140, 50},
    {3 * 140, 0, 140, 50},
    {4 * 140, 0, 140, 50},
};

const Tile platform[6] {
    {0, 0, 73, 21},
    {0, 22, 73, 20},

    {0, 91, 77, 19},
    {0, 114, 77, 24},
    {2, 145, 72, 35},
    {2, 186, 72, 41},
};

const Tile item[4] {
    {86, 110, 22, 15},
    {86, 131, 22, 34},
    {84, 170, 24,20},
    {84, 170, 30, 30}
};

const Tile enemy[4] {
    {86, 0, 77, 110},
    {143,98,121,122},
    {163, 0, 102, 151},
    {265, 0, 102, 151},
};

} // namespace sprite