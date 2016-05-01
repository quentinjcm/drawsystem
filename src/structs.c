/**
 * \file structs.c
 *
 * \brief A source file for functions used ito intitialise structures requied for the program.
 *
 * Initialisation functions are required to insure defined behavior for every element in each
 * structure.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "structs.h"


void structInitLsystem(lsystem *lsys){
	/**
	 * \brief Initilaises an lsystem structure.
	 *
	 * For use when declaring an lsystem to ensure that all elements have defined values 
	 * and therfor predictable behavior.
	 * 
	 * \param[out] lsys 	 The lsystem structure to be initialized.
	 */

	SDL_Colour col = {0, 0, 0};

	strcpy(lsys->name, "\0");
	strcpy(lsys->axiom, "\0");

	lsys->bg_colour = col;
	lsys->ln_colour = col;
	structInitCoord(&(lsys->start));
	lsys->angle = 0;
	lsys->length = 0;
	lsys->iterations = 0;
    lsys->iteration_limit= 0;
    lsys->img_file_num = 0;
    lsys->seq_file_num = 0;
    lsys->string = NULL;
    lsys->line_list = NULL;
    lsys->line_list_length = 0;
    lsys->remake_lines_flag = 0;
    lsys->remake_string_flag = 0;
    lsys->info_disp_flag = 0;
    strcpy(lsys->rule_A, "\0");
    strcpy(lsys->rule_B, "\0");
    strcpy(lsys->rule_F, "\0");
    strcpy(lsys->rule_f, "\0");
    strcpy(lsys->rule_X, "\0");
    strcpy(lsys->rule_Y, "\0");
    strcpy(lsys->rule_plus, "\0");
    strcpy(lsys->rule_minus, "\0");
    strcpy(lsys->rule_store, "\0");
    strcpy(lsys->rule_pop, "\0");
}

void structInitCoord(coordinate *coord){
	/**
	 * \brief Initilaises a coordinate structure.
	 * 
	 * For use when declaring a coordinate to ensure that all elements have defined 
	 * values and therfor predictable behavior.
	 * 
	 * \param[out] coord 	 The coordinate structue to be initialised.
	 */

	coord->x_pos = 0;
	coord->y_pos = 0;
}

void structInitLine(line *ln){
	/**
	 * \brief Nnitilaises a line structure.
	 * 
	 * For use when declaring a line to ensure that all elements hae defined 
	 * values and predictable behavior.
	 * 
	 * \param[out] ln 		The line structure to be initialized.
	 */

	structInitCoord(&(ln->start));
	structInitCoord(&(ln->end));
}

void structInitBtn(btn *ui_button){
	/**
	 * \brief Initilaises a button structure 
	 * 
	 * For use when declaring a button to ensure that all elements have defined 
	 * values and predictable behavior.
	 * 
	 * \param[out] ui_button 	The button structure to be initialized.
	 */

	SDL_Colour col = {0, 0, 0};

	structInitCoord(&(ui_button->tl_corner));
	ui_button->width = 0;
	ui_button->height = 0;
	ui_button->font = NULL;
	strcpy(ui_button->text, "\0");
	ui_button->colour = col;
}

void structInitTurtleState(turtle_state *turtle){
	/**
	 * \brief Initilaises a turtle_state structure
	 *
	 * For use when declaring a turtle_state structure to ensure that all 
	 * elements have defined values and predictable behavior.
	 * 
	 * \param[out] turtle    The turtle structure to be initialized.
	 */
	structInitCoord(&(turtle->pos));
	turtle->heading = 0;
	turtle->next = NULL;
}
