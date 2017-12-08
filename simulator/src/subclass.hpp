#ifndef SUBCLASS_HPP
#define SUBCLASS_HPP

#include <iostream>
#include <cstdint>

class opcode {
public:
    opcode();
    opcode (uint8_t code);
    uint8_t get();
private:
	uint8_t input;
};

class RS {
public:
    RS();
    RS(uint8_t code);
    uint8_t get();
private:
	uint8_t input;
};

class RT {
public:
    RT();
    RT(uint8_t code);
    uint8_t get();
private:
	uint8_t input;
};

class RD {
public:
    RD();
    RD(uint8_t code);
    uint8_t get();
private:
	uint8_t input;
};

class SHAM {
public:
    SHAM();
    SHAM(uint8_t code);
    uint8_t get();
private:
	uint8_t input;
};

class function {
public:
    function();
    function(uint8_t code);
    uint8_t get();
private:
	uint8_t input;
};

class address {
public:
    address();
    address(uint16_t code);
    uint16_t get();
private:
	uint16_t input;
};

class target {
public:
    target();
    target(uint32_t code);
    uint8_t get();
private:
	uint32_t input;
};


#endif
