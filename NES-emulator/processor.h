
#define STATUS_C (0)
#define STATUS_Z (1)
#define STATUS_I (2)
#define STATUS_D (3)
#define STATUS_B (4)
#define STATUS_V (6)
#define STATUS_S (7)

typedef struct {
	char data[ 65536 ];
} Memory;

int getStatus( char status, int bit );

void setStatus( char* status, int bit );

void clearStatus( char* status, int bit );

/*
 * Add data to accumulator.
 *
 * C,A <= A + M + C
 *
 * N Z C I D V
 * / / / _ _ /
 *
 */
void adc( char* accum, char* status, unsigned char arg );

/*
 * Bitwise and operation between data and accumulator.
 *
 * A <= A and M
 *
 * N Z C I D V
 * / / _ _ _ _
 *
 */
void and( char* accum, char* status, char arg );

/*
 * Shift accumulator left.
 *
 * A <= A << 1;
 *
 * N Z C I D V
 * / / / _ _ _
 *
 */
void asl( char* accum, char* status );

/*
 * Branch on C = 0
 *
 * N Z C I D V
 * _ _ _ _ _ _
 *
 */
void bcc( unsigned short int* pc, char status, char arg );

/*
 * Branch on C = 1
 *
 * N Z C I D V
 * _ _ _ _ _ _
 *
 */
void bcs( unsigned short int* pc, char status, char arg );

/*
 * Branch on Z = 1
 *
 * N Z C I D V
 * _ _ _ _ _ _
 *
 */
void beq( unsigned short int* pc, char status, char arg );

void bit( char accum, char* status, char arg );

/*
 * Branch on N = 1
 *
 * N Z C I D V
 * _ _ _ _ _ _
 *
 */
void bmi( unsigned short int* pc, char status, char arg );

/*
 * Branch on Z = 0
 *
 * N Z C I D V
 * _ _ _ _ _ _
 *
 */
void bne( unsigned short int* pc, char status, char arg );

/*
 * Branch on N = 0
 *
 * N Z C I D V
 * _ _ _ _ _ _
 *
 */
void bpl( unsigned short int* pc, char status, char arg );

/*
 * Force an interrupt and set interrupt flag.
 * 
 * (PCH) toS
 * (PCL) toS
 * (ST)  toS
 *
 * (PCH) <= M[ 0xFFFE ]
 * (PCL) <= M[ 0xFFFF ]
 *
 * N Z C I D V
 * _ _ _ 1 _ _
 *
 */
void brk( unsigned short int* pc, char* status, unsigned char* sp, Memory mem );

/*
 * Branch on overflow clear.
 *
 * N Z C I D V
 * _ _ _ _ _ _
 *
 */
void bvc( unsigned short int* pc, char status, char arg );

/*
 * Branch on overflow set.
 *
 * N Z C I D V
 * _ _ _ _ _ _
 *
 */
void bvs( unsigned short int* pc, char status, char arg );

/*
 * Clear carry flag
 *
 * N Z C I D V
 * _ _ 0 _ _ _
 *
 */
void clc( char* status );

/*
 * Clear decimal flag
 *
 * N Z C I D V
 * _ _ _ _ 0 _
 *
 */
void cld( char* status );

/*
 * Clear interrupt disable flag
 *
 * N Z C I D V
 * _ _ _ 0 _ _
 *
 */
void cli( char* status );

/*
 * Clear overflow flag
 *
 * N Z C I D V
 * _ _ _ _ _ 0
 *
 */
void clv( char* status );

/*
 * compare memory and accumulator
 *
 * A - M
 *
 * N Z C I D V
 * / / / _ _ _
 *
 */
void cmp( char accum, char* status, char arg );

/*
 * compare memory and x index
 *
 * X - M
 *
 * N Z C I D V
 * / / / _ _ _
 *
 */
void cpx( char x, char* status, char arg );

/*
 * compare memory and y index
 *
 * Y - M
 *
 * N Z C I D V
 * / / / _ _ _
 *
 */
void cpy( char y, char* status, char arg );

/*
 * Decrement memory by one
 *
 * M < = M - 1
 *
 * N Z C I D V
 * / / _ _ _ _
 *
 */
void dec( char* memory, char* status );

/*
 * Decrement x index by one
 *
 * X <= X - 1
 *
 * N Z C I D V
 * / / _ _ _ _
 *
 */
void dex( char* x, char* status );

/*
 * Decrement y index by one
 *
 * Y <= Y - 1
 *
 * N Z C I D V
 * / / _ _ _ _
 *
 */
void dey( char* y, char* status );

/*
 * Exclusive-or memory with accumulator
 *
 * A <= A xor M
 *
 * N Z C I D V
 * / / _ _ _ _
 *
 */
void eor( char* accum, char* status, char arg );

/*
 * Increment memory by one
 *
 * M <= M + 1
 *
 * N Z C I D V
 * / / _ _ _ _
 *
 */
void inc( char* memory, char* status );

/*
 * Increment x index by one
 *
 * X <= X + 1
 *
 * N Z C I D V
 * / / _ _ _ _
 *
 */
void inx( char* x, char* status );

/*
 * Increment y index by one
 *
 * Y <= Y + 1
 *
 * N Z C I D V
 * / / _ _ _ _
 *
 */
