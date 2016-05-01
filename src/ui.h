#ifndef _UI_H_
#define _UI_H_

#define TITLE_SIZE 30
#define BODY_SIZE 16


/*************************************
*       General UI Functions         *
*************************************/

/*
 * Adds a home button to the screens list of buttons.
 */
void createHomeButton(btn *screen, TTF_Font *font);

/*
 * Adds a back button the the screens list of buttons.
 */
void createBackButton(btn *screen, TTF_Font *font);

/*
 * Sets all buttons to not exist so that they can be turned on as they are added.
 */
void initScreen(btn *screen, int length);

/*
 * Adds a button the the button list
 */
void addButton(btn *button, coordinate pos, int width, int height, SDL_Colour colour, TTF_Font *font, char *text);

/*
 * Draws text to the renderer
 */
void drawTextToRenderer(SDL_Renderer *renderer, int x_pos, int y_pos, char *text, TTF_Font *font, int allignment);

/*
 * Draws a single button to the renderer
 */
void drawButtonToRenderer(SDL_Renderer *renderer, btn info);

/*
 * Draws all button in the button array of length len to the renderer
 */ 
void drawAllButtonsToRenderer(SDL_Renderer *renderer, btn *screen, int len);

/*
 * Draws a colour chart to the renderer for colour picking
 */
void drawColourChartToRenderer(SDL_Renderer *renderer, int x_pos, int y_pos);

/*
 * Draws a bounded box of the input colour to the specified position on the renderer
 */
void drawInputColourBox(SDL_Renderer *renderer, SDL_Colour colour, int x_pos, int y_pos);

/*
 * Draws lsystem information to renderer
 */
void drawInfoToRenderer(SDL_Renderer *renderer, int x_pos, int y_pos, lsystem lsys, TTF_Font *title_font, TTF_Font *body_font);

/*
 * Draws a line to the renderer
 */
void drawLine(SDL_Renderer *renderer, coordinate start, coordinate end, int x_max, int x_min, int y_max, int y_min);

/*
 * Draws the shape defined in line_list to the renderer
 */
void drawFractal(SDL_Renderer *renderer, int length, line *line_list, SDL_Colour line_colour);

/*
 * Prints a single rule to the renderer
 */
void printRule(SDL_Renderer *renderer, int x_pos, int y_pos, char *original, char *replacement, TTF_Font *font);

/*
 * Returns true if the click event passed to it happens inside the button.
 */
int clickInButton(SDL_Event event, btn ui_button);

/*
 * Returns the colour of the inputed point on the renderer
 */
SDL_Colour getPixelColour(SDL_Renderer *renderer, int win_width, int win_height, int x_pos, int y_pos);

/*
 * Draws the background to the renderer
 */
void drawBG(SDL_Renderer *renderer);


/*************************************
*       Specific UI Functions        *
*************************************/

/*
 * Defines all the buttons that will appear on the home screen.
 */
void createHomeScreenButtons(btn *screen_buttons, TTF_Font *font);

/*
 * Defines all the buttons that will appear on the options screen.
 */
void createOptionsScreenButtons(btn *screen_buttons, TTF_Font *font);

/*
 * Defines all of the buttons that will appear on the drawing screen.
 */
void createDrawScreenButtons(btn *screen_buttons, TTF_Font *title_font, TTF_Font *body_font);

/*
 * Draws the home screen to the renderer
 */
void drawHomeScreen(SDL_Renderer *renderer, btn *screen_buttons, TTF_Font *title_font, TTF_Font *body_font);

/*
 * Draws the options screen to the renderer
 */
void drawOptionsScreen(SDL_Renderer *renderer, btn *screen_buttons, TTF_Font *title_font, TTF_Font *body_font, lsystem *lsys);

/*
 * Draws the drawing screen to the renderer
 */
void drawDrawingScreen(SDL_Renderer *renderer, btn *screen_buttons, TTF_Font *title_font, TTF_Font *body_font, lsystem *lsys);

/*
 * Handles a click while the home screen is being displayed
 */
int homeScreenClick(SDL_Event event, btn *button_list, int win_flag);

/*
 * Handles a click while the options screen is being displayed
 */
int optionsScreenClick(SDL_Renderer *renderer, SDL_Event event, btn *button_list, int win_flag, lsystem *lsys);

/*
 * Handles a click while the draw screen is beign displayed
 */
int drawScreenClick(SDL_Renderer *renderer, SDL_Event event, btn *button_list, int win_flag, lsystem *lsys, TTF_Font *title_font, TTF_Font *body_font);


/*************************************
*           save functions           *
*************************************/

/*
 * Saves the fractal viewing window as .bmp file
 */
void imgSave(SDL_Renderer *renderer, lsystem *lsys);

/*
 * Saves the fractal as a sequence of up to 100 bmp files
 */
void sequenceSave(SDL_Renderer *renderer, lsystem *lsys, TTF_Font *title_font, TTF_Font *body_font);


#endif
