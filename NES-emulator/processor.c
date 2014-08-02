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
	if( (unsigned char)(*accum) / 0x80 == 1 ) {
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

void brk( unsigned short int* pc, char* status, unsigned char* sp, Memory* mem ) {

	char mask;

	/*increment program counter*/
	*pc = *pc + 1;

	/*Push high program counter onto stack*/
	mem->data[ STACK_OFFSET + *sp ] = *pc / 0x0100;
	*sp = *sp + 1;

	/*Push low program counter onto stack*/
	mem->data[ STACK_OFFSET + *sp ] = *pc % 0x0100;
	*sp = *sp + 1;

	/*push status register*/
	mask = 1 << STATUS_B;
	mem->data[ STACK_OFFSET + *sp ] = *status | mask;
	*sp = *sp + 1;

	/*set interrupt flag*/
	setStatus( status, STATUS_I );

	/*load the vector into the PC*/
	*pc = (mem->data[0xFFFE] << 8) + mem->data[0xFFFF];
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

void cpx( char x, char* status, char arg ) {
	char diff = x - arg;
	checkZeroStatus( status, diff );
	checkSignStatus( status, diff );
	if( x < arg ) {
		setStatus( status, STATUS_C );
	} else {
		clearStatus( status, STATUS_C );
	}
}

void cpy( char y, char* status, char arg ) {
	char diff = y - arg;
	checkZeroStatus( status, diff );
	checkSignStatus( status, diff );
	if( y < arg ) {
		setStatus( status, STATUS_C );
	} else {
		clearStatus( status, STATUS_C );
	}
}

void dec( char* memory, char* status ) {
	*memory -= 1;
	checkZeroStatus( status, *memory );
	checkSignStatus( status, *memory );
}

void dex( char* x, char* status ) {
	*x -= 1;
	checkZeroStatus( status, *x );
	checkSignStatus( status, *x );
}

void dey( char* y, char* status ) {
	*y -= 1;
	checkZeroStatus( status, *y );
	checkSignStatus( status, *y );
}

void eor( char* accum, char* status, char arg ) {
	*accum = *accum ^ arg;
	checkZeroStatus( status, *accum );
	checkSignStatus( status, *accum );
}

void inc( char* memory, char* status ) {
	*memory += 1;
	checkZeroStatus( status, *memory );
	checkSignStatus( status, *memory );
}

void inx( char* x, char* status ) {
	*x += 1;
	checkZeroStatus( status, *x );
	checkSignStatus( status, *x );
}

void iny( char* y, char* status ) {
	*y += 1;
	checkZeroStatus( status, *y );
	checkSignStatus( status, *y );
}

void jmp( unsigned short int* pc, unsigned short int target ) {
	*pc = target;
}

void jsr( unsigned short int* pc, unsigned short int target, unsigned char* sp, Memory* mem ) {

	/*push the current pc onto the stack*/
	mem->data[ *sp + STACK_OFFSET ] = *pc;

	/*update the stack pointer*/
	*sp += 1;

	/*copy the target address to the program counter*/
	*pc = target;
}

void lda( char* accum, char* status, char arg ) {
	*accum = arg;	
	checkZeroStatus( status, *accum );
	checkSignStatus( status, *accum );
}

void ldx( char* x, char* status, char arg ) {
	*x = arg;
	checkZeroStatus( status, *x );
	checkSignStatus( status, *x );
}

void ldy( char* y, char* status, char arg ) {
	*y = arg;
	checkZeroStatus( status, *y );
	checkSignStatus( status, *y );
}

void lsr( char* target, char* status ) {
	if( (unsigned int)(*target) % 2 == 0 ) {
		clearStatus( status, STATUS_C );
	} else {
		setStatus( status, STATUS_C );
	}
	clearStatus( status, STATUS_S );
	checkZeroStatus( status, *target );
	*target = *target >> 1;
}

void nop( ) {
	/*does nothing. At least for now, until I
	  implement timing*/
}

void ora( char* accum, char* status, char arg ) {
	*accum = *accum | arg;
	checkZeroStatus( status, *accum );
	checkSignStatus( status, *accum );
}

void pha( char accum, unsigned char* sp, Memory* mem ) {
	mem->data[ *sp + STACK_OFFSET ] = accum;
	*sp += 1;
}

void php( char status, unsigned char* sp, Memory* mem ) {
	mem->data[ *sp + STACK_OFFSET ] = status;
	*sp += 1;
} 

void pla( char* accum, unsigned char* sp, const Memory* mem ) {
	*sp -= 1;
	*accum = mem->data[ *sp + STACK_OFFSET ];
}

void plp( char* status, unsigned char* sp, const Memory* mem ) {
	*sp -= 1;
	*status = mem->data[ *sp + STACK_OFFSET ];
}

void rol( char* target, char* status ) {
	int carryOut = (*target & 0x80);
	*target = *target << 1;
	if( getStatus( *status, STATUS_C ) ) {
		*target = *target | 0x01;
	} else {
		*target = *target | 0x00;
	}
	if( carryOut == 0 ) {
		clearStatus( status, STATUS_C );
	} else {
		setStatus( status, STATUS_C );
	}
	checkZeroStatus( status, STATUS_Z );
	checkSignStatus( status, STATUS_S );
}

void ror( char* target, char* status ) {
	int carryOut = (*target & 0x01);
	*target = *target >> 1;
	if( getStatus( *status, STATUS_C ) ) {
		*target = *target | 0x80;
	} else {
		*target = *target | 0x00;
	}
	if( carryOut == 0 ) {
		clearStatus( status, STATUS_C );
	} else {
		setStatus( status, STATUS_C );
	}
	checkZeroStatus( status, STATUS_Z );
	checkSignStatus( status, STATUS_S );
}

void rti( unsigned short int* pc, unsigned char* sp, char* status, const Memory* mem ) {
	unsigned char pcl, pch;
	*sp = *sp - 1;
	*status = 0xEF & mem->data[ STACK_OFFSET + * sp ];
	*sp = *sp - 1;
	pcl = mem->data[ STACK_OFFSET + *sp ];
	*sp = *sp - 1;
	pch = mem->data[ STACK_OFFSET + *sp ];
	*pc = (pch << 8) + pcl;
}

void sec( char* status ) {
	setStatus( status, STATUS_C );
}

void sed( char* status ) {
	setStatus( status, STATUS_D );
}

void sei( char* status ) {
	setStatus( status, STATUS_I );
}

void sta( char accum, char* memory ) {
	*memory = accum;
}

void stx( char x, char* memory ) {
	*memory = x;
}

void sty( char y, char* memory ) {
	*memory = y;
}

void tax( char accum, char* status, char* x ) {
	*x = accum;
	checkZeroStatus( status, *x );
	checkSignStatus( status, *x );
}

void tay( char accum, char* status, char* y ) {
	*y = accum;
	checkZeroStatus( status, *y );
	checkSignStatus( status, *y );
}

void tsx( char sp, char* status, char* x ) {
	*x = sp;
	checkZeroStatus( status, *x );
	checkSignStatus( status, *x );
}

void txa( char x, char* status, char* a ) {
	*a = x;
	checkZeroStatus( status, *a );
	checkSignStatus( status, *a );
}

void txs( char x, char* status, char* sp ) {
	*sp = x;
	checkZeroStatus( status, *sp );
	checkSignStatus( status, *sp );
}

void tya( char y, char* status, char* a ) {
	*a = y;
	checkZeroStatus( status, *a );
	checkSignStatus( status, *a );
}
