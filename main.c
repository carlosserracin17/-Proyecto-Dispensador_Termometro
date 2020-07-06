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

void setflag(int);
int getflag();

volatile int flag = 0; //flag which control the actions timing inside the infinite loop

#define s_signal PORTD1
#define servo PORTB1




void init_servo(void)
{
	DDRB |= (1<<servo);	//set pwm pin (OC1A)
	TCNT1 = 0;		// timer 1 register to 0
	ICR1 = 2499;	// counting till icr1 value


	TCCR1A |=
	(1<<COM1A1) |(0<<COM1A0) //Clear OC1A on Compare Match, set OC1A at BOTTOM (non-inverting mode)
	|(1<<WGM11) |(0<<WGM10); //waveform generation mode #14 (Fast PWM, TOP = ICR1, UPDATE OCR1A at BOTTOM, TOV1 FLAG set on TOP )
	
	TCCR1B |=
	(1<<WGM13) | (1<<WGM12) //waveform generation mode #14 complementary bits
	|(0<<CS12) |(1<<CS11)|(0<<CS10); //clock pre-scaler for pwm fq
}

int init_tim (void)
{
	//Timer con delay de 0.5 seg (500ms)

	TCCR1B |= (0<<CS12)|(1<<CS11)|(0<<CS10); /* Fsys: 1Mhz Timer1: timer 16-bits Pre-scaler: 8 */
	
	TIMSK1 |= (1<<TOIE1); /* Enable Overflow Interrupt */
	
	TIFR1 |= (1<<TOV1); /* Clearing overflow flag */
	
	TCNT1=3036;
}

int main(void)
{
	cli();
	init_servo();
	init_tim();
	sei();
	
	//Aqui vamos a establecer las entradas, que en este caso solo será la señal proveniente del sensor
	DDRD &=~ (1<<s_signal);
	PORTD = (1<<s_signal);
	
	OCR1A = 125;
	
	
	while (1)
	{
		if (PIND & (1<<s_signal))
		{
			OCR1A = 187;
			_delay_ms(100);
			
			if(getflag() == 1)
			{
				OCR1A = 125;
				TCNT1=3036;
			}
		}
		
	}
}

ISR (TIMER1_OVF_vect){
	setflag(1); /* Toggle a pin on timer overflow */
}



void setflag(int f){
	flag = f;
}

int getflag(){
	return flag;
}