# include "common.h"

int main(int argc, char **argv)
{
    parameters pms;
    pms.numNeurons = 2;
    pms.dt = 0.5;

    simulation(pms);
    return 0;
}
