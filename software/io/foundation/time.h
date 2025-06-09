/*
 *
 * (c) see end of file for license terms.
 * 
 */ 
#ifndef _io_time_H_
#define _io_time_H_

#include <limits.h>

typedef union PACK_STRUCTURE io_time {
	int64_t nanoseconds;
	int64_t ns;
	uint64_t u64;
	uint8_t bytes[8];
	volatile uint32_t u32[2];
	volatile uint16_t u16[4];
	volatile uint8_t u8[8];
	volatile struct {
		uint32_t low;
		uint32_t high;
	} part;
} io_time_t;

#define microsecond_time(m)			(io_time_t){(int64_t)(m) * 1000LL}
#define millisecond_time(m)			(io_time_t){(int64_t)(m) * 1000000LL}
#define second_time(m)					(io_time_t){(int64_t)(m) * 1000000000LL}
#define minute_time(m)					(io_time_t){(int64_t)(m) * 60000000000LL}
#define time_zero()						(io_time_t){0LL}
#define zero_time()						(io_time_t){0LL}
#define beginning_of_time()			(io_time_t){0LL}

#define time_to_milliseconds(t)		((t)/1000000LL)
#define time_in_milliseconds(m)		((int64_t)(m) / 1000000LL)

#define END_OF_TIME	LLONG_MAX

typedef struct io_time_clock_implementation io_time_clock_implementation_t;
typedef struct io_time_clock io_time_clock_t;

struct io_time_clock_implementation {
	bool (*start) (io_t*,io_time_clock_t*,io_ticket_t*);
	io_time_t (*get_time) (io_time_clock_t*);
	bool (*set_alarm_time) (io_time_clock_t*,io_time_t);
};

#define IO_TIME_CLOCK_STRUCT_MEMBERS \
io_time_clock_implementation_t const *implementation;\
/**/

struct PACK_STRUCTURE io_time_clock {
	IO_TIME_CLOCK_STRUCT_MEMBERS
};

INLINE_FUNCTION io_time_t
io_time_clock_get_time (io_time_clock_t *tc) {
	return tc->implementation->get_time (tc);
}

INLINE_FUNCTION bool
io_time_clock_start (io_t *io,io_time_clock_t *tc,io_ticket_t *alarm) {
	return tc->implementation->start (io,tc,alarm);
}

INLINE_FUNCTION bool
io_time_clock_set_alarm_time (io_time_clock_t *tc,io_time_t when) {
	return tc->implementation->set_alarm_time (tc,when);
}

#ifdef IMPLEMENT_IO
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------

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




