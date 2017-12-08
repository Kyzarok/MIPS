#include "subclass.hpp"

opcode::opcode(){
    input = 0;
}
opcode::opcode (uint8_t code) {
    input = code;
}
uint8_t opcode::get() { return input; }


RS::RS(){
    input = 0;
}
RS::RS(uint8_t code) {
    input = code;
}
uint8_t RS::get() { return input; }


RT::RT(){
    input = 0;
}
RT::RT(uint8_t code) {
    input = code;
}
uint8_t RT::get() { return input; }


RD::RD(){
    input = 0;
}
RD::RD(uint8_t code) {
    input = code;
}
uint8_t RD::get() { return input; }


SHAM::SHAM(){
    input = 0;
}
SHAM::SHAM(uint8_t code) {
    input = code;
}
uint8_t SHAM::get() { return input; }


function::function(){
    input = 0;
}
function::function(uint8_t code) {
    input = code;
}
uint8_t function::get() { return input; }


address::address(){
    input = 0;
}
address::address(uint16_t code) {
    input = code;
}
uint16_t address::get() { return input; }


target::target(){
    input = 0;
}
target::target(uint32_t code) {
    input = code;
}
uint8_t target::get() { return input; }
