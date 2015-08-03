#include "common.h"


double alpha(double x, double theta, double sigma)
{
    return 1.0/(1.0 + exp(-(x - theta)/sigma));
}


double f_inf(double x, double y, double neg, double pos)
{
    if (x < y)
        return neg * (x - y);
    else
        return pos * (x - y);
}


/*
 * f routine. Compute function f(t,y). 
 */
int f(realtype t, N_Vector y, N_Vector ydot, void *user_data)
{
    realtype y1, y2, y3, y4;
    UserData data;
    double k = 1.0;
    double n0 = -1.1, eps_n = .02, eps_z = .0001;
    double k_n_neg = 0.9, k_n_pos = 7.;
    double k_z_neg = 0.0, k_z_pos = 100.0;
    double V0 = -.5, V1 = -1.2;

    data = (UserData) user_data;

    y1 = Ith(y, 1); y2 = Ith(y, 2); y3 = Ith(y, 3); y4 = Ith(y, 4);

    Ith(ydot,1) = k * y1 - pow(y1, 3)/3. - pow(y2 + n0, 2) + 
        data->Ie + data->Is - y3;
    Ith(ydot,2) = eps_n * (f_inf(y1, V0, k_n_neg, k_n_pos) - y2);
    Ith(ydot,3) = eps_z * (f_inf(y1, V1, k_z_neg, k_z_pos) - y3);
    Ith(ydot,4) = alpha(data->Vold, 10.0, 2.0)*(1.0 - y4) - 1.0*y4;
    
    return 0;
}
