/**
 * \file ui.c 
 * 
 * \brief File containing source code for all UI functions.
 *
 * The first half of the functions defined in the file are specific to the drawsystem
 * program, containing instructions on creating, drawing and handeling clicks on the 
 * various screens used by the program. The second half of the file contains genral UI
 * functions used by the program specific functions.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "structs.h"
#include "lsys.h"
#include "turtle.h"
#include "ui.h"


void createHomeScreenButtons(btn *screen_buttons, TTF_Font *font){
	/**
	 * \brief Defines all of the buttons that will appear on the home screen.
	 *
	 * An array of buttons is created that can be passed to both the screen drawing
	 * functions and the click handeling functions so that they are both looking at
	 * the same array of buttons. This makes updating, changing and adding to the 
	 * buttons that appear on each screen much easier.
	 *
	 * \param[out] screen_buttons		a structure that will hold information on buttons to appear on the home screen.
	 * \param[in] font 					font for the button lables.
	 */

	//initialising variables
	coordinate pos = {500, 350};
	SDL_Colour colour = {255, 64, 129, 255};

	//adds a home button to the list
	createHomeButton(screen_buttons, font);
	
	//adds a back button to the list
	createBackButton(screen_buttons, font);

	//adds an enter button to the list
	addButton(&(screen_buttons[2]), pos, 200, 50, colour, font, "ENTER");
}

void createOptionsScreenButtons(btn *screen_buttons, TTF_Font *font){
	/**
	 * \brief Defines all of the buttons that will appear on the options screen.
	 * 
	 * An array of buttons is created that can be passed to both the screen drawing
	 * functions and the click handeling functions so that they are both looking at
	 * the same array of buttons. This makes updating, changing and adding to the 
	 * buttons that appear on each screen much easier.
	 *
	 * \param[out] screen_buttons 	a structure that will hold infromation on buttons to appear on the options screen.
	 * \param[in] font 				font for the button lables.
	 */

	//initialising button variables
    int i = 0;
	int width = 200;
	int height = 50;
	SDL_Colour colour_1 = {63, 81, 181, 255};
    char *names[8] = {"Sierpinski Triangle", 
                        "Dragon Curve", 
                        "Fractal Plant 1", 
                        "Fractal Plant 2", 
                        "Islands and Lakes", 
                        "Koch Snwflake", 
                        "Quadratic Koch Islands", 
                        "Gosper Curve"};
    SDL_Colour draw_btn_col = {255, 64, 129, 255};
	coordinate draw_btn_pos ={950, 600};

    //adds a home button to the list
	createHomeButton(screen_buttons, font);

	//adds a back button to the list
	createBackButton(screen_buttons, font);

    //creating buttons that set the L-System to be drawn
    for (i = 0; i < 8; i++){
        coordinate pos = {20, 250+70*i};
        addButton(&(screen_buttons[2+i]), pos, width, height, colour_1, font, names[i]);
    }

    //adding a draw button that will take the user to the drawing screen
	height = 70;
	addButton(&(screen_buttons[10]), draw_btn_pos, width, height, draw_btn_col, font, "DRAW!");
}

void createDrawScreenButtons(btn *screen_buttons, TTF_Font *title_font, TTF_Font *body_font){
	/**
	 * \brief Defines all of the buttons that will appear on the options screen.
	 * 
	 * An array of buttons is created that can be passed to both the screen drawing
	 * functions and the click handeling functions so that they are both looking at
	 * the same array of buttons. This makes updating, changing and adding to the 
	 * buttons that appear on each screen much easier.
	 *
	 * \param screen_buttons 	an array that will hold infromation on buttons to appear on the draw screen.
	 * \param title_font		large font to be used on some buttons.
	 * \param body_font 		small font to be used on some buttons.
	 */

	//adds a home button to the array
	createHomeButton(screen_buttons, body_font);
	
	//adds a back button to the array
	createBackButton(screen_buttons, body_font);
	
	//setting parameters for drawing options buttons
	SDL_Colour colour_1 = {63, 81, 181, 255};
	SDL_Colour colour_2 = {255, 64, 129, 255};
	int height = 30;
	int width = 30;

	//line length decrease button
	coordinate pos_1 = {60, 100};
	addButton(&(screen_buttons[2]), pos_1, width, height, colour_1, title_font, "-");

	//line length incrase button
	coordinate pos_2 = {110, 100};
	addButton(&(screen_buttons[3]), pos_2, width, height, colour_1, title_font, "+");

	//fractal depth decrease button
	coordinate pos_3 = {60, 200};
	addButton(&(screen_buttons[4]), pos_3, width, height, colour_1, title_font, "-");

	//fractal depth increase button
	coordinate pos_4 = {110, 200};
	addButton(&(screen_buttons[5]), pos_4, width, height, colour_1, title_font, "+");

	//show/hide info button;
	coordinate pos_5 = {20, 370};
	addButton(&(screen_buttons[6]), pos_5, 160, 40, colour_1, body_font, "Show/Hide Info");

	//save img button
	coordinate pos_6 = {10, 450};
	addButton(&(screen_buttons[7]), pos_6, 180, 50, colour_2, body_font, "Save image");

	//save sequence button
	coordinate pos_7 = {10, 550};
	addButton(&(screen_buttons[8]), pos_7, 180, 50, colour_2, body_font, "Save sequence");
}