void iny( char* y, char* status );

/*
 * Jump to instruction (doesn't save return address)
 *
 * PC <= M
 *
 * N Z C I D V
 * _ _ _ _ _ _
 *
 */
void jmp( unsigned short int* pc, unsigned short int target );

/*
 * Jump to instruction and save return address
 *
 * PCL toS
 * PCH toS
 * PC <= M
 *
 * N Z C I D V
 * _ _ _ _ _ _
 *
 */
void jsr( unsigned short int* pc, unsigned short int target, unsigned char* sp, Memory* mem );

/*
 * Load value to accumulator
 *
 * A <= M
 *
 * N Z C I D V
 * / / _ _ _ _
 *
 */
void lda( char* accum, char* status, char arg );

/*
 * Load value to x pointer
 *
 * X <= M
 *
 * N Z C I D V
 * / / _ _ _ _
 *
 */
void ldx( char* x, char* status, char arg );

/*
 * Load value to y pointer
 * 
 * Y <= M
 *
 * N Z C I D V
 * / / _ _ _ _
 *
 */
void ldy( char* y, char* status, char arg );

/*
 * logical shift left (either memory or accumulator
 *
 * N Z C I D V
 * 0 / / _ _ _
 *
 */
void lsr( char* target, char* status );

/*
 * does nothing
 */
void nop();

/*
 * Logical "or" operation on accumulator
 *
 * A <= A or M
 *
 * N Z C I D V
 * / / _ _ _ _
 *
 */
void ora( char* accum, char* status, char arg );

/*
 * Push accumulator onto stack
 *
 * A toS
 *
 * N Z C I D V
 * _ _ _ _ _ _
 *
 */
void pha( char accum, unsigned char* sp, Memory* mem );

/*
 * Push status register onto stack
 *
 * S toS
 *
 * N Z C I D V
 * _ _ _ _ _ _
 *
 */
void php( char status, unsigned char* sp, Memory* mem );

/*
 * Pull accumulator from stack
 *
 * A fromS
 *
 * N Z C I D V
 * _ _ _ _ _ _
 *
 */
void pla( char* accum, unsigned char* sp, const Memory* memory );

/*
 * Pull status from stack
 *
 * S fromS
 *
 * N Z C I D V
 * from status 
 *
 */
void plp( char* status, unsigned char* sp, const Memory* mem );

/*
 * Rotate one bit left (memory or accumulator)
 *
 * N Z C I D V
 * / / / _ _ _
 *
 */
void rol( char* target, char* status );

/*
 * Rotate one bit right (memory or accumulator)
 *
 * N Z C I D V
 * / / / _ _ _
 *
 */
void ror( char* target, char* status );

/*
 * Return from interrupt
 *
 * S  fromS
 * PC fromS
 *
 * N Z C I D V
 * From Stack
 *
 */
void rti( char* pc, unsigned char* sp, char* status, const Memory* mem );

/*
 * Return from subroutine
 *
 * PC fromS
 * PC <= PC + 1
 *
 * N Z C I D V
 * _ _ _ _ _ _
 *
 */
void rts( char* pc, unsigned char* sp, const Memory* mem );

/*
 * Subtract memory from accumulator with borrow
 *
 * A <= A - M - C
 *
 * N Z C I D V
 * / / / _ _ /
 *
 */
void sbc( char* accum, char* status, char arg );

/*
 * Set carry flag
 *
 * N Z C I D V
 * _ _ 1 _ _ _
 *
 */
void sec( char* status );

/*
 * Set decimal mode
 *
 * N Z C I D V
 * _ _ _ _ 1 _
 *
 */
void sed( char* status );

/*
 * Set interrupt disable status
 *
 * N Z C I D V
 * _ _ _ 1 _ _
 *
 */
void sei( char* status );

/*
 * Store accumulator in memory
 *
 * N Z C I D V
 * _ _ _ _ _ _
 *
 */
void sta( char accum, char* memory );

/*
 * Store x index in memory
 *
 * N Z C I D V
 * _ _ _ _ _ _
 *
 */
void stx( char x, char* memory );

/*
 * Store y index in memory
 *
 * N Z C I D V
 * _ _ _ _ _ _
 *
 */
void sty( char y, char*memory );

/*
 * Transfer accumulator to index X
 *
 * N Z C I D V
 * / / _ _ _ _
 *
 */
void tax( char accum, char* status, char* x );

/*
 * Transfer accumulator to index Y
 *
 * N Z C I D V
 * / / _ _ _ _
 *
 */
void tay( char accum, char* status, char* y ); 

/*
 * Transfer stack pointer to index X
 *
 * N Z C I D V
 * / / _ _ _ _
 *
 */
void tsx( char sp, char* status, char* x );

/*
 * Transfer index X to accumulator
 *
 * N Z C I D V
 * / / _ _ _ _
 *
 */
void txa( char x, char* status, char* accum );

/*
 * Transfer index X to stack pointer
 *
 * N Z C I D V
 * / / _ _ _ _
 *
 */
void txs( char x, char* status, char* sp );

/*
 * Transfer index Y to accumulator
 *
 * N Z C I D V
 * / / _ _ _ _
 *
 */
void tya( char y, char* status, char* accum );
