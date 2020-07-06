# ACTUALIZAR LOS CAMBIOS 
#  Proyecto Dispensador de Gel Automatico 


Este es un repositorio en donde se va a ir desarrollando nuestro proyecto final para la materia de Cricuitos Electronicos lV de la carrera de ing. mecatronica de la Universidad Latina de Panamá. Estudiantes: Carlos Serracin y Aaron Mclean. Profesor: Pablo González Robles.

## Fundamento de la investigacion

Este proyecto fue pensado como una solucion para los problemas que hoy se enfrentan en esta crisis sanitaria producto de la pandemia.
La vida ha cambiado al igual que la manera en la que vemos el aseo personal. Se ha vuelto indispensable el distanciamiento entre las personas, portar mascarillas desechales y tener siempre las sonas de contacto limpias al igual que tus manos y pies cuando entras y sales de un recinto.

Los sanitizadores de manos han llegado para cumplir un rol indispensable en la sociedad que enfrenta la pandemia, debido al hecho que nuestras manos son la parte de nuestro cuerpo que están en constante contacto con el medio, y por ende ser un ente portador del virus y distribuidor de el, pues así como vemos, no solo podriamos portar el virus para contagiarnos a nosotros mismos, sino tambien llevarlo desde el punto A, donde habian contagio, al punto B donde no había virus.

Los sanitizadores cumplen la labor de eliminar todos los germenes y virus que puedan estar en tus manos, y así evitar tanto la propagacion como el contagio.
 
Los sanitizadores comunes trabajan mediante nua valvula mecanica que se abre y se cierra al contacto de la mano, sin embargo, hemos visto en la actualidad que ya existen sanitizadores con luz infraroja que reconocen la presencia del individuo y proporcionan el liquido sanitizante sin que la persona tenga que tocar ningun objeto. Aqui radica el punto más importante de nuestro proyecto.

Esta es la manera en la que buscamos estructurar nuestro microcontrolador y pues claro, utlizando la tecnología mas reciente que se tenga a la mano con el fín de mejorar el funcionamiento y la disposiscion actual de estos equipos que forman parte de nuestras vida diaria, y no solo en los recintos publicos o restaurantes y baños, sino incluso ahora en las puertas de entrada de entra de las casas, 
oficinas, bancos, tiendas y un sinnumero de lugares.


## Servo motor y PWM
![image](https://user-images.githubusercontent.com/66341655/86657713-12de6180-bfae-11ea-988f-512e9ec3371f.png)
El servo motor es un componente que contiene basicamente un motor dc dentro, junto a una sere de engranajes; y se caracteriza por poder ser controlable en cuanto posicion se refiere. Para que esto sea posible, el PWM juega un papel importante. El servo tiene 3 pines, el de alimentacion (**+5V**), el de tierra y el de señal por donde entraran los pulsos o la señal PWM.
![pwm_servo_9g](https://user-images.githubusercontent.com/66341655/86658446-afa0ff00-bfae-11ea-833c-b651269a1144.png)
Este servo motor se mueve en un rango de 0 a 180°. Para mover el servomotor a la posicion de 0°, es necesario un pulso de 1.5ms, para moverse hacia la derecha completamente hacia los 90° positivos, es necesario un pulso aproximado de 2ms y para moverse hacia la izquierda completamente es decir, hacia los 90° negativos, es necesario un pulso de aproximadamente 1ms.
Es importante resaltar que, para el PWM tenga un funcionamioento adecuado en este servomotor, se necesita generar un PWM a una frecuencia de 50Hz, es decir ondas de 20ms.

##Duty Cycle
El duty cycle es una medida que se utiliza para represantar que porcentaje del periodo de nuestra Onda cuadrada, en nuestro caso, va a estar en high y que porcentaje de la onda va a esta en low.
Si decimosque queremos un duty cycle del 30%, eso quiere decir que la onda va a estar 30% en High y un 70% en Low. Ojo, esto suponiendo que estamos trabajando el el modo PWM-No-Invertido. 
Pues sí, exite un modo PWM, invertido pero en la elaboracion de nuestro proyecto no lo usaremos, por ello, obviaremos su explicacion.


