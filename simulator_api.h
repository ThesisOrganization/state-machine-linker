#ifndef SIMULATOR_API_H
#define SIMULATOR_API_H

//#include "RootSim"


typedef struct _device_state {
	int num_acts_types;
	double * prob_actuators;
    void* state_machine;
} device_state;



void funzione_stampa(int intero);


#endif /* SIMULATOR_API_H */
