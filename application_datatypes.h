#ifndef APPLICATION_DATATYPES_H
#define APPLICATION_DATATYPES_H

//#include "RootSim"


typedef struct _device_state {
	int num_acts_types;
	double * prob_actuators;
    void* state_machine;
} device_state;



#endif /* APPLICATION_DATATYPES_H */
