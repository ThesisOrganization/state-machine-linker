#include <stdio.h>
#include <stdlib.h>
#include "linking.h"


void funzione1(int intero, int value){
    printf("FUNZIONE1\n");
    printf("%d %d\n", intero, value);
}
void funzione2(int intero, int value){
    printf("FUNZIONE2\n");
    printf("%d %d\n", intero, value);
}

//void (* global_ptr[7][2])();

void (** init_ptr[NUM_OF_ELEMENTS_TYPES])();
void (*** raise_ptr[NUM_OF_ELEMENTS_TYPES])();



int main(){


    fill_init_ptr(init_ptr);
    fill_raise_ptr(raise_ptr);

    device_state ds1;
    device_state ds2;
    device_state ds3;
    device_state ds4;

    ds1.num_acts_types = 1;
    ds2.num_acts_types = 2;
    ds3.num_acts_types = 3;
    ds4.num_acts_types = 4;

    init_ptr[REGIONAL][1](&ds1);
    init_ptr[REGIONAL][2](&ds2);
    init_ptr[ACTUATOR][0](&ds3);
    init_ptr[CENTRAL][0](&ds4);

    raise_ptr[REGIONAL][1][0](ds1.state_machine);
    printf("%d\n", statechart_is_state_active(ds1.state_machine, Statechart_main_region_StateB));
    raise_ptr[REGIONAL][1][0](ds1.state_machine);
    printf("%d\n", statechart_is_state_active(ds1.state_machine, Statechart_main_region_StateB));
    
    raise_ptr[REGIONAL][2][0](ds2.state_machine);
    printf("%d\n", statechart_is_state_active(ds2.state_machine, Statechart_main_region_StateB));

    raise_ptr[ACTUATOR][0][0](ds3.state_machine);

    raise_ptr[CENTRAL][0][0](ds4.state_machine);




}
