/*
 * File:   main_proyecto.c
 * Author: Marco Flores
 *
 * Created on 16 de mayo de 2019, 11:59 PM
 */

//Librerias.
#include <xc.h>
#include "config_proyect.h"
#include "lcd_lib.h"

//Frecuencia de 4MHz
#define _XTAL_FREQ 4000000


//Función delay que aceptar valores no const.
void delay_us(unsigned int time)
{
   while(time > 0)
   {
       __delay_us(1);
      time--;
    }
}

int main(void) {
    
	// Arreglo sine para señal senoidal -> 128 points.
    const int sine[]={  0x80,0x86,0x8c,0x92,0x98,0x9e,0xa5,0xaa,
                        0xb0,0xb6,0xbc,0xc1,0xc6,0xcb,0xd0,0xd5,
                        0xda,0xde,0xe2,0xe6,0xea,0xed,0xf0,0xf3,
                        0xf5,0xf8,0xfa,0xfb,0xfd,0xfe,0xfe,0xff,
                        0xff,0xff,0xfe,0xfe,0xfd,0xfb,0xfa,0xf8,
                        0xf5,0xf3,0xf0,0xed,0xea,0xe6,0xe2,0xde,
                        0xda,0xd5,0xd0,0xcb,0xc6,0xc1,0xbc,0xb6,
                        0xb0,0xaa,0xa5,0x9e,0x98,0x92,0x8c,0x86,
                        0x80,0x79,0x73,0x6d,0x67,0x61,0x5a,0x55,
                        0x4f,0x49,0x43,0x3e,0x39,0x34,0x2f,0x2a,
                        0x25,0x21,0x1d,0x19,0x15,0x12,0xf,0xc,
                        0xa,0x7,0x5,0x4,0x2,0x1,0x1,0x0,
                        0x0,0x0,0x1,0x1,0x2,0x4,0x5,0x7,
                        0xa,0xc,0xf,0x12,0x15,0x19,0x1d,0x21,
                        0x25,0x2a,0x2f,0x34,0x39,0x3e,0x43,0x49,
                        0x4f,0x55,0x5a,0x61,0x67,0x6d,0x73,0x79};
    
    
	// Arreglo triangular para señal triangular -> 128 points.
    const int triangular[]={0x4,0x8,0xc,0x10,0x14,0x18,0x1c,0x20,
                            0x24,0x28,0x2c,0x30,0x34,0x38,0x3c,0x40,
                            0x44,0x48,0x4c,0x50,0x54,0x58,0x5c,0x60,
                            0x64,0x68,0x6c,0x70,0x74,0x78,0x7c,0x80,
                            0x83,0x87,0x8b,0x8f,0x93,0x97,0x9b,0x9f,
                            0xa3,0xa7,0xab,0xaf,0xb3,0xb7,0xbb,0xbf,
                            0xc3,0xc7,0xcb,0xcf,0xd3,0xd7,0xdb,0xdf,
                            0xe3,0xe7,0xeb,0xef,0xf3,0xf7,0xfb,0xff,
                            0xfb,0xf7,0xf3,0xef,0xeb,0xe7,0xe3,0xdf,
                            0xdb,0xd7,0xd3,0xcf,0xcb,0xc7,0xc3,0xbf,
                            0xbb,0xb7,0xb3,0xaf,0xab,0xa7,0xa3,0x9f,
                            0x9b,0x97,0x93,0x8f,0x8b,0x87,0x83,0x80,
                            0x7c,0x78,0x74,0x70,0x6c,0x68,0x64,0x60,
                            0x5c,0x58,0x54,0x50,0x4c,0x48,0x44,0x40,
                            0x3c,0x38,0x34,0x30,0x2c,0x28,0x24,0x20,
                            0x1c,0x18,0x14,0x10,0xc,0x8,0x4,0x0};
    
         
/* ---- Configuración de frecuencia del oscilador. ---- */
    OSCCON = 0x53; //Oscilador interno 4 MHz 
    
	
	
/* ---- Configuración de puertos. ---- */ 
    
    //Puerto B
    ANSELB = 0x00; //Declaramos el puerto B como digital.
    TRISB = 0x00; //Declaramos el puerto B como salida.
    
    //Puerto C
    ANSELC = 0x00; //Declaramos el puerto C como digital.
    
	
	//Salidas para los push botton
	TRISCbits.RC0 = 1; //RC0 como entrada -> Push botton -> Señal Senoidal.
    TRISCbits.RC1 = 1; //RC1 como entrada -> Push botton -> Señal Triangular.
         
    TRISCbits.RC6 = 1; //RC6 como entrada -> Push botton -> Señal PWM.
    TRISCbits.RC7 = 1; //RC7 como entrada -> Push botton -> Salir de las opciones.
       
    
	   
	   
    // Registros de configuración del Convertidor analogico digital.
    ADCON0 = 0x01; //Canal analógico AN0, Habilita ADC        
    ADCON1 = 0x00; //Basandose en la hoja de datos la configuracion queda de esta manera ya que se selecciono canal AN0.                  
    ADCON2 = 0x24; //FOSC/4, 4TD, justificado a la izquierda   // 0010|0100 -> 36
    
    
    //Puerto A
    PORTA = 0x00; //Puerto A como lectura o escritura.
    ANSELA = 0x00; //Declaramos el puerto A como digital.
    TRISAbits.RA1 = 1; //RA1 como entrada -> Para el potenciometro.
    TRISAbits.RA2 = 0; //RA2 como salida -> Led rojo para señal seno. 
    TRISAbits.RA3 = 0; //RA3 como salida -> Led amarillo para señal triangular.
    TRISAbits.RA4 = 0; //RA4 como salida -> Led verde para señal selecionar una opción.
       
	TRISAbits.RA6 = 1;
    TRISAbits.RA7 = 1;
    
    
    //Puerto D
    LATD = 0x00; //Declaramos el puerto D como escritura.
    ANSELD = 0x00; //Declaramos el puerto D como digital.
    TRISD = 0x00; //Declaramos el puerto D como salida.
    
	
		/*----Menú ----*/
	
        Lcd_Init(); //Función para inicializar LCD
        
        Lcd_Clear(); //Función para limpiar LCD
        Lcd_Set_Cursor(1,1); //Coloca el cursor en la posición 1,1
        Lcd_Write_String("Generador De"); //Escritura de cadena
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("Funciones");
        //__delay_ms(500);
        __delay_ms(1500); //Retardo para el mostrar el mensaje.
        
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Opcion: 1");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("Seinal SIN");
        //__delay_ms(500);
        __delay_ms(1500);
        
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Opcion: 2");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("Seinal TRI");
        //__delay_ms(500);
        __delay_ms(1500);
        
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Opcion: 3");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("Seinal PWM");
        //__delay_ms(500);
        __delay_ms(1500);
        
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Select Opc: ");
        __delay_ms(3000);
        //__delay_ms(500);
        


			/* ---- Configuración del PWM ----*/

             PR2 = 124; //Asignación de valor al PR2
             CCPR1L = 0; // Porcentaje del ciclo de trabajo.

             ANSELC = 0; // Declaramos el puerto C como digital.
             TRISCbits.RC2 = 0; //Declaramos el pin 17 como salida.

             T2CON = 0x00;   // Asignacion del valor Prescaler 1 al Timer 2 OFF   
             CCP1CON = 0x0C; // Controlador de los dos bits del registro CCPRXL

             TMR2 = 0; // Declaracion de Timer 2
             T2CONbits.TMR2ON = 1; //Timer 2 ON
             
        
    
	//Variabe time para aguardar el resultado de la conversión
    unsigned int time;
    
    int aux = 0; 
    while(1){ 
        
		
		//Inicialización de leds
        PORTAbits.RA4 =1; //Led verde encendido.
        PORTAbits.RA3 =0; //Led rojo apagado.
        PORTAbits.RA2 =0; //Led amarillo apagado.
 
        ADCON0bits.GO=1; //Inicio conversión
        while(ADCON0bits.GO==1);
        time = ADRESH;
              
			  
	    //Caso para la señal senoidal
        if ( PORTCbits.RC0 == 1 && PORTCbits.RC1 == 0 && PORTCbits.RC6 == 0 && PORTCbits.RC7 == 0 ) {
        

			/* ---- Menú ----*/
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Mostrando SIN ");
            Lcd_Set_Cursor(2,1);
            Lcd_Write_String("Salir 4 ");           
            
			
			//Inicialización de leds
            PORTAbits.RA4 =0;//Led verde apagado
            PORTAbits.RA2 =1;//Led rojo encendido
            PORTAbits.RA3 =0;//Led amarillo apagado
            
			
            CCPR1L = 0; // Señal PWM apagada.
            aux = 0;
			
			//Si RC7 es indentico a cero (no se presiona el boton de salir) se realiza la operación interna del while.
            while(PORTCbits.RC7 == 0){
   
                LATB = sine[aux];
                delay_us(time);
				//Operador ternario -> (si aux es identico a 127) es verdadero entonces es cero y si es falso aux iniciara a conteo.
                aux=(aux==127)? 0 : aux++;
                
                ADCON0bits.GO=1; //Inicio conversión
                while(ADCON0bits.GO==1); 
                time = ADRESH;//Guarda el resultado de la conversión.
          
            }
            //Esperar una opción
             Lcd_Clear();
             Lcd_Set_Cursor(1,1);
             Lcd_Write_String("Select Opc: ");

        }
		
		//Caso para la señal triangular.
        else if ( PORTCbits.RC1 == 1 && PORTCbits.RC0 == 0 && PORTCbits.RC6 == 0 && PORTCbits.RC7 == 0 ) {
            
			/* ---- Menú ----*/
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Mostrando TRI ");
            Lcd_Set_Cursor(2,1);
            Lcd_Write_String("Salir 4 ");
            
			//Inicialización de leds
            PORTAbits.RA4 =0; //Led verde apagado
            PORTAbits.RA2 =0; //Led rojo apagado
            PORTAbits.RA3 =1; //Led amarillo encendido
             
            CCPR1L = 0;  //// Señal PWM apagada.
			
            aux = 0;
            while(PORTCbits.RC7 == 0){
            
                LATB = triangular[aux];
                delay_us(time);
				//Operador ternario -> (si aux es identico a 127) es verdadero entonces es cero y si es falso aux iniciara a conteo.
                //Para que no tenga un desbordamiento.
                aux=(aux==127) ? 0 : aux++;
                
                ADCON0bits.GO=1; //Inicio conversión
                while(ADCON0bits.GO==1); 
                time = ADRESH;//Guarda el resultado de la conversión.
          
            }
            
            //Esperar una opción
             Lcd_Clear();
             Lcd_Set_Cursor(1,1);
             Lcd_Write_String("Select Opc: ");
   
        }
        
		//Caso para la señal PWM.
        else if ( PORTCbits.RC6 == 1 && PORTCbits.RC0 == 0 && PORTCbits.RC1 == 0 && PORTCbits.RC7 == 0 ) {
            
			/* ---- Menú ----*/
			Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Mostrando PWM ");
            Lcd_Set_Cursor(2,1);
            Lcd_Write_String("Salir 4 ");
			
			//Puerto en cero por lo tanto señales apagadas(senoidal y triangular).
            LATB = 0;
            CCPR1L = 100;
            
            
            
            //int pulso = CCPR1L;
            
            while (PORTCbits.RC7 == 0) {
                
				//Inicialización de leds
                PORTAbits.RA4 =0;//Led verde apagado
                
				
                ADCON0bits.GO=1;
                while(ADCON0bits.GO==1); 
                time = ADRESH;//Guarda el resultado de la conversión.
                //pulso = CCPR1L;
                
                //Boton para restar.
                if(PORTAbits.RA6 == 1){
                
                    if( CCPR1L - 20 < 0){
                    
                        CCPR1L = 0;
                        //pulso = CCPR1L;
                    
                    }
                    else{
                    
                        CCPR1L = CCPR1L - 20;
                        //pulso = CCPR1L;
                    
                    }
 
                }
                
                //Boton para sumar.
                if(PORTAbits.RA7== 1){
                
                    if(CCPR1L + 20 > 255){
                    
                        CCPR1L = 255;
                        //pulso = CCPR1L;
                    
                    }
                    else{
                    
                        CCPR1L = 20 + CCPR1L;
                        //pulso = CCPR1L;
                    
                    }
                 
                }
                
                //Frecuencia de 2Khz
                if ( time <= 80 ) {
                    //Prescaler 4
                    T2CONbits.T2CKPS = 1;
                    PR2 = 124;
                    //CCPR1L = 100;
                    
                }
                
                //Frecuencia de 4Khz
                if ( time > 80 && time < 160 ) {
                    //Prescaler 1
                    T2CONbits.T2CKPS = 0;
                    PR2 = 249; 
                    //CCPR1L = 200;     
                }
                
                
                //Frecuencia de 8Khz
                if ( time >= 160 ) {
                    //Prescaler 1
                    T2CONbits.T2CKPS = 0;
                    PR2 = 124;
                    //CCPR1L = 100; 
                }
                __delay_ms(50);
                
            }
            //Esperar una opción
             Lcd_Clear();
             Lcd_Set_Cursor(1,1);
             Lcd_Write_String("Select Opc: ");
        }
        
    }   
    return 0;    
}
