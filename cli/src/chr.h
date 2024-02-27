#pragma once

#include <stdint.h>


typedef struct tile_t {
    uint8_t bytes[16];
} Tile;


typedef struct tile_section_t {
    Tile tiles[256];
} TileSection;


typedef struct chr_t {
    TileSection left;
    TileSection right;
} CHR;


int set_pixel( Tile * tile, int x, int y, int color_index );
int save_chr( char * file_name, CHR * chr ) { return 0; }