#ifndef INCLUDED_INPUT
#define INCLUDED_INPUT


#include "external_libraries/libsdl_fwd.h"

// input handler return values.
enum InReaction
{
	// (the handlers' return values are checked and these
	// 'strange' values might bring errors to light)

	// pass the event to the next handler in the chain
	IN_PASS = 4,

	// we've handled it; no other handlers will receive this event.
	IN_HANDLED = 2
};

typedef InReaction (*InHandler)(const SDL_Event_*);

// register an input handler, which will receive all subsequent events first.
// events are passed to other handlers if handler returns IN_PASS.
extern void in_add_handler(InHandler handler);

// remove all registered input handlers
extern void in_reset_handlers();

// send event to each handler (newest first) until one returns true
extern void in_dispatch_event(const SDL_Event_* event);

// push an event onto the back of a high-priority queue - the new event will
// be returned by in_poll_event before any standard SDL events
extern void in_push_priority_event(const SDL_Event_* event);

// reads events that were pushed by in_push_priority_event
// returns 1 if an event was read, 0 otherwise.
extern int in_poll_priority_event(SDL_Event_* event);

// reads events that were pushed by in_push_priority_event, or, if there are
// no high-priority events) reads from the SDL event queue with SDL_PollEvent.
// returns 1 if an event was read, 0 otherwise.
extern int in_poll_event(SDL_Event_* event);

#endif	// #ifndef INCLUDED_INPUT
