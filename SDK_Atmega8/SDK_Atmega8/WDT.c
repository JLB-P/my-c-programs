/*
 * WDT.c
 *
 * Created: 29/03/2016 08:36:17 a. m.
 *  Author: JLB
 */ 
#include <avr/io.h>
#include <avr/wdt.h> //incluir esta librería
#include <util/delay.h>

/************************************************************************
* USO DEL WATCHDOG 
* Es un contador que envía un pulso cuando llega a la cuenta deseada.
* El pulso puede ser usado para generar una interrupción o para generar
* un RESET al MCU (o hacer ambas tareas).
************************************************************************/
void WDT_example(void)
{
	//Usar PC3 para observar la salida (inicializa el PC3 en IO_PORTs.c)	
	//Usar el PD2 como entrada (inicializa el PD2 en IO_PORTs.c)
	
	/***************************************
	* Espera hasta que se presione el botón
	* para visualizar el efecto del WATCHDOG
	****************************************/
	while ((PIND & (1<<PD2)) >= 1)
	{
		PORTC &= ~(1 << PC3); //LED rojo encendido.
	}
	
	/**************************************
	* Activa WATCHDOG
	***************************************/
	wdt_enable(WDTO_2S); //Habilita WATCHDOG y define 2s para enviar reset al MCU
	
	/**************************************
	* Después que se oprime el botón y se
	* activó el WATCHDOG, esperamos, para
	* observar que ya se activó el WATCHDOG
	* sin embargo, el WATCHDOG tiene que ser
	* "reseteado" por lo menos cada 2s(WDTO_2S)
	* para evitar que el MCU sea "reseteado".
	* Por lo tanto, mientras mantenemos oprimido
	* el botón, el LED enciende y apaga y el
	* WATCHDOG es "reseteado cada vez"
	***************************************/
	while((PIND & (1<<PD2)) == 0)//Permanece en el ciclo mientras esté presionado el botón
	{
		//wdt_reset(); //Reset al wd	
		PORTC ^= 1 << PC3; //LED enciende 50ms y apaga 50ms
		_delay_ms(50);
	}
	
	/**************************************
	* Cuando soltamos el botón, el programa 
	* cae en el "while infinito" (para indicarlo,
	* el LED se apaga), pero, debido a que el wd 
	* ya no es "reseteado", después de 2 segundos(WDTO_2S)
	* provocará un reset al MCU, el programa
	* iniciará y volveremos a ver el LED encendido.
	***************************************/
	while(1) //Ciclo infinito
	{
		PORTC |= 1 << PC3;//Apaga el LED.
	} 
}
