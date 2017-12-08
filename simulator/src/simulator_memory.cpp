#include "simulator_memory.h"
#include <bitset>
#include <iostream>
#include "stdint.h"

//#define AADR_NULL 0x0;
//#define START_EXE 0x10000000;
//#define END_EXE 0x11000000;
//#define START_RW 0x20000000;
//#define END_RW 0x24000000;
//#define ADDR_GETC 0x30000000;
//#define ADDR_PUTC 0x30000004;

using namespace std;

memory::memory() {
	mem = new uint8_t[0x30000008];
	for (int i = 0x20000000; i <= 0x24000000; i++) {
		mem[i] = 0;  //inistialise read write area of memory to 0
	}
	for (int i = 0x0; i <= 0x11000000; i++) {
		mem[i] = 0;	//EXE mem now initialised to 0
	}
}

void memory::write_byte(uint8_t data_in, PC pc){
    mem[pc.value()]=data_in;
}

uint32_t memory::read_word(PC pc){
	if (pc.value()%4!=0) { //check it is reading the first byte of a word if not exit
				exit(-11);
	}
	if (pc.value() > 0x11000000) {
		exit(-11); //CHECK TO ENSURE
	}
    uint32_t word = (mem[pc.value()]<<24)+(mem[pc.value()+1]<<16)+(mem[pc.value()+2]<<8)+mem[pc.value()+3];
	return word; //combine the 4 consecutive characters to create one 32 bit instruction



}
//rewrite
void memory::store_word(int address, uint32_t data){
    if (((address > 0x24000000) || (address < 0x20000000)) && (address!=0x30000004)) { //stop it reading or writting outside of area
        exit(-11);
    }// exception occurs here
	if(address == 0x30000004){
		uint8_t output;
		output=((data<<24)>>24);
		putchar(output);
	}
	else{
    uint8_t store=0;  //data from registers input as 32 bit number
    store = (data >> 24); //split the data into bytes and store
    mem[address+3]=store;
    store = ((data << 8) >> 24);
    mem[address+2]=store;
    store = ((data << 16) >> 24);
    mem[address+1]=store;
    store = ((data << 24) >> 24);
    mem[address]=store;
	}
}

uint32_t memory::load_word(int address){
		if (((address > 0x24000000) || (address < 0x20000000)) & (address!=0x30000000)) { //trying to read outside of area			
            exit(-11);
		}
        if(address == 0x30000000){ //read from loaction get_c
        uint8_t input;
		input = getchar();
		if((input & 0x80) == 0x80){ //MSB equal to 1
			return (0xFFFFFFFF & input); //sign extend with 1
		}
		else{
			return (0x000000FF & input); //sign extend with 0
		}
    }
	else{
		return (mem[address+3]<<24)+(mem[address+2]<<16)+(mem[address+1]<<8)+mem[address];
	}
		}

void memory::store_byte(int address, uint8_t data){
    if (((address > 0x24000000) || (address < 0x20000000)) && (address!=0x30000004) && (address!=0x30000005) && (address!=0x30000006) && (address!=0x30000007)) { //trying to read outside of area       

exit(-11);
    }
   if((address == 0x30000004) || (address == 0x30000005) || (address == 0x30000006) || (address == 0x30000007)){
		uint8_t output;
		output=((data<<24)>>24);
		putchar(output);
	}
	else{

    mem[address]=data;
}
	}

uint32_t memory::load_byteU(int address){ //
if (((address > 0x24000000) || (address < 0x20000000)) && (address!=0x30000000) && (address!=0x30000001) && (address!=0x30000002) && (address!=0x30000003)) { //trying to read outside of area      
        exit(-11);
    }
	  if((address==0x30000000) || (address==0x30000001) || (address==0x30000002) || (address==0x30000003)){ //read from loaction get_c
        uint8_t input;
		input = getchar();
		if((input & 0x80) == 0x80){ //MSB equal to 1
			return (0xFFFFFFFF & input); //sign extend with 1
		}
		else{
			return (0x000000FF & input); //sign extend with 0
		}
    }
	else{
uint8_t byte;
byte = mem[address]; //address points to first byte 
uint32_t word;
word = 0x0 ^ byte; //point 0s in front of byte
return word;
	}
}

