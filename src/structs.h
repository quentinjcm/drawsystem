

#ifndef _STRUCTS_H_
#define _STRUCTS_H_

/**
 * A coordinate structure to hold an (x, y) coordinate pair.
 */
typedef struct coordinate{
    /** \brief x positon of the coordinate pair.*/
	double x_pos; 
    /** \brief y position of the coordinate pair.*/
	double y_pos; 
}coordinate;


/**
 * A line structure that holds a coordinate pair that defines a line between two points
 */
typedef struct line{
    /** \brief Coordinate sructure for the start of the line.*/
	coordinate start;
    /** \brief Coordinate structure for the end of the line.*/
	coordinate end;
}line;


/**
 * A structure that stores information on a turtle, including a pointer to the next
 * turtle for the creation of a linked list that will be used to create a turtle stack.
 */
typedef struct turtle_state{
    /** \brief Current position of the turtle.*/
	coordinate pos;
    /** \brief Heading of the turtle (stored as radians).*/
	double heading;
    /** \brief Pointer to the next element in a linked list.*/
	struct turtle_state *next;
}turtle_state;


/**
 * A structure for holding all the information required for creating a button on the screen.
 */
typedef struct btn{
    /** \brief Coordinate of the top left corner of the box.*/
	coordinate tl_corner;
    /** \brief Width of the button.*/
	int width;
    /** \brief Height of the button.*/
	int height;
    /** \brief A font to be used for the text lable on the button.*/
	TTF_Font *font;
    /** \brief A characer string to hold the buttons lable.*/
	char text[40];
    /** \brief The colour of the button.*/
	SDL_Colour colour;
}btn;


/**
 * A structure that holds all of the information required for the creation and drawing of an lsystem
 */
typedef struct lsystem{
    /** \brief A character string for the name of the L-System.*/
    char name[40];
    /** \brief A haracter array for the starting string (axiom) of the L-System.*/
    char axiom[40];
    /** \brief Background colour for the drawing screen.*/
    SDL_Colour bg_colour;
    /** \brief Line colour for the drawing screen.*/
    SDL_Colour ln_colour;
    /** \brief Starting point for the turtle drawing the L-System.*/
    coordinate start;
    /** \brief Angle for the turtle to turn through each time the angle is increased or decreaseed.*/
    double angle;
    /** \brief Length of each individual line to be drawn.*/
    int length;
    /** \brief Fractal depth of the L-System (how many times the character replacement is performed).*/
    int iterations;
    /** \brief A maximum fractal depth which can be different for different L-Systems so that the program is not drawing too much and stays fast.*/
    int iteration_limit;
    /** \brief A counter that counts how many images have been saved so that conflicting names are not produced in a single run of the program.*/
    int img_file_num;
    /** \brief A counter that counts how many images have been saved to a sequence so that conflicting names are not produced in a single run of the program.*/
    int seq_file_num;

    //containers
    /** \brief A pointer to the L-System string to be drawn.*/
    char *string;
    /** \brief A opinter to an array of lines that are calculated using the string.*/
    line *line_list;
    /** \brief A counter that recrds the length of the line list.*/
    int line_list_length;

    //flags
    /** \brief A flag which tells the program to recalculate the line list.*/
    int remake_lines_flag;
    /** \brief A flag which tells the program to recalculate the string.*/
    int remake_string_flag;
    /** \brief A flag which tells the program to display the L-System info to the screen.*/
    int info_disp_flag;

    //rules
    /** \brief character replacement string for the 'A' chracter.*/
    char rule_A[40];
    /** \brief character replacement string for the 'B' chracter.*/
    char rule_B[40];
    /** \brief character replacement string for the 'F' chracter.*/
    char rule_F[40];
    /** \brief character replacement string for the 'f' chracter.*/
    char rule_f[40];
    /** \brief character replacement string for the 'X' chracter.*/
    char rule_X[40];
    /** \brief character replacement string for the 'Y' chracter.*/
    char rule_Y[40];
    /** \brief character replacement string for the '+' chracter.*/
    char rule_plus[40];
    /** \brief character replacement string for the '-' chracter.*/
    char rule_minus[40];
    /** \brief character replacement string for the '[' chracter.*/
    char rule_store[40];
    /** \brief character replacement string for the ']' chracter.*/
    char rule_pop[40];
}lsystem;

/*
 * Initialisation function to be used whenever an L-System structure is declared.
 */
void structInitLsystem(lsystem *lsys);

/*
 * Initialisation function to be used whenever an coordinate structure is declared.
 */
void structInitCoord(coordinate *coord);

/*
 * Initialisation function to be used whenever a line structure is declared.
 */
void structInitLine(line *ln);

/*
 * Initialisation function to be used whenever a btn structure is declared.
 */
void structInitBtn(btn *ui_button);

/*
 * Initialisation function to be used whenever an turtle structure is declared.
 */
void structInitTurtleState(turtle_state *turtle);

#endif
