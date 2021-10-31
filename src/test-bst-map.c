#include "bst_map.h"

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


int main(void){

	bst_map *p_tree = (bst_map*)calloc(1, sizeof(bst_map));
	nil(p_tree);

	for(int i = 0; i < 36; i++){

        FILE *p_file = NULL;
        p_file = fopen(init_maps_filename[i], "r");
        if (p_file == NULL) {
            fprintf(stderr, "Cannot read file %s!\n", init_maps_filename[i]);
            exit(EXIT_FAILURE);
        }
        map* value = load(p_file); /*loading the map*/
		fclose(p_file);

		insert(p_tree, value);

		int s = size(*p_tree);
		int h = height(*p_tree);

		printf("size: %d\nheight: %d\n", s, h);
	}

	FILE *p_file = NULL;
	p_file = fopen(init_maps_filename[3], "r");
	if (p_file == NULL) {
	    fprintf(stderr, "Cannot read file %s!\n", init_maps_filename[3]);
	    exit(EXIT_FAILURE);
	}
	map* value = load(p_file); /*loading the map*/
	fclose(p_file);


	if(is_in_bst(*p_tree, value)){
		printf("init_maps_filename[3] is in the tree\n");
	}else{
		printf("init_maps_filename[3] isn't in the tree\n");
	}

	delete(p_tree, value);

	if(is_in_bst(*p_tree, value)){
		printf("init_maps_filename[3] is in the tree\n");
	}else{
		printf("init_maps_filename[3] isn't in the tree\n");
	}

	deallocate_bst(p_tree);

	return 0;
}