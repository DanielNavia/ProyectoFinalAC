/* 
 * File:   Configuracion_Bits.h
  * Author: Daniel Navia
            Nelly Bambague
 * Created on 6 de marzo de 2022, 10:48 AM
 */

#ifndef LCD_H
#define	LCD_H
#ifdef	__cplusplus
extern "C" {
#endif
#include <xc.h>   
#define _XTAL_FREQ 8000000

#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
void Lcd_Port(char a)
{
   if(a & 1)
      D4 = 1;
   else
      D4 = 0;

   if(a & 2)
      D5 = 1;
   else
      D5 = 0;

   if(a & 4)
      D6 = 1;
   else
      D6 = 0;

   if(a & 8)
      D7 = 1;
   else
      D7 = 0;
}
void Lcd_Cmd(char a)
{
   RS = 0;             // => RS = 0
   Lcd_Port(a);
   EN  = 1;             // => E = 1
        __delay_ms(4);
        EN  = 0;             // => E = 0
}
//Limpiar pantalla
void lcd_clear()
{
   Lcd_Cmd(0);
   Lcd_Cmd(1);
}

void lcd_posCursor(char a, char b)
{
   char temp,z,y;
   if(a == 1)
   {
     temp = 0x80 + b - 1;
      z = temp>>4;
      y = temp & 0x0F;
      Lcd_Cmd(z);
      Lcd_Cmd(y);
   }
   else if(a == 2)
   {
      temp = 0xC0 + b - 1;
      z = temp>>4;
      y = temp & 0x0F;
      Lcd_Cmd(z);
      Lcd_Cmd(y);
   }
}

void lcd_init()
{
  Lcd_Port(0x00);
   __delay_ms(20);
  Lcd_Cmd(0x03);
   __delay_ms(5);
  Lcd_Cmd(0x03);
   __delay_ms(11);
  Lcd_Cmd(0x03);
  Lcd_Cmd(0x02);
  Lcd_Cmd(0x02);
  Lcd_Cmd(0x08);
  Lcd_Cmd(0x00);
  Lcd_Cmd(0x0C);
  Lcd_Cmd(0x00);
  Lcd_Cmd(0x06);
}
 //Funcion escribir un caracter.
void lcd_write_char(char a)
{
   char temp,y;
   temp = a&0x0F;
   y = a&0xF0;
   RS = 1;    
   //transferencia de Data
   Lcd_Port(y>>4);              
   EN = 1;
   __delay_us(40);
   EN = 0;
   Lcd_Port(temp);
   EN = 1;
   __delay_us(40);
   EN = 0;
}
//Llenar pantalla
void lcd_putc(char *a) .
{
   int i;
   for(i=0;a[i]!='\0';i++)
      lcd_write_char(a[i]);
}
//Funcion cambiar a la derecha
void lcd_shift_right()
{
   Lcd_Cmd(0x01);
   Lcd_Cmd(0x0C);
}
//Funcion cambiar a la izquierda
void lcd_shift_left() 
{
   Lcd_Cmd(0x01);
   Lcd_Cmd(0x08);
}

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

