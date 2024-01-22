/*
HDC2080v2.C: HDC2080 sensor routines
V2.0 - BENABADJI Noureddine - Oran - Dec. 31st, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#include <c:\Program Files\Microchip\xc32\v1.43\pic32mx\include\xc.h>
#include "hdc2080v2.h"
#include "i2c1bn.h"

//unsigned char rd_hdc2080[8] ;
//unsigned char *pRd2080 = (unsigned char *)rd_hdc2080 ;

//-----------------------------------------------------------------------------
void HDC2080_Init(void)
{
  //enT3() ;
  
    //cfg. Configuration Registers (0x0E) and (0x0F))
  i2c1_write (HDC2080_ADDR, "\x0E\x40\x01", 3) ; //cfg. + 14bit resolution
  //i2c1_write (HDC2080_ADDR, "\x0E\x40\x51", 3) ; //cfg. + 11bit resolution
  //i2c1_write (HDC2080_ADDR, "\x0E\x40\xA1", 3) ; //cfg. + 9bit resolution

  delay1ms(20) ;

  //disT3() ; 
}
//-----------------------------------------------------------------------------
unsigned int HDC2080_readID(unsigned char c)
{
unsigned char buf[2] ;
unsigned int value ;
int ret ;

  //enT3() ;
 
  if (c == 0xFE) i2c1_write (HDC2080_ADDR | I2C_NOSTOP, "\xfe", 1) ;//Device ID
  if (c == 0xFC) i2c1_write (HDC2080_ADDR | I2C_NOSTOP, "\xfc", 1) ;//Manuf. ID
  delay1ms(7) ;
  //delay1ms(20) ;
  ret = i2c1_read (HDC2080_ADDR | I2C_RESTART, buf, 2) ;

  //if (ret == 2) { value = 256*buf[0] + buf[1] ; return value ; }
  if (ret == 2) { value = 256*buf[1] + buf[0] ; return value ; }
  else return 0 ;
  
  //disT3() ; 
}

//-----------------------------------------------------------------------------
void HDC2080_read(void)
{
unsigned char buf[4] ;
int ret ;

  //enT3() ;

  i2c1_write (HDC2080_ADDR | I2C_NOSTOP, "\x00", 1) ;
  ///////delay1ms(2) ; //14-bit conversion needs 0.61ms(temp) + 0.66ms(hum) typical (p.6/44)
  //delay1ms(10) ;
  //delay1ms(1) ; //11-bit conversion needs 0.35ms(temp) + 0.4ms(hum) typical (p.6/44)
  //delay1us(750) ; //9-bit conversion needs 0.225ms(temp) + 0.275ms(hum) typical (p.6/44)  
  ret = i2c1_read (HDC2080_ADDR | I2C_RESTART, buf, 4) ;
   
  if (ret == 4) 
  { tempHDC = (unsigned int)buf[1] << 8 | buf[0] ; //ça donne 0 fixe
    //tempHDC = buf[1] *256 + buf[0] ;
    tempHDC = ((unsigned long)tempHDC * 165L)/65536L - 40 ;  //in °C

    humHDC = (((unsigned int)buf[3] << 8 | buf[2])) ; //ça donne 0 fixe
    //humHDC = buf[3] *256 + buf[2] ;
    humHDC = ((unsigned long)humHDC * 100L)/65536L ;  //in %  
  }
  else { tempHDC = 0 ; humHDC = 0 ; }
  
  //disT3() ;
}
