//-----------------------------------------------------------------------------
// minivm.c -- The basic definitions for the vm.
// Copyright (C) Philip Conrad 4/30/2013 @ 3:56 PM -- MIT License
//
//-----------------------------------------------------------------------------

#include "minivm.h"
#include <stdbool.h>

extern bool is_running;

//---------------------------------------------------------
// FUNCTION IMPLEMENTATIONS:


void halt(struct VMContext* ctx __attribute__((unused)), const uint32_t instr __attribute__((unused)))
{
    is_running = false;
}


// load (reg1), (reg2)
// Loads 1 byte value from memory located at address reg2 into reg1
void load(struct VMContext* ctx, const uint32_t instr)
{
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t reg2 = EXTRACT_B2(instr);
    uint32_t addr = ctx->r[reg2].value;

    if(addr >= HEAP_SIZE)
    {
        printf("\tSegmentation fault (load)\n");
        exit(1);
    }

    ctx->r[reg1].value = (uint32_t)ctx->heap[addr];
}

// store (reg1), (reg2)
// Store 1 byte value of the reg2 to memory located at address reg1
void store(struct VMContext* ctx, const uint32_t instr)
{
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t reg2 = EXTRACT_B2(instr);
    uint32_t addr = ctx->r[reg1].value;

    if(addr >= HEAP_SIZE)
    {
        printf("\tSegmentation fault (store)\n");
        exit(1);
    }

    ctx->heap[addr] = (uint32_t)ctx->r[reg2].value;
}

// move (reg1), (reg2)
// Move 32 bit value from reg2 to reg1
void move(struct VMContext* ctx, const uint32_t instr)
{
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t reg2 = EXTRACT_B2(instr);

    ctx->r[reg1].value = ctx->r[reg2].value;
}

// puti (reg), (imm)
// Move an 8 bit immediate value (imm1) to a reg1
void puti(struct VMContext* ctx, const uint32_t instr)
{
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t imm1 = EXTRACT_B2(instr);

    ctx->r[reg1].value = imm1;
}

// add (reg1), (reg2), (reg3)
// adds the values stored in reg2 and reg3 then stores the result in reg1
void add(struct VMContext* ctx, const uint32_t instr)
{
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t reg2 = EXTRACT_B2(instr);
    uint8_t reg3 = EXTRACT_B3(instr);

    ctx->r[reg1].value = ctx->r[reg2].value + ctx->r[reg3].value;
}

// sub (reg1), (reg2), (reg3)
// subtracts the values stored in reg2 and reg3 then stores the result in reg1
void sub(struct VMContext* ctx, const uint32_t instr)
{
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t reg2 = EXTRACT_B2(instr);
    uint8_t reg3 = EXTRACT_B3(instr);

    ctx->r[reg1].value = ctx->r[reg2].value - ctx->r[reg3].value;
}

// gt (reg1), (reg2), (reg3)
// Compares the values stored in reg2 and reg3, stores 1 in reg1 if reg2 > re3 or stores zero otherwise.
void gt(struct VMContext* ctx, const uint32_t instr)
{
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t reg2 = EXTRACT_B2(instr);
    uint8_t reg3 = EXTRACT_B3(instr);

    if(ctx->r[reg2].value > ctx->r[reg3].value)
    {
        ctx->r[reg1].value = 1;
    }
    else
    {
        ctx->r[reg1].value = 0;
    }
}

// ge (reg1), (reg2), (reg3)
// Compares the values stored in reg2 and reg3, stores 1 in reg1 if reg2 >= re3 or stores zero otherwise.
void ge(struct VMContext* ctx, const uint32_t instr)
{
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t reg2 = EXTRACT_B2(instr);
    uint8_t reg3 = EXTRACT_B3(instr);

    if(ctx->r[reg2].value >= ctx->r[reg3].value)
    {
        ctx->r[reg1].value = 1;
    }
    else
    {
        ctx->r[reg1].value = 0;
    }
}

// eq (reg1), (reg2), (reg3)
// Compares the values stored in reg2 and reg3, stores 1 in reg1 if reg2 == re3 or stores zero otherwise.
void eq(struct VMContext* ctx, const uint32_t instr)
{
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t reg2 = EXTRACT_B2(instr);
    uint8_t reg3 = EXTRACT_B3(instr);

    if(ctx->r[reg2].value == ctx->r[reg3].value)
    {
        ctx->r[reg1].value = 1;
    }
    else
    {
        ctx->r[reg1].value = 0;
    }
}

