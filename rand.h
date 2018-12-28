/* Declaration for random number related variables and routines */
# ifndef _RAND_H
# define _RAND_H


/* Variable declarations for the random number generator */

/* Function declarations for the random number generator */
void randomize(double seed);
void warmup_random (double seed);
void advance_random ();
double randomperc();
int rnd (int low, int high);
double rndreal ( double low, double high);
void initrandomnormaldeviate();
double noise (double mu, double sigma);
double randomnormaldeviate();

# endif
