/** Generated by YAKINDU Statechart Tools code generator. */

#ifndef MACCHINA_STATI_H_
#define MACCHINA_STATI_H_

#ifdef __cplusplus
extern "C" { 
#endif

/*!
* Forward declaration for the Macchina_stati state machine.
*/
typedef struct Macchina_stati Macchina_stati;

/*!
* Forward declaration of the data structure for the Macchina_statiIface interface scope.
*/
typedef struct Macchina_statiIface Macchina_statiIface;

#ifdef __cplusplus
}
#endif

#include "../simulator_api.h"
#include "../src/sc_types.h"

#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'macchina_stati'.
*/

#ifndef MACCHINA_STATI_EVENTQUEUE_BUFFERSIZE
#define MACCHINA_STATI_EVENTQUEUE_BUFFERSIZE 20
#endif
#ifndef MACCHINA_STATI_IN_EVENTQUEUE_BUFFERSIZE
#define MACCHINA_STATI_IN_EVENTQUEUE_BUFFERSIZE MACCHINA_STATI_EVENTQUEUE_BUFFERSIZE
#endif
#ifndef SC_INVALID_EVENT_VALUE
#define SC_INVALID_EVENT_VALUE 0
#endif
/*! Define number of states in the state enum */
#define MACCHINA_STATI_STATE_COUNT 2

/*! Define dimension of the state configuration vector for orthogonal states. */
#define MACCHINA_STATI_MAX_ORTHOGONAL_STATES 1

/*! Define indices of states in the StateConfVector */
#define SCVI_MACCHINA_STATI_MAIN_REGION_STATEA 0
#define SCVI_MACCHINA_STATI_MAIN_REGION_STATEB 0


/*
 * Enum of event names in the statechart.
 */
typedef enum  {
	Macchina_stati_invalid_event = SC_INVALID_EVENT_VALUE,
	Macchina_stati_myEvent
} Macchina_statiEventID;

/*
 * Struct that represents a single event.
 */
typedef struct {
	Macchina_statiEventID name;
} macchina_stati_event;

/*
 * Queue that holds the raised events.
 */
typedef struct macchina_stati_eventqueue_s {
	macchina_stati_event *events;
	sc_integer capacity;
	sc_integer pop_index;
	sc_integer push_index;
	sc_integer size;
} macchina_stati_eventqueue;

/*! Enumeration of all states */ 
typedef enum
{
	Macchina_stati_last_state,
	Macchina_stati_main_region_StateA,
	Macchina_stati_main_region_StateB
} Macchina_statiStates;




/*! Type declaration of the data structure for the Macchina_statiIface interface scope. */
struct Macchina_statiIface
{
	sc_boolean myEvent_raised;
	void* state;
};






/*! 
 * Type declaration of the data structure for the Macchina_stati state machine.
 * This data structure has to be allocated by the client code. 
 */
struct Macchina_stati
{
	Macchina_statiStates stateConfVector[MACCHINA_STATI_MAX_ORTHOGONAL_STATES];
	sc_ushort stateConfVectorPosition; 
	Macchina_statiIface iface;
	sc_boolean isExecuting;
	macchina_stati_eventqueue in_event_queue;
	macchina_stati_event in_buffer[MACCHINA_STATI_IN_EVENTQUEUE_BUFFERSIZE];
};



/*! Initializes the Macchina_stati state machine data structures. Must be called before first usage.*/
extern void macchina_stati_init(Macchina_stati* handle);


/*! Activates the state machine. */
extern void macchina_stati_enter(Macchina_stati* handle);

/*! Deactivates the state machine. */
extern void macchina_stati_exit(Macchina_stati* handle);




/*! Raises the in event 'myEvent' that is defined in the default interface scope. */ 
extern void macchina_stati_raise_myEvent(Macchina_stati* handle);
/*! Gets the value of the variable 'state' that is defined in the default interface scope. */ 
extern void* macchina_stati_get_state(const Macchina_stati* handle);
/*! Sets the value of the variable 'state' that is defined in the default interface scope. */ 
extern void macchina_stati_set_state(Macchina_stati* handle, void* value);

/*!
 * Checks whether the state machine is active (until 2.4.1 this method was used for states).
 * A state machine is active if it was entered. It is inactive if it has not been entered at all or if it has been exited.
 */
extern sc_boolean macchina_stati_is_active(const Macchina_stati* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the state machine is considered being inactive. In this case this method returns false.
 */
extern sc_boolean macchina_stati_is_final(const Macchina_stati* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was called isActive()). */
extern sc_boolean macchina_stati_is_state_active(const Macchina_stati* handle, Macchina_statiStates state);


#ifdef __cplusplus
}
#endif 

#endif /* MACCHINA_STATI_H_ */