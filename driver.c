#include <stdio.h>
#include <stdlib.h>


void funzione1(int intero, int value){
    printf("FUNZIONE1\n");
    printf("%d %d\n", intero, value);
}
void funzione2(int intero, int value){
    printf("FUNZIONE2\n");
    printf("%d %d\n", intero, value);
}

//void (* global_ptr[7][2])();


typedef enum _element_type{
    CENTRAL = 0,
	REGIONAL,
	LOCAL,
	SENSOR,
	ACTUATOR,
	LAN,
    NUM_OF_ELEMENTS_TYPES
} element_type;

void (** init_ptr[NUM_OF_ELEMENTS_TYPES])();
void (*** raise_ptr[NUM_OF_ELEMENTS_TYPES])();


#define NUM_TYPES_FOR_CENTRAL 2
#define NUM_RAISE_FOR_TYPE0 1
#define NUM_RAISE_FOR_TYPE1 1

void fill_init_ptr( void(*** ref_init_ptr)() ){

    ref_init_ptr[CENTRAL] = malloc(sizeof( void (*)() ) * NUM_TYPES_FOR_CENTRAL);
    ref_init_ptr[CENTRAL][0] = funzione1;
    ref_init_ptr[CENTRAL][1] = funzione2;

}

void fill_raise_ptr( void(**** ref_raise_ptr)() ){

    ref_raise_ptr[CENTRAL] = malloc(sizeof( void (**)() ) * NUM_TYPES_FOR_CENTRAL);
    ref_raise_ptr[CENTRAL][0] = malloc(sizeof( void (*)() ) * NUM_RAISE_FOR_TYPE0);
    ref_raise_ptr[CENTRAL][1] = malloc(sizeof( void (*)() ) * NUM_RAISE_FOR_TYPE1);

    ref_raise_ptr[CENTRAL][0][0] = funzione1;
    ref_raise_ptr[CENTRAL][1][0] = funzione2;

}

int main(){


    fill_init_ptr(init_ptr);
    fill_raise_ptr(raise_ptr);
    
    int type0 = 0;
    int type1 = 1;
    
    init_ptr[CENTRAL][type0](3, 4);
    init_ptr[CENTRAL][type1](2, 8);

    int event0 = 0;

    raise_ptr[CENTRAL][type0][event0](8, 9);
    raise_ptr[CENTRAL][type1][event0](1, 6);


}
