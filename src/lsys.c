/**
 * \file lsys.c
 *
 * \brief A source file for functions used in the creation of lsystem strings.
 *
 * The L-System string is created by performing a character replacement
 * on a starting string (axiom) using a set of character replacement rules
 * and then recursivly calling the same character replacement reules on the 
 * result of the previous string to the required depth of iterations.
 */


#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "structs.h"
#include "lsys.h"


/** \def M_PI
 *   \brief A macro definition for the mathematical constant Pi 
 */
#ifndef M_PI
#define M_PI 3.14156265359
#endif


void iteration(lsystem *lsys){
    /**
     * \brief Performes a single iteration of character replacement for a string.
     *
     * This is done by firstly counting up the new length of the string, then allocating 
     * the required amout of memory before finaly creating the new string, freeing the old 
     * one, thensetting the poonter to point at the newly created string.
     *
     * \param[out] lsys        the lsystem that holds the rules for character replacement and the string
     */

    int i = 0; // A counter to be used for iterating through arrays.
    int newLen = 1; // Counter for the new lenght of the characger string.
    char character; // Container to hold the character in the string which is currently beign looked at.
    char *temp = NULL; // Temporary character to hold the new string while it is being created.

    // Finding the lenght of the new string.
    for(i = 0; i < strlen(lsys->string); i++){
        character = (lsys->string)[i];
        switch(character){
            case 'A': newLen += strlen(lsys->rule_A); break;
            case 'B': newLen += strlen(lsys->rule_B); break;
            case 'F': newLen += strlen(lsys->rule_F); break;
            case 'f': newLen += strlen(lsys->rule_f); break;
            case 'X': newLen += strlen(lsys->rule_X); break;
            case 'Y': newLen += strlen(lsys->rule_Y); break;
            case '+': newLen += strlen(lsys->rule_plus); break;
            case '-': newLen += strlen(lsys->rule_minus); break;
            case '[': newLen += strlen(lsys->rule_store); break;
            case ']': newLen += strlen(lsys->rule_pop); break;
            default : break;
        }
    }

    // Allocating memory for new string.
    temp = (char*)calloc(newLen, sizeof(char));

    // Running through the string a second time to copy the required replacements 
    // into the newly allocatd memory.
    for(i = 0; i < strlen(lsys->string); i++){
        character = (lsys->string)[i];
        switch(character){
            case 'A': strcat(temp, lsys->rule_A); break;
            case 'B': strcat(temp, lsys->rule_B); break;
            case 'F': strcat(temp, lsys->rule_F); break;
            case 'f': strcat(temp, lsys->rule_f); break;
            case 'X': strcat(temp, lsys->rule_X); break;
            case 'Y': strcat(temp, lsys->rule_Y); break;
            case '+': strcat(temp, lsys->rule_plus); break;
            case '-': strcat(temp, lsys->rule_minus); break;
            case '[': strcat(temp, lsys->rule_store); break;
            case ']': strcat(temp, lsys->rule_pop); break;
            default : break;
        }
    }

    // Freeing old string to make way for the new one.
    free(lsys->string);
    (lsys->string) = temp;
    temp = NULL;
}

int makeString(lsystem *lsys){
    /**
     * \brief takes in the axiom and the rules and produces the final string, using the
     * \brief number of iterations specified by the user.
     *
     * Firstly, memory is allocated for the axiom to be places in the string container, this 
     * allocation is then checked before the iteration() function is then run on the string 
     * for the required number of iterations.
     *
     * \param[out] lsys      a pointer to the lsystem that contaisn the rules, axiom, old string, and number of iterations.
     *
     * \return               returns 1 if sucessfull, and 0 if memory allocation failed.
     */

    int i;

    // Allocating and checking that memory for the string was correctly allocated.
    lsys->string = (char*)calloc(strlen(lsys->axiom)+1, sizeof(char));
    if(lsys->string == NULL){
        printf("string memory allocation failed\n");
        return 0;
    }

    // Coppying the axiom to the string holder.
    strcpy(lsys->string, lsys->axiom);
    for(i = 0; i < lsys->iterations; i++){
        iteration(lsys);
    }

    // Return 1 if all happened sucessfully.
    return 1;
}

void initLsystem(lsystem *lsys){
    /**
     * \brief Sets all rules in an lsystem to map to them selves so that there will be a 
     * \brief default rule for each character in the string. Also intiialises other values
     * \brief that will be the default values for creation/drawing ect.
     *
     * \param[out] lsys       an lsystem that will store the information.
     */

    //Settign default rules.
    strcpy(lsys->rule_A, "A");
    strcpy(lsys->rule_B, "B");
    strcpy(lsys->rule_F, "F");
    strcpy(lsys->rule_f, "f");
    strcpy(lsys->rule_X, "X");
    strcpy(lsys->rule_Y, "Y");
    strcpy(lsys->rule_plus, "+");
    strcpy(lsys->rule_minus, "-");
    strcpy(lsys->rule_store, "[");
    strcpy(lsys->rule_pop, "]");

    //settign default drawing parameters
    lsys->length = 5;
    lsys->iterations = 3;

    //setting drawing starting point
    coordinate start = {700, 500};
    lsys->start = start;

    //setting flags to defaults
    lsys->remake_lines_flag = 1;
    lsys->remake_string_flag = 1;
    lsys->info_disp_flag = 0;

}

double dtor(double degrees){
    /**
     * \brief converts an angle from degrees into radians.
     * 
     * \parm[in] degrees      angle to be converted into radians.
     *
     * \return                angle in radians.
     */

    double radians = degrees * M_PI/180;
    return radians;
}

