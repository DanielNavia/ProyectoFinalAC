/* 
 * File:   Configuracion_Bits.h
  * Author: Daniel Navia
            Nelly Bambague
 * Created on 6 de marzo de 2022, 10:48 AM
 */

#ifndef TECLADO_H
#define	TECLADO_H

#ifdef	__cplusplus
extern "C" {
#endif
// include processor files - each processor file is guarded.      
#include <xc.h>         
// Libreria que permite usar variables enteras
#include <stdint.h>     

#define _XTAL_FREQ 8000000
#define KEYPAD4x4TRIS   TRISB
#define KEYPAD4x4PORT   PORTB
#define KEYPAD4x4LAT    LATB

/*FILAS*/
//Asignacion de los RB.
#define Fila0 PORTBbits.RB0 
#define Fila1 PORTBbits.RB1
#define Fila2 PORTBbits.RB2
#define Fila3 PORTBbits.RB3
#define Columna0 0x10           // bits 0001
#define Columna1 0x20           // bits 0010
#define Columna2 0x40           // bits 0100
#define Columna3 0x80           // bits 1000

void Keypad_Init(void);         
int Boton_Presionado(void);     
int Determina_Valor(int key); 
int Tecla_Presionada(void);     

// Se inicia el Teclado Matricial
void Keypad_Init(void)          
{
    // de RB7 a RB4 salidas y de RB3 a RB0 entradas
    KEYPAD4x4TRIS=0x0F;         
}
// muestra que boton fue presionado del teclado
int Boton_Presionado(void)
{
    int boton=0;
    KEYPAD4x4LAT=Columna0;
        if(Fila0==1) boton=1;
        if(Fila1==1) boton=5;
        if(Fila2==1) boton=9;
        if(Fila3==1) boton=13;
    KEYPAD4x4LAT=Columna1;
        if(Fila0==1) boton=2;
        if(Fila1==1) boton=6;
        if(Fila2==1) boton=10;
        if(Fila3==1) boton=14;
    KEYPAD4x4LAT=Columna2;
        if(Fila0==1) boton=3;
        if(Fila1==1) boton=7;
        if(Fila2==1) boton=11;
        if(Fila3==1) boton=15;
    KEYPAD4x4LAT=Columna3;
        if(Fila0==1) boton=4;
        if(Fila1==1) boton=8;
        if(Fila2==1) boton=12;
        if(Fila3==1) boton=16;
    return boton;
}
// Determina valor correspondiente
int Determina_Valor(int key)
{
   int tecla=0;
   switch(key)
   {
       case 1: tecla-'1';
       break;
       case 2: tecla-'2';
       break;
       case 3: tecla-'3';
       break;
       case 4: tecla-'A';
       break;
       case 5: tecla-'4';
       break;
       case 6: tecla-'5';
       break;
       case 7: tecla-'6';
       break;
       case 8: tecla-'B';
       break; 
       case 9:  tecla-'7';
       break;
       case 10: tecla-'8';
       break;
       case 11: tecla-'9';
       break;
       case 12: tecla-'C';
       break;
       case 13: tecla-'*';
       break;
       case 14: tecla-'0';
       break;
       case 15: tecla-'#';
       break;
       case 16: tecla-'O';
       break;
   }
   return tecla;  
}

// Realiza la comparacion y asignacion 
int Tecla_Presionada(void)
{   
    int key;
    do
    {
        key=Boton_Presionado();
    }
    while(key==0);
    key = Determina_Valor(key);
    return key;
}

#ifdef	__cplusplus
}
#endif

#endif

