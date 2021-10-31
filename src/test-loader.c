#include "sokoban.h"

int main (int argc, char *argv[]){
	    // testing if a filename has been given
    if (argc != 2) {
        fprintf(stderr, "You must provide a file name!\n");
        exit(EXIT_FAILURE);
    }
    // open file. The filename is the first argument on the command
    // line, hence stored in argv[1]
    FILE *p_file = NULL;

    p_file = fopen(argv[1], "r");

    if (p_file == NULL) {
        fprintf(stderr, "Cannot read file %s!\n", argv[1]);
        exit(EXIT_FAILURE);
    }




    // load and print the map with the created fonctions in loader
    map* p_loaded_map = load(p_file);
    print_map(*p_loaded_map);
    deallocate_map(p_loaded_map);
    


    fclose(p_file);

    return 0;
}