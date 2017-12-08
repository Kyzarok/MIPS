#include <iostream>
#include <fstream>
#include <bitset>
#include "simulator_memory.h"
#include "program_counter.h"
#include <cmath>
#include <cstdlib>
#include "readReg.h"

using namespace std;

void Rsort(Reg current, const uint32_t& rs, const uint32_t& rt, uint32_t& rd, PC&pc, uint32_t& HI, uint32_t& LO, uint32_t  registers[32]);

void Isort(Reg current, const uint32_t& rs, uint32_t& rd, uint16_t adr, memory& mem, PC&pc, uint32_t registers[32]);

void Jsort(const uint8_t& opcode, uint32_t tgt, PC&pc, uint32_t registers[32]);

int main(int argc, char* argv[]) {
	memory mem;
	PC pc;
	uint8_t data_in;
	uint32_t registers[32];
	for(int i = 0; i <= 31; i++){
		registers[i] = 0;
	}
	uint32_t HI, LO;
	ifstream binary_in;
	char data;
	binary_in.open(argv[1], ios::in | ios::binary);
	if (!(binary_in.is_open())) {
		cerr << "binary not found" << endl;
		exit(-21);
	}
	while (binary_in.get(data)) {
		//see what data goes in
		data_in = data;
		mem.write_byte(data_in,pc); //put binary values in array
		pc.increment_byte(); //increment the pc
	}
	pc.reset(); //reset the pc to read out of the array
	uint32_t input;
    	while(true){   //go through ROM while stuff in ROM to go through
		pc.increment_word();
		input = mem.read_word(pc);

		
		if(pc.value()==0){
		  exit(((registers[2]<<24)>>24));
		}
		if(pc.check_delay()==true){
			pc.jump();
			pc.change_delay();

		}
		Reg tmp(input);
		tmp.generate(); //put the bits of the instruction in to a 32 element array
		//function to decode
		//check opcode, if R or I type get registers that are relevant and return as parameters

		if (tmp.get_op() == 0b000000) {

		    uint8_t rs = tmp.get_rs();
		    uint8_t rt = tmp.get_rt();
		    uint8_t rd = tmp.get_rd();
		    Rsort(tmp, registers[rs], registers[rt], registers[rd], pc, HI, LO, registers);
		}
		if (tmp.get_op() == (0b000010) | tmp.get_op() == (0b000011)) {
		   uint32_t tgt = tmp.get_tgt();
		    Jsort(tmp.get_op(), tgt, pc, registers);

		  //  Jsort(tmp, tgt);
		    //will figure out the logistics of this later :P
        	}
        else {

            		uint8_t rs = tmp.get_rs();
            		uint8_t rd = tmp.get_rt(); //in this situation there is never a second source operand so we can treat rt as rd
			uint16_t adr = tmp.get_adr();
            		//make sure adr is made relevant to mem_loc
            		//we will need to do this by accessing mem here and returning it as a parameter to Isort
            		Isort(tmp, registers[rs], registers[rd], adr, mem, pc, registers);	//ergo, adr should be mem(adr)
        	}
/*for(int j=0;j<5;j++){
cout<<j<<"  "<<bitset<32>(registers[j])<<endl;
cout<<endl;
}*/
		}
    return 0;
}