void drawHomeScreen(SDL_Renderer *renderer, btn *screen_buttons, TTF_Font *title_font, TTF_Font *body_font){
	/**
	 * \brief Draws the home sceen to the renderer.
	 * 
	 * draws the background colour to the renderer, then all the buttons defined in the btn array
	 * and then some title text.
	 *
	 * \param[out] renderer			renderer for screen to be drawn to.
	 * \param[in] screen_buttons 	buttons to be drawn to the screen.
	 * \param[in] title_font 		font for the title text
	 * \param[in] body_font 		font for the body text.
	 */

	//drawing background colours
	drawBG(renderer);
	
	//drawing buttons over background
	drawAllButtonsToRenderer(renderer, screen_buttons, 3);
	
	//writing title
	drawTextToRenderer(renderer, 600, 300, "WELCOM TO THE L-SYSTEM DRAWING PROGRAM", title_font, 0);
}

void drawOptionsScreen(SDL_Renderer *renderer, btn *screen_buttons, TTF_Font *title_font, TTF_Font *body_font, lsystem *lsys){
	/**
	 * \brief Draws the options screen to the renderer.
	 *
	 * Sraws the background, then some title text, then colour charts for picking drawing colours, then 
	 * the buttons defined in the btn array and finally some text to indicate the current L-System loaded 
	 * into the lsystem structre.
	 * 
	 * \param[out] renderer 		renderer for screen to be drawn to.
	 * \param[in] screen_buttons  	buttons to be drawn to the screen.
	 * \param[in] title_font 		font to be used for the title text.
	 * \param[in] body_font 		font to be used for the body text.
	 * \param[out] lsys 			lsystem container that has drawing information to be changed byt options buttons.
	 */

	//drawing background
	drawBG(renderer);

	//drawing instruction text
	drawTextToRenderer(renderer, 600, 100, "Please Choose a fractal pattern and colour scheme", title_font, 0);

	//drawing buttons
	drawAllButtonsToRenderer(renderer, screen_buttons, 11);

	//drawing colour charts
	drawTextToRenderer(renderer, 300, 170, "Background Colour:", body_font, 1);
	drawColourChartToRenderer(renderer, 300, 200);
	drawTextToRenderer(renderer, 600, 170, "Line Colour:", body_font, 1);
	drawColourChartToRenderer(renderer, 600, 200);

	//drawing current colour selection boxes to the renderer
	drawTextToRenderer(renderer, 950, 170, "Current line colour:", body_font, 1);
	drawInputColourBox(renderer, lsys->ln_colour, 950, 200);
	drawTextToRenderer(renderer, 950, 370, "Current background colour:", body_font, 1);
	drawInputColourBox(renderer, lsys->bg_colour, 950, 400);

	//writing out currently selected lsystem
	drawTextToRenderer(renderer, 950, 550, "Currently selected L-System:", body_font, 1);
	drawTextToRenderer(renderer, 950, 580, lsys->name, body_font, 1);
}

void drawDrawingScreen(SDL_Renderer *renderer, btn *screen_buttons, TTF_Font *title_font, TTF_Font *body_font, lsystem *lsys){
	/**
	 * \brief Sraws the drawing screen to the renderer.
	 *
	 * Starts by drawing the background to the renderer, then buttons, instruction text and finally
	 * the lsystem drawign window. The drawing of the window runs the functions defined in lsys.c and
	 * turtle.c if the relevant flags are set to create the string, and then the line list that are
	 * required to draw the lsystem.
	 *
	 * To allow the buttons to update the screen live the lsystem needs to be redrawn each frame. To keep
	 * the speed up and minimize the number of calultions being done by the computer flags are set to tell
	 * the program when the string and line list need to be recalulated and when it can just redraw the 
	 * last ones that is used (which are stored in the lsystem stucture).
	 * 
	 * \param[out] renderer  		renderer for the screen to be drawn to.
	 * \param[in] screen_buttons  	buttons to be drawn to the screen.
	 * \param[in] title_font 		font to be used for the title text.
	 * \param[in] body_font 		font to be used for the body text.
	 * \param[out] lsys 			lsystem that contains information to be drawn to the screen.
	 */

	SDL_Rect bg = {200, 0, 1000, 1000};

	//drawing background
	drawBG(renderer);

	//drawing buttons
	drawAllButtonsToRenderer(renderer, screen_buttons, 9);

	//writing button lables and instructions
	drawTextToRenderer(renderer, 100, 80, "Line length:", body_font, 0);
	drawTextToRenderer(renderer, 100, 180, "Fractal Depth:", body_font, 0);
	drawTextToRenderer(renderer, 100, 290, "Click in window to redraw", body_font, 0);
	drawTextToRenderer(renderer, 100, 310, "fractal from new position", body_font, 0);
	drawTextToRenderer(renderer, 100, 620, "WARNING!", body_font, 0);
	drawTextToRenderer(renderer, 10, 650, "save sequence will save", body_font, 1);
	drawTextToRenderer(renderer, 10, 670, "up to 201 .bmp images", body_font, 1);
	drawTextToRenderer(renderer, 10, 690, "showing the full creation", body_font, 1);
	drawTextToRenderer(renderer, 10, 710, "of the fractal but it can", body_font, 1);
	drawTextToRenderer(renderer, 10, 730, "be slow. Do not move", body_font, 1);
	drawTextToRenderer(renderer, 10, 750, "window while saving.", body_font, 1);
	drawTextToRenderer(renderer, 10, 770, "Progress shown in the", body_font, 1);
	drawTextToRenderer(renderer, 10, 790, "terminal.", body_font, 1);
	
	//checking flags and drawing lsystem window
	if (lsys->remake_string_flag){
		makeString(lsys);
		lsys->remake_string_flag = 0;
	}
	
	if (lsys->remake_lines_flag){
		lsys->line_list_length = stringToTurtle(lsys);
		lsys->remake_lines_flag = 0;
	}
	
	//drawing background
    SDL_SetRenderDrawColor(renderer, lsys->bg_colour.r, lsys->bg_colour.g, lsys->bg_colour.b, lsys->bg_colour.a);
    SDL_RenderFillRect(renderer, &bg);

    //drawing fractal
    drawFractal(renderer, lsys->line_list_length, lsys->line_list, lsys->ln_colour);

    //drawing info
    if (lsys->info_disp_flag){
        drawInfoToRenderer(renderer, 220, 20, *lsys, title_font, body_font);
    }

    //setting a boarder on the draw screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &bg);
}

