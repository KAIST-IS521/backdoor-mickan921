//-----------------------------------------------------------------------------
// minivm.c -- The basic definitions for the vm.
// Copyright (C) Philip Conrad 4/30/2013 @ 3:56 PM -- MIT License
//
//-----------------------------------------------------------------------------

#include "minivm.h"



//---------------------------------------------------------
// FUNCTION IMPLEMENTATIONS:


void halt(struct VMContext* ctx, const uint32_t instr)
{

}
void load(struct VMContext* ctx, const uint32_t instr)
{
    uint8_t reg1 = EXTRACT_B1(instr);
    uint8_t reg2 = EXTRACT_B2(instr);

}
void store(struct VMContext* ctx, const uint32_t instr)
{

}
void move(struct VMContext* ctx, const uint32_t instr)
{

}
void puti(struct VMContext* ctx, const uint32_t instr)
{

}
void add(struct VMContext* ctx, const uint32_t instr)
{

}
void sub(struct VMContext* ctx, const uint32_t instr)
{

}
void gt(struct VMContext* ctx, const uint32_t instr)
{

}
void ge(struct VMContext* ctx, const uint32_t instr)
{

}
void eq(struct VMContext* ctx, const uint32_t instr)
{

}
void ite(struct VMContext* ctx, const uint32_t instr)
{

}
void jump(struct VMContext* ctx, const uint32_t instr)
{

}
void op_puts(struct VMContext* ctx, const uint32_t instr)
{

}
void op_gets(struct VMContext* ctx, const uint32_t instr)
{

}




// Defers decoding of register args to the called function.
// dispatch :: VMContext -> uint32_t -> Effect()
void dispatch(struct VMContext* ctx, const uint32_t instr) {
    const uint8_t i = EXTRACT_B0(instr);
    (*ctx->funtable[i])(ctx, instr);
}


// Initializes a VMContext in-place.
// initVMContext :: VMContext -> uint32_t -> uint32_t -> [Reg] -> [FunPtr] -> Effect()
void initVMContext(struct VMContext* ctx, const uint32_t numRegs, const uint32_t numFuns, Reg* registers, FunPtr* funtable) {
    ctx->numRegs    = numRegs;
    ctx->numFuns    = numFuns;
    ctx->r          = registers;
    ctx->funtable   = funtable;
}


// Reads an instruction, executes it, then steps to the next instruction.
// stepVMContext :: VMContext -> uint32_t** -> Effect()
void stepVMContext(struct VMContext* ctx, uint32_t** pc) {
    // Read a 32-bit bytecode instruction.
    uint32_t instr = **pc;
    //printf("inst: %u\n", instr);
    // Dispatch to an opcode-handler.
    dispatch(ctx, instr);

    // Increment to next instruction.
    (*pc)++;
}

