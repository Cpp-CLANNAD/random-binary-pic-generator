#ifndef BITMAP_H
#define BITMAP_H
#pragma once

#include <stdio.h>

#pragma pack(push,1)
typedef struct FileHeader{
	unsigned short	bfType;
	unsigned int	bfSize;
	unsigned short	bfReserved1;
	unsigned short	bfReserved2;
	unsigned int	bfOffBits;
} FileHeader;

typedef struct InfoHeader{
	unsigned int	biSize;
	int				biWidth;
	int				biHeight;
	unsigned short	biPlanes;
	unsigned short	biBitCount;
	unsigned int	biCompression;
	unsigned int	biSizeImage;
	int				biXPelsPerMeter;
	int 			biYPelsPerMeter;
	unsigned int	biClrUsed;
	unsigned int	biClrImportant;
} InfoHeader;

#pragma pack(pop)

typedef struct tagRGBQUAD{
	unsigned char	rgbBlue;
	unsigned char	rgbGreen;
	unsigned char	rgbRed;
	unsigned char	rgbReserved;
}RGBQUAD;

int outputBmp(FILE *fp, unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable);

#endif
