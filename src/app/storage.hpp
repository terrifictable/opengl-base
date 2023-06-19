#pragma once

#ifndef STORE_H
#define STORE_H

#define nl  234

struct t_data {
    char str[256];
    float anim_strength;
    float text_x, text_y;
    int display_w, display_h;
    bool centered = true;
};

extern t_data g_data;

#endif

