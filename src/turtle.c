/**
 * \file turtle.c
 *
 * \brief A source file for functions used to convert lsystem strings into arrays
 * of coordinate pairs that make up the lines to be drawn.
 *
 * The sting is counted for characters which will produce a visible line and allocate 
 * memory for an array of lines of the required length, and then the 
 * program will run through the string again, updating the turtle as it goes and and 
 * add a pair of coordinates to the line list every time a line drawing character is
 * encountered.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "structs.h"
#include "turtle.h"
#include "lsys.h"

int stringToTurtle(lsystem *lsys){
	/**
	 * \brief The main function for converting the string produced by an lsystem into a list of coordinate 
	 * pairs for lines to be drawn between.
	 *
	 * This is done by firstly runnung through the string that defines the pattern to be drawn and counting
	 * the number of lines that will need to be drawn. This length is then used to allocate Memory for an 
	 * array of lines. A turtle is then introduced and the string is gone through again. The turtle is kept
	 * updated and everytime it draws a line, one is added to the line list and if the position needs to be 
	 * stored or retrieved from the turtle stack then it extracts or adds to the top element of the linked 
	 * list.
	 * 
	 * \param[out] lsys 		pointer to the lsystem (needed for angle incriment and line length).
	 * 
	 * \return			the number of coordinate pairs that are held in the line_list.
	 */

	//initialising variables
	int i = 0; 
	int line_list_pos = 0;
	turtle_state current_turtle; 
	structInitTurtleState(&current_turtle);

	//pointer to the top of the turtle stack used for storing positions
	turtle_state *root = NULL; 

	//counting the number of movement characters in the string.
	int num_moves = countMoves(lsys->string);

	//setting the starting point and heading for the turtle
	current_turtle.pos.x_pos = lsys->start.x_pos; 
	current_turtle.pos.y_pos = lsys->start.y_pos;
	current_turtle.heading = 0;

	//allocating and checking memory for the line list
	lsys->line_list = (line*)calloc(num_moves, sizeof(line));
	if (lsys->line_list == NULL){
		printf("memory allocation for line list failed\n");
		return 1;
	}

	// iterating through the string and performing the required action for each character
	for (i = 0; lsys->string[i] != 0; i++){ 
		switch(lsys->string[i]){
			case 'A': 
			case 'B':
			case 'F': line_list_pos = penDownLine(&current_turtle, lsys->length, line_list_pos, lsys); break; // adds a pair of coordinates to the line list
			case 'f': penUpLine(&current_turtle, lsys->length); break; 
			case 'X': break;
			case 'Y': break;
			case '+': current_turtle.heading += lsys->angle; break; // changes heading of current turtle
			case '-': current_turtle.heading -= lsys->angle; break; // changes heading for current turtle
			case '[': savePos(&root, current_turtle); break; //saves current state to stack
			case ']': popPos(&root, &current_turtle); break; //pops off saved state from the stack beign pointed to by the stack_pos variable
			default : break;
		}
	}


	//if there was an unbalanced number of left and right brackets in the string, some 
	//sotred positions may not be poped off and freed and there for require freeing at the 
	//end to prevent memory leaks.
	if (root != NULL){ 
		turtle_state *temp;
		turtle_state *place;

		place = root;
		while (place != NULL){
			temp = place;
			place = place->next;
			free(temp);
		}
	}

	//returns the total number of line drawing characters in the string.
	return num_moves;
}

void savePos(turtle_state **root, turtle_state current_turtle){
	/**
	 * \brief Saves the current position of the turtle to the top of the linked list.
	 *
	 * This is done by initialising a new turtle state and filling it with the current_turtle
	 * data. This is then set to point to the top of the turtle stack and the previous pointer
	 * to the top is then set to point to the new top.
	 * 
	 * \param[out] root 		 	 ponter pointer to the root of the chain of positions.
	 * \param[in] current_turtle	 the currentky active turtle.
	 */

	turtle_state *new_pos = (turtle_state*)malloc(sizeof(turtle_state));

	new_pos->pos = current_turtle.pos;
	new_pos->heading = current_turtle.heading;
	
	//setting the new turtle to point at the top of the stack
	//and the old pointer to the new top of the stack
	new_pos->next = *root;
	*root = new_pos;
}	

