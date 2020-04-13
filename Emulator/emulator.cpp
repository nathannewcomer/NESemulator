/*
 * emulator.cpp
 * Emulates an NES.
 */

#include<stdio.h>
#include <stdint.h>
#include <malloc.h>


/* represents the CPU registers */
struct Registers {
	/* these 4 are 1 byte */
	uint8_t a;	/* accumulator */
	uint8_t x;	/* x index */
	uint8_t y;	/* y index */
	uint8_t p;	/* processor status aka condition codes */

	/* these 2 are 2 bytes */
	uint16_t pc;	/* program counter */
	uint16_t s;	/* stack pointer */
} registers;

/* represents RAM, equal to 2KB (2048 bytes) */
uint8_t *memory;

/* making these global might be a bad idea but I don't want to pass these into every function */

/* inintializes the registers and allocates RAM */
void initialize() {
	int i = 0;

	/* initialize everything to 0x0 */
	registers = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
	
	memory = (uint8_t*)malloc(sizeof(uint8_t) * 2048);

	for (i = 0; i < 2048; i++) {
		memory[i] = 0x0;
	}

}

/* frees memory */
void powerdown() {
	free(memory);
}

int main() {
	
	initialize();

}
