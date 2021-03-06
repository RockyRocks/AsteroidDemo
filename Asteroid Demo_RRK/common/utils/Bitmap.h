#ifndef _BITMAP_H
#define _BITMAP_H

#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

const short BITMAP_MAGIC_NUMBER=19778;
const int RGB_BYTE_SIZE=3;

#pragma pack(push,bitmap_data,1)

typedef struct tagRGBQuad {
	char rgbBlue;
	char rgbGreen;
	char rgbRed;
	char rgbReserved;
} RGBQuad;

typedef struct tagBitmapFileHeader {
	unsigned short bfType;
	unsigned int bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int bfOffBits;
} BitmapFileHeader;

typedef struct tagBitmapInfoHeader {
	unsigned int biSize;
	int biWidth;
	int biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	int biXPelsPerMeter;
	int biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
} BitmapInfoHeader;

#pragma pack(pop,bitmap_data)

// Bitmap Description
//
// Thanks to Captain Jester from GameDev.net for setting me on the right track ;)
// Simple bitmap loader that will load the pixels into a char array for use with
// OpenGL.
//
// Usage:
//
// Bitmap *image;
//
//	if (image->loadBMP("mytexture.bmp")) {
//		glGenTextures(1, &texture[0]); 
//
//		glBindTexture(GL_TEXTURE_2D, textureHandle);
//		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
//		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
//		glTexImage2D(GL_TEXTURE_2D, 0, 3, image->width, image->height, 0, 
//					GL_RGB, GL_UNSIGNED_BYTE, image->data);
// }

class Bitmap {
public:
    //variables
    RGBQuad *colours;
    char *data;
    bool loaded;
    int width,height;
    unsigned short bpp;
    string error;
    //methods
    Bitmap(void);
    Bitmap(char *);
    ~Bitmap();
    bool loadBMP(char *);
private:
    //variables
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;
    int byteWidth;            //the width in bytes of the image
    int padWidth;             //the width in bytes of the added image
    unsigned int dataSize;                //size of the data in the file
    //methods
    void reset(void);
    bool convert24(char *);		//convert to 24bit RGB bottom up data
    bool convert8(char *);		//convert to 24bit RGB bottom up data
};

#endif //_BITMAP_H

