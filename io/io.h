/*
 *
 * mini io
 *
 * (c) see end of file for license terms.
 *
 */
#ifndef _io_H_
#define _io_H_
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdalign.h>

#if defined ( __GNUC__ )
# define PACK_STRUCTURE __attribute__((__packed__))
# define ALLOCATE_ALIGN(size)	__attribute__((__aligned__(size)))
# define UNUSED(v) (void)(v)
# define SIZEOF(a) (sizeof(a)/sizeof(a[0]))
# define INLINE_FUNCTION static inline
# define ATTRIBUTE_CLEANUP_FUNCTION(function)	__attribute__((cleanup(function)))
#else
# error "this compiler is not supported"
#endif

#define MIN(a,b) (((a)<(b))?(a):(b))

typedef struct io io_t;
typedef struct io_implementation io_implementation_t;
typedef struct io_alarm io_alarm_t;

#include "foundation/work.h"
#include "foundation/interrupt.h"
#include "foundation/time.h"

struct PACK_STRUCTURE io_implementation {

	uint32_t (*enter_critical_section) (io_t*);
	void (*exit_critical_section) (io_t*,uint32_t);

	void (*enqueue_event) (io_t*,io_ticket_t*);
	void (*dequeue_event) (io_t*,io_ticket_t*);
	void (*signal_event_pending) (io_t*);
	bool (*do_next_event) (io_t*);

	void (*wait_for_interrupt) (io_t*);

	void (*panic) (io_t*,int32_t);
};

#define IO_STRUCT_MEMBERS \
	io_implementation_t const *implementation;\
	io_ticket_t *event_list;\
	/**/

struct PACK_STRUCTURE io {
	IO_STRUCT_MEMBERS
};

bool initialise_io (io_t*);
io_t* get_device_io (void);

INLINE_FUNCTION uint32_t
io_enter_critical_section (io_t *io) {
	return io->implementation->enter_critical_section (io);
}

INLINE_FUNCTION void
io_exit_critical_section (io_t *io,uint32_t h) {
	io->implementation->exit_critical_section (io,h);
}

INLINE_FUNCTION void
io_enqueue_event (io_t *io,io_ticket_t *ev) {
	io->implementation->enqueue_event (io,ev);
}

INLINE_FUNCTION void
io_dequeue_event (io_t *io,io_ticket_t *ev) {
	io->implementation->dequeue_event (io,ev);
}

INLINE_FUNCTION void
io_signal_event_pending (io_t *io) {
	io->implementation->signal_event_pending (io);
}

INLINE_FUNCTION bool
io_do_next_event (io_t *io) {
	return io->implementation->do_next_event (io);
}

INLINE_FUNCTION void
io_wait_for_interrupt (io_t *io) {
	io->implementation->wait_for_interrupt (io);
}

#define ENTER_IO_CRITICAL_SECTION(io) do {\
	uint32_t __h_critical = io_enter_critical_section(io);

#define EXIT_IO_CRITICAL_SECTION(io) \
		io_exit_critical_section(io,__h_critical);\
	} while (0)

void enqueue_io_event (io_t*,io_ticket_t*);
void dequeue_io_event (io_t*,io_ticket_t*);
bool do_next_io_event (io_t*);
void io_default_panic (io_t*,int32_t);
void io_void_nop (io_t*);

#define SPECIALISE_IO_IMPLEMENTATION() \
	.do_next_event = do_next_io_event,\
	.enqueue_event = enqueue_io_event, \
	.dequeue_event = dequeue_io_event, \
	.signal_event_pending = io_void_nop,\
	.wait_for_interrupt = io_void_nop,\
	.panic = io_default_panic,\
	/**/


#ifdef IMPLEMENT_IO
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------

bool
initialise_io (io_t *io) {
	io->event_list = &s_null_io_ticket;
	return true;
}

void
io_default_panic (io_t *io,int32_t code) {
	while (1);
};

void
io_void_nop (io_t *io) {
}

void
enqueue_io_event (io_t *io,io_ticket_t *ev) {
	ENTER_IO_CRITICAL_SECTION(io);
	if (ev->next_ticket == NULL) {
		ev->next_ticket = io->event_list;
		io->event_list = ev;
	}
	EXIT_IO_CRITICAL_SECTION(io);
	io_signal_event_pending (io);
}

bool
io_ticket_list_remove_ticket (io_ticket_t **list,io_ticket_t *old) {
	bool removed = false;
	if (
			*list != &s_null_io_ticket
		&&	old->next_ticket != NULL
	) {
		if (*list == old) {
			*list = old->next_ticket;
			removed = true;
		} else {
			io_ticket_t *ev = *list;
			while (ev->next_ticket != &s_null_io_ticket) {
				if (ev->next_ticket == old) {
					ev->next_ticket = old->next_ticket;
					removed = true;
					break;
				}
				ev = ev->next_ticket;
			}
		}
	}

	old->next_ticket = NULL;
	return removed;
}

void
dequeue_io_event (io_t *io,io_ticket_t *old) {
	bool removed;
	
	ENTER_IO_CRITICAL_SECTION(io);
	removed = io_ticket_list_remove_ticket (&io->event_list,old);
	EXIT_IO_CRITICAL_SECTION(io);
	
	if (removed) {
		io_ticket_release (old);
	}
}

io_ticket_t*
io_take_last_ticket (io_t *io,io_ticket_t **list) {
	io_ticket_t *ticket;

	ENTER_IO_CRITICAL_SECTION(io);

	ticket = *list;
	if (ticket != &s_null_io_ticket) {
		if (ticket->next_ticket != &s_null_io_ticket) {
			io_ticket_t *last;
			while(ticket->next_ticket->next_ticket != &s_null_io_ticket) {
				ticket = ticket->next_ticket;
			}
			last = ticket->next_ticket;
			ticket->next_ticket = &s_null_io_ticket;
			ticket = last;
		} else {
			*list = ticket->next_ticket;
		}
	}
	ticket->next_ticket = NULL;

	EXIT_IO_CRITICAL_SECTION(io);
	
	return ticket;
}

bool
do_next_io_event (io_t *io) {
	io_ticket_t *ev = io_take_last_ticket (io,&io->event_list);
	if (ev != &s_null_io_ticket) {
		ev->handler(ev);
		io_ticket_release (ev);
		return true;
	} else {
		return false;
	}
}

#endif /* IMPLEMENT_IO */
#endif
/*

BSD 3-Clause License

Copyright (c) 2025, Gregor Bruce

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */




