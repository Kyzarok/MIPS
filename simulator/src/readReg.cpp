#include "readReg.h"

Reg::Reg(){
    bigun = 0;
}

Reg::Reg(const uint32_t& sent) {
	bigun = sent;
}

void Reg::generate() {
	//bitwise traversal
    uint32_t tmp = bigun;
    op = tmp >> 26;
    rs = (tmp << 6) >> 27;
    rt = (tmp << 11) >> 27;
    rd = (tmp << 16) >> 27;
    sham = (tmp << 21) >> 27;
    func = (tmp << 26) >> 26;
    adr = (tmp << 16) >> 16;
    tgt = (tmp << 6) >> 6;
    
    
	/*op(bits[0 - 5]);
	rs(bits[6 - 10]);
	rt(bits[11 - 15]);
	rd(bits[16 - 20]);
	sham(bits[21 - 25]);
	func(bits[26 - 31]);
	adr(bits[16 - 31]);
	tgt(bits[6 - 31]);*/
}
Reg::~Reg(){
    
}
uint8_t Reg::get_op() { return op.get(); }
uint8_t Reg::get_rs() { return rs.get(); }
uint8_t Reg::get_rt() { return rt.get(); }
uint8_t Reg::get_rd() { return rd.get(); }
uint8_t Reg::get_sham() { return sham.get(); }
uint8_t Reg::get_func() { return func.get(); }
uint16_t Reg::get_adr() { return adr.get(); }
uint32_t Reg::get_tgt() { return tgt.get(); }





