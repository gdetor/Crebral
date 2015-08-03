#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/* Header files with a description of contents used */

#include <cvode/cvode.h>             /* prototypes for CVODE fcts., consts. */
#include <nvector/nvector_serial.h>  /* serial N_Vector types, fcts., macros */
#include <sundials/sundials_types.h> /* definition of type realtype */

/* User-defined vector and matrix accessor macros: Ith */

/* These macros are defined in order to write code which exactly matches
   the mathematical problem description.

   Ith(v,i) references the ith component of the vector v, where i is in
   the range [1..NEQ] and NEQ is defined below. The Ith macro is defined
   using the N_VIth macro in nvector.h. N_VIth numbers the components of
   a vector starting from 0.
*/

#define Ith(v,i)    NV_Ith_S(v,i-1)       /* Ith numbers components 1..NEQ */


/* Problem Constants */

#define NEQ   4                /* number of equations  */
#define Y1    RCONST(0.03)      /* initial y components */
#define Y2    RCONST(0.02)
#define Y3    RCONST(0.01)
#define Y4    RCONST(0.03)
#define RTOL  RCONST(1.0e-4)   /* scalar relative tolerance            */
#define ATOL1 RCONST(1.0e-8)   /* vector absolute tolerance components */
#define ATOL2 RCONST(1.0e-8)
#define T0    RCONST(0.0)      /* initial time           */
#define T1    RCONST(0.3)      /* first output time      */
#define TF    RCONST(160.0)    /* output time factor     */
#define TOTPOINTS   160       /* number of output times */
#define DTOUT RCONST(0.08)    /* output time increment     */
#define NOUT  5000            /* number of output times    */



typedef struct Parameters{
    int numNeurons;
    double dt;
} parameters;


typedef struct Neuron{
    int id;
    int numPreSyn;
    double *V;
    double *N;
    double *Z;
    double *S;
    double *W;
    double *Iext;
    double E;
    double coord[3];
    int *pre_id;
    N_Vector y;
} neuron;


typedef struct {
    double Vold;
    double Ie;
    double Is;
    double tau;
} *UserData;


int check_flag(void *, char *, int);


/* Memory allocation functions */
void allocate(neuron **, int, int);
void deallocate(neuron **, int, int);


/* Mathematical (Model) Functions declarations*/
double randm(double, double);
double alpha(double, double, double);
double f_inf(double, double, double, double);
int f(realtype, N_Vector, N_Vector, void *);


/* Auxiliary Functions declerations */
int readFromFileParams(char *);
int write2file(char *, neuron *, int, int);
int writeVector2File(char *, double *, int);
void printParemeters(parameters);


/* Initialization functions declarations */
void initializeParams(neuron **, int);
int initialization(neuron **, int, int);


/* Main simulation */
int simulation(parameters);

#endif  /* !COMMON_H */
