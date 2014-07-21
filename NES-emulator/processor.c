#include <stdio.h>
#include <stdlib.h>

#define STATUS_C (0)
#define STATUS_Z (1)
#define STATUS_I (2)
#define STATUS_D (3)
#define STATUS_B (4)
#define STATUS_V (6)
#define STATUS_S (7)

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
	if( sum / 0xFF ) {
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

void asl( char* accum, char* status, char arg ) {

	/*if the leftmost bit is 1, carry out will be 1*/
	if( *accum / 0x7F == 1 ) {
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

/*
 * processor self-test
 */
int main( int argc, char* argv[] ) {

	char accum,/*xind, yind,*/ status/*, sp*/;
	/*unsigned short int pc;*/

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

	return 0;
}
