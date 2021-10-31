#include <stdbool.h>
#include <stdlib.h>

#include "gui.h"
#include "sokoban.h"

void print_level(int width, int height, char* elements) {
    for (int line = 0; line < height; line++){
        for (int col = 0; col < width; col++){
            GUI_Show(col, line, *(elements + line*width + col));
        }
    }
}

int main(int argc, char *argv[]) {
	// testing if a filename has been given
    if (argc != 2) {
        fprintf(stderr, "You must provide a file name and the movement!\n");
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

    int width = (*p_loaded_map).width; /*define the dimension*/
    int height = (*p_loaded_map).height;

    GUI_Init("Sokoban", width, height);
    
    map* p_map_result = p_loaded_map; /*the name of the map that will change*/

    char* elements = (*p_map_result).elements;

	
	//this is for the resart
    map* p_map_restart = copy_map(*p_loaded_map);



    char answer_player = 'a'; /*"a" because I don't want it to be a "q" at the begining!*/
    bool WIN = SokoWin(*p_map_result); /*is it a won map?*/

    while ((!WIN)&&(answer_player != 'q')){ /*while the game is on*/
        // print the map before the movement
    	print_level(width, height, elements);

        //ask the movement or the quitting
        switch (GUI_GetKey()) {
        case SDLK_UP:
            answer_player = 'N';
            break;
        case SDLK_DOWN:
            answer_player = 'S';
            break;
        case SDLK_LEFT:
            answer_player = 'W';
            break;
        case SDLK_RIGHT:
            answer_player = 'E';
            break;
        case 'q':
            answer_player = 'q';
            break;
        case 'r':
        	answer_player = 'r';
        }

        //movement if the player want to continue
        if((answer_player != 'q')&&(answer_player != 'r')){ /*but not restart*/
            map* map_trash = p_map_result;
            p_map_result = move(p_map_result, answer_player);
            //free memory
            if (p_map_result != map_trash){
                deallocate_map(map_trash);
            }
        }else{
            if(answer_player == 'r'){ /*if the player want to restart the game...*/
                map* map_trash = p_map_result;
                p_map_result = copy_map(*p_map_restart);
                if (p_map_result != map_trash){
                    deallocate_map(map_trash);
                }
            }
        }

        elements = (*p_map_result).elements;/*change the elements to int on the map*/

        WIN = SokoWin(*p_map_result); /*is the new map a won map?*/   
    }

    if(answer_player != 'q'){ /*is the game has ended not because of a 'q' command*/
        print_level(width, height, elements);
        WaitClick();
        deallocate_map(p_map_restart);
        deallocate_map(p_map_result);
        GUI_Close(EXIT_SUCCESS);

        return 0;

    }else{ /*else, the game end*/
    	deallocate_map(p_map_restart);
        deallocate_map(p_map_result);
    	GUI_Close(EXIT_SUCCESS);
        return 0;
    }
}
