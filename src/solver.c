#include "solver.h"



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



char* winning_plan(queue_map my_queue,int *p_lenght){
	if(!is_queue_empty(my_queue)){	
		cell_queue_map* p_curr_cell = my_queue.last; /*the cell of the winning map*/
		
		*p_lenght = (*p_curr_cell).depth;

		char* plan = calloc(*p_lenght + 1, sizeof(char)); /*the size of the plan is the depth of the final map + 1 for the '\0'*/

		
		for(int i = 0 ; i < *p_lenght ; i++){

			char dir = (*p_curr_cell).action;

			*(plan + *p_lenght - 1 - i) = dir;

			p_curr_cell = (*p_curr_cell).p_cell_mother_map;
		}

		*(plan + *p_lenght) = '\0';

		return plan;
	
	}else{
		printf("WINNING_PLAN: THE QUEUE IS EMPTY\n");
		return NULL;
	}
}


void forloop(char dir,queue_map* p_search_queue, map* p_curr_map, linked_list_map* p_explored_list, cell_queue_map *p_curr_cell){

	map* p_new_map = move(p_curr_map, dir);
	int depth = (*p_curr_cell).depth;


	if(is_in(*p_new_map, *p_explored_list)){
		if(p_new_map != p_curr_map){
			deallocate_map(p_new_map);
		}
	}else{
		cons(p_new_map, p_explored_list);
		enqueue(p_search_queue, new_cell(dir, p_new_map, p_curr_cell, depth + 1));
	}
}




stats* solver(map* p_initial_map){

	queue_map* p_search_queue = (queue_map*)calloc(1, sizeof(queue_map));
	create_empty_queue(*p_search_queue);

	queue_map* p_dequeued_queue = (queue_map*)calloc(1, sizeof(queue_map));
	create_empty_queue(*p_dequeued_queue);
	
	linked_list_map* p_explored_list = (linked_list_map*)calloc(1, sizeof(linked_list_map));
	*p_explored_list = CreateList();

	char def_dir = '\0'; /*default direction for the begining, it will define the initial map easily*/

	enqueue(p_search_queue, new_cell(def_dir, p_initial_map, NULL, 0));

	cons(p_initial_map, p_explored_list); /*this list make it possible to know if the search is in a good direction*/

	bool win = false;




	while((!is_queue_empty(*p_search_queue))&&(!win)){
		cell_queue_map* p_curr_cell = dequeue(p_search_queue); /*free at the end of the loop, inside*/
		
		map* p_curr_map = (*p_curr_cell).value;

		enqueue(p_dequeued_queue, p_curr_cell);

		if(SokoWin(*p_curr_map)){
			win = true;
		}else{
			forloop('N', p_search_queue, p_curr_map, p_explored_list, p_curr_cell);
			forloop('S', p_search_queue, p_curr_map, p_explored_list, p_curr_cell);
			forloop('E', p_search_queue, p_curr_map, p_explored_list, p_curr_cell);
			forloop('W', p_search_queue, p_curr_map, p_explored_list, p_curr_cell);
		}
	}

	char* plan = NULL;
	int *p_lenght = (int*)calloc(1, sizeof(int));

	if(win){
		plan = winning_plan(*p_dequeued_queue, p_lenght);
	}else{
		printf("THERE IS NO POSSIBLE PLAN TO WIN\n");
	}

	stats *p_stats_initial_map = (stats*)calloc(1, sizeof(stats));

	p_stats_initial_map->winning_map = win;
	p_stats_initial_map->p_lenght = p_lenght;
	p_stats_initial_map->plan = plan; 

	deallocate_queue(p_search_queue);
	deallocate_queue(p_dequeued_queue);
	deallocate_list(p_explored_list);

	return p_stats_initial_map;
}



void deallocate_stats(stats *p_stats){
	if(p_stats->plan != NULL){
		free(p_stats->plan);
	}
	free(p_stats->p_lenght);
	free(p_stats);
}

