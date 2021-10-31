#include "loader.h"

map* load(FILE* p_file){

	// allocation memory for the map

	map* p_loaded_map = (map*)calloc(1, sizeof(map));

    int nb_mvmt       = 0;
    int width         = 0;
    int height        = 0;
    int fscanf_result = 0;


    // read dimensions on first line
    fscanf_result = fscanf(p_file, "%d %d\n", &width, &height);

    if (fscanf_result != 2) {
        fprintf(stderr, "First line is not syntactically correct!\n");
        exit(EXIT_FAILURE);
    }


    //get the elements of the map and the player position
    char* p_elements = (char*)calloc(width*height, sizeof(char));
    int x_position = -1;
    int y_position = -1;


    // read following lines
    // line_buffer contains a line and is a correct string
    // width + 2 is needed to get the carriage return symbol
    char line_buffer[width + 2];

    for (int i = 0; i < height; i++) {
        fgets(line_buffer, width + 2, p_file);

        //get the element of the map
        for (int j = 0; j< width; j++){
        	*(p_elements + i*width + j) = *(line_buffer + j);

        	//get the player position (y = 0 is the upper right angle of the map)
        	if ((*(p_elements + i*width + j) == '@')||(*(p_elements + i*width + j) == '+')){
        		x_position = j ;
   				y_position = i ;
        	}
        }
    }

    if ((x_position == -1)||(y_position == -1)){
    	printf("THERE IS NO PLAYER POSITION\n");
    	exit(EXIT_FAILURE);
    }else{
    	//give the data to the map structure

        (*p_loaded_map).nb_mvmt = nb_mvmt;
	    (*p_loaded_map).width = width;
	    (*p_loaded_map).height = height;
	    (*p_loaded_map).elements = p_elements;
	    (*p_loaded_map).x_position = x_position;
	    (*p_loaded_map).y_position = y_position;

	    return p_loaded_map;
    }
}