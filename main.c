/*
 * Final_listo.c
 *
 * Created: 07/05/2020 5:04:54 p. m.
 * Author : cesh_
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t previousReading  = 1;
uint8_t estadoMano = 1;

#define s_signal PORTD1
#define servo PORTB1



void init_servo(void)
{
	DDRB |= (1<<servo);	//vamos a utilizar este pin del registro B como  (OC1A)
	TCNT1 = 0;		// registro de timer 1 a 0
	ICR1 = 2499;	// vamos a contar hasta el valor de ICR1


	TCCR1A |=
	(1<<COM1A1) |(0<<COM1A0) // seteamos el registro OC1A a BOTTOM  en el modo No-inversor
	|(1<<WGM11) |(0<<WGM10); // Utilizamos el modo de generacion de forma de onda #14 (Fast PWM, TOP = ICR1, UPDATE OCR1A at BOTTOM, TOV1 FLAG set on TOP )
	
	TCCR1B |=
	(1<<WGM13) | (1<<WGM12) //Estos otros 2 bits tambien son para el seteo de forma de Onda #14 que hicimos arriba
	|(0<<CS12) |(1<<CS11)|(0<<CS10); // seteamos un pre-escalador de reloj de 8 para la frecuencia de PWM 
}


int main(void)
{
	cli();  //anulamos las interrupciones globales
	init_servo(); //incializamos la funcion servo
	sei(); //habilitamos las funciones globales
	
	//Aqui vamos a establecer el puerto D1 (s_signal) como una entrada, que será la señal proveniente del sensor
	DDRD &=~ (1<<s_signal);
	PORTD = (1<<s_signal);
	
	OCR1A = 125; // inicializamos el servomotor en 90° negatios (-88.6) realmente. Esta será su posicion en reposo
	
	
	while (1) //En este while se le dice al maicro lo que debe hacer y en que orden lo debe hacer
	{
		if ((PIND & (1<<s_signal))!= previousReading) // Aqui le estoy diciendo: Si estoy recibiendo un 1 en el sensor y no es igual a previousReading entonces hago esto 
		{
			
			if (!estadoMano)// ahora, si el estado de la mano (1= si se ha puesto la mano 0= si no se ha puesto la mano)Esto no tiene nada que ver con la señal del sensor
			{
				OCR1A = 187;
				_delay_ms(2000);	  //de ser así entonces muevo el servo a 0° y espero 2 seg	
				estadoMano = 1;
			}
			else
			{
				estadoMano = 0;
			}
			
			OCR1A = 125;        //Cuando entonces salga de esa comrobacion y ejecucion el volverá a su estado de reposo
			_delay_ms(2000);
			previousReading = (PIND & (1<<s_signal)); //incluso si la mano sigue estando debajo del sensor
			
		}
		
	}
}