int homeScreenClick(SDL_Event event, btn *button_list, int win_flag){
    /**
     * \brief Handles what happens when a button is clicked by checking the position against
     * buttons defined in the button list.
     *
     * The position of the click is checked against each button in the array and if it is 
     * inside one of these then the relevant value is returned.
     * 
     * \param[in] event     	a click event that contains infromation about which mouse button was pressed and where.
     * \param[in] win_flag      a flag that indicates which window is currently being sent to the screen (main menu, creation options, display lsystem ect.).
	 * \param[in] button 		an array of the buttons that are on the screen.
	 * \param[in] win_flag 		the old window flag.
	 * 
     * \return          		the new win_flag that will indicate what the new window should be (default is the same value that came in).
     */

    //click on home button
    if (clickInButton(event, button_list[0]))
    	return 1;

    //click on back button
    if (clickInButton(event, button_list[1]))
    	return 1;

    //click on enter button
    if (clickInButton(event, button_list[2]))
    	return 2;

    //default is to return the input window flag
    return win_flag;
}

int optionsScreenClick(SDL_Renderer *renderer, SDL_Event event, btn *button_list, int win_flag, lsystem *lsys){
    /**
     * \brief Handles what happens when a button is clicked by checking the position against
     * buttons on the current screen (which is indicated by the win_flag).
     *
     * The position of the click is checked against each button in the array and if it is 
     * inside one of these then the relevant value is returned and changes made to the lsystem 
     * structure.
     * 
     * \param[in] event     	a click event that contains infromation about which mouse button was pressed and where.
     * \param[in] win_flag      a flag that indicates which window is currently being sent to the screen (main menu, creation options, display lsystem ect.).
	 * \param[in] button_list 	an array of the buttons that are on the screen.
	 * \param[in] win_flag 		the old window flag.
	 * \param[in] lsys 			container for information about the lsystem, which will be edited depending on the options chosen.
	 *
     * \return          		the new win_flag that will indicate what the new window should be (default is the same value that came in).
    */

    //click on home button
    if (clickInButton(event, button_list[0]))
    	return 1;

    //click on back button
    if (clickInButton(event, button_list[1]))
    	return win_flag-1;

    //click on sierpinski triangle button
    if (clickInButton(event, button_list[2])){
    	sierpinski(lsys);
        return 2;
    }

    //click on dragon curve button
    if (clickInButton(event, button_list[3])){
    	dragon(lsys);
        return 2;
    }

    //click on fractal plant 1 button
    if (clickInButton(event, button_list[4])){
        plant1(lsys);
        return 2;
    }

    //click on fractal plant 2 button
    if (clickInButton(event, button_list[5])){
        plant2(lsys);
        return 2;
    }

    //click on islands button
    if (clickInButton(event, button_list[6])){
        islands(lsys);
        return 2;
    }

    //click on koch snowflake button
    if (clickInButton(event, button_list[7])){
        snowflake(lsys);
        return 2;
    }

    //click on quadratic koch island button
    if (clickInButton(event, button_list[8])){
        quadKoch(lsys);
        return 2;
    }

    //click on koch variation 2 button
    if (clickInButton(event, button_list[9])){
        gosper(lsys);
        return 2;
    }

    //checking to see if the click is inside one of the colour pickers
    if (event.button.y > 200 && event.button.y < 668){

        //if click in Background colour picker
        if (event.button.x > 300 && event.button.x < 540){
        	lsys->bg_colour = getPixelColour(renderer, 1200, 800, event.button.x, event.button.y);
            return win_flag;
        }

        //if click in line colour picker
        if (event.button.x > 600 && event.button.x < 840){
        	lsys->ln_colour  = getPixelColour(renderer, 1200, 800, event.button.x, event.button.y);
            return win_flag;
        }
    }

    //click on draw button
    if (clickInButton(event, button_list[10])){
    	return 3;
	}

    //default to return the input flag
    return win_flag;
}

