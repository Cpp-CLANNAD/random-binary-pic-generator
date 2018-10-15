#include "bitmap.h"

int outputBmp(FILE *fp, unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable){
	if (!imgBuf) return -1;

	int colorTablesize = 0;
	int tableLen = 2ul << biBitCount;
	if (pColorTable) colorTablesize = tableLen * 4;

	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;

	FileHeader fileHead;
	fileHead.bfType = 0x4D42;

	fileHead.bfSize = sizeof(FileHeader) + sizeof(InfoHeader) + colorTablesize + lineByte * height;

	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;

	fileHead.bfOffBits = 54 + colorTablesize;

	fwrite(&fileHead, sizeof(FileHeader), 1, fp);

	InfoHeader infoHead;
	infoHead.biWidth = width;
	infoHead.biHeight = height;
	infoHead.biBitCount = biBitCount;
	infoHead.biClrImportant = 0;
	infoHead.biClrUsed = 0;
	infoHead.biCompression = 0;
	infoHead.biPlanes = 1;
	infoHead.biSize = 40;
	infoHead.biSizeImage = lineByte * height;
	infoHead.biXPelsPerMeter = 0;
	infoHead.biYPelsPerMeter = 0;

	fwrite(&infoHead, sizeof(InfoHeader), 1, fp);

	if (colorTablesize) fwrite(pColorTable, sizeof(RGBQUAD), tableLen, fp);

	fwrite(imgBuf, height * lineByte, 1, fp);

	fclose(fp);

	return 0;
}
