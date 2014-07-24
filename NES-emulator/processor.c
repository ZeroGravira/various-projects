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

/*self-test functions*/

void displayStatus( char status ) {
	printf( "SV BDIZC\n" );
	int i;
	for( i = 7; i >= 0; i-- ) {
		if( getStatus( status, i ) == 1 ) {
			printf( "1" );
		} else {
			printf( "0" );
		}
	}
	printf( "\n\n" );
}

void displayAdcTest( char* accum, char* status, unsigned char arg ) {
	printf( "\nadding %d to accumulator\n", arg );
	adc( accum, status, arg );
	printf( "accum = %d\n", (unsigned char)*accum );
	displayStatus( *status );
}

void printBinary( char reg ) {
	unsigned char mask = 0x80;
	int i;
	for( i = 0; i < 8; i++ ) {
		if( ( mask & reg ) == 0 ) {
			printf( "0" );
		} else {
			printf( "1" );
		}
		/*printf( "mask = %d\n", mask );*/
		mask = mask >> 1;
	}
	printf( "\n" );
}

void displayAndTest( char* accum, char* status, unsigned char arg ) {
	printf( "\naccumulator \"and\" test:\n" );
	printBinary( *accum );
	printBinary( arg );
	printf( "--------\n" );
	and( accum, status, arg );
	printBinary( *accum );
	printf( "\n" );
	displayStatus( *status );
}

void displayAslTest( char* accum, char* status ) {
	printf( "\naccumulator shift left test:\n" );
	printBinary( *accum );
	printf( "---------\n" );
	asl( accum, status );
	printBinary( *accum );
	printf( "\n" );
	displayStatus( *status );
}

void displayBccTest( unsigned short int* pc ,char status, char arg ) {
	printf( "\n" );
	printf( "branch carry clear test %d:\n", arg );
	displayStatus( status );
	printf( "pc before branch: %d\n", *pc );
	bcc( pc, status, arg );
	printf( "pc after branch: %d\n", *pc );
	printf( "\n" );
}

void displayBcsTest( unsigned short int* pc ,char status, char arg ) {
	printf( "\n" );
	printf( "branch carry set test %d:\n", arg );
	displayStatus( status );
	printf( "pc before branch: %d\n", *pc );
	bcs( pc, status, arg );
	printf( "pc after branch: %d\n", *pc );
	printf( "\n" );
}

void displayBeqTest( unsigned short int* pc ,char status, char arg ) {
	printf( "\n" );
	printf( "branch equal test %d:\n", arg );
	displayStatus( status );
	printf( "pc before branch: %d\n", *pc );
	beq( pc, status, arg );
	printf( "pc after branch: %d\n", *pc );
	printf( "\n" );
}

void displayBneTest( unsigned short int* pc ,char status, char arg ) {
	printf( "\n" );
	printf( "branch not equal test %d:\n", arg );
	displayStatus( status );
	printf( "pc before branch: %d\n", *pc );
	bne( pc, status, arg );
	printf( "pc after branch: %d\n", *pc );
	printf( "\n" );
}

void displayBplTest( unsigned short int* pc ,char status, char arg ) {
	printf( "\n" );
	printf( "branch on positive test %d:\n", arg );
	displayStatus( status );
	printf( "pc before branch: %d\n", *pc );
	bpl( pc, status, arg );
	printf( "pc after branch: %d\n", *pc );
	printf( "\n" );
}

void displayBmiTest( unsigned short int* pc ,char status, char arg ) {
	printf( "\n" );
	printf( "branch on negative test %d:\n", arg );
	displayStatus( status );
	printf( "pc before branch: %d\n", *pc );
	bmi( pc, status, arg );
	printf( "pc after branch: %d\n", *pc );
	printf( "\n" );
}

void displayBvcTest( unsigned short int* pc ,char status, char arg ) {
	printf( "\n" );
	printf( "branch on overflow clear test %d:\n", arg );
	displayStatus( status );
	printf( "pc before branch: %d\n", *pc );
	bvc( pc, status, arg );
	printf( "pc after branch: %d\n", *pc );
	printf( "\n" );
}

void displayBvsTest( unsigned short int* pc ,char status, char arg ) {
	printf( "\n" );
	printf( "branch on overflow set test %d:\n", arg );
	displayStatus( status );
	printf( "pc before branch: %d\n", *pc );
	bvs( pc, status, arg );
	printf( "pc after branch: %d\n", *pc );
	printf( "\n" );
}



