emulator: television.c
	gcc -Wall -ansi -o emulator television.c `pkg-config --libs --cflags gtk+-2.0`

processor: processor_test.c processor.c processor.h
	gcc -Wall -ansi -o processor_test processor_test.c processor.c
