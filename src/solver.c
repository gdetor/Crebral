#include "common.h"


/* Simulation of the network */
int simulation(parameters pms)
{
    int t, i, k, flag, iout;
    int simTime;
    double tmp, *T;

    time_t t0, t1;

    void *cvode_mem;

    N_Vector y, abstol;
    realtype reltol, time, tout;

    neuron *nrn;
    UserData data;

    simTime = NOUT;
    nrn = (neuron *)malloc(pms.numNeurons*sizeof(neuron));
    data = (UserData)malloc(sizeof(* data));
    T = (double *) malloc(simTime*sizeof(double));

    y = abstol = NULL;
    cvode_mem = NULL;
    
    /* Print the very basic parameters */
    printParemeters(pms);
    
    /* Initialize parameters */
    initializeParams(&nrn, pms.numNeurons);

    /* Allocate memory */
    allocate(&nrn, pms.numNeurons, simTime);
    printf("%-30s", "Memory allocated");
    printf("OK\n");

    /* Initial conditions */
    initialization(&nrn, pms.numNeurons, simTime);

    /* Create serial vector of length NEQ for I.C. and abstol */
    y = N_VNew_Serial(NEQ);
    if (check_flag((void *)y, "N_VNew_Serial", 0)) return(1);
    for(i = 0; i < pms.numNeurons; ++i){
        nrn[i].y = N_VNew_Serial(NEQ);
    }

    abstol = N_VNew_Serial(NEQ);
    if (check_flag((void *)abstol, "N_VNew_Serial", 0)) return(1);

    /* Call CVodeCreate to create the solver memory and specify the 
     * Adams integration scheme */
    cvode_mem = CVodeCreate(CV_ADAMS, CV_FUNCTIONAL);
    if (check_flag((void *)cvode_mem, "CVodeCreate", 0)) return(1);

    t0 = clock();
    tout = pms.dt;
    for(iout=1, tout=T1; iout <= NOUT; iout++, tout += DTOUT){
        t = iout;

        for(i = 0; i < pms.numNeurons; ++i){
            /* Set the scalar relative tolerance */
            reltol = RTOL;

            /* Set the vector absolute tolerance */
            Ith(abstol,1) = ATOL1;
            Ith(abstol,2) = ATOL2;
            Ith(abstol,3) = ATOL2;
            Ith(abstol,4) = ATOL2;

            /* Initialize y */
            if(t == 1){
                Ith(nrn[i].y,1) = Y1;
                Ith(nrn[i].y,2) = Y2;
                Ith(nrn[i].y,3) = Y3;
                Ith(nrn[i].y,4) = Y3;
            
                /* Call CVodeInit to initialize the integrator memory and specify the
                 * user's right hand side function in y'=f(t,y), the inital time T0,
                 * and the initial dependent variable vector y. */
                flag = CVodeInit(cvode_mem, f, T0, nrn[i].y);
                if (check_flag(&flag, "CVodeInit", 1)) return(1);

                /* Call CVodeSVtolerances to specify the scalar relative tolerance
                 * and vector absolute tolerances */
                flag = CVodeSVtolerances(cvode_mem, reltol, abstol);
                if (check_flag(&flag, "CVodeSVtolerances", 1)) return(1);

                if(i){
                    flag = CVodeReInit(cvode_mem, T0, nrn[i].y);
                     if (check_flag(&flag, "CVodeReInit", 1)) return(1);
                }
            }

            if(t != 1){
                flag = CVodeReInit(cvode_mem, tout-DTOUT, nrn[i].y);
                if (check_flag(&flag, "CVodeReInit", 1)) return(1);
            }

            tmp = 0.0;
            for(k = 0; k < nrn[i].numPreSyn; ++k){
                tmp += nrn[i].W[k] * nrn[k].S[t-1];
            }
                
            /* data->Is = tmp; */
            data->Is = tmp * (nrn[i].V[t-1] - nrn[i].E);
            data->Ie = nrn[i].Iext[t-1];
            if (i == 0) printf("%f  %f   %f\n", data->Is, data->Ie, data->Is+data->Ie);
            if (i == 0) data->tau = 5;
            if (i == 1) data->tau = 10;
            data->Vold = nrn[i].V[t-1];

            flag = CVodeSetUserData(cvode_mem, data);
            if (check_flag(&flag, "CVodeSetUserData", 1)) return 1;

            if (CVode(cvode_mem, tout, nrn[i].y, &time, CV_NORMAL) < 0) {
                fprintf(stderr, "Error in CVode: %d\n", flag);
                return -1;
            }
            nrn[i].V[t] = Ith(nrn[i].y,1);
            nrn[i].N[t] = Ith(nrn[i].y,2);
            nrn[i].Z[t] = Ith(nrn[i].y,3);
            nrn[i].S[t] = Ith(nrn[i].y,4);
            T[t] = time;
        }
    }

    t1 = clock();
    printf("%-30s", "Duration of simulation");
    printf("%f\n", (double)(t1-t0)/CLOCKS_PER_SEC);

    flag = write2file("solution.dat", nrn, pms.numNeurons, simTime);
    flag = writeVector2File("time.dat", T, simTime);

    /* Free y and abstol vectors */
    N_VDestroy_Serial(y);
    N_VDestroy_Serial(abstol);

    for(i = 0; i < pms.numNeurons; ++i)
        free(nrn[i].y);

    /* Free integrator memory */
    CVodeFree(&cvode_mem);

    /* Memory deallocation */
    free(data);
    data = NULL;
    deallocate(&nrn, pms.numNeurons, simTime);
    free(nrn);
    nrn = NULL;
    free(T);
    T = NULL;
    printf("%-30s", "Memory dealloced"); printf("Ok\n");


    return 0;
}
