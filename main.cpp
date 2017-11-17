#include <iostream> 
#include <fstream> 
#include <bitset>


using namespace std; 

int main(){
	
	//int argc, char* argv[]
	char buffer[1]; //declare buffer memory
	ifstream myFile("data.bin", ios::in | ios::binary); //file name i/m mode parameter to the constructor when declaring object
	//ifstream myFile(argv[1], ios::in| ios::binary);
	myFile.read(buffer, 1); //states the memory location and number of bytes to read
	
	if(!myFile){
		myFile.gcount();
		myFile.clear();
		
	}
	
	if(myFile.is_open()){
		for(int i=0; i< 1; i++){
		cout<< bitset<32> (buffer[i]);
	}
	}

	myFile.close();
}