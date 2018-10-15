#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <string.h>

int error(char *p){
	int ret = errno;
	perror(p ? p : strerror(ret));
	exit(ret?ret:-1);
}

int main(int argc, char** argv){
	//import rand to test
	void initrand(unsigned int seed);
	unsigned int genrand();

	//parse parameters
	char *filepath = "output.bmp"; int width=512, height=512;//default parameters
	unsigned seed;
	if (argc >= 2) filepath = argv[1];
	if (argc >= 4){
		width = atoi(argv[2]);
		height = atoi(argv[3]);
		if (width<=0||height<=0) error("Size error");//including parse error
	}

	//seeding
	if (argc >= 5){
		seed = atoi(argv[4]);
		if (seed <= 0) error("Size error");//including parse error
	}else{
		seed = (unsigned)time(NULL);
	}
	initrand(seed);

	FILE *fp = fopen(filepath, "wb");
	if (!fp) error("File open failed");

	int lineByte = (width / 8 + 3) / 4 * 4;
	unsigned char *buff = malloc(lineByte * height);

	int i, j;
	for (i = 0; i < height; i++){
		for (j = 0; j < (width/8); j++){
			buff[i*lineByte + j] = (unsigned char)(genrand()) % 256ul;
		}
	}

	RGBQUAD colorTable[2] = { { 255ul, 255ul, 255ul, 0ul }, { 0ul, 0ul, 0ul, 0ul } };

	int ret = outputBmp(fp, buff, width, height, 1, colorTable);
	free(buff);
	return ret;
}