int drawScreenClick(SDL_Renderer *renderer, SDL_Event event, btn *button_list, int win_flag, lsystem *lsys, TTF_Font *title_font, TTF_Font *body_font){
	/**
     * \brief Handles what happens when a button is clicked by checking the position against
     * buttons on the current screen (which is indicated by the win_flag).
     * 
     * the position of the click is checked against each button in the array and if it is 
     * inside one of these then the relevant value is returned and flags set.
     * 
     * \param[in] window 		window that renderer renders too.
     * \param[out] renderer 	renderer to be drawn to.
     * \param[in] event    		a click event that contains infromation about which mouse button was pressed and where.
     * \param[in] win_flag      a flag that indicates which window is currently being sent to the screen (main menu, creation options, display lsystem ect.).
	 * \param[in] button 		an array of the buttons that are on the screen.
	 * \param[in] win_flag 		the old window flag.
	 * \param[out] lsys 		container for information about the lsystem, which will be edited depending on the options chosen.
	 * \param[in] tile_font 	large font used in the save sequence button.
	 * \param[in] body_font 	small font used in the save sequence button.
	 * 
     * \return         			the new win_flag that will indicate what the new window should be (default is the same value that came in).
     */

    //click on home button
    if (clickInButton(event, button_list[0])){
		resetLines(lsys);
		resetString(lsys);
    	return 1;
	}

    //click on back button
    if (clickInButton(event, button_list[1])){
		resetLines(lsys);
		resetString(lsys);
    	return win_flag-1;
	}

    //line length decrease
    if (clickInButton(event, button_list[2])){
		//making sure line length is greater than 1
    	if (lsys->length > 1){
    		lsys->length -= 1;
			resetLines(lsys);
			return win_flag;
		}
    }

    //line length increase
    if (clickInButton(event, button_list[3])){
		//setting a limit on the line length
		if (lsys->length < 20){
			lsys->length += 1;
			resetLines(lsys);
			return win_flag;
		}
    }

    //fractal depth decrease
    if (clickInButton(event, button_list[4])){
        if (lsys->iterations > 1){
    	    lsys->iterations -= 1;
			resetLines(lsys);
			resetString(lsys);
			return win_flag;
		}
    }

    //fractal depth increase
    if (clickInButton(event, button_list[5])){
        if (lsys->iterations < lsys->iteration_limit){
    	    lsys->iterations += 1;
			resetLines(lsys);
			resetString(lsys);
			return win_flag;
		}
    }

    //show/hide info button
    if (clickInButton(event, button_list[6])){
    	if (lsys->info_disp_flag)
    		lsys->info_disp_flag = 0;
    	else
    		lsys->info_disp_flag = 1;
    }

    //save img button
    if (clickInButton(event, button_list[7])){
    	printf("img saved\n");
    	imgSave(renderer, lsys);
    }

    //save seq button
    if (clickInButton(event, button_list[8])){
    	printf("img sequence saved\n");
    	sequenceSave(renderer, lsys, title_font, body_font);
    }

    //move fractal
    if (event.button.x > 200){
		free(lsys->line_list);
    	lsys->start.x_pos = event.button.x;
    	lsys->start.y_pos = event.button.y;
    	lsys->remake_lines_flag  = 1;
    }

    //default return value
    return win_flag;
}

void createHomeButton(btn *screen, TTF_Font *font){
	/**
	 * \brief Adds a home button to the input btn array which makes up a screen.
	 *
	 * Every screen will have a home button in the same place that looks the same to
	 * help make the program feel continuous.
	 *
	 * \param[out] screen 	the screen that the home button is to be added to.
     * \param[in] font	 	font for the text on the home button.
	 */

	//initialising variable that will be the same for all home buttons
	SDL_Colour colour = {255, 64, 129, 255};
	coordinate corner = {10, 10};

	//adding the home button as the first element of the array
	addButton(&(screen[0]), corner, 70, 30, colour, font, "Home");
}

void createBackButton(btn *screen, TTF_Font *font){
	/**
	 *\brief Adds a back button to the input screen.
	 *
	 * Every screen will have a back button in the same place that looks the same to
	 * help make the program feel continuous.
	 *
	 * \param[out] screen 	the screen that the back button is to be added to.
     * \param[in] font  	font for the text on the home button.
	 */

	//initialising variables
	SDL_Colour colour = {255, 64, 129, 255};
	coordinate corner = {90, 10};

	//adding back button to the second element of the array
	addButton(&(screen[1]), corner, 70, 30, colour, font, "Back");
}

void addButton(btn *button_array, coordinate pos, int width, int height, SDL_Colour colour, TTF_Font *font, char *text){
	/**
	 * \brief A function that sets the variable for the button structure taken as input.
	 *
	 * \param[out] button 		button that is to hold the information.
	 * \param[in] pos 			position of the top left corner of the button.
	 * \param[in] width 		width of the button.
	 * \param[in] height 		height of the button.
	 * \param[in] colour 		colour of the button.
	 * \param[in] font 			font for the button text.
	 * \param[in] text 			string containing the lable for the button.
	 */

	//adding all the input parameters to the btn structure
	button_array->tl_corner = pos;
	button_array->width = width;
	button_array->height = height;
	button_array->font = font;
	strcpy(button_array->text, text);
	button_array->colour = colour;
}

