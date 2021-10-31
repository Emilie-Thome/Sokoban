#include "linked_list_map.h"



linked_list_map CreateList(void) {
	return NULL;
}




bool is_empty(linked_list_map list) {
	return (list == NULL);
}




void cons(map* p_map, linked_list_map* p_list) {
	cell_map* p_new = (cell_map*)calloc(1, sizeof(cell_map));
	(*p_new).next = *p_list;
	(*p_new).value = p_map;
	*p_list = p_new;
}




int size(linked_list_map list) {
	if(list == NULL){
		return 0;
	}else{
		cell_map current_cell = *list;
		int size = 1;
		while(current_cell.next != NULL){
			size = 1 + size;
			current_cell = *(current_cell.next);
		}
		return size;
	}
}





map* get_element(int ind, linked_list_map list) {
	cell_map cell = *list;
	
	if (ind==0){
		return cell.value;
	}else{
		for(int k = 0; k < ind; k++){
			if(cell.next == NULL){
				printf("PROBLEME get_element LISTE PAS ASSEZ LONGUE\n");
			}else{
				cell = *(cell.next); 
			}
		}
		return cell.value;
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


void insert_element(map* p_map, int ind, linked_list_map list) {
	cell_map* p_current_cell = list;

	for(int k = 0; k<ind-1; k++){
		if((*p_current_cell).next == NULL){
			printf("PROBLEME insert_element LISTE PAS ASSEZ LONGUE\n");
		}else{
			p_current_cell = (*p_current_cell).next; 
		}
	}

	cell_map* p_new = (cell_map*)calloc(1, sizeof(cell_map));
	(*p_new).next = (*p_current_cell).next;
	(*p_new).value = p_map;
	(*p_current_cell).next = p_new;
}

void remove_element(int ind, linked_list_map* p_list) {
	cell_map* p_current_cell = *p_list;
	// Si pas racine
	if (ind > 1){
		for(int k = 0; k<ind-1; k++){
			if((*p_current_cell).next == NULL){
				printf("PROBLEME remove_element LISTE PAS ASSEZ LONGUE\n");
			}else{
				p_current_cell = (*p_current_cell).next; 
			}
		}

		if((*p_current_cell).next == NULL){
			printf("PROBLEME remove_element LISTE PAS ASSEZ LONGUE\n");
		}else{
			cell_map* p_trash = (*p_current_cell).next;
			(*p_current_cell).next = (*((*p_current_cell).next)).next;
			deallocate_map((*p_trash).value);
			free(p_trash);
		}
	}else{
		if(ind == 0){
			cell_map* p_trash = *p_list;
			*p_list = (**p_list).next;
			deallocate_map((*p_trash).value);
			free(p_trash);

		}else{
			cell_map* p_trash = (**p_list).next;
			(**p_list).next = (*((**p_list).next)).next;
			deallocate_map((*p_trash).value);
			free(p_trash);

		}
	}				
}


void print_list(linked_list_map list) {
	cell_map* p_current_cell = list;

	while(p_current_cell != NULL){
		print_map(*(*p_current_cell).value);
		p_current_cell = (*p_current_cell).next;
	}
}

void deallocate_list(linked_list_map*  p_list) {
	while (! is_empty(*p_list)){
		remove_element(0, p_list);
	}
	free(p_list);
}
