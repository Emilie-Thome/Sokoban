#include "bst_map.h"


void fusion(bst_map *p_tree1, bst_map *p_tree2){ /*the new tree is in &tree2*/
	if(is_empty(*p_tree1)){
	/*nothing move*/
	}else{
		if(is_empty(*p_tree2)){
			*p_tree2 = *p_tree1;
		}else{
			insert(p_tree2, (**p_tree1).value);
			fusion(&((**p_tree1).left), p_tree2);
			fusion(&((**p_tree1).right), p_tree2);
		}
	}
}




void deallocate_nodes(bst_map tree){
	if(!is_empty(tree)){
		deallocate_map(tree->value);
		deallocate_nodes(tree->left);
		deallocate_nodes(tree->right);
		free(tree);
	}
}

// functions from the signature

void nil(bst_map *p_tree){
	*p_tree = NULL;
}


bool is_empty(bst_map tree){
	return (tree == NULL);
}


map* value(bst_map tree){
	if(!is_empty(tree)){
		bst_node_map root_node = *tree;
		return root_node.value;
	}else{
		printf("VALUE: THE TREE IS EMPTY\n");
		return NULL; /*no warning*/ 
	}
}


int size(bst_map tree){
	if(is_empty(tree)){
		return 0;
	}else{	
		bst_node_map root_node = *tree;
		return size(root_node.left) + size(root_node.right) + 1;
	}
}

int height(bst_map tree){
	if(is_empty(tree)){
		return 0;
	}else{
		bst_node_map root_node = *tree;
		int height_left = height(root_node.left);
		int height_right = height(root_node.right);
		if(height_right < height_left){
			return height_left + 1;
		}else{
			return height_right + 1;
		}
	}
}


bool is_in_bst(bst_map tree, map *value){
	if(is_empty(tree)){
		return false;
	}else{
		bst_node_map root_node = *tree;
		char *s1 =  (*value).elements;
		char *s2 =  (*(root_node.value)).elements;
		int size = ((*value).width) * ((*value).height);

	    int res = strncmp(s1, s2, size); /*lexico graphic order*/
		if(res == 0){/*si les maps sont identiques*/
			return true;
		}else{
			if(res < 0){
				return is_in_bst(root_node.left, value);
			}else{
				return is_in_bst(root_node.right, value);
			}
		}
	}
}





void insert(bst_map *p_tree, map *value){
	if(is_empty(*p_tree)){
		bst_node_map* p_new = (bst_node_map*)calloc(1, sizeof(bst_node_map));
		p_new -> value = value;
		p_new -> left = NULL;
		p_new -> right = NULL;
	
		*p_tree = p_new;
		
	}else{
		bst_node_map root_node = **p_tree;
		char *s1 =  (*value).elements;
		char *s2 =  (*(root_node.value)).elements;
		int size = ((*value).width) * ((*value).height);

	    int res = strncmp(s1, s2, size); /*lexico graphic order*/
		if(res < 0){
			insert(&((**p_tree).left), value);
		}else{
			if(res > 0){
				insert(&((**p_tree).right), value);
			}
		}
	}
}



void delete(bst_map *p_tree, map *value){
	if(is_empty(*p_tree)){
		printf("DELETE: THE TREE IS EMPTY\n");
	}else{
		bst_node_map root_node = **p_tree;
		char *s1 =  (*value).elements;
		char *s2 =  (*(root_node.value)).elements;
		int size = ((*value).width) * ((*value).height);

	    int res = strncmp(s1, s2, size); /*lexico graphic order*/
		if(res == 0){
			bst_node_map* p_trash = (*p_tree);

			deallocate_map(p_trash->value);

			bst_map left = (*p_tree)->left;
			bst_map right = (*p_tree)->right;

			fusion(&left, &right); /*the new tree is in &right*/
			*p_tree = right;

			free(p_trash);
		}else{
			if(res < 0){
				delete(&((**p_tree).left), value);
			}else{
				delete(&((**p_tree).right), value);
			}
		}
	}
}



void deallocate_bst(bst_map *p_tree){
	deallocate_nodes(*p_tree);
	free(p_tree);
}
