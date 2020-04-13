/*
 * disassembler.cpp
 * Disassembles machine code for a MOS 6502 processor.
 */

#include <cstdio>
#include <malloc.h>

/*
 * Disassembles 6502 machine code
 * param buffer: data stream
 * param pc: program counter
 * param output: file to output
 * returns: number of bytes in the opcode
 */
int disassemble(unsigned char *buffer, int pc, FILE *output) {
    int opbytes = 1;

    switch (buffer[pc]) {

        /* look up the opcodes for the 6502, I'm not explaining it all here */
        case 0x00: 	fprintf(output, "BRK\n");    break;
        case 0x01:  fprintf(output, "ORA($%02X, X)\n",   buffer[pc + 1]); opbytes = 2;    break;
        case 0x05:  fprintf(output, "ORA $%02X\n", buffer[pc + 1]);   opbytes = 2;    break;
        case 0x06:  fprintf(output, "ASL $%02X\n", buffer[pc + 1]);   opbytes = 2;    break;
        case 0x08:  fprintf(output, "PHP\n");    break;
        case 0x09:  fprintf(output, "ORA #%02X\n", buffer[pc + 1]);   opbytes = 2;   break;
        case 0x0a: 	fprintf(output, "ASL A\n");  break;
        case 0x0d: 	fprintf(output, "ORA $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);    opbytes = 3;    break;
        case 0x0e: 	fprintf(output, "ASL $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);    opbytes = 3;    break;
        case 0x10: 	fprintf(output, "BPL $%02X\n", buffer[pc + 1]); break;
        case 0x11: 	fprintf(output, "ORA($%02X), Y\n", buffer[pc + 1]); opbytes = 2;  break;
        case 0x15: 	fprintf(output, "ORA $%02X, X\n", buffer[pc+1]); opbytes = 2;    break;
        case 0x16: 	fprintf(output, "ASL $%02X, X\n", buffer[pc + 1]);  opbytes = 2;  break;
        case 0x18: 	fprintf(output, "CLC\n");    break;
        case 0x19: 	fprintf(output, "ORA $%02X%02X, Y\n", buffer[pc + 1], buffer[pc + 2]); opbytes = 3;    break;
        case 0x1d: 	fprintf(output, "ORA $%02X%02X, X\n", buffer[pc + 1], buffer[pc + 2]); opbytes = 3;    break;
        case 0x1e: 	fprintf(output, "ASL $%02X%02X, X\n", buffer[pc + 1], buffer[pc + 2]);   opbytes = 3;    break;
        case 0x20: 	fprintf(output, "JSR $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0x21: 	fprintf(output, "AND($%02X, X)\n", buffer[pc + 1]); opbytes = 2;  break;
        case 0x24: 	fprintf(output, "BIT $%02X\n", buffer[pc + 1]); opbytes = 2;  break;
        case 0x25: 	fprintf(output, "AND $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x26: 	fprintf(output, "ROL $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x28: 	fprintf(output, "PLP\n");    break;
        case 0x29: 	fprintf(output, "AND #%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x2a: 	fprintf(output, "ROL A\n");  break;
        case 0x2c: 	fprintf(output, "BIT $%02X %02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3; break;
        case 0x2d: 	fprintf(output, "AND $%02X %02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3; break;
        case 0x2e: 	fprintf(output, "ROL $%02X %02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3; break;
        case 0x30: 	fprintf(output, "BMI $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x31: 	fprintf(output, "AND($%02X), Y\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x35: 	fprintf(output, "AND $%02X, X\n", buffer[pc + 1]); opbytes = 2; break;
        case 0x36: 	fprintf(output, "ROL $%02X, X\n", buffer[pc + 1]); opbytes = 2; break;
        case 0x38: 	fprintf(output, "SEC\n"); break;
        case 0x39: 	fprintf(output, "AND $%02X%02X, Y\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;  break;
        case 0x3d: 	fprintf(output, "AND $%02X%02X, X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;  break;
        case 0x3e: 	fprintf(output, "ROL $%02X%02X, X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;  break;
        case 0x40: 	fprintf(output, "RTI\n");    break;
        case 0x41: 	fprintf(output, "EOR($%02X, X)\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x45: 	fprintf(output, "EOR $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x46: 	fprintf(output, "LSR $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x48: 	fprintf(output, "PHA\n");    break;
        case 0x49: 	fprintf(output, "EOR #%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x4a: 	fprintf(output, "LSR A\n");  break;
        case 0x4c: 	fprintf(output, "JMP $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3; break;
        case 0x4d: 	fprintf(output, "EOR $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3; break;
        case 0x4e: 	fprintf(output, "LSR $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3; break;
        case 0x50: 	fprintf(output, "BVC $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x51: 	fprintf(output, "EOR($%02X), Y\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x55: 	fprintf(output, "EOR $%02X, X\n", buffer[pc + 1]); opbytes = 2; break;
        case 0x56: 	fprintf(output, "LSR $%02X, X\n", buffer[pc + 1]); opbytes = 2; break;
        case 0x58: 	fprintf(output, "CLI\n");  break;
        case 0x59: 	fprintf(output, "EOR $%02X%02X, Y\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;  break;
        case 0x5d: 	fprintf(output, "EOR $%02X%02X, X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0x5e: 	fprintf(output, "LSR $%02X%02X, X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0x60: 	fprintf(output, "RTS\n");    break;
        case 0x61: 	fprintf(output, "ADC($%02X, X)\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x65: 	fprintf(output, "ADC $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x66: 	fprintf(output, "ROR $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x68: 	fprintf(output, "PLA\n");    break;
        case 0x69: 	fprintf(output, "ADC #%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x6a: 	fprintf(output, "ROR A\n");  break;
        case 0x6c: 	fprintf(output, "JMP $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x6d: 	fprintf(output, "ADC $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0x6e: 	fprintf(output, "ROR $%02X%02X, X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0x70: 	fprintf(output, "BVS $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x71: 	fprintf(output, "ADC($%02X), Y\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x75: 	fprintf(output, "ADC $%02X, X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x76: 	fprintf(output, "ROR $%02X, X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x78: 	fprintf(output, "SEI\n");    break;
        case 0x79: 	fprintf(output, "ADC $%02X%02X, Y\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0x7d: 	fprintf(output, "ADC $%02X%02X, X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0x7e: 	fprintf(output, "ROR $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0x81: 	fprintf(output, "STA($%02X, X)\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x84: 	fprintf(output, "STY $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x85: 	fprintf(output, "STA $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x86: 	fprintf(output, "STX $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x88: 	fprintf(output, "DEY\n");    break;
        case 0x8a: 	fprintf(output, "TXA\n");
        case 0x8c: 	fprintf(output, "STY $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0x8d: 	fprintf(output, "STA $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0x8e: 	fprintf(output, "STX $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0x90: 	fprintf(output, "BCC $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x91: 	fprintf(output, "STA($%02X), Y\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x94: 	fprintf(output, "STY $%02X, X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x95: 	fprintf(output, "STA $%02X, X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x96: 	fprintf(output, "STX $%02X, Y\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0x98: 	fprintf(output, "TYA\n");    break;
        case 0x99: 	fprintf(output, "STA $%02X%02X, Y\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0x9a: 	fprintf(output, "TXS\n");    break;
        case 0x9d: 	fprintf(output, "STA $%02X%02X, X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xa0: 	fprintf(output, "LDY #%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xa1: 	fprintf(output, "LDA($%02X, X)\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xa2: 	fprintf(output, "LDX #%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xa4: 	fprintf(output, "LDY $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xa5: 	fprintf(output, "LDA $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xa6: 	fprintf(output, "LDX $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xa8: 	fprintf(output, "TAY\n");    break;
        case 0xa9: 	fprintf(output, "LDA #%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xaa: 	fprintf(output, "TAX\n");    break;
        case 0xac: 	fprintf(output, "LDY $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xad: 	fprintf(output, "LDA $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xae: 	fprintf(output, "LDX $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xb0: 	fprintf(output, "BCS $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xb1: 	fprintf(output, "LDA($%02X), Y\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xb4: 	fprintf(output, "LDY $%02X, X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xb5: 	fprintf(output, "LDA $%02X, X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xb6: 	fprintf(output, "LDX $%02X, Y\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xb8: 	fprintf(output, "CLV\n");    break;
        case 0xb9: 	fprintf(output, "LDA $%02X%02X, Y\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xba: 	fprintf(output, "TSX\n");    break;
        case 0xbc: 	fprintf(output, "LDY $%02X%02X, X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xbd: 	fprintf(output, "LDA $%02X%02X, X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xbe: 	fprintf(output, "LDX $%02X%02X, Y\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xc0: 	fprintf(output, "CPY #%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xc1: 	fprintf(output, "CMP($%02X, X)\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xc4: 	fprintf(output, "CPY $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xc5: 	fprintf(output, "CMP $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xc6: 	fprintf(output, "DEC $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xc8: 	fprintf(output, "INY\n");    break;
        case 0xc9: 	fprintf(output, "CMP #%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xca: 	fprintf(output, "DEX\n");    break;
        case 0xcc: 	fprintf(output, "CPY $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xcd: 	fprintf(output, "CMP $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xce: 	fprintf(output, "DEC $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xd0: 	fprintf(output, "BNE $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xd1: 	fprintf(output, "CMP($%02X), Y\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xd5: 	fprintf(output, "CMP $%02X, X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xd6: 	fprintf(output, "DEC $%02X, X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xd8: 	fprintf(output, "CLD\n");    break;
        case 0xd9: 	fprintf(output, "CMP $%02X%02X, Y\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xdd: 	fprintf(output, "CMP $%02X%02X, X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xde: 	fprintf(output, "DEC $%02X%02X, X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xe0: 	fprintf(output, "CPX #%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xe1: 	fprintf(output, "SBC($%02X, X)\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xe4: 	fprintf(output, "CPX $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xe5: 	fprintf(output, "SBC $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xe6: 	fprintf(output, "INC $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xe8: 	fprintf(output, "INX\n");    break;
        case 0xe9: 	fprintf(output, "SBC #%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xea: 	fprintf(output, "NOP\n");    break;
        case 0xec: 	fprintf(output, "CPX $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xed: 	fprintf(output, "SBC $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xee: 	fprintf(output, "INC $%02X%02X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xf0: 	fprintf(output, "BEQ $%02X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xf1: 	fprintf(output, "SBC($%02X), Y\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xf5: 	fprintf(output, "SBC $%02X, X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xf6: 	fprintf(output, "INC $%02X, X\n", buffer[pc + 1]); opbytes = 2;    break;
        case 0xf8: 	fprintf(output, "SED\n");    break;
        case 0xf9: 	fprintf(output, "SBC $%02X%02X, Y\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xfd: 	fprintf(output, "SBC $%02X%02X, X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        case 0xfe: 	fprintf(output, "INC $%02X%02X, X\n", buffer[pc + 1], buffer[pc + 2]);  opbytes = 3;    break;
        default:    break;

    }


    return opbytes;
}

int main()
{
    int i;
	int pc = 0;	/* program counter */
    unsigned char* buffer;  /* buffer to hold bytes */
    FILE *rom; /* ROM file containing machine code */
    FILE *output;    /* file to output to */
    errno_t error;
    long filesize;  /* size of ROM file */

    error = fopen_s(&rom, "mario.nes", "rb");
    fopen_s(&output, "output.txt", "w");

    if (error) {
        printf("File was not opened.\n");
        return error;
    }

    /* get size of file */
    fseek(rom, 0L, SEEK_END);
    filesize = ftell(rom);
    fseek(rom, 0L, SEEK_SET);

    /* set aside memory for the buffer */
    buffer = (unsigned char*)malloc(filesize);

    /* put contents of file into buffer */
    fread(buffer, 1, filesize, rom);
    /* close file */
    fclose(rom);

    /* disassemble */
    while (pc < filesize) {
        pc += disassemble(buffer, pc, output);
    }

    /* close file */
    fclose(output);

    free(buffer);

    return 0;
}