void drawTextToRenderer(SDL_Renderer *renderer, int x_pos, int y_pos, char *text, TTF_Font *font, int allignment){
    /**
     * \brief Wraps up all of the SDL and SDL_ttf functions required for drawing to the renderer and brings them
     * together into an easy to use function.
     *
     * To draw text to the renderer, the text must be created as a surface, then copied to a texture which 
     * can then be copied to a renderer inside a rectangle that is the same size as the texture. This 
     * function wraps this proces up and also allows a flag to be set for text allignment to make positioning
     * easier for the user.
	 *
     * \param[out] renderer     pointer to the renderer that will hold the output.
     * \param[in] x_pos         x position for the text on the renderer.
     * \param[in] y_pos         y position for the text on the renderer.
     * \param[in] text          character array for the text to be written to the renderer.
     * \param[in] font          the font for the text to be written.
     * \param[in] allignment    an option for thext allignment, 0 is centered, 1 is left alligned and 
     *							2 is right alligned in relation to the input coorinates.
     */

    //initilaising  variables
    int text_w = 0;
    int text_h = 0;
    SDL_Surface *text_surface = NULL;
    SDL_Texture *text_texture = NULL;
    SDL_Colour text_colour = {0, 0, 0, 255};

    //Writing the text to  a surface, then copying that surface to the renderer
    text_surface = TTF_RenderText_Solid(font, text, text_colour);
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_QueryTexture(text_texture, NULL, NULL, &text_w, &text_h);

    //Setting the drawing position acording to allignment flag
    y_pos -= text_h/2;
    if (allignment == 0)
        x_pos -= text_w/2;
    else if (allignment == 3)
        x_pos -= text_w;

    //Coppying the text to the renderer
    SDL_Rect dest_rect = {x_pos, y_pos, text_w, text_h}; 
    SDL_RenderCopy(renderer, text_texture, NULL, &dest_rect); 
  
  	//freeing helper structures
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}

void drawButtonToRenderer(SDL_Renderer *renderer, btn ui_button){
	/**
	 * \brief draws a single button to the renderer
	 *
	 * \param[out] renderer 	The renderer that the button is to be drawn to.
	 * \param[in] ui_button			 	a structure that holds information on the button to be drawn.
	 */

	//initialising variables
	SDL_Rect area = {ui_button.tl_corner.x_pos, ui_button.tl_corner.y_pos, ui_button.width, ui_button.height};
	int x_pos = ui_button.tl_corner.x_pos + ui_button.width/2;
	int y_pos = ui_button.tl_corner.y_pos + ui_button.height/2;

	//drawing button background
	SDL_SetRenderDrawColor(renderer, ui_button.colour.r, ui_button.colour.g, ui_button.colour.b, ui_button.colour.a);
	SDL_RenderFillRect(renderer, &area);
	
	//drawing text over background
	drawTextToRenderer(renderer, x_pos, y_pos, ui_button.text, ui_button.font, 0);
}

void drawAllButtonsToRenderer(SDL_Renderer *renderer, btn *screen, int len){
	/**
	 * \brief Runs through the button list that mekes up a screen and prints each one to the renderer
	 * if it exists.
	 * 
	 * \param[out] renderer 	renderer for buttons to be drawn to.
	 * \param[in] screen 		array contianing buttons to be drawn to the renderer.
     * \param[in] len           number of buttons in the btn array.
	 */

	//initilainsing a counter variable
	int i = 0;

	//running throught the array, drawing each button
	for (i = 0; i < len; i++)
		drawButtonToRenderer(renderer, screen[i]);
}

void drawColourChartToRenderer(SDL_Renderer *renderer, int x_pos, int y_pos){
    /**
     * \brief Draws a colour selection chart to the rendenderer.
     *
     * To crate a colour selection chart for the user to use, red, green and blue
     * variables are initialised, and then cycled through in multiples of 51 in 
     * nested for loops to create a distribution of colours. This creates 6 
     * different values for each colour chanel, resulting in 216 colours to chooe 
     * from. Each colour is then drawn in its own box on the renderer and after 
     * evey 6 blocks a new line is started.
     * 
     * \param[out] renderer     pointer to the renderer that is to be drawn to.
     * \param[in] x_pos         x position of the top left-hand corner of the chart.
     * \param[in] y_pos         y position of the top left_hand corner of the chart.
     */

    //initilaising variables 
    int r = 0, g = 0, b = 0;
    int x = x_pos;
    int y = y_pos;
    int box_width = 40;
    int box_height = 13;
    SDL_Rect box = {x, y, box_width, box_height};
    int i = 1;
    
    //iterating through 6 values of red
    for (r = 0; r <= 255; r += 51){
    	//for each red value 6 green values are used
        for (g = 0; g <= 255; g += 51){
        	//for each green value 6 values of blue are used
            for (b = 0; b <= 255; b += 51, i++){
                SDL_SetRenderDrawColor(renderer, r, g, b, 255);
                SDL_RenderFillRect(renderer, &box);

                // moving along one box width
                box.x += box_width;

                //6 boxes to a line
                if (i%6 == 0){
                    box.y += box_height;
                    box.x = x_pos;
                }
            }
        }
    }
}

void drawInputColourBox(SDL_Renderer *renderer, SDL_Colour colour, int x_pos, int y_pos){
    /**
     * \brief A function for drawing a coloured box to the screen. 
     *
     * Used for displaying the current line and background colours before 
     * drawing the fractal to the renderer.
     * 
     * \param[out] renderer 	renderer for box to be drawn to.
     * \param[in] colour        colour that the box will be.
     * \param[in] x_pos         x position for the top left corner of the box.
     * \param[in] y_pos         y position for the top left corner of the box.
     */

    //initialising variables
    int width = 160;
    int height = 100;
    SDL_Rect box = {x_pos, y_pos, width, height};

    //setting render draw colour to the inpout colour
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);
    
    //drawing rectangle and boarder to the renderer
    SDL_RenderFillRect(renderer, &box);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &box);
}

