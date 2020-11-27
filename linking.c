void fill_init_ptr( void(*** ref_init_ptr)() ){

	ref_init_ptr[CENTRAL] = malloc(sizeof( void (*)() ) * 1);
	ref_init_ptr[CENTRAL][0] = init_CENTRAL_0;

	ref_init_ptr[REGIONAL] = malloc(sizeof( void (*)() ) * 2);
	ref_init_ptr[REGIONAL][0] = init_REGIONAL_0;
	ref_init_ptr[REGIONAL][1] = init_REGIONAL_1;

	ref_init_ptr[LOCAL] = malloc(sizeof( void (*)() ) * 1);
	ref_init_ptr[LOCAL][0] = init_LOCAL_0;

	ref_init_ptr[SENSOR] = malloc(sizeof( void (*)() ) * 2);
	ref_init_ptr[SENSOR][0] = init_SENSOR_0;
	ref_init_ptr[SENSOR][1] = init_SENSOR_1;

	ref_init_ptr[ACTUATOR] = malloc(sizeof( void (*)() ) * 3);
	ref_init_ptr[ACTUATOR][0] = init_ACTUATOR_0;
	ref_init_ptr[ACTUATOR][1] = init_ACTUATOR_1;
	ref_init_ptr[ACTUATOR][2] = init_ACTUATOR_2;

	ref_init_ptr[LAN] = malloc(sizeof( void (*)() ) * 5);
	ref_init_ptr[LAN][0] = init_LAN_0;
	ref_init_ptr[LAN][1] = init_LAN_1;
	ref_init_ptr[LAN][2] = init_LAN_2;
	ref_init_ptr[LAN][3] = init_LAN_3;
	ref_init_ptr[LAN][4] = init_LAN_4;

}

void init_CENTRAL_0(){
}

void init_REGIONAL_0(){
}

void init_REGIONAL_1(){
}

void init_LOCAL_0(){
}

void init_SENSOR_0(){
}

void init_SENSOR_1(){
}

void init_ACTUATOR_0(){
}

void init_ACTUATOR_1(){
}

void init_ACTUATOR_2(){
}

void init_LAN_0(){
}

void init_LAN_1(){
}

void init_LAN_2(){
}

void init_LAN_3(){
}

void init_LAN_4(){
}

void fill_raise_ptr( void(**** ref_raise_ptr)() ){

	ref_raise_ptr[CENTRAL] = malloc(sizeof( void (**)() ) * 1);
	ref_raise_ptr[CENTRAL][0] = malloc(sizeof( void (*)() ) * 1);
	ref_raise_ptr[CENTRAL][0][0] = raise0;

	ref_raise_ptr[REGIONAL] = malloc(sizeof( void (**)() ) * 2);
	ref_raise_ptr[REGIONAL][0] = malloc(sizeof( void (*)() ) * 2);
	ref_raise_ptr[REGIONAL][0][0] = raise0;
	ref_raise_ptr[REGIONAL][0][1] = raise1;
	ref_raise_ptr[REGIONAL][1] = malloc(sizeof( void (*)() ) * 2);
	ref_raise_ptr[REGIONAL][1][0] = raise0;
	ref_raise_ptr[REGIONAL][1][1] = raise1;

	ref_raise_ptr[LOCAL] = malloc(sizeof( void (**)() ) * 1);
	ref_raise_ptr[LOCAL][0] = malloc(sizeof( void (*)() ) * 1);
	ref_raise_ptr[LOCAL][0][0] = raise0;

	ref_raise_ptr[SENSOR] = malloc(sizeof( void (**)() ) * 2);
	ref_raise_ptr[SENSOR][0] = malloc(sizeof( void (*)() ) * 2);
	ref_raise_ptr[SENSOR][0][0] = raise0;
	ref_raise_ptr[SENSOR][0][1] = raise1;
	ref_raise_ptr[SENSOR][1] = malloc(sizeof( void (*)() ) * 2);
	ref_raise_ptr[SENSOR][1][0] = raise0;
	ref_raise_ptr[SENSOR][1][1] = raise1;

	ref_raise_ptr[ACTUATOR] = malloc(sizeof( void (**)() ) * 3);
	ref_raise_ptr[ACTUATOR][0] = malloc(sizeof( void (*)() ) * 3);
	ref_raise_ptr[ACTUATOR][0][0] = raise0;
	ref_raise_ptr[ACTUATOR][0][1] = raise1;
	ref_raise_ptr[ACTUATOR][0][2] = raise2;
	ref_raise_ptr[ACTUATOR][1] = malloc(sizeof( void (*)() ) * 3);
	ref_raise_ptr[ACTUATOR][1][0] = raise0;
	ref_raise_ptr[ACTUATOR][1][1] = raise1;
	ref_raise_ptr[ACTUATOR][1][2] = raise2;
	ref_raise_ptr[ACTUATOR][2] = malloc(sizeof( void (*)() ) * 3);
	ref_raise_ptr[ACTUATOR][2][0] = raise0;
	ref_raise_ptr[ACTUATOR][2][1] = raise1;
	ref_raise_ptr[ACTUATOR][2][2] = raise2;

	ref_raise_ptr[LAN] = malloc(sizeof( void (**)() ) * 5);
	ref_raise_ptr[LAN][0] = malloc(sizeof( void (*)() ) * 5);
	ref_raise_ptr[LAN][0][0] = raise0;
	ref_raise_ptr[LAN][0][1] = raise1;
	ref_raise_ptr[LAN][0][2] = raise2;
	ref_raise_ptr[LAN][0][3] = raise3;
	ref_raise_ptr[LAN][0][4] = raise4;
	ref_raise_ptr[LAN][1] = malloc(sizeof( void (*)() ) * 5);
	ref_raise_ptr[LAN][1][0] = raise0;
	ref_raise_ptr[LAN][1][1] = raise1;
	ref_raise_ptr[LAN][1][2] = raise2;
	ref_raise_ptr[LAN][1][3] = raise3;
	ref_raise_ptr[LAN][1][4] = raise4;
	ref_raise_ptr[LAN][2] = malloc(sizeof( void (*)() ) * 5);
	ref_raise_ptr[LAN][2][0] = raise0;
	ref_raise_ptr[LAN][2][1] = raise1;
	ref_raise_ptr[LAN][2][2] = raise2;
	ref_raise_ptr[LAN][2][3] = raise3;
	ref_raise_ptr[LAN][2][4] = raise4;
	ref_raise_ptr[LAN][3] = malloc(sizeof( void (*)() ) * 5);
	ref_raise_ptr[LAN][3][0] = raise0;
	ref_raise_ptr[LAN][3][1] = raise1;
	ref_raise_ptr[LAN][3][2] = raise2;
	ref_raise_ptr[LAN][3][3] = raise3;
	ref_raise_ptr[LAN][3][4] = raise4;
	ref_raise_ptr[LAN][4] = malloc(sizeof( void (*)() ) * 5);
	ref_raise_ptr[LAN][4][0] = raise0;
	ref_raise_ptr[LAN][4][1] = raise1;
	ref_raise_ptr[LAN][4][2] = raise2;
	ref_raise_ptr[LAN][4][3] = raise3;
	ref_raise_ptr[LAN][4][4] = raise4;

}

