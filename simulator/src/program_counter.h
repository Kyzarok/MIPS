#ifndef PC_H
#define PC_H

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <stdint.h>


class PC {
public:
	PC();
    void increment_byte();
    void increment_word();
    int value();
    void reset();
    void store_addressJ(int address);
    void store_addressB(int address);
    void jump();
    bool check_delay();
    void change_delay();
	int get_jump();
private:
	int jump_address;
	int count;
	bool delay_solt;
};

#endif
