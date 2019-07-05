#include <gb/gb.h>
#include <gb/drawing.h>

#include <rand.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dino_new.c" // dino sprites

typedef enum { false, true } bool; // booleans in C :D
typedef enum { up, down, left, right } direction; // direction for char movement

#define SPX 30 // starting position X (player)
#define SPY 111 // starting position Y (player)
#define PFC 2 // player frame count (1-indexed) 

#define GRND 111 // ground Y value

#define SCLX 0 // screen left X
#define SCRX 159 // screen right X
#define SCTY 0 // screen top y
#define SCBY 143 // screen bottom y

#define MAXANIMTIME 25 // max age of the current frame
#define MAXSCORETIME 20 // max age of the previous score

#define MAXJUMPTIME 100 // max time the dino can be in the air before falling
#define MAXJUMPHEIGHT 3 // max height the dino can be before falling back to the ground (unused)

#define TX 0 // title X
#define TY 3 // title Y
#define STX 0 // start message X
#define STY 3 // start message Y

int px, py; // player x & player y
int score; // score pointertime between score increment

int score_time; // time between score incrementing

int anim_time; // animation time between frames
int cur_frame; // index of the current frame

bool jumping; // true/false of whether the player is mid-jump
bool paused; // true/false of whether the game is paused

char sbuffer[64]; // score char buffer (256 (64 * 4) bytes)

void init_sprites() {
    SPRITES_8x8;
    // dino tile data; 4 tiles; starting from 0
    set_sprite_data(0, 11, dino);
    // set the sprites and tiles
    set_sprite_tile(0, 0); // dino tl
    set_sprite_tile(1, 1); // dino tr
    set_sprite_tile(2, 2); // dino bl
    set_sprite_tile(3, 3); // dino br
    
    // TODO: finish setting sprites (cactus sprites mostly)
}

void init_player() {
    px = SPX;
    py = SPY;
    move_sprite(0, px, py);
    move_sprite(1, px + 8, py);
    move_sprite(2, px, py + 8);
    move_sprite(3, px + 8, py + 8);
}

void player_move(int x, int y) {
    px -= x;
    py -= y;
    move_sprite(0, px, py);
    move_sprite(1, px + 8, py);
    move_sprite(2, px, py + 8);
    move_sprite(3, px +  8, py + 8);
}

void init_bg() {
    // color(LTGREY, WHITE, SOLID); // line color
    line(SCLX, GRND, SCRX, GRND); // ground
    // color(BLACK, WHITE, SOLID); // normal color
}

void animate_player() {
    if (cur_frame == 0) {
        cur_frame = 1; // set the current frame to the first frame
        // set_sprite_tile(2, 4);
        set_sprite_tile(3, 5);
    }

    else if (cur_frame == 1 && anim_time == MAXANIMTIME) {
        anim_time = 0;
        cur_frame = 2;
        set_sprite_tile(2, 4);
        set_sprite_tile(3, 3);
    }

    else if (cur_frame == 2 && anim_time == MAXANIMTIME) {
        anim_time = 0;
        cur_frame = 1;
        set_sprite_tile(3, 5);
        set_sprite_tile(2, 6);
    }

    anim_time++;
}

void inc_score() {
    if (score != 9999 && score_time == MAXSCORETIME) {
        score_time = 0;
        score += 1;
    }
    score_time++;
}

void draw_score() {
    // itoa(score, sbuffer, DECd);
    gotogxy(7, 1); // set to score position
    itoa(score, sbuffer); // convert score int to string
    gprintf(sbuffer); // display the data in the buffer
    inc_score(); // debug
}

void init_score() {
    gotogxy(0, 1);
    gprintf("SCORE: ");
    draw_score(); // just to get the initial number up with no extra effort here
}

void draw_title() {
    gotogxy(TX, TY);
    gprintf("DINO");
    gotogxy(STX, STY);
    gprintf("PRESS \'START\' TO BEGIN");
}

void clear_title() {
    // char clear_buffer[22];
    // int i;
    
    // for (i = 0; i < sizeof(clear_buffer); i++) {
    //     clear_buffer[i] = " ";
    // }

    // char clear_buffer = "                      "; // 22 chars long
    
    gotogxy(TX, TY);
    // gprintf(clear_buffer);
    gprintf("                      ");
    gotogxy(STX, STY);
    // gprintf(clear_buffer);
    gprintf("                      ");
}

void player() {
    switch(joypad()) { // switch function for gamepad possibilities

    }
}

int main() {
    disable_interrupts();
    DISPLAY_OFF;
    
    init_bg();
    init_sprites();
    init_player();
    init_score();
    // draw_title();
    
    enable_interrupts();
    SHOW_SPRITES;
    DISPLAY_ON;

    waitpad(J_START);

    while(1) {
        draw_score();
        animate_player();
        // player_move(0, 1); // debug
    }
}