void drawInfoToRenderer(SDL_Renderer *renderer, int x_pos, int y_pos, lsystem lsys, TTF_Font *title_font, TTF_Font *body_font){
    /**
     * \brief displays information about the lsystem being drawn to the screen.
     * 
     * If the display_info flag is true, then information about the lsystem will be
     * drawn to the renderer as well as the fractal its self. This info will also
     * be present in the saved images if it is on the screen at the time of the save
     * button being pressed.
     *
     * \param[out] renderer      renderer for information to be drawn to.
     * \param[in] x_pos          x coordinate of top left corner of info box.
     * \param[in] y_pos          y coordinate of top left corner of info box.
     * \param[in] lsys           lsystem containing information to be printed.
     * \param[in] title_font     large font.
     * \param[in] body_font      small font.
     */

    //initialising variables
    char depth_string[20];
    char angle_string[40];

    //drawing the lsystem name to the renderer
    drawTextToRenderer(renderer, x_pos, y_pos, lsys.name, title_font, 1);
    
    //writing fractal depth
    y_pos += 40;
    sprintf(depth_string, "Fractal Depth: %d", lsys.iterations);
    drawTextToRenderer(renderer, x_pos, y_pos, depth_string, body_font, 1);

    //writing angle
    y_pos += 30;
    sprintf(angle_string, "angle increment: %f", rtod(lsys.angle));
    drawTextToRenderer(renderer, x_pos, y_pos, angle_string, body_font, 1);

    //drawing rule set for charactwrs which do not map to themselves
    y_pos += 30;
    if (strncmp(lsys.rule_A, "A", 2)){
        char str[] = "A";
        printRule(renderer, x_pos, y_pos, str, lsys.rule_A, body_font);
        y_pos += 20;
    }

    if (strncmp(lsys.rule_B, "B", 2)){
        char str[] = "B";
        printRule(renderer, x_pos, y_pos, str, lsys.rule_B, body_font);
        y_pos += 20;
    }

    if (strncmp(lsys.rule_F, "F", 2)){
        char str[] = "F";
        printRule(renderer, x_pos, y_pos, str, lsys.rule_F, body_font);
        y_pos += 20;
    }

    if (strncmp(lsys.rule_f, "f", 2)){
        char str[] = "f";
        printRule(renderer, x_pos, y_pos, str, lsys.rule_f, body_font);
        y_pos += 20;
    }

    if (strncmp(lsys.rule_X, "X", 2)){
        char str[] = "X";
        printRule(renderer, x_pos, y_pos, str, lsys.rule_X, body_font);
        y_pos += 20;
    }

    if (strncmp(lsys.rule_Y, "Y", 2)){
        char str[] = "Y";
        printRule(renderer, x_pos, y_pos, str, lsys.rule_Y, body_font);
        y_pos += 20;
    }

    if (strncmp(lsys.rule_plus, "+", 2)){
        char str[] = "+";
        printRule(renderer, x_pos, y_pos, str, lsys.rule_plus, body_font);
        y_pos += 20;
    }

    if (strncmp(lsys.rule_minus, "-", 2)){
        char str[] = "-";
        printRule(renderer, x_pos, y_pos, str, lsys.rule_minus, body_font);
        y_pos += 20;
    }

    if (strncmp(lsys.rule_store, "[", 2)){
        char str[] = "[";
        printRule(renderer, x_pos, y_pos, str, lsys.rule_store, body_font);
        y_pos += 20;
    }

    if (strncmp(lsys.rule_pop, "]", 2)){
        char str[] = "]";
        printRule(renderer, x_pos, y_pos, str, lsys.rule_pop, body_font);
        y_pos += 20;
    }
}

void drawLine(SDL_Renderer *renderer, coordinate start, coordinate end, int x_max, int x_min, int y_max, int y_min){
    /**
     * \brief A line drawing function that implements the bresenheim line drawing
     * algorithm to draw a line between two points. 
     * 
     * Based on source code from Eike Anderson, Computing for Graphics level c, lecture 
     * 19, 2015. Edited to work with struct Coordinate as start and end points for line.
     * I felt it was necessary to write my own (as opposed to using th SDL_RederDrawLine() 
     * function) as I could therefor check the pixels being drawn to on a point by point 
     * basis so that I could constrain the drawing to a box on the screen while not having 
     * to miss out whole lines.
     * 
     * \param[out] renderer  	target to be rendered to.
     * \param[in] start        	start point for the line.
     * \param[in] end          	end point of the line.
     * \param[in] x_max         maximum x coordinate to draw to.
     * \param[in] x_min         minimum x coordinate to draw to.
     * \param[in] y_max         maximum y coordinate to draw to.
     * \param[in] y_min         minimum y coordinate to draw to.
     */

    //initialising variables
    //start and end positions are stored as doubles to reducing rounding errors during calulation
    //they are rounded here to descrete values to be drawn to specific pixles 
    int x0 = round(start.x_pos);
    int y0 = round(start.y_pos);

    int xn = round(end.x_pos);
    int yn = round(end.y_pos);

    int dx = abs(xn-x0);
    int sx = x0<xn ? 1 : -1;

    int dy = abs(yn-y0);
    int sy = y0<yn ? 1 : -1;

    int error = (dx>dy ? dx : -dy)/2;
    int e2;

    while (1){

        //only draws point within min and max ranges.
        if (x0 > x_min && x0 < x_max && y0 > y_min && y0 < y_max)
            SDL_RenderDrawPoint(renderer ,x0, y0);

        //breaks if the end of the line has been reached
        if (x0 == xn && y0 == yn)
            break;

        e2 = error;
        if (e2 > -dx){
            error -= dy;
            x0 += sx;
        }
        
        if (e2 < dy){
            error += dx;
            y0 += sy;
        }
    }
}

