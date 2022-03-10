/* 
 * File:   Configuracion_Bits.h
  * Author: Daniel Navia
            Nelly Bambague
 * Created on 6 de marzo de 2022, 10:50 AM
 */

#ifndef UTILIDADES_H
#define	UTILIDADES_H
#ifdef	__cplusplus
extern "C" {
#endif
#include "LCD.h"

int i;    
int tecla_OK(char pTecla);
void imprimir(char pDato[], int pPosicion, int pNumVeces);
int comparar_Password(char pPasword[], char pDato[],  int pNumPass, int pNumDato);

int tecla_OK(char pTecla){
    int band =0;
    if(pTecla == 'O'){
        lcd_clear();
    }
    return band = 1;
}

void imprimir(char pDato[],int pPosicion, int pNumVeces){
    int numVeces=1;
    for(i=0;i<= pPosicion; i++){
        lcd_write_char(pDato[i]);
        lcd_posCursor(pNumVeces,1);
        pNumVeces++;
    }
}

int comparar_Password(char pPasword[], char pDato[], int pNumPass, int pNumDato)
{
    int bandera=0, i, j;
    if(pNumPass == pNumDato)
    {
        for(i=0; i<= pNumPass; i++)
        {
            if(pPasword[i] != pDato[i])
            {
                bandera=0;
                return;
            }  
            bandera = 1;
        }
    }
    return bandera;
}




#ifdef	__cplusplus
}
#endif

#endif	/* UTILIDADES_H */