void Rsort(Reg current, const uint32_t& rs, const uint32_t& rt, uint32_t& rd, PC&pc, uint32_t& HI, uint32_t& LO, uint32_t registers[]) {
    //char sham = current.get_sham();
    /*uint8_t sham = current.get_sham();
     uint16_t rdsham = (rd << 5) + sham; //10 bits used*/
    uint8_t sham = current.get_sham();
    current.generate();
    uint8_t func = current.get_func();

    if (func == 0b100000) {	//ADD
        /*if(rs>>31 == 1 && rt >> 31 == 1 && (rs+rt)>>31 == 1 | rs>>31 == 0 && rt >>31 == 0 && (rs+rt)>>31 == 0 ){                                //overflow
            rd=rs+rt;
        }*/
	int32_t signedRS = rs;
	int32_t signedRT = rt;
	if((signedRS < 0)&&(signedRT < 0)){
		uint32_t output = rs + rt;
		int32_t check = output;
		if(check > 0){
			exit(-10);	//
		}
		else{
			rd = rs + rt;
		}
	}
	if((signedRS > 0)&&(signedRT > 0)){
		uint32_t output = rs + rt;
		int32_t check = output;
		if(check < 0){
			exit(-10);	//
		}
		else{
			rd = rs + rt;
		}
	}
	else{
		rd = rs + rt;
	}
    }
    if (func == 0b100001) {	//ADDU
        rd = rs + rt;
    }
    if (func == 0b100100) {	//AND
        rd = rs & rt;
    }
    if (func == 0b011010) {	//DIV
        int32_t signedRS = rs;
        int32_t signedRT = rt;
		if(signedRT==0){
			cerr<<"attempt to divide by 0"<<endl;
			exit(-10);
		}
        int64_t now = signedRS/signedRT;
        LO = signedRS / signedRT;
        HI = signedRS % signedRT;
    }
    if (func == 0b011011) {	//DIVU
        uint64_t now = rs/rt;
		if(rt==0){
			cerr<<"attempt to divide by 0"<<endl;
			exit(-10);
		}
            LO = rs/rt;
        HI = rs%rt;
    }
    if (func == 0b011000) {	//MULT
        int32_t signedRS = rs;
        int32_t signedRT = rt;
        int64_t now = signedRS * signedRT;
        LO = (now << 32) >> 32;
        HI = now >> 32;
    }
    if (func == 0b011001) {	//MULTU
        uint64_t now = (rs * rt);
        LO = (now << 32) >> 32;
        HI = now >> 32;
    }
    if (func == 0b100111) {	//NOR
        rd=~(rs|rt);
    }
    if (func == 0b100101) {	//OR
        rd=(rs|rt);
    }
    if (func == 0b000000) {	//SLL
        rd=(rt << sham);
    }
    if (func == 0b000100) {	//SLLV
        rd=(rt<<rs);
    }
    if (func == 0b000011) {	//SRA
        int32_t data_0msb = rt;
	rd = (data_0msb >> sham);

    }
    if (func == 0b000111) {	//SRAV
        int32_t data_0msb = rt;

	rd = (data_0msb >> rs);

    }
    if (func == 0b000010) {	//SRL
        rd=(rt >> sham);
    }
    if (func == 0b000110) {	//SRLV
        rd=(rt>>rs);
    }
    if (func == 0b100010) {	//SUB
	int32_t signedRS = rs;
	int32_t signedRT = rt;
	if((signedRS > 0)&&(signedRT < 0)){
		uint32_t output = rs - rt;
		int32_t check = output;
		   if(check < 0){

			 exit(-10);	//
		                }
		    else{
			rd = rs - rt;
		        }
	}
     else if((signedRS < 0)&&(signedRT > 0)){
		uint32_t output = rs - rt;
		int32_t check = output;
		if(check > 0){

			exit(-10);	//
		            }
		else{
			rd = rs - rt;
		   }
	          }
else{
rd=rs-rt;
}
	  }
    if (func == 0b100011) {	//SUBU
        rd=rs-rt;
    }
    if (func == 0b100110) {	//XOR
        rd=rs^rt;
    }
    if(func == 0b001000){ //jr
       uint32_t address;
       address=rs;
        if((address > 0x11000000| address <0x10000000)&address!=0){
            exit(-11);
        }
        pc.store_addressJ(address);
    }

    if(func == 0b001001){ //jlr
       rd=pc.value()+8;
       uint32_t address = rs;
        if((address > 0x11000000| address <0x10000000)&address!=0){
            exit(-11);
        }
        pc.store_addressJ(address);
    }

    if(func == 0b101011){ //sltu
        if(rs<rt){
            rd=1;
        }
        else{
            rd=0;
        }
    }
    if(func == 0b101010){ //slt
	int32_t signedRS = rs;
	int32_t signedRT = rt;
        if(rs < rt){                                      //overflow
            rd=1;
        }
        else{
            rd=0;
        }
    }
    if(func == 0b010000){//MFHI
        rd = HI;
    }
    if(func == 0b010010){//MFLO
        rd = LO;
    }
    if(func == 0b010001){//MTHI
        HI = rs;
    }
    if(func == 0b010011){//MTLO
        LO = rs;
    }
}