void drawFractal(SDL_Renderer *renderer, int length, line *line_list, SDL_Colour line_colour){
    /**
     * \brief Draws the fractal storred as int line_list which is of length 'length'
     * 
     * \param[out] renderer  	renderer to be drawn to.
     * \param[in] length        number of items in the line list.
     * \param[in] line_list     a list of coordinate pairs whcih define the lines that need to be drawn.
     * \param[in] line_colour  	colour for the lines to be drawn.
     */

    //iitialising drawing variables
    int i = 0;
    int x_max = 1200;
    int x_min= 200;
    int y_max = 1000;
    int y_min = 0;

   	//setting render draw colour to the line coloue stored in the L-System
    SDL_SetRenderDrawColor(renderer, line_colour.r, line_colour.g, line_colour.b, line_colour.a);

    //running through the line list and drawing them one by one.
    for (i = 0; i < length; i++){
        drawLine(renderer, line_list[i].start, line_list[i].end, x_max, x_min, y_max, y_min);
    }
}

void printRule(SDL_Renderer *renderer, int x_pos, int y_pos, char *original, char *replacement, TTF_Font *font){
    /**
     * \brief Formats and writes out the rule for the input character.
     *
     * For printing the rules to the drawing screen, the strings needed to be
     * specifically formatted and this function wraps up that formatting.
     * 
     * \param[out] renderer  	renderer for the rule to be written to.
     * \param[in] x_pos         x position for the top left hand corner of the text.
     * \param[in] y_pos         y position of the top left hand corner of the text.
     * \param[in] original      the character that is to be replaced in a string format.
     * \param[in] replacement   the replacement string for that character.
     * \param[in] body_font     the font to be used.
     */

    //initialising variables
    char text[45]= {};

    //formating output
    strcat(text, original);
    strcat(text, " -> ");
    strcat(text, replacement);

    //drawing output
    drawTextToRenderer(renderer, x_pos, y_pos, text, font, 1);
}

int clickInButton(SDL_Event event, btn screen_button){
	/**
	 * \brief checks to see if a click happened inside a specific button.
	 * 
	 * Uses the button to calulate upper and lower boundaries for x and y positions that
	 * fall inside the button and then gets the click event data and compares the position 
	 * to these limits. Includes a safety check to make sure that the event is a click event.
	 *
	 * \param[in] event 			the click event in question.
	 * \param[in] screen_button		the button that contains the information on the position of the window.
	 * 
	 * \return 				 		true (1) if click is inside the button, fase (0) if not.
	 */

	//safety chek on event type before anthing else is done
	if (event.type != SDL_MOUSEBUTTONDOWN)
		return 0;

	//extracting event data and initialisng variables
	int x = event.button.x;
	int y = event.button.y;
	int upper_height = screen_button.tl_corner.y_pos + screen_button.height;
	int lower_height = screen_button.tl_corner.y_pos;
	int upper_width = screen_button.tl_corner.x_pos + screen_button.width;
	int lower_width = screen_button.tl_corner.x_pos;

	//checking to see if the click falls inside the boundaries
	if (x > lower_width && x < upper_width && y > lower_height && y < upper_height){
		return 1;
	}
	
	//return 0 if no return value has been reached (default to outside the button if something went wrong)
	return 0;
}

SDL_Colour getPixelColour(SDL_Renderer *renderer, int win_width, int win_height, int x_pos, int y_pos){
    /**
     * \brief Finds the pixel colour on the renderer of the point given by x_pos, y_pos. 
     * 
     * Based on source code from Eike Anderson, Computing for Graphics level c, 
     * 2015. Edited to work with struct SDL_Colour. It works by firstly ckecking 
     * to make sure that the click was inside the window, then, if it was, a 
     * helper surface is created and then reformatted to take the information 
     * retrieved from the renderer using SDL_RenderReadPixels. The RGB values from
     * this data is then copied into the p_colour variable that is then returned.
	 *
     * \param[in] renderer  	renderer that holds the pixel information.
     * \param[in] win_width     width of the window (used to make sure the pixel piosition exists).
     * \param[in] win_height    height of the window (used to make sure the pixel position exists).
     * \param[in] x_pos         x coordinate of the pixel being looked at.
     * \param[in] y_pos         y coordinate of the pixel beign looked at.
	 *
     * \return       			the colour of the pixel in rgba format.
     */

    //initilaising variables
    SDL_Colour p_colour = {0, 0, 0, 0};
    Uint32 pixels[10];

    //Making sure point exists.
    if(x_pos>=0 && x_pos<win_width && y_pos>=0 && y_pos<win_height){

    	//initialising variables
        SDL_Rect point = {x_pos, y_pos, 1, 1};
        //Creating helper surface.
        SDL_Surface *s = SDL_CreateRGBSurface(0,5,5,32,0,0,0,0);
        //reformatting helper surface
        SDL_Surface *ns = SDL_ConvertSurfaceFormat(s,SDL_PIXELFORMAT_ARGB8888,0);

        //if pixel is read sucessfully, then the rgb data is copied into the SDL_Colour structure
        if(!SDL_RenderReadPixels(renderer, &point, SDL_PIXELFORMAT_ARGB8888, pixels,5))
            SDL_GetRGB(pixels[0], ns->format, &(p_colour.r), &(p_colour.g), &(p_colour.b));

        //freeing surfaces
        SDL_FreeSurface(s);
        SDL_FreeSurface(ns);
    }
    
    //return the colour at the point clicked on
    return p_colour;
}

