#include "queue_map.h"


void create_empty_queue(queue_map my_queue){
	my_queue.first = NULL;
	my_queue.last = NULL;
}




bool is_queue_empty(queue_map my_queue){
	return (my_queue.first == NULL);
}




cell_queue_map* dequeue(queue_map* p_queue){ 

	if(!is_queue_empty(*p_queue)){
		cell_queue_map* p_returned;
		if((*p_queue).first == (*p_queue).last){ /*case where there is only one cell in the queue*/

			p_returned = (*p_queue).first;

			(*p_queue).first = NULL;
			(*p_queue).last = NULL;

			return p_returned;
		}else{
			cell_queue_map* p_prev_cell = (*((*p_queue).first)).next;

			cell_queue_map* p_returned = (*p_queue).first;			

			(*p_queue).first = p_prev_cell;

			return p_returned;
		}


	}else{
		printf("ERROR QUEUE EMPTY\n");
		return NULL;
	}

}



cell_queue_map* new_cell(char dir, map* p_map, cell_queue_map* p_cell_mother_map, int depth){
	cell_queue_map* p_newcell = (cell_queue_map*)calloc(1, sizeof(cell_queue_map));

	(*p_newcell).next = NULL;
	(*p_newcell).action = dir;
	(*p_newcell).depth = depth;
	(*p_newcell).p_cell_mother_map = p_cell_mother_map;
	(*p_newcell).value = p_map;

	return p_newcell;
}


void enqueue(queue_map* p_queue,cell_queue_map* p_cell){
	if(is_queue_empty(*p_queue)){
		(*p_queue).first = p_cell;
		(*p_queue).last = p_cell;

	}else{
		(*((*p_queue).last)).next = p_cell;
		(*p_queue).last = p_cell;
	}
}





void deallocate_queue(queue_map* p_queue){
	while (! is_queue_empty(*p_queue)){
		cell_queue_map* p_trash = dequeue(p_queue);

		free(p_trash);
	}
	free(p_queue);
}




int size_queue(queue_map my_queue){
	int rep = 0;
	cell_queue_map* p_curr_cell= my_queue.first;

	while(p_curr_cell != NULL){
		rep++;

		p_curr_cell = (*p_curr_cell).next;
	}

	return rep;
}