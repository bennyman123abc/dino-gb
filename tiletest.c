#include <gb/gb.h>

#include "dino_new.h"

#define BX 0 // base x
#define BY 0 // base y
#define IX 8 // x increment
#define IY 8 // y increment
#define TC 11 // tile count
#define MX 20 // max tiles in X
#define MY 18 // max tiles in Y

void draw_sprites() {
    int i;
    int cx = BX; // current x
    int cy = BY; // current y
    int cr = 0; // current tiles in row (max is MX)

    for (i = 0; i < TC; i++) {
        if (cr == MX) { // max tiles hit
            cx = BX; // set x back to base
            cy += IY; // increment y
        }
        move_sprite(i, cx, cy);
        cx += IX; // increment x
        cr++;
    }
}

void init_sprites() {
    int i;

    set_sprite_data(0, TC, dino);

    for (i = 0; i < TC; i++) {
        set_sprite_tile(i, i);
    }

    draw_sprites();
}

int main() {
    disable_interrupts();
    DISPLAY_OFF;

    init_sprites();

    enable_interrupts();
    SHOW_SPRITES;
    DISPLAY_ON;
}