// ite (reg1), (imm1), (imm2)
// if-then-else, if the value in reg1 is > 0 then the instruction pointer will have imm1.
// if reg1 ==0 then the intruction pointer will have imm2
void ite(struct VMContext* ctx, const uint32_t instr)
{
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t imm1 = EXTRACT_B2(instr);
    uint8_t imm2 = EXTRACT_B3(instr);

    if(ctx->r[reg1].value > 0)
    {
        ctx->pc = imm1;
    }
    else
    {
        ctx->pc = imm2;
    }
}

// jump (imm1)
// Changes the intruction pointer. imm1 indicates the addess to be executed next.
// ex. jump 2 means go to the third instrunction of the code
void jump(struct VMContext* ctx, const uint32_t instr)
{
    uint8_t imm1 = EXTRACT_B1(instr);

    ctx->pc = imm1;
}

// puts (reg1)
// outputs an ASCII string (terminated by NULL) located at memory address (reg) to the screen
void op_puts(struct VMContext* ctx, const uint32_t instr)
{
    uint8_t reg1 = EXTRACT_B1(instr);
    uint32_t ascii_string = ctx->r[reg1].value;

    char c;
    while(true)
    {
        if(ascii_string >= HEAP_SIZE)
        {
            printf("\tSegmentation fault (puts)\n");
            exit(1);
        }
        c = ctx->heap[ascii_string];
        if(c == 0)
        {
            break;
        }
        putchar(c);
        ascii_string++;
    }
}

// gets (reg1)
// takes an ASCII string (terminated by null) as an input from STDIN and store the string to memory address reg1
void op_gets(struct VMContext* ctx, const uint32_t instr)
{
    uint8_t reg1 = EXTRACT_B1(instr);
    uint32_t ascii_string = ctx->r[reg1].value;

    uint8_t c;
    while(true)
    {
        c = (uint8_t) getchar();
        if(c == '\n' || c == '\0')
        {
            break;
        }
        if(ascii_string >= HEAP_SIZE)
        {
            printf("\tSegmentation fault (gets)\n");
            exit(1);
        }
        ctx->heap[ascii_string] = c;
        ascii_string++;
    }
}




// Defers decoding of register args to the called function.
// dispatch :: VMContext -> uint32_t -> Effect()
void dispatch(struct VMContext* ctx, const uint32_t instr) {
    const uint8_t i = EXTRACT_B0(instr);
    
    // Checking if opcide is valid
    FunPtr opcode = *ctx->funtable[i];
    if(opcode)
    {
        (opcode)(ctx, instr);
        // ite and jum does not increment pc
        if (i == 0xa0 || i == 0xb0)
        {
            return;
        }
        ctx->pc++;
    }
    else
    {
        printf("\t Invalid opcode\n");
        exit(1);
    }
    //(*ctx->funtable[i])(ctx, instr);
}


// Initializes a VMContext in-place.
// initVMContext :: VMContext -> uint32_t -> uint32_t -> [Reg] -> [FunPtr] -> Effect()
void initVMContext(struct VMContext* ctx, const uint32_t numRegs, const uint32_t numFuns, Reg* registers, FunPtr* funtable, uint32_t* code, uint32_t codeSize) {
    ctx->numRegs    = numRegs;
    ctx->numFuns    = numFuns;
    ctx->r          = registers;
    ctx->funtable   = funtable;

    ctx->pc         = 0;
    ctx->code       = code;
    ctx->codeSize   = codeSize;
}


// Reads an instruction, executes it, then steps to the next instruction.
// stepVMContext :: VMContext -> uint32_t** -> Effect()
void stepVMContext(struct VMContext* ctx) {
    if (ctx->pc >= HEAP_SIZE)
    {
        printf("\t Heap overflow\n");
        exit(1);
    }
    // Read a 32-bit bytecode instruction.
    uint32_t instr = *(ctx->code + ctx->pc);

    // Dispatch to an opcode-handler.
    dispatch(ctx, instr);

    // Increment to next instruction.
    //(*pc)++;
}

