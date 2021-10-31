#include "sokoban.h"



int main (int argc, char *argv[]){
	    // testing if a filename has been given
    if (argc != 4) {
        fprintf(stderr, "You must provide a file name, a lenght of movements and the movements!\n");
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

    char* p_lenght = NULL;
    p_lenght = argv[2];
    if (p_lenght == NULL) {
        fprintf(stderr, "Cannot read lenght %s!\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    int lenght = atoi(p_lenght); /*char to int conversion*/

    char* movements = argv[3];
   
    map* p_loaded_map = load(p_file); /*loading*/

    map* p_map_result = replay(p_loaded_map, lenght, movements); /*replay fonction*/

    // print the map resulted from the movements
    print_map(*p_map_result);
    if(SokoWin(*p_map_result)){
        printf("WIN\n");
    }else{
        printf("NO WIN\n");
    }

    // free the memory
    deallocate_map(p_map_result);

    //and close the file
    fclose(p_file);

    return 0;
}