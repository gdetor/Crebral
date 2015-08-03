#include "common.h"


double randm(double min, double max)
{
    return (max + rand() / (RAND_MAX / (min - max + 1) + 1));
}


/* Read from file (parameters) */
int readFromFileParams(char *filename)
{
    return 0;
}


/* Write to a file */
int write2file(char *filename, neuron *nrn, int numNeurons, int simTime)
{
    int i, j;
    FILE *fp;

    if(!(fp = fopen(filename, "w")))
        goto fail;

    for(i = 0; i < numNeurons; ++i){
        for(j = 0; j < simTime; ++j){
            fprintf(fp, "%f ", nrn[i].V[j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    return 0;

fail:
    printf("The file cannot be created!\n");
    exit(-1);
}


int writeVector2File(char *filename, double *x, int size)
{
    int i;
    FILE *fp;

    if (!(fp = fopen(filename, "w"))){
        goto fail;
    }

    for(i = 0; i < size; ++i)
        fprintf(fp, "%lf \n", x[i]);

    fclose(fp);
    return 0;

fail:
    printf("File %s cannot be opened!\n", filename);
    exit(-1);
}


/*
 * Check function return value...
 *   opt == 0 means SUNDIALS function allocates memory so check if
 *            returned NULL pointer
 *   opt == 1 means SUNDIALS function returns a flag so check if
 *            flag >= 0
 *   opt == 2 means function allocates memory so check if returned
 *            NULL pointer 
 */
int check_flag(void *flagvalue, char *funcname, int opt)
{
    int *errflag;

    /* Check if SUNDIALS function returned NULL pointer - no memory allocated*/
    if (opt == 0 && flagvalue == NULL) {
        fprintf(stderr, "\nSUNDIALS_ERROR: %s() failed - returned NULL pointer\n\n",
                funcname);
        return 1; 
    }

    /* Check if flag < 0 */
    else if (opt == 1) {
        errflag = (int *) flagvalue;
        if (*errflag < 0) {
            fprintf(stderr, "\nSUNDIALS_ERROR: %s() failed with flag = %d\n\n",
                    funcname, *errflag);
            return 1; 
        }
    }

    /* Check if function returned NULL pointer - no memory allocated */
    else if (opt == 2 && flagvalue == NULL) {
        fprintf(stderr, "\nMEMORY_ERROR: %s() failed - returned NULL pointer\n\n",
                funcname);
        return 1; 
    }

    return 0;
}


void printParemeters(parameters pms)
{
    printf("%-30s", "Total number of neurons");
    printf("%d\n", pms.numNeurons);

    printf("%-30s", "Simulation time");
    printf("%f\n", pms.dt * TOTPOINTS);
}

