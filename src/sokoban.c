#include "sokoban.h"




void print_map(map my_map){

	int width = my_map.width;
	int height = my_map.height;
	char* elements = my_map.elements;

	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			printf("%c",*(elements + i*width + j));
		}
		printf("\n");
	}
}




void deallocate_map(map* p_map){
	free((*p_map).elements);
	free(p_map);
}




char* copy_elem(map my_map){
	int width = my_map.width;
	int height = my_map.height;
	char* elements = my_map.elements;

	char* copy_elements = calloc(width*height, sizeof(char)); 

	for(int i = 0; i < width*height; i++){
		*(copy_elements + i) = *(elements + i);
	}

	return copy_elements;
}

map* copy_map(map my_map){
	map* p_new_map = (map*)calloc(1, sizeof(map));
    char * elements = copy_elem(my_map);
    (*p_new_map).width = my_map.width;
    (*p_new_map).height = my_map.height; 
    (*p_new_map).x_position = my_map.x_position;
    (*p_new_map).y_position = my_map.y_position;
    (*p_new_map).elements = elements;
    (*p_new_map).nb_mvmt = my_map.nb_mvmt;

    return p_new_map;
}





map* ChangeMap(map* p_map, char movmt){
	int nb_mvmt = (*p_map).nb_mvmt;
	int width = (*p_map).width;
	int height = (*p_map).height;
	int x = (*p_map).x_position;
	int y = (*p_map).y_position;
	char* elements = copy_elem(*p_map);

	char act_pos = *(elements + x + y*width); /*know if there is a storage destination (SD) under the player*/

	map* p_new_map = (map*)calloc(1, sizeof(map));/*new allocation*/

	(*p_new_map).width = width;
	(*p_new_map).height = height;
	(*p_new_map).nb_mvmt = nb_mvmt + 1;


	char in_north_pos = *(elements + x + (y - 1)*width); /*no declaration in a switch!*/
	char in_east_pos = *(elements + x + 1 + y*width);
	char in_south_pos = *(elements + x + (y + 1)*width);
	char in_west_pos = *(elements + x - 1 + y*width);

	int correct_movmnt = 0;

	switch(movmt){
		case 'N':

			(*p_new_map).x_position = x;
			(*p_new_map).y_position = y - 1;

			if((in_north_pos == '$')||(in_north_pos == '*')){ /*know if there is a box where the player wants to go*/
				
				char norther = *(elements + x + (y - 2)*width);
				if(norther == '.'){ /*know if there is a SD where the box go*/
					*(elements + x + (y - 2)*width) = '*';
				}else{
					*(elements + x + (y - 2)*width) = '$';
				}
			}

			if((in_north_pos == '.')||(in_north_pos == '*')){ /*know if there is a SD where the player wants to go*/
				*(elements + x + (y - 1)*width) = '+';
			}else{
				*(elements + x + (y - 1)*width) = '@';
			}

			correct_movmnt = 1;

			break;

		case 'E':

			(*p_new_map).x_position = x + 1;
			(*p_new_map).y_position = y;

			if((in_east_pos == '$')||(in_east_pos == '*')){ /*know if there is a box where the player wants to go*/
				
				char easter = *(elements + x + 2 + y*width);
				if(easter == '.'){ /*know if there is a SD where the box go*/
					*(elements + x + 2 + y*width) = '*';
				}else{
					*(elements + x + 2 + y*width) = '$';
				}
			}			

			if((in_east_pos == '.')||(in_east_pos == '*')){ /*know if there is a SD where the player wants to go*/
				*(elements + x + 1 + y*width) = '+';
			}else{
				*(elements + x + 1 + y*width) = '@';
			}

			correct_movmnt = 1;

			break;

		case 'S':

			(*p_new_map).x_position = x;
			(*p_new_map).y_position = y + 1;

			if((in_south_pos == '$')||(in_south_pos == '*')){ /*know if there is a box where the player wants to go*/
				
				char souther = *(elements + x + (y + 2)*width);
				if(souther == '.'){ /*know if there is a SD where the box go*/
					*(elements + x + (y + 2)*width) = '*';
				}else{
					*(elements + x + (y + 2)*width) = '$';
				}
			}			

			if((in_south_pos == '.')||(in_south_pos == '*')){ /*know if there is a SD where the player wants to go*/
				*(elements + x + (y + 1)*width) = '+';
			}else{
				*(elements + x + (y + 1)*width) = '@';
			}

			correct_movmnt = 1;

			break;

		case 'W': 

			(*p_new_map).x_position = x - 1;
			(*p_new_map).y_position =  y;

			if((in_west_pos == '$')||(in_west_pos == '*')){ /*know if there is a box where the player wants to go*/
				
				char wester = *(elements + x - 2 + y*width);
				if(wester == '.'){ /*know if there is a SD where the box go*/
					*(elements + x - 2 + y*width) = '*';
				}else{
					*(elements + x - 2 + y*width) = '$';
				}
			}

			if((in_west_pos == '.')||(in_west_pos == '*')){ /*know if there is a SD where the player wants to go*/
				*(elements + x - 1 + y*width) = '+';
			}else{
				*(elements + x - 1 + y*width) = '@';
			}

			correct_movmnt = 1;

			break;

		default:
			printf("THE DIRECTION IS NOT CORRECT\n");

	}

	if(correct_movmnt == 1){
		if(act_pos == '+'){ /*change the ancient position, only if the movement demanded is correct!*/
			*(elements + x + y*width) = '.';
		}else{
			*(elements + x + y*width) = ' ';
		}
	}

	(*p_new_map).elements = elements;

	return p_new_map;
}