void popPos(turtle_state **root, turtle_state *current_turtle){
	/**
	 * \brief pops off the top of the chain of saved turtle states, changing where the root points and 
	 * freeing the removed data.
	 * 
	 * This is done by copying the data from the top of the turtle stack to the current_turtle, then 
	 * setting a temporary pointet to point to the second element in the stack. The top of the stack 
	 * is then freed and the pointer that wa pointing to the top is now set to the temporary pointer.
	 *
	 * \param[out] root 			pointer pointer to the top of the turtle stack.
	 * \param[out] current_turtle	pointer to the currently active turtle.
	 */

	//exit the functions if there are no turtles in the stack
	if (*root == NULL)
		return;
	
	turtle_state *temp = NULL;

	current_turtle->pos = (*root)->pos;
	current_turtle->heading = (*root)->heading;

	//set temp to look at the new top of the stack before
	//freeing the old top and setting the pointer to the
	//new top
	temp = (*root)->next;
	free(*root);
	*root = temp;
}

int penDownLine(turtle_state *current_turtle, int length, int line_list_pos, lsystem *lsys){
	/**
	 * \brief Adds a line to the line list and updates the turtles position.
	 * 
	 * This function uses some simple trigonometry to calculate the final position of the
	 * turtle after drawing a line of a given length, from a given starting point at a given
	 * heading. The starting position and end position are then added to the line list as a pair
	 * of coordinates.
	 *
	 * \param[out] current_turtle	pointer to the currently active turtle.
	 * \param[out] line_list 		pointer pointer to the array of coordinate pairs for drawing lines.
	 * \param[in] length 			length of each line to be drawn
	 * \param[in] linelist_pos 		an integer that holds the current position of the next empty element in the line list.
	 * 
	 * \return 					the current position in the line list.
	 */

	//extracting the starting point of the turtle for the line list
	coordinate start = current_turtle->pos;

	//calculating the change in x and y positions
	double dx = length * sin(current_turtle->heading);
	double dy = -length * cos(current_turtle->heading);
	
	//creating a coorinate pair to hold the end position of the line
	double x_end = (start.x_pos + dx);
	double y_end = (start.y_pos + dy);
	coordinate end = {x_end, y_end};

	//new line is created and added to the line list
	line new_line = {start, end};
	lsys->line_list[line_list_pos] = new_line;
	line_list_pos++;

	//turtle position is set to the end of the line
	current_turtle->pos = end;

	//returns a counter that tells you how full the line list is.
	return line_list_pos;
}

void penUpLine(turtle_state *current_turtle, int length){
	/**
	 * \brief Moves the turtle by the line length using the current heading, but without adding that line to the line list.
	 * 
	 * This is done using simple trigonometry to calculate the change in x and y  using the given length anf heading. These
	 * values are then added to the starting position and then the turtle is updated to this new position.
	 *
	 * \param[out] current_turtle	pointer to the current active turtle.
	 * \param[in] length 			length of the distance to be moved.
	 */

	//start point is extracted
	coordinate start = current_turtle->pos;

	//change in x and y are calculated
	double dx = length * sin(current_turtle->heading);
	double dy = -length * cos(current_turtle->heading);
	
	//dy and dx are then added to the start position
	double x_end = (start.x_pos + dx);
	double y_end = (start.y_pos + dy);

	//a coordinate pair is created out of the final x and y position and the turtle is updated to this new position.
	coordinate end = {x_end, y_end};
	current_turtle->pos = end;
}

int countMoves(char *string){
	/**
	 * \brief Runs through the string and counts the number of line drawing characters.
	 * 
	 * \param[in] string 	string that is going to be run through and counted.
	 */

	//initialising variables
	int i = 0;
	int counter = 0;

	//iterating through the string and incrementing the counter for each movement character encountered
	for (i = 0; i <= strlen(string); i++){
		if (string[i] == 'F' || string[i] == 'A' || string[i] == 'B')
			counter++;
	}

	//returns the number of movement characters.
	return counter;
}

