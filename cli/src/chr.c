#include "chr.h"


int set_pixel( Tile * tile, int x, int y, int color_index ) {
    switch ( color_index ) {
    case 0x01:
        tile->bytes[y] |= (1 << x);
        tile->bytes[y+8] &= ~(1 << x);
        return 0;
    case 0x02:
        tile->bytes[y] &= ~(1 << x);
        tile->bytes[y+8] |= (1 << x);
        return 0;
    case 0x03:
        tile->bytes[y] |= (1 << x);
        tile->bytes[y+8] |= (1 << x);
        return 0;
    default:
        return -1;
    }
}