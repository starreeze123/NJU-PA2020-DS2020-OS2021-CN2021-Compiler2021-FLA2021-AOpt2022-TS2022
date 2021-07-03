#include "cpu/instr.h"
/*
Put the implementations of `xor' instructions here.
*/
static void instr_execute_2op() 
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
	opr_dest.val = alu_xor(sign_ext(opr_src.val, opr_src.data_size), opr_dest.val, opr_dest.data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(xor, r, rm, b)
make_instr_impl_2op(xor, r, rm, v)
make_instr_impl_2op(xor, rm, r, b)
make_instr_impl_2op(xor, rm, r, v)
make_instr_impl_2op(xor, i, rm, b)
make_instr_impl_2op(xor, i, rm, bv)
make_instr_impl_2op(xor, i, rm, v)
make_instr_impl_2op(xor, i, r, b)
make_instr_impl_2op(xor, i, r, v)
make_instr_impl_2op(xor, i, r, bv)

make_instr_func(xor_al) {
    OPERAND imm;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    imm.data_size = 8;
    imm.sreg = SREG_CS;
    
    operand_read(&imm);
    cpu.gpr[0]._8[0] = alu_xor(imm.val, cpu.gpr[0]._8[0], 8);
    
    return 2;
}
make_instr_func(xor_eax) {
    OPERAND imm;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    imm.data_size = data_size;
    imm.sreg = SREG_CS;
    
    operand_read(&imm);
    if(data_size == 32)
        cpu.eax = alu_xor(imm.val, cpu.eax, data_size);
    else    cpu.gpr[0]._16 = alu_xor(imm.val, cpu.gpr[0]._16, data_size);
    
    return 1 + data_size / 8;
}