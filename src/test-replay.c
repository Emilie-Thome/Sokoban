#include "sokoban.h"

#include<assert.h>






static char* init_maps_filename[] = {
    "data/soko_dumb.in",
    "data/soko_dumb.in",
    "data/soko_dumb.in",
    "data/soko_dumb.in",
    "data/soko_dumb.in",
    "data/soko1.in",
    "data/soko1.in",
    "data/soko1.in"
};

static char* moved_maps_filename[] = {
    "data/soko_dumb_1.in",
    "data/soko_dumb_2.in",
    "data/soko_dumb_win.in",
    "data/soko_dumb_3.in",
    "data/soko_dumb_win.in",
    "data/soko1_1.in",
    "data/soko1_2.in",
    "data/soko1_win.in"
};

static int lenght_tab[] = {
    3,
    5,
    7,
    7,
    9,
    100,
    150,
    184
};

static char* plan[] = {
    "SSSEENN",
    "SSSEENN",
    "SSSEENN",
    "ESEESSWNN",
    "ESEESSWNN",
    "NNWWSWWNEESWSWWWNNEESSESSWWNSEENNNENENESSSWSWENEESWWNENNWWSWWNWWSSESSEENNWNEWNEEENESSSWSWENENNWWWWWWSSESSEENNWESEENEESWWWENENNWWWWSSENWNEEENESSNWWWWWWSSESSEENEEEENWSWWWNNWNEEENESSSESWW",
    "NNWWSWWNEESWSWWWNNEESSESSWWNSEENNNENENESSSWSWENEESWWNENNWWSWWNWWSSESSEENNWNEWNEEENESSSWSWENENNWWWWWWSSESSEENNWESEENEESWWWENENNWWWWSSENWNEEENESSNWWWWWWSSESSEENEEEENWSWWWNNWNEEENESSSESWW",
    "NNWWSWWNEESWSWWWNNEESSESSWWNSEENNNENENESSSWSWENEESWWNENNWWSWWNWWSSESSEENNWNEWNEEENESSSWSWENENNWWWWWWSSESSEENNWESEENEESWWWENENNWWWWSSENWNEEENESSNWWWWWWSSESSEENEEEENWSWWWNNWNEEENESSSESWW"
};





int main (void){
    
    
    for(int i = 0; i < 8; i++){
        // testing if a filename has been given
        FILE *p_file = NULL;
        p_file = fopen(init_maps_filename[i], "r");
        if (p_file == NULL) {
            fprintf(stderr, "Cannot read file %s!\n", init_maps_filename[i]);
            exit(EXIT_FAILURE);
        }

        int lenght = 0;
        lenght = lenght_tab[i];
        if (lenght == 0) {
            fprintf(stderr, "Cannot read lenght %d!\n", lenght_tab[i]);
            exit(EXIT_FAILURE);
        }

        char* movements = plan[i];

        FILE *p_file_compare = NULL; /*the file to compare*/
        p_file_compare = fopen(moved_maps_filename[i], "r");
        if (p_file_compare == NULL) {
            fprintf(stderr, "Cannot read file %s!\n", moved_maps_filename[i]);
            exit(EXIT_FAILURE);
        }

        map* p_loaded_map = load(p_file); /*loading*/
        map* p_map_compare = load(p_file_compare); /*loading*/


        map* p_map_result = replay(p_loaded_map, lenght, movements); /*replay fonction*/


        //comparaison of the two maps


        assert((*p_map_compare).width == (*p_map_result).width);
        assert((*p_map_compare).height == (*p_map_result).height);
        assert((*p_map_compare).x_position == (*p_map_result).x_position);
        assert((*p_map_compare).y_position == (*p_map_result).y_position);
        assert(*((*p_map_compare).elements) == *((*p_map_result).elements));

        // free the memory
        deallocate_map(p_map_compare);

        deallocate_map(p_map_result);

        //and close the file
        fclose(p_file);
        fclose(p_file_compare);
    }

    printf("TEST RESULT: OK\n");

    return 0;
}