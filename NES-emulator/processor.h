
#define STATUS_C (0)
#define STATUS_Z (1)
#define STATUS_I (2)
#define STATUS_D (3)
#define STATUS_B (4)
#define STATUS_V (6)
#define STATUS_S (7)

typedef struct {
	char data[256];
} Stack;

int getStatus( char status, int bit );

void setStatus( char* status, int bit );

void clearStatus( char* status, int bit );

void checkZeroStatus( char* status, char reg );

void checkSignStatus( char* status, char reg );

void adc( char* accum, char* status, unsigned char arg );

void and( char* accum, char* status, char arg );

void asl( char* accum, char* status );

void bcc( unsigned short int* pc, char status, char arg );

void bcs( unsigned short int* pc, char status, char arg );

void beq( unsigned short int* pc, char status, char arg );

void bmi( unsigned short int* pc, char status, char arg );

void bne( unsigned short int* pc, char status, char arg );

void bpl( unsigned short int* pc, char status, char arg );

void brk( unsigned short int* pc, char status );

void bvc( unsigned short int* pc, char status, char arg );

void bvs( unsigned short int* pc, char status, char arg );

void clc( char* status );

void cld( char* status );

void cli( char* status );

void clv( char* status );

void cmp( char accum, char* status, char arg );

void cpx( char x, char* status, char arg );

void cpy( char y, char* status, char arg );

void dec( char* memory, char* status );

void dex( char* x, char* status );

void dey( char* y, char* status );

void eor( char* accum, char* status, char arg );

void inc( char* memory, char* status );

void inx( char* x, char* status );

void iny( char* y, char* status );

void jmp( unsigned short int* pc, unsigned short int* target );

void jsr( unsigned short int* pc, unsigned short int* target, char* sp, Stack* stack );

void lda( char* accum, char* status, char arg );

void ldx( char* x, char* status, char arg );

void ldy( char* y, char* status, char arg );

void lsr( char* target, char* status );

void nop();

void ora( char* accum, char* status, char arg );

void pha( char accum, char* sp, Stack* stack );

void php( char status, char* sp, Stack* stack );

void pla( char* accum, char* sp, const Stack* stack );

void plp( char* status, char* sp, const Stack* stack );

void rol( char* target, char* status );

void ror( char* target, char* status );

void rts( char* pc, char* sp, const Stack* stack );

void sbc( char* accum, char* status, char arg );

void sec( char* status );

void sed( char* status );

void sei( char* status );

void sta( char* accum, char arg );

void stx( char* x, char arg );

void sty( char* y, char arg );

void tax( char accum, char* status, char* x );

void tay( char accum, char* status, char* y );

void tsx( char sp, char* status, char* x );

void txa( char x, char* status, char* accum );

void txs( char x, char* status, char* sp );

void tya( char y, char* status, char* accum );
