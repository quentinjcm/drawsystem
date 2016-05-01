#ifndef _LSYS_H_
#define _LSYS_H_


/*************************************
*    L-System creation functions     *
*************************************/

/*
 * \brief performs a single iteration of character replacement
 */
void iteration(lsystem *lsys);

/*
 * \brief makes the final string from rules defined in the lsystem
 */
int makeString(lsystem *lsys);

/*
 * \brief fills the lsystem with default starting values
 */
void initLsystem(lsystem *lsys);

/*
 * \brief resets the lsystem parameters for a new set of rules ect
 */
void resetLsystem(lsystem *lsys);

/*
 * \brief degrees to radians conversion function
 */
double dtor(double degrees);

/*
 * \brief radians to degrees conversion function
 */
double rtod(double radians);

/*
 * \brief frees and sets flag for the lsystem string
 */
void resetString(lsystem* lsys);

/*
 * \brief frees and sets flag for the lsystem line list
 */
void resetLines(lsystem *lsys);




/*************************************
*   Pre Defined Lsystem Rule Sets    *
*************************************/

/*
  * \brief rule set for a sierpinski triange
  */
void sierpinski(lsystem *lsys);

/*
 * \brief rule set for a dragon curve
 */
void dragon(lsystem *lsys);

/*
 * \brief rule set for a plant fractal
 */
void plant1(lsystem *lsys);

/*
 * \brief rule set for a plant fractal
 */
void plant2(lsystem *lsys);

/*
 * \brief rule set for islands and lakes fractal
 */
void islands(lsystem *lsys);

/*
 * \brief rule set for a koch snowflake
 */
void snowflake(lsystem *lsys);

/*
 * \brief rule set for a variation of a quadratic koch curve
 */
void quadKoch(lsystem *lsys);

/*
 * \brief rule set for a variation of a gosper curve
 */
void gosper(lsystem *lsys);



#endif
