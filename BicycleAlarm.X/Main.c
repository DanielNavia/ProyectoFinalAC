/* 
 * File:   Configuracion_Bits.h
  * Author: Daniel Navia
            Nelly Bambague
 * Created on 6 de marzo de 2022, 10:45 AM
 */

#include <xc.h>
#include <pic18f4550.h>
#include <stdint.h>
#include <stdio.h>
#include "Configuracion_Bits.h"
#include "Teclado.h"
#include "LCD.h"
#include "Utilidades.h"
#define _XTAL_FREQ 8000000
// Definimos TRIS_LED = Registro TRISB 
#define TRIS_KEYPAD    TRISB        
// Definimos PORT_KEYPAD = Regitro PORTB
#define PORT_KEYPAD    PORTB        
// Definimos LAT_LED = Registro LATB
#define LAT_KEYPAD     LATB       
#define FILA0       0                 
#define FILA1       1
#define FILA2       2
#define FILA3       3
#define COLUMNA0    4
#define COLUMNA1    5
#define COLUMNA2    6
#define COLUMNA3    7
// Buffer de entero 16 bits Almacena el formato de las variables a mostrar en la pantalla LCD.
int buffer_lcd[16];  
int  contador=0;             
int  n=1;                    
char tecla;  
char dato[16];                        
int  numColumnas;                      
int  posDato=0;
int  numFilas;                      
int  numVeces=2;
char const password[] = {'1','2','3','A'};
//Funcion AntiRebote.
void antiRebote(void);              
bit Columnas(void);             
int i;
void capturar_password(void);

//Distribucion de teclado 
char const TECLAS[4][4]={           
                        {'1','2','3','A'},
                        {'4','5','6','B'},
                        {'7','8','9','C'},
                        {'*','0','#','D'}};

//censa el cambio de estado.
bit Columnas(void)              
{
    if((PORT_KEYPAD&(1<<COLUMNA0))&&(PORT_KEYPAD&(1<<COLUMNA1))&&(PORT_KEYPAD&(1<<COLUMNA2))&&(PORT_KEYPAD&(1<<COLUMNA3)))
    
        return 0;
    else
        return 1;
}

void main(void)                     
{
    PORT_KEYPAD&(1<<COLUMNA0);
    PORT_KEYPAD&(1<<COLUMNA1);
    PORT_KEYPAD&(1<<COLUMNA2);
    PORT_KEYPAD&(1<<COLUMNA3);
    TRIS_KEYPAD&=~((1<<FILA0)|(1<<FILA1)|(1<<FILA2)|(1<<FILA3)); // Configuramos RB0, RB1, RB2, RB3 como salidas
    LAT_KEYPAD&((1<<FILA0)|(1<<FILA1)|(1<<FILA2)|(1<<FILA3));    // Inicializamos RB0, RB1, RB2, RB3  a nivel alto 1
    TRISD=0x00;                     // El Puerto D sera la salida.     
    // Inicializamos la libreria LCD
    lcd_init();                     
    // Limpiamos la pantalla LCD
    lcd_clear();                    
    lcd_posCursor(1,1);
    lcd_putc("Binvenido ");
    __delay_ms(500);
    lcd_clear(); 
    lcd_posCursor(1,1);
    lcd_putc("Password;");
    __delay_ms(500);
    
    // Bucle Infinito   
    while(1)                        
    {
//      imprimir(password,3,2);
        capturar_password();
    }
    return;
}

void antiRebote(void)               
{
    //Espera hasta que el pulsador este inactivo 
    while(PORT_KEYPAD&(1<<COLUMNA0)==0);    
    while(PORT_KEYPAD&(1<<COLUMNA1)==0);
    while(PORT_KEYPAD&(1<<COLUMNA2)==0);
    while(PORT_KEYPAD&(1<<COLUMNA3)==0);
    __delay_ms(300);
    // Asigna a passsword el valor de la tecla ubicada en la fila numFilas, columna numColumnas.
    dato[posDato]=TECLAS[numFilas][numColumnas];       
    //    tecla = TECLAS[numFilas][numColumnas]; 
    tecla = '*';
    //    if(tecla_OK(dato[posDato])== 1)
    //        {
    //            imprimir(dato, posDato-1,numVeces);
    //            return;
    //        }
    if(dato[posDato] =='D'){
        lcd_clear();
    //        for(i=0;i<posDato-1; i++){
    //        lcd_write_char(dato[i]);
    //        lcd_posCursor(numVeces,1);
    //        numVeces++;
    //        }
          imprimir(dato, posDato-1,numVeces);
        return;
        }
    lcd_write_char(tecla);
    lcd_posCursor(numVeces,1); 
    posDato++;
}

void capturar_password(void)
{
     if(contador<4)                
      {
          numFilas=contador; 
          // Se invierte el valor de n y se carga en el Puerto B
          LAT_KEYPAD=~n; 
          // n desplaza su valor 1 bit a la izquierda.
          n=n<<1;                   
          ++contador;
          // Detecta si hay cambios en las columnas.
          Columnas();               
      }
      else                          
      {
          contador=0;
          // Se reinicia las variables a sus valores iniciales 
          LAT_KEYPAD=0xFF;
          n=1;
      }
      // Si hay un cambio en la columna
      if(Columnas())                
      {
          if((PORT_KEYPAD&(1<<COLUMNA0))==0)
          {
              numColumnas=0;
          }
          else if((PORT_KEYPAD&(1<<COLUMNA1))==0)
          {
              numColumnas=1;
          }
          else if((PORT_KEYPAD&(1<<COLUMNA2))==0)
          {
              numColumnas=2;
          }
          else if((PORT_KEYPAD&(1<<COLUMNA3))==0)
          {
              numColumnas=3;
          }
          // LLamamos a la funcion AntiRebote
         antiRebote();              
         numVeces++;
      } 
}

