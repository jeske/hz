// HZ Engine Source
// Copyright (C) 2000 Brandon C. Long

#include <stdio.h>
#include <malloc.h>
#include <sys/stat.h>
#include "config.h"
#include "image.h"
#include "i_console.h"
#include "bmp.h"

int load_bmp_v3 (IMAGEDATA *im, uint8 *data);

static uint32 read_little_32 (uint8 **data)
{
  uint32 x;
  uint8 a,b,c,d;

  a = **data;
  b = *(*data+1);
  c = *(*data+2);
  d = *(*data+3);

  *data = *data + 4;

  x = long_little_endian(d<<24 | c<<16 | b<<8 | a);

  return x;
}

static uint16 read_little_16 (uint8 **data)
{
  uint16 x;
  uint8 a,b;

  a = **data;
  b = *(*data + 1);

  *data = *data + 2;

  x = little_endian (b<<8 | a);
  return x;
}

static int read_8 (FILE *fp, uint8 *x)
{
  if (fread (x, sizeof (uint8), 1, fp) < 1)
  {
    I_Perror ("Error reading file");
    return (-1);
  }
  return 0;
}

int load_bmp (IMAGEDATA *im, const char *filename)
{
  FILE *fp;
  uint16 x;
  int ret;
  uint8 *data = NULL;
  uint8 *ptr = NULL;
  int size = 0;
  struct stat st;

  if (stat (filename, &st) == -1)
  {
    I_Perror ("Error statting file %s", filename);
    return (-1);
  }
  size = st.st_size;
  data = ptr = (uint8 *) malloc (size * sizeof(uint8));

  if ((fp = fopen (filename, "r")) == NULL)
  {
    free(ptr);
    I_Perror ("Error openning file %s", filename);
    return (-1);
  }
  if (fread(data, sizeof(uint8), size, fp) < size)
  {
    free(ptr);
    I_Perror ("Error reading file %s", filename);
    return (-1);
  }
  fclose (fp);
  x = read_little_16 (&data);

  switch (x)
  {
    case BMP_TYPE_V1:
      I_Message ("Type 1 BMP\n");
      break;
    case BMP_TYPE_V3:
//      I_Message ("Type 3 BMP\n");
      ret = load_bmp_v3 (im, data);
      break;
    default:
      I_Message ("UnknownBMP\n");
  }

  free (ptr);
  return ret;
}

int load_bmp_v3 (IMAGEDATA *im, uint8 *data)
{
  uint8  byte;
  uint16 word;
  uint32 dword, data_offset;
  uint32 compression, size;
  uint32 scan_len, data_len;
  int x, y;

  /* go through header */
  dword = read_little_32 (&data);
  dword = read_little_32 (&data);
  data_offset = read_little_32 (&data);

  /* load info struct */
  /* header size */
  dword = read_little_32 (&data);
  if (dword != 40)
  {
    I_Error ("load_bmp(): Unexpected header size, expected 40 got %d", word);
    return (-1);
  }
  dword = read_little_32 (&data);
  im->width = dword;
  dword = read_little_32 (&data);
  im->height = dword;
  /* image planes, always 1 */
  word = read_little_16 (&data);
  /* bits per pixel */
  word = read_little_16 (&data);
  im->colordepth = word;
  /* compression method */
  dword = read_little_32 (&data);
  compression = dword;
  dword = read_little_32 (&data);
  size = dword;
  if (!size)
  {
    I_Message ("-W- Uh oh, image size is 0, guessing\n");
    size = im->height * im->width * im->colordepth / 8;
  }
//  else
//    I_Message ("Size is %d\n", size);

  /* horz resolution */
  dword = read_little_32 (&data);
  /* vert resolution */
  dword = read_little_32 (&data);
  /* colors */
  dword = read_little_32 (&data);
  im->numcolors = dword;
  /* significant colors */
  dword = read_little_32 (&data);

  /* Palette on 1, 4 or 8 bit displays */
  if (im->colordepth != 24)
  {
    if (im->numcolors == 0)
    {
      /* Hmm, if numcolors is 0, guess using the start of data */
      im->numcolors = (data_offset - 54) / 4;
    }

    im->palette = (RGBQUAD *) malloc (im->numcolors * sizeof (RGBQUAD));
    for (x = 0; x < im->numcolors; x++)
    {
      dword = read_little_32 (&data);
      im->palette[x].red = (dword >> 16) & 0x0ff;
      im->palette[x].green = (dword >> 8) & 0x0ff;
      im->palette[x].blue = (dword >> 0) & 0x0ff;
    }
  }
  else
    im->palette = NULL;

  /* Image data */
  im->data = (BYTE *) malloc (size);
  
  if (im->data == NULL)
    return (-1);

  data_len = (im->width * im->colordepth) / 8;
  scan_len = data_len;
  if (data_len % 4)
    scan_len += 4-(scan_len % 4);

//  I_Message ("Width is %d  Scan Length is %d\n", im->width, scan_len);

  switch (compression)
  {
    case BMP_COMPRESSION_NONE:
      for (y = im->height; y; y--)
      {
	for (x = 0; x < scan_len; x++)
	{
	  byte = *data;
	  data = data + 1;
	  if (x < data_len)
	    im->data[x + ((y-1) * data_len)] = byte;
	}
      }
      break;
    case BMP_8BIT_RLE:
    case BMP_4BIT_RLE:
    default:
      I_Error ("Unhandled BMP compression type %d", compression);
      break;
  }


  return 0;
}
