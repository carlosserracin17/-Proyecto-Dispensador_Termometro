
#  Proyecto Dispensador de Gel Automatico 
### Fase 1


Este es un repositorio en donde se va a ir desarrollando nuestro proyecto final para la materia de Cricuitos Electronicos lV de la carrera de ing. mecatronica de la Universidad Latina de Panamá. Estudiantes: Carlos Serracin y Aaron Mclean. Profesor: Pablo González Robles.

## Fundamento de la investigacion

Este proyecto fue pensado como una solución para los problemas que hoy se enfrentan en esta crisis sanitaria producto de la pandemia. La vida ha cambiado al igual que la manera en la que vemos el aseo personal. Se ha vuelto indispensable el distanciamiento entre las personas, portar mascarillas desechables y tener siempre las zonas de contacto limpias al igual que tus manos y pies cuando entras y sales de un recinto.


Los sanitizadores de manos han llegado para cumplir un rol indispensable en la sociedad que enfrenta la pandemia, debido al hecho que nuestras manos son la parte de nuestro cuerpo que están en constante contacto con el medio, y por ende ser un ente portador del virus y distribuidor de el, pues así como vemos, no solo podríamos portar el virus para contagiarnos a nosotros mismos, sino también llevarlo desde el punto A, donde había contagio, al punto B donde no había virus.

Los sanitizadores cumplen la labor de eliminar todos los gérmenes y virus que puedan estar en tus manos, y así evitar tanto la propagación como el contagio.

Los sanitizadores comunes trabajan mediante una válvula mecánica que se abre y se cierra al contacto de la mano, sin embargo, hemos visto en la actualidad que ya existen sanitizadores con luz infrarroja que reconocen la presencia del individuo y proporcionan el liquido sanitizante sin que la persona tenga que tocar ningún objeto. Aquí radica el punto más importante de nuestro proyecto.

Esta es la manera en la que buscamos estructurar nuestro microcontrolador y pues claro, utilizando la tecnología más reciente que se tenga a la mano con el fín de mejorar el funcionamiento y la disposición actual de estos equipos que forman parte de nuestra vida diaria, y no solo en los recintos públicos o restaurantes y baños, sino incluso ahora en las puertas de entrada de las casas, oficinas, bancos, tiendas y un sinnúmero de lugares.


## Servo motor y PWM
![image](https://user-images.githubusercontent.com/66341655/86657713-12de6180-bfae-11ea-988f-512e9ec3371f.png)

El servo motor es un componente que contiene basicamente un motor DC dentro, junto a una sere de engranajes; y se caracteriza por poder ser controlable en cuanto posicion se refiere. Para que esto sea posible, el PWM juega un papel importante. El servo tiene 3 pines, el de alimentacion (**+5V**), el de tierra y el de señal por donde entraran los pulsos o la señal PWM.
![pwm_servo_9g](https://user-images.githubusercontent.com/66341655/86658446-afa0ff00-bfae-11ea-833c-b651269a1144.png)

Este servo motor se mueve en un rango de 0 a 180°. Para mover el servomotor a la posicion de 0°, es necesario un pulso de 1.5ms, para moverse hacia la derecha completamente hacia los 90° positivos, es necesario un pulso aproximado de 2ms y para moverse hacia la izquierda completamente es decir, hacia los 90° negativos, es necesario un pulso de aproximadamente 1ms.
Es importante resaltar que, para el PWM tenga un funcionamioento adecuado en este servomotor, se necesita generar un PWM a una frecuencia de 50Hz, es decir ondas de 20ms.

## Duty Cycle
El duty cycle es una medida que se utiliza para represantar que porcentaje del periodo de nuestra Onda cuadrada, en nuestro caso, va a estar en high y que porcentaje de la onda va a esta en low.
Si decimosque queremos un duty cycle del 30%, eso quiere decir que la onda va a estar 30% en High y un 70% en Low. Ojo, esto suponiendo que estamos trabajando el el modo PWM-No-Invertido. 
Pues sí, exite un modo PWM, invertido pero en la elaboracion de nuestro proyecto no lo usaremos, por ello, obviaremos su explicacion.

## Explicacion del código
Bien, primero que todo, ya sabiendo las razones por las que escogimos cada uno de los componentes a utilizar en el hardware de nuestro dispositivo, ahora vamos a la programacion de nuestro microcontrolador. 
En este punto del desarrollo del proyecto es donde ponemos en práctica todo lo aprendido durante el curso. Sin la programacion de nuestro micro-controlador, nuestro proyecto detectaría nada y tampoco se movería ningun motor.

1.  En esta linea observamos que estamos seteando la Frecuencia de nuestra CPU del microcontrolador a 1MHz, por qué esta frecuencia pues, basicamente por dos razones, la primera, es que esta frecuencia nos funciona para luego generar un PWM de 20Ms de periodo y segundo porque a esta Velocidad nuestro CPU es Eficiente, en terminos de consumo y velocidad.
Adicionalmente tambien observamos que incluímos la librería `<avr/io.h>`, para nuestro Chip atmel, la librería `<util/delay.h>`, para habilitar el funcionamiento de un delay y el `<avr/interrupt.h>`, pues para las interrupciones.
```
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
```

2. Ahora definimos 2 variables muy importantes que nos van a ayudar dentro del while loop de nuestra funcion Main. El `previousReading` va a ser utilizado para sensiorarnos y notificar lo que se acaba de leer,lo explicaremos con detalles en el while loop y el `estadoMano` para en teoría revisar si el sensor aun está detectando la mano.
Definimos, la señal del sensor como `s_signal` en el puerto D1 y la señal `servo` en el Puerto B1 (PORTB1), porque ahí es donde podremos configurar el registro OC1A, que usaremos para nuestro PWM.
```
uint8_t previousReading  = 1;
uint8_t estadoMano = 1;

#define s_signal PORTD1
#define servo PORTB1
```
3. Ahora, escribimos la funcion `init_servo` generar un PWM para el servo. En esta parte, colocamos la explicacion de cada linea, alado del codigo, para una mejor comprension y visualizacion. 
```
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
``` 
4. Aqui es donde viene la ejecucion de nuestra funcion principal.
```
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

```
