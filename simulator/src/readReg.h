#ifndef READREG_H
#define READREG_H

#include "subclass.hpp"

class Reg {

public:
    Reg();
	Reg(const uint32_t& sent);
	void generate();
	uint32_t get_bigun();
	~Reg();
	uint8_t get_op();
	uint8_t get_rs();
	uint8_t get_rt();
	uint8_t get_rd();
	uint8_t get_sham();
	uint8_t get_func();
	uint16_t get_adr();
	uint32_t get_tgt();

private:
	uint32_t bigun;
	opcode op;
	RS rs;
	RT rt;
	RD rd;
	SHAM sham;
	function func;
	address adr;
	target tgt;
	//together they should make the four bytes of the register
	
};
#endif
