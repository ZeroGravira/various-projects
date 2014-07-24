#include "processor.h"

#include <stdio.h>
#include <stdlib.h>


/*
 * check a bit in the status register
 *
 * @arg status the status register
 * @arg bit the bit to retrieve. Leftmost bit is 7,
            rightmost bit is 0*/
int getStatus( char status, int bit ) {
	char mask = 1 << bit;
	return (status & mask) ? 1 : 0;
}

/*
 * set a bit in the status register to 1
 *
 * @arg status pointer to the status register
 * @arg bit the bit to set
 */
void setStatus( char* status, int bit ) {
	char mask = 1 << bit;
	*status |= mask;
}

/*
 * clear a bit in the status register (set it to 0)
 *
 * @arg status pointer to the status register
 * @arg bit the bit to clear
 */
void clearStatus( char* status, int bit ) {
	char mask = ~(1 << bit);
	*status &= mask;
}

void checkZeroStatus( char* status, char reg ) {
	if( reg == 0 ) {
		setStatus( status, STATUS_Z );
	} else {
		clearStatus( status, STATUS_Z );
	}
}

void checkSignStatus( char* status, char reg ) {
	if( (unsigned char)reg / 0x80 == 1 ) {
		setStatus( status, STATUS_S );
	} else {
		clearStatus( status, STATUS_S );
	}
}

/*
 * add to accumulator
 */
void adc( char* accum, char* status, unsigned char arg ) {

	unsigned short int sum;
	
	sum = (unsigned char)(*accum) + arg + getStatus( *status, STATUS_C );
	*accum = sum % 0x0100;

	/*set or clear the carry and overflow flags*/
	if( sum / 0x0100 ) {
		setStatus( status, STATUS_C );
		setStatus( status, STATUS_V );
	} else {
		clearStatus( status, STATUS_C );
		clearStatus( status, STATUS_V );
	}

	/*set or clear the zero flag*/
	checkZeroStatus( status, *accum );

	/*set or clear the sign flag*/
	checkSignStatus( status, *accum );
	
}

void and( char* accum, char* status, char arg ) {
	*accum &= arg;

	/*set or clear the zero flag*/
	checkZeroStatus( status, *accum );

	/*set or clear the sign flag*/
	checkSignStatus( status, *accum );
}

void asl( char* accum, char* status ) {

	/*if the leftmost bit is 1, carry out will be 1*/
	if( *accum / 0x80 != 1 ) {
		setStatus( status, STATUS_C );
	} else {
		clearStatus( status, STATUS_C );
	}

	*accum = *accum << 1;

	/*set or clear the zero flag*/
	checkZeroStatus( status, *accum );

	/*set or clear the sign flag*/
	checkSignStatus( status, *accum );
}

void bcc( unsigned short int* pc, char status, char arg ) {

	/*if the carry bit clear, branch*/
	if( !getStatus( status, STATUS_C ) ) {
		*pc += arg;
	}
	
}

void bcs( unsigned short int* pc, char status, char arg ) {

	/*if the carry bit is set, branch*/
	if( getStatus( status, STATUS_C ) ) {
		*pc += arg;
	}
}

void beq( unsigned short int* pc, char status, char arg ) {

	/*if the zero bit is set, branch*/
	if( getStatus( status, STATUS_Z ) ) {
		*pc += arg;
	}
}

void bit( char accum, char* status, char arg ) {

	checkZeroStatus( status, accum & arg );
	if( ( arg & 0x80 ) == 0 ) {
		clearStatus( status, STATUS_S );
	} else {
		setStatus( status, STATUS_S );
	}

	if( ( arg & 0x40 ) == 0 ) {
		clearStatus( status, STATUS_V );
	} else {
		setStatus( status, STATUS_V );
	}
}

void bmi( unsigned short int* pc, char status, char arg ) {
		
	/*if the sign bit is set, branch*/
	if( getStatus( status, STATUS_S ) ) {
		*pc += arg;
	}
}

void bne( unsigned short int* pc, char status, char arg ) {

	/*if the zero bit is clear, branch*/
	if( !getStatus( status, STATUS_Z ) ) {
		*pc += arg;
	}
}

void bpl( unsigned short int* pc, char status, char arg ) {

	/*if the sign bit is clear, branch*/
	if( !getStatus( status, STATUS_S ) ) {
		*pc += arg;
	}
}

void brk( unsigned short int* pc, char status ) {

}

void bvc( unsigned short int* pc, char status, char arg ) {

	/*if the overflow bit is clear, branch*/
	if( !getStatus( status, STATUS_V ) ) {
		*pc += arg;
	}
}

void bvs( unsigned short int* pc, char status, char arg ) {

	/*if the overflow bit is set, branch*/
	if( getStatus( status, STATUS_V ) ) {
		*pc += arg;
	}
}

void clc( char* status ) {
	clearStatus( status, STATUS_C );
}

void cld( char* status ) {
	clearStatus( status, STATUS_D );
}

void cli( char* status ) {
	clearStatus( status, STATUS_I );
}

void clv( char* status ) {
	clearStatus( status, STATUS_V );
}

void cmp( char accum, char* status, char arg ) {
	char diff = accum - arg;
	checkZeroStatus( status, diff );
	checkSignStatus( status, diff );
	if( accum < arg ) {
		setStatus( status, STATUS_C );
	} else {
		clearStatus( status, STATUS_C );
	}
}