/*
 * processor self-test
 */
int main( int argc, char* argv[] ) {

	char accum,/*xind, yind,*/ status/*, sp*/;
	unsigned short int pc;

	/*clear all registers*/
	/*accum, xind, yind = 0;*/
	int i;
	status = 0;
	/*sp = 0;*/

	/*set bit 5 of the status register*/
	setStatus( &status, 5 );

	/*test setting and clearing of status register*/
	printf( "status register initially:\n" );
	displayStatus( status );

	printf( "\nsetting each bit one at a time\n" );
	for( i = 0; i < 8; i++ ) {
		setStatus( &status, i );
		displayStatus( status );
	}

	printf( "\nclearing only even bits\n" );
	for( i = 0; i < 8; i++ ) {
		if( i % 2 == 0 ) {
			clearStatus( &status, i );
			displayStatus( status );
		}
	}

	printf( "\nresetting status register to default\n" );
	clearStatus( &status, 7 );
	clearStatus( &status, 3 );
	clearStatus( &status, 1 );
	displayStatus( status );

	/*test adc*/
	displayAdcTest( &accum, &status, 1 );
	displayAdcTest( &accum, &status, 3 );
	displayAdcTest( &accum, &status, 9 );
	displayAdcTest( &accum, &status, 12 );
	displayAdcTest( &accum, &status, 27 );
	displayAdcTest( &accum, &status, 51 );
	displayAdcTest( &accum, &status, 20 );
	displayAdcTest( &accum, &status, 17 );
	displayAdcTest( &accum, &status, 100 );

	printf( "testing edge case...\n" );
	displayAdcTest( &accum, &status, 16 );
	displayAdcTest( &accum, &status, 132 );
	displayAdcTest( &accum, &status, 170 );

	/*test and*/
	displayAndTest( &accum, &status, 0xFF );
	displayAndTest( &accum, &status, 0x55 );
	displayAndTest( &accum, &status, ~(0x5) );
	displayAdcTest( &accum, &status, 0xFE );
	displayAndTest( &accum, &status, 0x80 );
	
	/*test asl*/
	displayAslTest( &accum, &status );
	displayAdcTest( &accum, &status, 0x56 );
	for( i = 0; i < 8; i++ ) {
		displayAslTest( &accum, &status );
	}

	/*test bcc and bcs*/
	pc = 200;
	displayBccTest( &pc, status, 62 );
	displayBccTest( &pc, status, -53 );
	displayBcsTest( &pc, status, 17 );
	displayBcsTest( &pc, status, -9 );
	displayAdcTest( &accum, &status, 21 );
	displayBccTest( &pc, status, 62 );
	displayBccTest( &pc, status, -53 );
	displayBcsTest( &pc, status, 17 );
	displayBcsTest( &pc, status, -9 );

	/*test beq and bne*/
	displayBeqTest( &pc, status, 31 );
	displayBeqTest( &pc, status, -17 );
	displayBneTest( &pc, status, 47 );
	displayBneTest( &pc, status, -37 );
	displayAndTest( &accum, &status, 0 );
	displayBeqTest( &pc, status, 31 );
	displayBeqTest( &pc, status, -17 );
	displayBneTest( &pc, status, 47 );
	displayBneTest( &pc, status, -37 );

	/*test bpl and bmi*/
	displayBplTest( &pc, status, 11 );
	displayBplTest( &pc, status, -7 );
	displayBmiTest( &pc, status, 29 );
	displayBmiTest( &pc, status, -61 );
	displayAdcTest( &accum, &status, -12 );
	displayBplTest( &pc, status, 11 );
	displayBplTest( &pc, status, -7 );
	displayBmiTest( &pc, status, 29 );
	displayBmiTest( &pc, status, -61 );

	/*test bvc and bvs*/
	displayBvsTest( &pc, status, 71 );
	displayBvsTest( &pc, status, -54 );
	displayBvcTest( &pc, status, 23 );
	displayBvcTest( &pc, status, -33 );
	displayAdcTest( &accum, &status, -127 );
	displayBvsTest( &pc, status, 71 );
	displayBvsTest( &pc, status, -54 );
	displayBvcTest( &pc, status, 23 );
	displayBvcTest( &pc, status, -33 );
	return 0;
}