bool MovementPossible(map* p_map, char movmt){


	int width = (*p_map).width;
	int x = (*p_map).x_position;
	int y = (*p_map).y_position;
	char* elements = (*p_map).elements;


	char in_north_pos = *(elements + x + (y - 1)*width); /*no declaration in a switch!*/
	char in_east_pos = *(elements + x + 1 + y*width);
	char in_south_pos = *(elements + x + (y + 1)*width);
	char in_west_pos = *(elements + x - 1 + y*width);



	switch(movmt){
		case 'N':
			
			if(in_north_pos == '#'){ /*know if there is a wall where the player wants to go*/
				return false;
			}else{
				if((in_north_pos == '$')||(in_north_pos == '*')){ 
					char norther = *(elements + x + (y - 2)*width);
					bool two_boxes = (norther == '$')||(norther == '*')||(norther == '#'); /*know if there is a boxe or a wall where the boxe will go*/
					return !two_boxes;
				}else{
					return true;
				}
			}

			break;

		case 'E':
			
			if(in_east_pos == '#'){ /*know if there is a wall where the player wants to go*/
				return false;
			}else{
				if((in_east_pos == '$')||(in_east_pos == '*')){ 
					char easter = *(elements + x + 2 + y*width);
					bool two_boxes = (easter == '$')||(easter == '*')||(easter == '#'); /*know if there is a boxe or a wall where the boxe will go*/
					return !two_boxes;
				}else{
					return true;
				}
			}

			break;

		case 'S':
			
			if(in_south_pos == '#'){ /*know if there is a wall where the player wants to go*/
				return false;
			}else{
				if((in_south_pos == '$')||(in_south_pos == '*')){ 
					char souther = *(elements + x + (y + 2)*width);
					bool two_boxes = (souther == '$')||(souther == '*')||(souther == '#');/*know if there is a boxe or a wall where the boxe will go*/
					return !two_boxes;
				}else{
					return true;
				}
			}

			break;

		case 'W':

			if(in_west_pos == '#'){ /*know if there is a wall where the player wants to go*/
				return false;
			}else{
				if((in_west_pos == '$')||(in_west_pos == '*')){ 
					char wester = *(elements + x - 2 + y*width);
					bool two_boxes = (wester == '$')||(wester == '*')||(wester == '#');/*know if there is a boxe or a wall where the boxe will go*/
					return !two_boxes;
				}else{
					return true;
				}
			}

			break;

		default:
			printf("THE DIRECTION IS NOT CORRECT\n");

	}

	return true; /*to avoid warnings, it is cheating...*/
}




map* move(map* p_map, char movmt){
	if(MovementPossible(p_map, movmt)){
		return ChangeMap(p_map, movmt);
	}else{
		return p_map;
	}
}




map* replay(map* p_map, int lenght, char* movements){
	map* p_curr_map = p_map;
	char curr_movement;

	for (int i = 0; i < lenght-1; i++){
		curr_movement = *(movements + i);
		map* map_trash = p_curr_map;
		p_curr_map = move(p_curr_map, curr_movement);

        if (p_curr_map != map_trash){
        	deallocate_map(map_trash);
        }
	}
	curr_movement = *(movements + lenght - 1);
	map* map_trash = p_curr_map;
	p_curr_map = move(p_curr_map, curr_movement);

	if (p_curr_map != map_trash){
      	deallocate_map(map_trash);
    }

    return p_curr_map;
}


bool SokoWin(map my_map){
	char* elements = my_map.elements;
	int width = my_map.width;
	int height = my_map.height;


	for(int i = 0; i < width*height; i++){
		if(*(elements + i) == '$'){
			return false;
		}
	}

	return true;
}