#include "processor.h"

#include <stdio.h>
#include <stdlib.h>

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

void displayClcTest( char* status ) {
	printf( "status before clc:\n" );
	displayStatus( *status );
	clc( status );
	printf( "status after clc:\n" );
	displayStatus( *status );
}

void displayClvTest( char* status ) {
	printf( "status before clv:\n" );
	displayStatus( *status );
	clv( status );
	printf( "status after clv:\n" );
	displayStatus( *status );
}

void displayCldTest( char* status ) {
	printf( "status before cld:\n" );
	displayStatus( *status );
	cld( status );
	printf( "status after cld:\n" );
	displayStatus( *status );
}

void displayCliTest( char* status ) {
	printf( "status before cli:\n" );
	displayStatus( *status );
	cli( status );
	printf( "status after cli:\n" );
	displayStatus( *status );
}

void displayLdaTest( char* accum, char* status, char arg ) {
	printf( "\ntesting load accumulator %d:\n", arg );
	printf( "status register before load:\n" );
	displayStatus( *status );
	printf( "accumulator before load: %d\n", *accum );
	lda( accum, status, arg );
	printf( "status register after load:\n" );
	displayStatus( *status );
	printf( "accumulator after load: %d\n\n", *accum );
	
}

void displayLdxTest( char* x, char* status, char arg ) {
	printf( "\ntesting load x index %d:\n", arg );
	printf( "status register before load:\n" );
	displayStatus( *status );
	printf( "x index before load: %d\n", *x );
	ldx( x, status, arg );
	printf( "status register after load:\n" );
	displayStatus( *status );
	printf( "x index after load: %d\n\n", *x );
	
}

void displayLdyTest( char* y, char* status, char arg ) {
	printf( "\ntesting load y index %d:\n", arg );
	printf( "status register before load:\n" );
	displayStatus( *status );
	printf( "y index before load: %d\n", *y );
	ldy( y, status, arg );
	printf( "status register after load:\n" );
	displayStatus( *status );
	printf( "y index after load: %d\n\n", *y );
}

void displayBrkTest( unsigned short int* pc, char* status, unsigned char* sp, Memory* mem ) {
	printf( "\ntesting brk:\n" );
	printf( "status register before break:\n" );
	displayStatus( *status );
	printf( "pc before break: %X\n", *pc );
	printf( "memory at 0xFFFE: %X\n", mem->data[ 0xFFFE ] );
	printf( "memory at 0xFFFF: %X\n", mem->data[ 0xFFFF ] );
	brk( pc, status, sp, mem );
	printf( "\nstatus register after break:\n" );
	displayStatus( *status );
	printf( "pc after break: %X\n", *pc );
	printf( "memory at 0x0100: %X\n", (unsigned char)(mem->data[ 0x100 ]) );
	printf( "memory at 0x0101: %X\n", (unsigned char)(mem->data[ 0x101 ]) );
	printf( "memory at 0x0102: %X\n", (unsigned char)(mem->data[ 0x102 ]) );
}

void displayRtiTest( unsigned short int* pc, unsigned char* sp, char* status, const Memory* mem ) {
	printf( "return-from-interrupt test\n" );
	printf( "pc before rti: %X\n", *pc );
	printf( "status register before rti:\n" );
	displayStatus( *status );
	rti( pc, sp, status, mem );
	printf( "pc after rti: %X\n", *pc );
	printf( "status register after rti:\n" );
	displayStatus( *status );
}

void displaySecTest( char* status ) {
	printf( "set carry flag test\n" );
	printf( "status register before sec:\n" );
	displayStatus( *status );
	sec( status );
	printf( "status register after sec:\n" );
	displayStatus( *status );
}

void displaySedTest( char* status ) {
	printf( "set decimal flag test\n" );
	printf( "status register before sec:\n" );
	displayStatus( *status );
	sed( status );
	printf( "status register after sec:\n" );
	displayStatus( *status );
}

void displaySeiTest( char* status ) {
	printf( "set interrupt flag test\n" );
	printf( "status register before sec:\n" );
	displayStatus( *status );
	sei( status );
	printf( "status register after sec:\n" );
	displayStatus( *status );
}

/*
 * processor self-test
 */
int main( int argc, char* argv[] ) {

	char accum, x, y, status;
	unsigned char sp;
	unsigned short int pc;
	Memory mem;

	int i;

	/*clear all registers*/
	accum = 0;
	x = 0;
	y = 0;
	status = 0;
	sp = 0;
	mem.data[ 0xFFFE ] = 0x20;
	mem.data[ 0xFFFF ] = 0x12;

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
	pc = 0xA198;
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

	/*test status clear instructions*/
	displayClcTest( &status );
	displayClvTest( &status );

	/*test load accumulator instruction*/
	displayLdaTest( &accum, &status,  97 );
	displayLdaTest( &accum, &status,  -1 );
	displayLdaTest( &accum, &status,   0 );
	displayLdaTest( &accum, &status, 127 );
	displayLdaTest( &accum, &status, -128 );

	
	/*test load index x instruction*/
	displayLdxTest( &x, &status,  97 );
	displayLdxTest( &x, &status,  -1 );
	displayLdxTest( &x, &status,   0 );
	displayLdxTest( &x, &status, 127 );
	displayLdxTest( &x, &status, -128 );

	/*test load index y instruction*/
	displayLdyTest( &y, &status,   97 );
	displayLdyTest( &y, &status,   -1 );
	displayLdyTest( &y, &status,    0 );
	displayLdyTest( &y, &status,  127 );
	displayLdyTest( &y, &status, -128 );

	/*test brk instruction*/
	displayBrkTest( &pc, &status, &sp, &mem );

	/*test cli instruction*/
	displayCliTest( &status );

	/*test set flag instructions*/
	displaySecTest( &status );
	displaySedTest( &status );
	displaySeiTest( &status );
	
	/*test rti instruction*/
	displayRtiTest( &pc, &sp, &status, &mem );
	return 0;
}
