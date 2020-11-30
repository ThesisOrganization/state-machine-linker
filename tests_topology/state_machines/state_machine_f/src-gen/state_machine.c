/** Generated by YAKINDU Statechart Tools code generator. */


#include "../src/sc_types.h"

#include "state_machine.h"

/*! \file Implementation of the state machine 'state_machine'
*/

#ifndef SC_UNUSED
#define SC_UNUSED(P) (void)(P)
#endif

/* prototypes of all internal functions */
static void enact_main_region_StateB(State_machine* handle);
static void enseq_main_region_StateA_default(State_machine* handle);
static void enseq_main_region_StateB_default(State_machine* handle);
static void enseq_main_region_default(State_machine* handle);
static void exseq_main_region_StateA(State_machine* handle);
static void exseq_main_region_StateB(State_machine* handle);
static void exseq_main_region(State_machine* handle);
static void react_main_region__entry_Default(State_machine* handle);

/*! State machine reactions. */
static sc_boolean react(State_machine* handle);

/*! The reactions of state StateA. */
static sc_boolean main_region_StateA_react(State_machine* handle, const sc_boolean try_transition);

/*! The reactions of state StateB. */
static sc_boolean main_region_StateB_react(State_machine* handle, const sc_boolean try_transition);


static void clearInEvents(State_machine* handle);

/*! Performs a 'run to completion' step. */
static void run_cycle(State_machine* handle);



static void state_machine_eventqueue_init(state_machine_eventqueue * eq, state_machine_event *buffer, sc_integer capacity);
static sc_integer state_machine_eventqueue_size(state_machine_eventqueue * eq);
static void state_machine_event_init(state_machine_event * ev, State_machineEventID name);
static state_machine_event state_machine_eventqueue_pop(state_machine_eventqueue * eq);
static sc_boolean state_machine_eventqueue_push(state_machine_eventqueue * eq, state_machine_event ev);
static void state_machine_add_event_to_queue(state_machine_eventqueue * eq, State_machineEventID name);
static void state_machine_dispatch_event(State_machine* handle, const state_machine_event * event);
static state_machine_event state_machine_get_next_event(State_machine* handle);
static void state_machine_dispatch_next_event(State_machine* handle);


void state_machine_init(State_machine* handle)
{
	sc_integer i;
	
	for (i = 0; i < STATE_MACHINE_MAX_ORTHOGONAL_STATES; ++i)
	{
		handle->stateConfVector[i] = State_machine_last_state;
	}
	
	
	handle->stateConfVectorPosition = 0;
	
	clearInEvents(handle);
	
	
	
	handle->isExecuting = bool_false;
	state_machine_eventqueue_init(&handle->in_event_queue, handle->in_buffer, STATE_MACHINE_IN_EVENTQUEUE_BUFFERSIZE);
}

void state_machine_enter(State_machine* handle)
{
	/* Activates the state machine. */
	if (handle->isExecuting == bool_true)
	{ 
		return;
	} 
	handle->isExecuting = bool_true;
	/* Default enter sequence for statechart state_machine */
	enseq_main_region_default(handle);
	handle->isExecuting = bool_false;
}

void state_machine_exit(State_machine* handle)
{
	/* Deactivates the state machine. */
	if (handle->isExecuting == bool_true)
	{ 
		return;
	} 
	handle->isExecuting = bool_true;
	/* Default exit sequence for statechart state_machine */
	exseq_main_region(handle);
	handle->isExecuting = bool_false;
}


sc_boolean state_machine_is_active(const State_machine* handle)
{
	sc_boolean result = bool_false;
	sc_integer i;
	
	for(i = 0; i < STATE_MACHINE_MAX_ORTHOGONAL_STATES; i++)
	{
		result = result || handle->stateConfVector[i] != State_machine_last_state;
	}
	
	return result;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean state_machine_is_final(const State_machine* handle)
{
	SC_UNUSED(handle);
	return bool_false;
}

sc_boolean state_machine_is_state_active(const State_machine* handle, State_machineStates state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case State_machine_main_region_StateA :
			result = (sc_boolean) (handle->stateConfVector[SCVI_STATE_MACHINE_MAIN_REGION_STATEA] == State_machine_main_region_StateA
			);
			break;
		case State_machine_main_region_StateB :
			result = (sc_boolean) (handle->stateConfVector[SCVI_STATE_MACHINE_MAIN_REGION_STATEB] == State_machine_main_region_StateB
			);
			break;
		default:
			result = bool_false;
			break;
	}
	return result;
}

static void clearInEvents(State_machine* handle)
{
	handle->iface.myEvent_raised = bool_false;
}

static void run_cycle(State_machine* handle)
{
	/* Performs a 'run to completion' step. */
	if (handle->isExecuting == bool_true)
	{ 
		return;
	} 
	handle->isExecuting = bool_true;
	state_machine_dispatch_next_event(handle);
	do
	{ 
		for (handle->stateConfVectorPosition = 0;
			handle->stateConfVectorPosition < STATE_MACHINE_MAX_ORTHOGONAL_STATES;
			handle->stateConfVectorPosition++)
			{
				
			switch (handle->stateConfVector[handle->stateConfVectorPosition])
			{
			case State_machine_main_region_StateA:
			{
				main_region_StateA_react(handle, bool_true);
				break;
			}
			case State_machine_main_region_StateB:
			{
				main_region_StateB_react(handle, bool_true);
				break;
			}
			default:
				break;
			}
		}
		clearInEvents(handle);
		state_machine_dispatch_next_event(handle);
	} while (handle->iface.myEvent_raised == bool_true);
	handle->isExecuting = bool_false;
}


