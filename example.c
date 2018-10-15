#include <stdlib.h>

void initrand(unsigned int seed){
	srand(seed);
}

unsigned int genrand(){
	return rand();
}