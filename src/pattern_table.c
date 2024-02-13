#include "pattern_table.h"

void set_pixel( Tile * tile, u8 x, u8 y, u8 color_index ) {
    u8 pixel_index = x + y*8;
    switch ( pixel_index ) {
    case 0x01:
        tile->planes[0] = tile->planes[0] | (1 << pixel_index);
        tile->planes[1] = tile->planes[1] & ~(1 << pixel_index);
        break;
    case 0x02:
        tile->planes[0] = tile->planes[0] & ~(1 << pixel_index);
        tile->planes[1] = tile->planes[1] | (1 << pixel_index);
        break;
    case 0x03:
        tile->planes[0] = tile->planes[0] | (1 << pixel_index);
        tile->planes[1] = tile->planes[1] | (1 << pixel_index);
        break;
    }
}