void Isort(Reg current, const uint32_t& rs, uint32_t& rd, uint16_t adr, memory& mem, PC&pc, uint32_t registers[]) {
    //memory access type
    //this will probably require us to access the mem within main
    int pcounterNew= 0;
    uint8_t opcode = current.get_op();

    if (opcode == 0b001000) {//ADDI
        int32_t signedRS = rs;
	int32_t signedRT = adr;
	if((signedRS < 0)&&(signedRT < 0)){
		uint32_t output = rs + adr;
		int32_t check = output;
		if(check > 0){
			exit(-10);	//
		}
		else{
			rd = rs + adr;
		}
	}
	if((signedRS > 0)&&(signedRT > 0)){
		uint32_t output = rs + adr;
		int32_t check = output;
		if(check < 0){
			exit(-10);	//
		}
		else{
			rd = rs + adr;
		}
	}
	else{
		rd = rs + adr;
	}
    }
    if (opcode == 0b001001 ) {//ADDIU
        rd=rs+adr;//16 bits signed is added to 32 bit rs value, if addition overflows, no overflow exception
    }
    if (opcode == 0b001100 ) {//ANDI
        uint32_t immediate;
        immediate = 0x0000FFFF & adr;
        rd=rs & immediate;//rd = rs & imm
    }
    if (opcode == 0b001001 ) {//BEQ
        if(rs==rd){
               /*   int address;
            if(adr>>15 == 1){ //if MSB equal to 1
            address=0xFFFC0000 ^ (adr<<2); //signextend 
            }
 	    else{
	    address=0x0003FFFF ^ (adr<<2);	
		}
            pc.store_addressB(address);
        }*/
     int address;
            if(adr>>15 == 1){ //if MSB equal to 1
            address=0xFFFC0000 + (adr<<2); //signextend 
            }
 	    else{
	    address=(adr<<2);	
		}
            pc.store_addressB(address);
        }
    }
    if (opcode == 0b000001) {//BGEZAL
        if(rs==0 | rs & 0x80000000 == 0x80000000){
            registers[31]=pc.value()+8;
               int address;
            if(adr>>15 == 1){ //if MSB equal to 1
            address=0xFFFC0000 + (adr<<2); //signextend 
            }
 	    else{
	    address=(adr<<2);	
		}
            pc.store_addressB(address);
        }
    }
    if (opcode == 0b000111 ) {//BGTZ
        if((rs>>31) == 0 && rs!=0){
                int address;
            if(adr>>15 == 1){ //if MSB equal to 1
            address=0xFFFC0000 + (adr<<2); //signextend 
            }
 	    else{
	    address=(adr<<2);	
		}
            pc.store_addressB(address);
        }
    }
    if (opcode == 0b000110 ) {//BLEZ
        if(rs == 0 || (rs>>31)==1){
                int address;
            if(adr>>15 == 1){ //if MSB equal to 1
            address=0xFFFC0000 + (adr<<2); //signextend 
            }
 	    else{
	    address=(adr<<2);	
		}
            pc.store_addressB(address);
        }
    }
    if (opcode == 0b000001 ) {//BLTZ
        if((rs>>31)==1){
              int address;
            if(adr>>15 == 1){ //if MSB equal to 1
            address=0xFFFC0000 + (adr<<2); //signextend 
            }
 	    else{
	    address=(adr<<2);	
		}
            pc.store_addressB(address);
        }
    }
    if (opcode == 0b000001 ) {//BLTZAL 
      if((rs>>31)==1){
registers[31]=pc.value()+8;
      /*         int address;
            if(adr>>15 == 1){ //if MSB equal to 1
            address=0xFFFC0000 + (adr<<2); //signextend 
            }
 	    else{
	    address=(adr<<2);	
		}
            pc.store_addressB(address);
        }*/
     int address;
            if(adr>>15 == 1){ //if MSB equal to 1
            address=0xFFFC0000 + (adr<<2); //signextend 
            }
 	    else{
	    address=(adr<<2);	
		}
            pc.store_addressB(address);
        }
    }
    if (opcode == 0b000101) {//BNE
        if(rs!=rd){
             int address;
            if(adr>>15 == 1){ //if MSB equal to 1
            address=0xFFFC0000 ^ (adr<<2); //signextend 
            }
 	    else{
	    address=0x0003FFFF ^ (adr<<2);	
		}
            pc.store_addressB(address);
        }
    }
    if (opcode == 0b100000) {//LB
        uint32_t address= rs+ adr;
        rd = mem.load_byte(address);
    }
    if (opcode == 0b100100 ) {//LBU
        uint32_t address= rs+ adr;
        rd = mem.load_byteU(address);
    }
    if (opcode == 0b100001 ) {//LH
        uint32_t address= rs+ adr;
        rd = mem.load_halfword(address);
    }
    if (opcode == 0b100101 ) {//LHU
        uint32_t address= rs+ adr;
        rd = mem.load_halfwordU(address);
    }
    if (opcode == 0b001111) {//LUI
        uint32_t immediate;
        immediate = ( adr << 16 );
        rd = immediate;
    }
    if (opcode == 0b100011) {//LW
        uint32_t address= rs+ adr;
        rd = mem.load_word(address);
    }
 /*   if (opcode == 0b100010 ) {//LWL
        
    }
    if (opcode == 0b100110) {//LWR
        
    } */
    if (opcode == 0b001101 ) {//ORI
        uint32_t immediate;
        immediate=0x0000FFFF;
        immediate=immediate&adr;
        rd=rs|immediate;
    }
    if (opcode == 0b101000) {//SB
        uint32_t address= rs+ adr;
	uint8_t data;

	data=((rd<<24)>>24);
	
        mem.store_byte(address,data);
        
        
    }
    if (opcode == 0b101001 ) {//SH
        uint32_t address= rs+ adr;
        uint16_t data= ((rd<<16)>>16);
        mem.store_halfword(address,data);
        
    }
    if (opcode == 0b001010 ) {//SLTI
        if(rs>>31==1){
            rd=1;
        }
        if(rs-adr<0){
           rd=1;
        }
        else{
            rd=0;
        }
    }
    if (opcode == 0b001011 ) {//SLTIU
        uint32_t immediate;
        immediate=0x0000FFFF;
        immediate=immediate&adr;
        if(rs<immediate){
            rd=1;
        }
        else{
            rd=0;
        }
    }
    if (opcode == 0b101011) {//SW
        uint32_t address= rs + adr;
        uint32_t data = rd;
        mem.store_word(address, data);
    }
    if (opcode == 0b001110 ) {//XORI
        uint32_t immediate;
        immediate = 0x0000FFFF & adr;
        rd=rs^immediate;
    }
}

void Jsort(const uint8_t& opcode, uint32_t tgt, PC&pc, uint32_t registers[]) {
	if(opcode == 0b000010 ){
        	uint32_t address;
        	address =0x0003FFFF & (tgt << 2);
		if((address > 0x11000000 | address <0x10000000)&address!=0){
        		exit(-11);
		}
		pc.store_addressJ(address);
	}
	if(opcode == 0b000011 ){
		registers[31]=pc.value()+8;
       		uint32_t address;
       		address =0x0003FFFF & (tgt << 2);
                if((address > 0x11000000| address <0x10000000)&address!=0){
	            	exit(-11);
	        }
       	pc.store_addressJ(address);
    	}
}





