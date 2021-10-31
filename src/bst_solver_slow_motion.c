#include "bst_solver.h"
#include "gui.h"
#include "sokoban.h"
#include <string.h>


void print_level(int width, int height, char* elements, int nb_mvmt) {


    char *buffer = (char*)calloc(width, sizeof(char));

    for(int i = 0; i < width; i++){ /*initialization*/
        *(buffer + i) = '#';
    }

    GUI_Show(1, 0, ' ');    /* There was a pb, the *(buffer + 1) does not print because of the '\0 added*/
    *(buffer + 2) = ' ';    /* it is more esthetical ^^ */


    snprintf (buffer, sizeof(char) * width, "%d",nb_mvmt); // print int 'nb_mvmt' into the char[] buffer

    for (int col = 0; col < width; col++){
        GUI_Show(col, 0, *(buffer + col));
    }

    free(buffer);

    for (int line = 0; line < height; line++){
        for (int col = 0; col < width; col++){
            GUI_Show(col, line + 1, *(elements + line*width + col));
        }
    }
}



void replay_slow(map* p_map, int lenght, char* movements){
    
    int width = (*p_map).width; /*define the dimension*/
    int height = (*p_map).height;


    GUI_Init("Sokoban Replay", width, height + 1);
    


    map* p_curr_map = p_map;/*the name of the map that will change*/
    char curr_movement;
 


    char* curr_elements = (*p_curr_map).elements;
    int nb_mvmt = (*p_curr_map).nb_mvmt;



    print_level(width, height, curr_elements, nb_mvmt);
    GUI_click_button(width, height);
    WaitClick();


    
    for (int i = 0; i < lenght-1; i++){
        curr_movement = *(movements + i);

        map* map_trash = p_curr_map;
        p_curr_map = move(p_curr_map, curr_movement);

        if (p_curr_map != map_trash){
            deallocate_map(map_trash);
        }

        curr_elements = (*p_curr_map).elements;
        nb_mvmt = (*p_curr_map).nb_mvmt;

        print_level(width, height, curr_elements, nb_mvmt);
        Pause(100);

    }

    curr_movement = *(movements + lenght - 1);
    map* map_trash = p_curr_map;
    p_curr_map = move(p_curr_map, curr_movement);

    if (p_curr_map != map_trash){
        deallocate_map(map_trash);
    }

    curr_elements = (*p_curr_map).elements;
    nb_mvmt = (*p_curr_map).nb_mvmt;

    print_level(width, height, curr_elements, nb_mvmt);
    Pause(3000);

    GUI_Close(EXIT_SUCCESS);
}

int main(int argc, char *argv[]){
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

    map* p_loaded_map = load(p_file); /*loading*/
    map* p_copy_map = copy_map(*p_loaded_map); /*copy, because after the solver the initial map is free*/

    
    //bst-solve the map
    stats* p_stats = bst_solver(p_loaded_map);



    //replay the fonction with a beautiful SDL interface if it is possible!!!
    if(p_stats->winning_map){
    	char* movements = p_stats->plan;

    	int lenght = *(p_stats->p_lenght);
    	replay_slow(p_copy_map, lenght, movements);
	}else{
        printf("There is no way to win this map!\n");
    }


    // free the memory
    deallocate_stats(p_stats);
    deallocate_map(p_copy_map);

    //and close the file
    fclose(p_file);

    return 0;
}