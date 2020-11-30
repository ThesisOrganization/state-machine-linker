#include <stdio.h>
#include "application_datatypes.h"

void funzione_stampa(int intero){
    
    printf("intero: %d\n", intero);

}

void send_msg(void* state){

    device_state* ds = (device_state*) state;
    printf("Num acts types= %d", ds->num_acts_types);

}
