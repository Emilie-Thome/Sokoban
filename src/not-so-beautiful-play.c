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
    

    map* p_loaded_map = load(p_file); /*loading*/
    map* p_map_result = p_loaded_map; /*this map will change during the game*/

    //this is for the resart
    map* p_map_restart = copy_map(*p_loaded_map);


    char answer_player = 'a'; /*"a" because I don't want it to be a "q" at the begining!*/
    bool WIN = SokoWin(*p_map_result); /*is it a won map?*/

    while ((!WIN)&&(answer_player != 'q')){ /*while the game is on*/
        // print the map before the movement
        print_map(*p_map_result);

        //ask the movement or the quitting
        printf("Movement? ('N', 'S', 'E' or 'W')\nIf you want to quit, it is 'q' ^^\nAnd if you are blocked, it is ok, you can restart with 'r'\n");
        scanf(" %c", &answer_player);

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
                deallocate_map(map_trash);
            }
        }

        WIN = SokoWin(*p_map_result); /*is the new map a won map?*/   
    }

    if(answer_player != 'q'){ /*is the game has ended not because of a 'q' command*/

        print_map(*p_map_result);
        deallocate_map(p_map_result);
        deallocate_map(p_map_restart);
        printf("\nYOU WIN\n");

        fclose(p_file);

        return 0;
    }else{ /*else, the game end*/
        deallocate_map(p_map_restart);
        deallocate_map(p_map_result);

        fclose(p_file);
        
        return 0;
    }
}