#include "common.h"

/* Allocate memory for all the neurons and their components*/
void allocate(neuron **nrn, int numNeurons, int simTime)
{
    int i;

    for(i = 0; i < numNeurons; ++i){
        (*nrn)[i].V = (double *)malloc(simTime*sizeof(double));
        (*nrn)[i].Z = (double *)malloc(simTime*sizeof(double));
        (*nrn)[i].N = (double *)malloc(simTime*sizeof(double));
        (*nrn)[i].S = (double *)malloc(simTime*sizeof(double));
        (*nrn)[i].Iext = (double *)malloc(simTime*sizeof(double));
        (*nrn)[i].pre_id = (int *)malloc(sizeof(int));
        (*nrn)[i].pre_id[0] = 0;
        (*nrn)[i].W = (double *)malloc(sizeof(double));
        (*nrn)[i].W[0] = 0.0;
    }
}

/* Deallocate memory */
void deallocate(neuron **nrn, int numNeurons, int simTime)
{
    int i;

    for(i = 0; i < numNeurons; ++i){
        free((*nrn)[i].V);
        (*nrn)[i].V = NULL;

        free((*nrn)[i].Z);
        (*nrn)[i].Z = NULL;

        free((*nrn)[i].N);
        (*nrn)[i].N = NULL;

        free((*nrn)[i].S);
        (*nrn)[i].S = NULL;

        free((*nrn)[i].Iext);
        (*nrn)[i].Iext = NULL;

        free((*nrn)[i].W);
        (*nrn)[i].W = NULL;

        free((*nrn)[i].pre_id);
        (*nrn)[i].pre_id = NULL;
    }
}
