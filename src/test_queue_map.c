#include "queue_map.h"

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


    queue_map* p_queue = (queue_map*)calloc(1, sizeof(queue_map));
    create_empty_queue(*p_queue);


    enqueue('N', p_queue, p_map1);
    enqueue('N', p_queue, p_map2);
    enqueue('N', p_queue, p_map3);

    cell_queue_map* p_cell = dequeue(p_queue);
    map* p_map = (*p_cell).value;
    print_map(*p_map);
    deallocate_map(p_map);
    free(p_cell);
      

    print_queue(*p_queue);

    deallocate_queue(p_queue);
    
    fclose(p_file1);
    fclose(p_file2);
    fclose(p_file3);
    
    return 0;
}