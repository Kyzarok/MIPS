#include "program_counter.h"
#include <stdint.h>
#include <bitset>

using namespace std;

PC::PC() {
	count = 0x10000000;
	delay_solt=false;
	jump_address=0;
	}
void PC::increment_byte() {
		count++;
	}
void PC::increment_word(){
        count=count+4;
    }
int PC::value() {
    return count;
	}
void PC::reset() {
		count = 0x10000000-4;
	}
void PC::store_addressJ(int address) {
	    delay_solt = true;
    	jump_address=address;
	}
void PC::store_addressB(int address){
        delay_solt = true;
    	jump_address=count+address;
}
void PC::jump(){
		count=jump_address-4;
	}
bool PC::check_delay(){
		return delay_solt;
	}
void PC::change_delay(){
delay_solt=false;
}
int PC::get_jump(){
	return jump_address;
}
