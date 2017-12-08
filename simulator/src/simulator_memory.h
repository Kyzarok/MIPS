#ifndef SIMULATOR_MEMORY_H
#define SIMULATOR_MEMORY_H

#include "program_counter.h"

// it was before stdlib we're using Cpp so we need this instead


class memory{
public:
    memory();
    void write_byte(uint8_t data, PC pc);
    uint32_t read_word(PC pc);
    void store_word(int address, uint32_t data);
    uint32_t load_word(int address);
    void store_byte(int address, uint8_t data);
    uint32_t load_byte(int address);
    uint32_t load_byteU(int address);
    uint32_t load_halfword(uint32_t address);
    uint32_t load_halfwordU(uint32_t address);
    void store_halfword(uint32_t address, uint16_t data);
    ~memory();

private:
    uint8_t* mem;
};

#endif
