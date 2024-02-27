#include <stdlib.h>
#include <errno.h>
#include <argp.h>
#include "load_png.h"

// thingies
const char * argp_program_version = "spansos character system 0.0.1";
const char * argp_program_bug_address = "NULL";
static char doc[] = "spansos character system - cli for nes chr-rom tools\v(some more detailed information)";
static char args_doc[] = "IN_FILES";
static struct argp_option options[] = {
    {"convert", 'c', 0, 0, "Convert png to chr (default)" },
    {"output", 'o', "FILE", 0, "Output to FILE" },
    { 0 }
};

struct files {
    char * file;
    struct files * next;
};

// struct containing parsed info
struct arguments {
    char * out_file;
    struct files * in_files;
    int mode;
};

// function to parse an opt
error_t parse_opt( int key, char *arg, struct argp_state *state ) {
    struct arguments *arguments = state->input;

    switch ( key ) {
    // set mode
    case 'c':
        arguments->mode = key;
        break;
    // set output file
    case 'o':
        arguments->out_file = arg;
        break;
    // add file to input
    case ARGP_KEY_ARG: {
        struct files *new_file = calloc( sizeof (struct files), 1 );
        new_file->file = arg;
        new_file->next = arguments->in_files;
        arguments->in_files = new_file;
        break;
    }
    // check arguments validity
    case ARGP_KEY_END: {
        switch ( arguments->mode ) {
        case 'c':
            if ( !arguments->in_files )
                argp_usage( state );
            break;
        }
        break;
    }
    }
    return 0;
}

// parser
static struct argp argp = { options, parse_opt, args_doc, doc };

int main( int argc, char ** argv ) {
    struct arguments arguments = {
        .out_file = ".",
        .in_files = NULL,
        .mode = 'c'
    };

    argp_parse( &argp, argc, argv, 0, 0, &arguments );

    switch ( arguments.mode ) {
        case 'c': {
            CHR chr;
            if ( load_image( arguments.in_files->file, &chr ) )
                return -1;
            if ( save_chr( arguments.out_file, &chr ) )
                return -1;
        }
    }
    return 0;
}