void drawBG(SDL_Renderer *renderer){
    /**
     * \brief Draws background to renderer.
     * 
     * clears the background to a single colour and then draws
     * a menu bar in a different colour to the top of the renderer.
     * 
     * \param[out] renderer 		renderer for the bakkground to be drawn to
     */

    //initialising variables
    SDL_Rect menu_bar = {0, 0, 1200, 50};

    //drawing background
    SDL_SetRenderDrawColor(renderer, 197, 202, 235, 255);
    SDL_RenderClear(renderer);

    //drawing menu bar
    SDL_SetRenderDrawColor(renderer, 48, 63, 159, 255);
    SDL_RenderFillRect(renderer, &menu_bar);
}

void imgSave(SDL_Renderer *renderer, lsystem *lsys){
	/**
	 * \brief Saves the fractal image as a single bmp image.
	 *
	 * Copies the drawing region of the renderer to a surface to be saved by the
	 * SDL_SaveBMP() function.
	 * 
	 * \param[in] renderer 		renderer that contains onformation to be copied
	 * \param[in] lsys 			the structure that contains the information for naming
	 */

	//initialising variables
	char name[100];
	time_t current_time = time(NULL);
	char *base_time = ctime(&current_time);
	SDL_Surface *out = SDL_CreateRGBSurface(0, 1000, 800, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_Rect area = {200, 0, 1000, 800};

	//creating name for the save file
	sprintf(name, "saves/%s_%s.bmp", lsys->name, base_time);

	//copy renderer to surface
	SDL_RenderReadPixels(renderer, &area, SDL_PIXELFORMAT_ARGB8888, out->pixels, out->pitch);

	//save surface as .bmp
	SDL_SaveBMP(out, name);

	//freeing surface
	SDL_FreeSurface(out);
}

void sequenceSave(SDL_Renderer *renderer, lsystem *lsys, TTF_Font *title_font, TTF_Font *body_font){
	/**
	 * \brief Saves the fractal as a sequence of bmp images that show the fractal being drawn line by line.
	 * 
	 * clears the renderer before iteratively drawing lines to it, then converting to surface and saving.
	 * The program splits up the lines being drawn so that there is a limit of 100 frames that can be saved.
	 * this keeps the program running quickly but limits what the user can do with the output. I decided on 
	 * doing it this way because the save sequence is error porne and slow (moving the window while saving
	 * off a sequence causes artifacts).
	 * 
	 * \param[in] window 		window that is being drawn to
	 * \param[in] renderer 		renderer being drawn to and saved
	 * \param[in] lsys 			structure that contians information for drawing img sequence.
	 * \param[in] title_font 	font for title text
	 * \param[in] body_font 	font for main body text
	 */

	//initialising variables
	SDL_Surface *out = SDL_CreateRGBSurface(0, 1000, 800, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	char name[100];
	time_t current_time = time(NULL);
	char *base_time = ctime(&current_time);
	SDL_Rect bg = {200, 0, 1000, 1000};
	int i = 0;

	//clearing renderer drawing screen
    SDL_SetRenderDrawColor(renderer, lsys->bg_colour.r, lsys->bg_colour.g, lsys->bg_colour.b, lsys->bg_colour.a);
    SDL_RenderFillRect(renderer, &bg);

    //drawing info if correct flag is shown
    if (lsys->info_disp_flag){
        drawInfoToRenderer(renderer, 220, 20, *lsys, title_font, body_font);
    }

	//drawing and saving as lines are drawn
	//the number of lines per frame is dependant on the numbe of lines in the line list
	//so that there is an upper limit to the number of frames being saved
	lsys->seq_file_num = 1;
	SDL_SetRenderDrawColor(renderer, lsys->ln_colour.r, lsys->ln_colour.g, lsys->ln_colour.b, lsys->ln_colour.a);
	
	for (i = 0; i < lsys->line_list_length; i++){
		sprintf(name, "saves/fractal_seq_%s_%03d.bmp", base_time, lsys->seq_file_num);
		
		drawLine(renderer, lsys->line_list[i].start, lsys->line_list[i].end, 1200, 200, 800, 0);

		if (i % (lsys->line_list_length/200+ 1) == 0 || i == lsys->line_list_length-1){

			SDL_RenderReadPixels(renderer, &bg, SDL_PIXELFORMAT_ARGB8888, out->pixels, out->pitch);
			SDL_SaveBMP(out, name);
			printf("%d of up to 201 frames saved.\n", lsys->seq_file_num);
			lsys->seq_file_num += 1;
		}
	}
	
	//freeing surface
	SDL_FreeSurface(out);
}
