/**
 * \file main.c
 *
 * \brief A source file for the main finction that will run the program.
 *
 * Firslty all SDL initilaisation functions are run and checked for sucess.
 * Then variables for the L-System and rendereing functions are initilaised 
 * before being passed to the relevant functions for default values to be
 * set up.
 *
 * Once all variables have been declared and initilaised, a while loop that 
 * checks for events and handles window drawing operations for different 
 * click events is entered and only exited when the program is quit.
 *
 * When the program is quit, all variables that need freeing/destroying are
 * handlend and the program exits.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "structs.h"
#include "lsys.h"
#include "ui.h"


/*
 * \brief Performs all intiialisation functions for sdl and checks to make sure the have worked.
 */
int init();


int main(){
    /**
     * \brief Intialisinf variables for, and controling the running of the program.
     *
     * Initialises all varaibles with default values and defines the button sets for each window
     * before frawing the rewuired window defined by the win_flag. Runs functions for handeling 
     * click events for changing the win_flag and parameters within the L-System.
     *
     * \return   0 if the program runs sucessfully.
     */

	//Initialising SDL elements.
    if (init()){
    	printf("ERROR: initialisation error.\n");
    	return 1;
	}
    
    //creating fonts 
    TTF_Font *arial_body = TTF_OpenFont("fonts/arial.ttf", BODY_SIZE);
    TTF_Font *arial_title = TTF_OpenFont("fonts/arial.ttf", TITLE_SIZE);

    //Creating and filling screen structures to contain information required for drawing and clicking functions.
    btn home_screen_buttons[3];
    int i = 0;
    for (i = 0; i < 3; i++)
        structInitBtn(&(home_screen_buttons[i]));
    createHomeScreenButtons(home_screen_buttons, arial_body);

    btn options_screen_buttons[12];
    for (i = 0; i < 12; i++)
        structInitBtn(&(options_screen_buttons[i]));
    createOptionsScreenButtons(options_screen_buttons, arial_body);

    btn draw_screen_buttons[9];
    for (i = 0; i < 9; i++)
        structInitBtn(&(draw_screen_buttons[i]));
    createDrawScreenButtons(draw_screen_buttons, arial_title, arial_body);

    //creating and initilaising the lsystem container, beofre setting the default lsystem to a sierpinksi triangle.
    lsystem lsys;
    structInitLsystem(&lsys);
    initLsystem(&lsys);
    sierpinski(&lsys);

    //setting default colour values
    SDL_Colour bg_default = {255, 255, 255, 255};
    SDL_Colour ln_default = {0, 0, 0, 255};
    lsys.bg_colour = bg_default;
    lsys.ln_colour = ln_default;

    //setting window flag to the opening window
    int win_flag = 1;

    //setting up window and renderer
    int win_width = 1200;
    int win_height = 800;
    SDL_Window *window = SDL_CreateWindow("Drawsystem", 
                                SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED, 
                                win_width,
                                win_height,
                                SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //entering screen drawing and refresh loop
    int go = 1;
    while (go){

    	//clear screen at the start of evey loop
    	
    	//deciding on the window to be drawn
    	switch(win_flag){
    		case 1: drawHomeScreen(renderer, home_screen_buttons, arial_title, arial_body); break;
    		case 2: drawOptionsScreen(renderer, options_screen_buttons, arial_title, arial_body, &lsys); break;
    		case 3: drawDrawingScreen(renderer, draw_screen_buttons, arial_title, arial_body, &lsys); break;
    	}

    	//checking for events
    	SDL_Event event;
    	SDL_WaitEvent(&event);

    	if (event.type == SDL_QUIT)
    		go = 0;

    	//click event on the home screen
    	if (event.type == SDL_MOUSEBUTTONDOWN && win_flag == 1){
    		win_flag = homeScreenClick(event, home_screen_buttons, win_flag);
    		continue;
    	}

    	//click event on the options screen
    	if (event.type == SDL_MOUSEBUTTONDOWN && win_flag == 2){
    		win_flag = optionsScreenClick(renderer, event, options_screen_buttons, win_flag, &lsys);
    		continue;
    	}

    	//click event on the draw screen
    	if (event.type == SDL_MOUSEBUTTONDOWN && win_flag == 3){
    		win_flag = drawScreenClick(renderer, event, draw_screen_buttons, win_flag, &lsys, arial_title, arial_body);
    		continue;
    	}
    	//rendering what has been drawn to the renderer to the screen
    	SDL_RenderPresent(renderer);
    }

    //freeing lsystem elements
    if (win_flag == 3){
        free(lsys.string);
        free(lsys.line_list);
    }

    //freeing fonts
    TTF_CloseFont(arial_body);
    TTF_CloseFont(arial_title);

    //destroying window and renderer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    //closing libraries
    SDL_Quit();
    TTF_Quit();
    return 0;
}


int init(){
    /**
     * \fn int init()
     *
     * \brief Initilaising SDL elements and printing errors if initialisation failed.
     *
     * \return     : true if errors occured during initilaisation.
     */

     //initilaising SDL
     if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
     {
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        return 1;
    }

    //initialising SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("Could not initilaize TTF_Init: %s\n", TTF_GetError());
        return 1;
    }

    //return 0 if all intialisations were sucessfull.
    return 0;   
}



















