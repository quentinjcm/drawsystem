#ifndef _TURTLE_H_
#define _TURTLE_H_

/*
 * Main function for converting a string to a line list.
 */
int stringToTurtle(lsystem *lsys);

/*
 * Saves the turtle position to the top of a turtle stack, implemented as a linked list.
 */
void savePos(turtle_state **root, turtle_state current_turtle);

/*
 * Pops the last stored position from the turtle stack.
 */
void popPos(turtle_state **root, turtle_state *current_turtle);

/*
 * Adds a pair of coordinates to the line list and updates the turtles position.
 */
int penDownLine(turtle_state *current_turtle, int length, int line_list_pos, lsystem *lsys);

/*
 * Updates the position of the turtle to the end of a line without adding it to the line list.
 */
void penUpLine(turtle_state *current_turtle, int length);

/*
 * Counts the number of line drawing characters in an lsystem string.
 */
int countMoves(char *string);

#endif
