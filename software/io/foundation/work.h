/*
 *
 * (c) see end of file for license terms.
 *
 */ 
#ifndef io_work_H_
#define io_work_H_

typedef struct io_ticket io_ticket_t;
typedef struct io_ticket_type io_ticket_type_t;

#define IO_TICKET_IMPLEMENTATION_STRUCT_MEMBERS \
	/**/

struct PACK_STRUCTURE io_ticket_implementation {
	IO_TICKET_IMPLEMENTATION_STRUCT_MEMBERS
};

typedef void (*io_ticket_handler_t) (io_ticket_t*);

#define IO_TICKET_TYPE_STRUCT_MEMBERS \
	io_ticket_handler_t handler;\
	void *user_value;\
	/**/

struct PACK_STRUCTURE io_ticket_type {
	IO_TICKET_TYPE_STRUCT_MEMBERS
};

#define IO_TICKET_STRUCT_MEMBERS \
	IO_TICKET_TYPE_STRUCT_MEMBERS \
	io_ticket_t *next_ticket;\
	/**/

struct io_ticket {
	IO_TICKET_STRUCT_MEMBERS
};

extern io_ticket_t s_null_io_ticket;

INLINE_FUNCTION io_ticket_t*
io_ticket_aquire (io_ticket_t *ticket) {
	return ticket;
}

INLINE_FUNCTION void
io_ticket_release (io_ticket_t *ticket) {
}

#define SPECIALISE_IO_TICKET_IMPLEMENTATION(I) \
	/**/
	
#ifdef IMPLEMENT_IO
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------

static void
null_io_ticket_handler (io_ticket_t *job) {
}

io_ticket_t s_null_io_ticket = {
	.handler = null_io_ticket_handler,
	.user_value = NULL,
	.next_ticket = NULL,
};


#endif /* IMPLEMENT_IO */
#endif
#include "event.h"
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