uint32_t memory::load_byte(int address){
    if (((address > 0x24000000) || (address < 0x20000000)) && (address!=0x30000000) && (address!=0x30000001) && (address!=0x30000002) && (address!=0x30000003)) { //trying to read outside of area
exit(-11);
    }
	  if((address==0x30000000) || (address==0x30000001) || (address==0x30000002) || (address==0x30000003)){ //read from loaction get_c
        uint8_t input;
		input = getchar();
		if((input & 0x80) == 0x80){ //MSB equal to 1
			return (0xFFFFFFFF ^ input); //sign extend with 1
		}
		else{
			return (0x000000FF ^ input); //sign extend with 0
		}
    }
	else{
uint8_t byte;
byte = mem[address]; //address points to first byte 
uint32_t word;
if((byte>>7) == 1){ //MSB equal to 1
word = 0xFFFFFF00 + byte; //point 1s in front of byte
}
if((byte>>7) == 0){ //MSB is 0
word = byte; //point 0s in front of byte
}
return word;
	}
}


uint32_t memory::load_halfword(uint32_t address){
    if(((address%2!=0) || (address > 0x24000000) || (address < 0x20000000) ) && (address!=0x30000000) && (address!=0x30000002)){ //check it is reading from half of a word
        
        exit(-11);
    }
    if((address==0x30000000) || (address==0x30000002) ){ //read from loaction get_c
        uint8_t input;
		input = getchar();
		if(((input) & (0x80)) == 0x80){ //MSB equal to 1
			return (0xFFFFFFFF & input); //sign extend with 1
		}
		else{
			return (0x000000FF & input); //sign extend with 0
		}
    }
	else{
        uint8_t byte1=mem[address+1];
        uint8_t byte2=mem[address];
        uint32_t word;
        uint32_t thalf; //top and bottom half of final 32 bit word
        uint32_t bhalf;
        if((byte2>>7) == 1){//MSB 1
            thalf=(0xFFFF0000 + byte1);
            bhalf=(byte2<<8);
            return word=(thalf+bhalf); //or the two halfs to give the final word
        }
        if((byte2>>7) == 0){// MSB 0
            thalf=(byte1);
            bhalf=(byte2<<8);
            return word=(thalf+bhalf); //or the two halfs to give the final word
        }
	}
}



uint32_t memory::load_halfwordU(uint32_t address){
    if(((address%2!=0) || (address > 0x24000000) || (address < 0x20000000)) && ((address!=0x30000000) || (address!=0x30000002))){ //check it is reading from half of a work
	
	exit(-11);
}
	  if(address==0x30000000 || address==0x30000002 ){ //read from loaction get_c
        uint8_t input;
		input = getchar();
		if((input & 0x80) == 0x80){ //MSB equal to 1
			return (0xFFFFFFFF & input); //sign extend with 1
		}
		else{
			return (0x000000FF & input); //sign extend with 0
		}
    }
	else{
	uint8_t byte1=mem[address+1];
    uint8_t byte2=mem[address];
	uint32_t word;
	uint32_t thalf; //top and bottom half of final 32 bit word
	uint32_t bhalf;
	thalf=(0x0 ^ byte1);
	bhalf=(byte2<<8);
	return word=(thalf^bhalf);
	}
}

void memory::store_halfword(uint32_t address, uint16_t data){
	if((address%2!=0 || address > 0x24000000 || address < 0x20000000) && (address!=0x30000004) && (address!=0x30000006)){//check it is storing to half of a word
	
	exit(-11);
}
if(address == 0x30000004 || address == 0x30000006){
		uint8_t output;
		output=((data<<24)>>24);
		putchar(output);
	}
else{
uint8_t store=0;
store= ((data >> 8));
mem[address]=store;
store = ((data << 8) >> 8);
mem[address+1]=store;
}
}
memory::~memory(){
    delete[] mem;
}
