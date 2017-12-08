#!/bin/bash
test=(JUMP LUI ADDI ADDIU ADD ADDU AND ANDI BNE BEQ LW_MEM_EXE SW_MEM_EXE LB_MEM_EXE LBU_MEM_EXE LH_MEM_EXE LHU_MEM_EXE LW_MEM_EXE SB_MEM_EXE SH_MEM_EXE SW_MEM_EXE SRA SRAV SRL SLL ADD_OVERFLOW SB LB DIVU NOR OR ORI SLLV SH LBU LH SUB MFHI MFLO MTHI MTLO XOR XORI SW LW BGTZ BLTZ BLEZ MULT MULTU SRLV)
output=(0 2 0 1 3 0 0 1 1 4 245 245 245 245 245 245 245 245 245 245 0 255 2 0 255 15 15 1 1 7 7 4 74 15 74 20 2 2 2 2 6 6 246 246 0 0 0 255 6 1)
echo " Instruction type, test number, Expected output, output, Test Result">>testbench/output/output.csv
for i in {0..60}
do
FILENAME="${test[i]}.bin"
./simulator/bin/mips_simulator testbench/binary/$FILENAME
let EXIT=$?
if [ $EXIT -eq ${output[i]} ]; then
echo "${test[i]}, $i, ${output[i]}, $EXIT, PASS"
echo "${test[i]}, $i, ${output[i]}, $EXIT, PASS">>testbench/output/output.csv
else 
echo "${test[i]}, $i, ${output[i]}, $EXIT, FAIL">>testbench/output/output.csv
echo "${test[i]}, $i, ${output[i]}, $EXIT, FAIL"
fi
done




