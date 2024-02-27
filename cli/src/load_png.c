#include "load_png.h"

#include <stdio.h>
#include <setjmp.h>
#include <errno.h>
#include <png.h>

int load_image( char * filename, CHR * out ) {
    // open file
    FILE * file = fopen( filename, "rb" );
    if ( !file )
        // return the error from fopen
        return errno;

    // check that file is a png
    png_byte header[8];
    fread( header, 1, 8, file );
    int is_png = !png_sig_cmp( header, 0, 8 );
    if ( !is_png )
        // EILSEQ is illegal byte sequence, don't know if it fits here but couldnt find alternative
        return EILSEQ;

    // create png object
    png_struct * png = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL );
    if ( !png )
        // ELIBBAD is that shared library is corrupted
        // probably not right but whatever
        return ELIBBAD;

    // create info object
    png_info * info = png_create_info_struct( png );
    if ( !info ) {
        png_destroy_read_struct( &png, NULL, NULL );
        // probably not right but whatever
        return ELIBBAD;
    }

    // create end-info object(?)
    png_info * end_info = png_create_info_struct( png );
    if ( !end_info ) {
        png_destroy_read_struct( &png, &end_info, NULL );
        // probably not right but whatever
        return ELIBBAD;
    }

    // setup error-handling
    if ( setjmp(png_jmpbuf(png)) ) {
        png_destroy_read_struct( &png, &info, &end_info );
        fclose( file );
        // should be changed later
        // or the other returns should be changed
        return 1;
    }

    // setup reading
    png_set_sig_bytes( png, 8 );
    png_init_io( png, file );
    // read
    png_read_info( png, info );
    png_read_png( png, info, PNG_TRANSFORM_IDENTITY, NULL );
    png_read_end( png, end_info );
    
    // set bits per pixel to 8
    if ( png_get_bit_depth( png, info) == 16)
        png_set_strip_16( png );
    if ( png_get_bit_depth(png, info) < 8 )
        png_set_packing( png );

    // pallete

    png_destroy_read_struct( &png, &info, &end_info );
    fclose( file );

    return 0;
}