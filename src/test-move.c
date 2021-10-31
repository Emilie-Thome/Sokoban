#include "sokoban.h"

#include<assert.h>



static char* init_maps_filename[] = {
    "data/soko_move_1.in",
    "data/soko_move_1.in",
    "data/soko_move_1.in",
    "data/soko_move_1.in",
    "data/soko_move_2.in",
    "data/soko_move_2.in",
    "data/soko_move_2.in",
    "data/soko_move_2.in",
    "data/soko_move_3_1.in",
    "data/soko_move_3_2.in",
    "data/soko_move_3_3.in",
    "data/soko_move_3_4.in",
    "data/soko_move_4_1.in",
    "data/soko_move_4_2.in",
    "data/soko_move_4_3.in",
    "data/soko_move_4_4.in",
    "data/soko_move_5_1.in",
    "data/soko_move_5_2.in",
    "data/soko_move_5_3.in",
    "data/soko_move_5_4.in",
    "data/soko_move_6_1.in",
    "data/soko_move_6_2.in",
    "data/soko_move_6_3.in",
    "data/soko_move_6_4.in",
    "data/soko_move_W_E.in",
    "data/soko_move_W_W.in",
    "data/soko_move_W_N.in",
    "data/soko_move_W_S.in",
    "data/soko_move_B_W_E.in",
    "data/soko_move_B_W_W.in",
    "data/soko_move_B_W_N.in",
    "data/soko_move_B_W_S.in",
    "data/soko_move_B_B_E.in",
    "data/soko_move_B_B_W.in",
    "data/soko_move_B_B_N.in",
    "data/soko_move_B_B_S.in"
};






static char* moved_maps_filename[] = {
    "data/soko_move_1_N.in",
    "data/soko_move_1_S.in",
    "data/soko_move_1_E.in",
    "data/soko_move_1_W.in",
    "data/soko_move_2_N.in",
    "data/soko_move_2_S.in",
    "data/soko_move_2_E.in",
    "data/soko_move_2_W.in",
    "data/soko_move_3_1_E.in",
    "data/soko_move_3_2_E.in",
    "data/soko_move_3_3_E.in",
    "data/soko_move_3_4_E.in",
    "data/soko_move_4_1_W.in",
    "data/soko_move_4_2_W.in",
    "data/soko_move_4_3_W.in",
    "data/soko_move_4_4_W.in",
    "data/soko_move_5_1_N.in",
    "data/soko_move_5_2_N.in",
    "data/soko_move_5_3_N.in",
    "data/soko_move_5_4_N.in",
    "data/soko_move_6_1_S.in",
    "data/soko_move_6_2_S.in",
    "data/soko_move_6_3_S.in",
    "data/soko_move_6_4_S.in",
    "data/soko_move_W_E.in",
    "data/soko_move_W_W.in",
    "data/soko_move_W_N.in",
    "data/soko_move_W_S.in",
    "data/soko_move_B_W_E.in",
    "data/soko_move_B_W_W.in",
    "data/soko_move_B_W_N.in",
    "data/soko_move_B_W_S.in",
    "data/soko_move_B_B_E.in",
    "data/soko_move_B_B_W.in",
    "data/soko_move_B_B_N.in",
    "data/soko_move_B_B_S.in"
};




static char movements[] = {
    'N',
    'S',
    'E',
    'W',
    'N',
    'S',
    'E',
    'W',
    'E',
    'E',
    'E',
    'E',
    'W',
    'W',
    'W',
    'W',
    'N',
    'N',
    'N',
    'N',
    'S',
    'S',
    'S',
    'S',
    'E',
    'W',
    'N',
    'S',
    'E',
    'W',
    'N',
    'S',
    'E',
    'W',
    'N',
    'S'

};



int main (void){

    for(int i = 0; i < 36; i++){

        char movement = movements[i];

        FILE *p_file = NULL; /*the file to compare*/
        p_file = fopen(init_maps_filename[i], "r");
        if (p_file == NULL) {
            fprintf(stderr, "Cannot read file %s!\n", init_maps_filename[i]);
            exit(EXIT_FAILURE);
        }

        FILE *p_file_compare = NULL; /*the file to compare*/
        p_file_compare = fopen(moved_maps_filename[i], "r");
        if (p_file_compare == NULL) {
            fprintf(stderr, "Cannot read file %s!\n", moved_maps_filename[i]);
            exit(EXIT_FAILURE);
        }


        map* p_loaded_map = load(p_file); /*loading*/
        map* p_map_compare = load(p_file_compare); /*loading*/

        map* p_new_map = NULL;

        p_new_map = move(p_loaded_map, movement);
        
        if (p_new_map == NULL){
            printf("ERROR, THE MOVEMENT FAILED\n");
            exit(EXIT_FAILURE);
        }
     
        assert((*p_map_compare).width == (*p_new_map).width);
        assert((*p_map_compare).height == (*p_new_map).height);
        assert((*p_map_compare).x_position == (*p_new_map).x_position);
        assert((*p_map_compare).y_position == (*p_new_map).y_position);
        assert(*((*p_map_compare).elements) == *((*p_new_map).elements));



        // free the memory
        if (p_new_map != p_loaded_map){
            deallocate_map(p_new_map);
        }

        deallocate_map(p_loaded_map);
        deallocate_map(p_map_compare);

        //and close the file
        fclose(p_file);
        fclose(p_file_compare);
    }


    printf("TEST RESULT: OK\n");


    return 0;
}