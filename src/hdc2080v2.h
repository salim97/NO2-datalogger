/*
HDC2080v2.h: header file, driver for HDC2080 sensor routines
V2.0 - BENABADJI Noureddine - Oran - Dec. 31st, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#ifndef HDC2080v2_HEADER_H
#define	HDC2080v2_HEADER_H

//#define HDC2080_ADDR  (0x40 << 1)  // (7-bit address)
#define HDC2080_ADDR  (0x40)  // (7-bit address)

//---------------------------  VAR.GLO -------------------------------

unsigned int tempHDC = 0, humHDC = 0 ;

//============================= external fct ================================= 

extern void HDC2080_Init(void) ;
extern unsigned int HDC2080_readID(unsigned char c) ;
extern void HDC2080_read(void) ;

#endif //HDC2080v2_HEADER_H
