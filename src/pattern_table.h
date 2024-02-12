#pragma once

#include <include.h>

typedef struct tile_t {
    u64 planes[2];
} Tile;

typedef struct tile_section_t {
    Tile tiles[256];
} TileSection;

typedef struct pattern_table_t {
    TileSection left;
    TileSection right;
} PatternTable;

void set_pixel( Tile * tile, u8 x, u8 y, u8 color_index );