double rtod(double radians){
    /**
     * \brief Converts an angle from radians into degrees.
     *
     * \param[in] radians     angle to be converted into degrees.
     *
     * \return                angle in dgrees
     */

    double degrees = radians * 180/M_PI;
    return degrees;
}

void resetString(lsystem* lsys){
	/**
	 * \brief Frees the pointers string and resets the flag.
	 *
	 * \param[out] lsys 	lsystem that holds the data to be freed.
     */
	
	free(lsys->string);
    lsys->string = NULL;
    lsys->remake_string_flag = 1;
}

void resetLines(lsystem *lsys){
	/**
	 * \brief Frees the line list and resets the flag.
	 *
	 * \param[out] lsys 	lsystem that holds data to be freed
	 */
	
	free(lsys->line_list);
	lsys->remake_lines_flag = 1;
}

void sierpinski(lsystem *lsys){
    /** 
     * \brief Copy Sierpinski Triangle rules to the lsystem.
     *
     * \param[out] lsys   lsystem for the rules to be copied to
     */

    // Reset lsystem default values.
    initLsystem(lsys);

    // Copying in new values.
    strcpy(lsys->name, "Sierpinski Triangle");
    strcpy(lsys->axiom, "A");
    lsys->angle = dtor(60.0);
    strcpy(lsys->rule_A, "B-A-B");
    strcpy(lsys->rule_B, "A+B+A");
    lsys->iteration_limit = 9;
}

void dragon(lsystem *lsys){
    /**
     * \brief Copy Dragon Curve rules to the lsystem.
     *
     * \param[out] lsys   lsystem for the rules to be copied to
     */

    // Reset lsystem default values.
    initLsystem(lsys);

    // Copying in new values.
    strcpy(lsys->name, "Dragon Curve");
    strcpy(lsys->axiom, "FX");
    lsys->angle = dtor(90.0);
    strcpy(lsys->rule_X, "X+YF+");
    strcpy(lsys->rule_Y, "-FX-Y");
    lsys->iteration_limit = 14;
}

void plant1(lsystem *lsys){
    /**
     * \brief Copy Fractal Plant 1 rules to the lsystem.
     *
     * \param[out] lsys   lsystem for the rules to be copied to
     */

    // Reset lsystem default values.
    initLsystem(lsys);

    // Copying in new values.
    strcpy(lsys->name, "Fractal Plant 1");
    strcpy(lsys->axiom, "X");
    lsys->angle = dtor(25.0);
    strcpy(lsys->rule_X, "F-[[X]+X]+F[+FX]-X");
    strcpy(lsys->rule_F, "FF");
    lsys->iteration_limit = 7;
}

void plant2(lsystem *lsys){
    /**
     * \brief Copy the rules for a fractal plant to the lsystem.
     *
     * \param[out] lsys   system for the rules to be copied to.
     */

    // Reset lsystem default values.
    initLsystem(lsys);

    // Copying in new values.
    strcpy(lsys->name, "Fractal Plant 2");
    strcpy(lsys->axiom, "F");
    lsys->angle = dtor(25.7);
    strcpy(lsys->rule_F, "F[+F]F[-F][F]");
    lsys->iteration_limit = 6;
}

void islands(lsystem *lsys){
    /**
     * \brief Copy island and lake rules to the lsystem.
     *
     * \param[out] lsys   lsystem for the rules to be copied to.
     */

    // Reset lsystem default values.
    initLsystem(lsys);

    // Copying in new values.
    strcpy(lsys->name, "Islands and Lake");
    strcpy(lsys->axiom, "F+F+F+F");
    lsys->angle = dtor(90);
    strcpy(lsys->rule_F, "F+f-FF+F+FF+Ff+FF-f+FF-F-FF-Ff-FFF");
    strcpy(lsys->rule_f, "ffffff");
    lsys->iteration_limit = 3;
}

void snowflake(lsystem *lsys){
    /**
     * \brief Copy Koch Snowflake rules to the lsystem.
     *
     * \param[out] lsys   lsystem for the rules to be copied to
     */
    initLsystem(lsys);
    strcpy(lsys->name, "Koch Snowflake");
    strcpy(lsys->axiom, "F++F++F");
    lsys->angle = dtor(60.0);
    strcpy(lsys->rule_F, "F-F++F-F");
    lsys->iteration_limit = 5;
}

void quadKoch(lsystem *lsys){
    /**
     * \brief Copy lsystem rules for a quadratic koch curve to the lsystem.
     *
     * \param[out] lsys   lsystem for the rules to be copied too.
     */
    initLsystem(lsys);
    strcpy(lsys->name, "Quadratic Koch Islands");
    strcpy(lsys->axiom, "F-F-F-F");
    lsys->angle = dtor(90);
    strcpy(lsys->rule_F, "F-F+F+FF-F-F+F");
    lsys->iteration_limit = 4;
}

void gosper(lsystem *lsys){
    /**
     * Copy lsystem rules for a gosper curve to the lsystem.
     *
     * \param[out] lsys   lsystem for the rules to be copied to.
     */
    initLsystem(lsys);
    strcpy(lsys->name, "Gosper Curve");
    strcpy(lsys->axiom, "A");
    lsys->angle = dtor(60);
    strcpy(lsys->rule_A, "A-B--B+A++AA+B-");
    strcpy(lsys->rule_B, "+A-BB--B-A++A+B");
    lsys->iteration_limit = 5;
}
