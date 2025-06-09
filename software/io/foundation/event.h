/*
 *
 * (c) see end of file for license terms.
 *
 */ 
#ifndef io_event_H_
#define io_event_H_

#define SPECIALISE_IO_EVENT_IMPLEMENTATION(I) \
	SPECIALISE_IO_TICKET_IMPLEMENTATION(I) \
	/**/

io_ticket_t* initialise_io_event_ticket (io_ticket_t*,io_ticket_handler_t fn,void*);


#ifdef IMPLEMENT_IO
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------


io_ticket_t*
initialise_io_event_ticket (
	io_ticket_t *ev,io_ticket_handler_t fn,void* user_value
) {
	ev->handler = fn;
	ev->user_value = user_value;
	ev->next_ticket = NULL;
	return ev;
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






