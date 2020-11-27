#include <stdio.h>
#include <stdlib.h>


void funzione1(int intero, int value){
    printf("%d %d\n", intero, value);
}
void funzione2(int intero, int value){
    printf("%d %d\n", intero, value);
}

//void (* global_ptr[7][2])();
void (*** global_ptr[7])();

int main(){


    funzione1(8, 9);

    //void* (*ptr_fun)() = funzione;

    //int value = ptr_fun(7, 10);
    //printf("%d\n", value);
    //
    //void* ptr = funzione;

    //value = ((void * (*)()) ptr)(7, 10);
    //printf("%d\n", value);
    
    global_ptr[0] = malloc(sizeof( void (**)() ));
    global_ptr[1] = malloc(sizeof( void (**)() ));
    
    global_ptr[0][0] = malloc(sizeof( void (*)() ));
    global_ptr[1][0] = malloc(sizeof( void (*)() ));

    global_ptr[0][0][0] = funzione1;
    global_ptr[1][0][0] = funzione2;

    global_ptr[0][0][0](3, 4);
    global_ptr[1][0][0](3, 4);


}
