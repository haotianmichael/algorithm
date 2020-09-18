

/*
#ifndef _DEBUG    //调试模式下
#define _malloc_crt malloc
#else 
#define _THISFILE _FILE
#define _malloc_crt(s) _malloc_dbg \
        (s, _CRT_BLOCK, _THISFILE, _LINE_)


typedef struct{
  long osfhnd;
  char osfile;
  char pipech;  
}ioinfo;

void __cdecl ioinit(void) {
  
    //32*8 = 256Bytes   100h
  if((pio = malloc_crt(IOINFO_ARRAY_ELTS*sizeof(ioinfo))) == NULL)
  
  //...
}
*/
