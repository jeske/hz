// HZ Engine Source
// Copyright (C) 1998 by David W. Jeske

//
// Information for loading images of type BMP
//

#ifndef _BMP_H_
#define _BMP_H_ 1

#include "config.h"

typedef struct _bmp_header_1x
{
  uint16 type;
  uint16 width;
  uint16 height;
  uint16 bytewidth;
  uint16 planes;
  uint16 bits_per_pixel;
} BMP_HEADER_1x;

typedef struct _bmp_header_3x
{
  uint16 type;
  uint32 filesize;
  uint16 reserved1;
  uint16 reserved2;
  uint32 image_data_offset;
} BMP_HEADER_3x;

typedef struct _bmp_info_3x
{
  uint16 header_size;
  uint32 width;
  uint32 height;
  uint16 planes;
  uint16 bits_per_pixel;
  uint32 compression;
  uint32 size;
  uint32 horz_resolution;
  uint32 vert_resolution;
  uint32 num_colors_used;
  uint32 num_significant_colors;
} BMP_INFO_3x;

#define BMP_TYPE_V1	0x0001
#define BMP_TYPE_V3	0x4d42

#define BMP_COMPRESSION_NONE	0
#define BMP_8BIT_RLE	1
#define BMP_4BIT_RLE	2

int load_bmp (IMAGEDATA *im, const char *filename);

#endif
