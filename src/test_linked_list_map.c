#include "linked_list_map.h"

bool same_map(map my_map1, map my_map2){
    bool rep;

    rep = (my_map1.width == my_map2.width);
    rep = rep && (my_map1.height == my_map2.height);
    rep = rep && (my_map1.x_position == my_map2.x_position);
    rep = rep && (my_map1.y_position == my_map2.y_position);

    if(!rep){
        return false; /*if even those are false, there is no point continuing*/
    }else{
        char* elem1 = my_map1.elements;
        char* elem2 = my_map2.elements;
        int width = my_map2.width;
        int height = my_map2.height;
        for(int i = 0; i < width*height; i++){
            if(*(elem1 + i) != *(elem2 + i)){
                return false;
            }
        }

        return true;
    }
}


bool is_in(map my_map, linked_list_map list){
    cell_map* p_curr_cell = list;

    while(p_curr_cell != NULL){
        if(same_map(my_map, *((*p_curr_cell).value))){
            return true;
        }else{
            p_curr_cell = (*p_curr_cell).next;
        }
    }

    return false;
}

int main(int argc, char *argv[]){

	if (argc != 4) {
        fprintf(stderr, "You must provide 3 file names!\n");
        exit(EXIT_FAILURE);
    }
    // open files.
    FILE *p_file1 = NULL;
    p_file1 = fopen(argv[1], "r");
    if (p_file1 == NULL) {
        fprintf(stderr, "Cannot read file %s!\n", argv[1]);
        exit(EXIT_FAILURE);
    }
	map* p_map1 = load(p_file1);

    FILE *p_file2 = NULL;
    p_file2 = fopen(argv[2], "r");
    if (p_file2 == NULL) {
        fprintf(stderr, "Cannot read file %s!\n", argv[1]);
        exit(EXIT_FAILURE);
    }
	map* p_map2 = load(p_file2);

    FILE *p_file3 = NULL;
    p_file3 = fopen(argv[3], "r");
    if (p_file3 == NULL) {
        fprintf(stderr, "Cannot read file %s!\n", argv[1]);
        exit(EXIT_FAILURE);
    }
	map* p_map3 = load(p_file3);



	linked_list_map* p_list = (linked_list_map*)calloc(1, sizeof(linked_list_map));
	*p_list = CreateList();


	cons(p_map1, p_list);
	cons(p_map2, p_list);
	insert_element(p_map3, 1, *p_list);

	map* p_map = get_element(2, *p_list);
	print_map(*p_map);

	int n = size(*p_list);
	printf("%d\n", n);

	print_list(*p_list);


    if(is_in(*p_map1, *p_list)){
        printf("\nmap1 is in list\n map1 is:\n");
        print_map(*p_map1);
        printf("\n");
    }

    remove_element(2, p_list);

    print_list(*p_list);


    if(is_in(*p_map1, *p_list)){
        printf("\nmap1 is in list\n map1 is:\n");
        print_map(*p_map1);
        printf("\n");
    }


	deallocate_list(p_list);

    fclose(p_file1);
    fclose(p_file2);
    fclose(p_file3);
    
	return 0;
}