void state_machine_raise_myEvent(State_machine* handle)
{
	state_machine_add_event_to_queue(&(handle->in_event_queue), State_machine_myEvent);
	run_cycle(handle);
}



void* state_machine_get_state(const State_machine* handle)
{
	return handle->iface.state;
}
void state_machine_set_state(State_machine* handle, void* value)
{
	handle->iface.state = value;
}

/* implementations of all internal functions */

/* Entry action for state 'StateB'. */
static void enact_main_region_StateB(State_machine* handle)
{
	/* Entry action for state 'StateB'. */
	send_msg(handle->iface.state);
}

/* 'default' enter sequence for state StateA */
static void enseq_main_region_StateA_default(State_machine* handle)
{
	/* 'default' enter sequence for state StateA */
	handle->stateConfVector[0] = State_machine_main_region_StateA;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state StateB */
static void enseq_main_region_StateB_default(State_machine* handle)
{
	/* 'default' enter sequence for state StateB */
	enact_main_region_StateB(handle);
	handle->stateConfVector[0] = State_machine_main_region_StateB;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
static void enseq_main_region_default(State_machine* handle)
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default(handle);
}

/* Default exit sequence for state StateA */
static void exseq_main_region_StateA(State_machine* handle)
{
	/* Default exit sequence for state StateA */
	handle->stateConfVector[0] = State_machine_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state StateB */
static void exseq_main_region_StateB(State_machine* handle)
{
	/* Default exit sequence for state StateB */
	handle->stateConfVector[0] = State_machine_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for region main region */
static void exseq_main_region(State_machine* handle)
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of state_machine.main_region) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case State_machine_main_region_StateA :
		{
			exseq_main_region_StateA(handle);
			break;
		}
		case State_machine_main_region_StateB :
		{
			exseq_main_region_StateB(handle);
			break;
		}
		default: break;
	}
}

/* Default react sequence for initial entry  */
static void react_main_region__entry_Default(State_machine* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_StateA_default(handle);
}


static sc_boolean react(State_machine* handle)
{
	/* State machine reactions. */
	SC_UNUSED(handle);
	return bool_false;
}

static sc_boolean main_region_StateA_react(State_machine* handle, const sc_boolean try_transition)
{
	/* The reactions of state StateA. */
 			sc_boolean did_transition = try_transition;
	if (try_transition == bool_true)
	{ 
		if ((react(handle)) == (bool_false))
		{ 
			if (handle->iface.myEvent_raised == bool_true)
			{ 
				exseq_main_region_StateA(handle);
				enseq_main_region_StateB_default(handle);
			}  else
			{
				did_transition = bool_false;
			}
		} 
	} return did_transition;
}

static sc_boolean main_region_StateB_react(State_machine* handle, const sc_boolean try_transition)
{
	/* The reactions of state StateB. */
 			sc_boolean did_transition = try_transition;
	if (try_transition == bool_true)
	{ 
		if ((react(handle)) == (bool_false))
		{ 
			if (handle->iface.myEvent_raised == bool_true)
			{ 
				exseq_main_region_StateB(handle);
				enseq_main_region_StateA_default(handle);
			}  else
			{
				did_transition = bool_false;
			}
		} 
	} return did_transition;
}




static void state_machine_eventqueue_init(state_machine_eventqueue * eq, state_machine_event *buffer, sc_integer capacity)
{
	eq->events = buffer;
	eq->capacity = capacity;
	eq->push_index = 0;
	eq->pop_index = 0;
	eq->size = 0;
}

static sc_integer state_machine_eventqueue_size(state_machine_eventqueue * eq)
{
	return eq->size;
}

static state_machine_event state_machine_eventqueue_pop(state_machine_eventqueue * eq)
{
	state_machine_event event;
	if(state_machine_eventqueue_size(eq) <= 0) {
		state_machine_event_init(&event, State_machine_invalid_event);
	}
	else {
		event = eq->events[eq->pop_index];
		
		if(eq->pop_index < eq->capacity - 1) {
			eq->pop_index++;
		} 
		else {
			eq->pop_index = 0;
		}
		eq->size--;
	}
	return event;
}
static sc_boolean state_machine_eventqueue_push(state_machine_eventqueue * eq, state_machine_event ev)
{
	if(state_machine_eventqueue_size(eq) == eq->capacity) {
		return bool_false;
	}
	else {
		eq->events[eq->push_index] = ev;
		
		if(eq->push_index < eq->capacity - 1) {
			eq->push_index++;
		}
		else {
			eq->push_index = 0;
		}
		eq->size++;
		
		return bool_true;
	}
}
static void state_machine_event_init(state_machine_event * ev, State_machineEventID name)
{
	ev->name = name;
}

static void state_machine_add_event_to_queue(state_machine_eventqueue * eq, State_machineEventID name)
{
	state_machine_event event;
	state_machine_event_init(&event, name);
	state_machine_eventqueue_push(eq, event);
}

static void state_machine_dispatch_event(State_machine* handle, const state_machine_event * event) {
	switch(event->name) {
		case State_machine_myEvent:
		{
			handle->iface.myEvent_raised = bool_true;
			break;
		}
		default:
			break;
	}
}

static state_machine_event state_machine_get_next_event(State_machine* handle)
{
	state_machine_event next_event;
	state_machine_event_init(&next_event, State_machine_invalid_event);
	if(state_machine_eventqueue_size(&(handle->in_event_queue)) > 0) {
		next_event = state_machine_eventqueue_pop(&(handle->in_event_queue));
	}
	return next_event;
}

static void state_machine_dispatch_next_event(State_machine* handle)
{
	state_machine_event nextEvent;
	nextEvent = state_machine_get_next_event(handle);
	state_machine_dispatch_event(handle, &nextEvent);
}
