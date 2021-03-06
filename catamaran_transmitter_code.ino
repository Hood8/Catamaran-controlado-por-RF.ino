/*Este proyecto esta protegido por la licencia de software libre GNU General Public License (GPL) 3.0
 
 Código para barco con dos motores eléctricos 
 Este código permite controlar dos motores eléctricos por radiofrecuencia con dos módulos RF CC1101, 
 invirtiendo el sentido de giro de sus ejes mediante un Joystick 
 y pudiendo controlar su velocidad mediante un potenciómetro.

  
  Circuito:
 
  2 Arduinos Uno u otras placas base compatibles
  2 Logic Level Converter Bi-Directional Board Module 5V/3.3V DC
  2 motores eléctricos de máximo 2 A de potencia
    
  Lista de componentes conectados a entradas:
     1 Joystick, 1 potenciómetro deslizante, 1 transceptor RF C1101
    
  Lista de componentes conectados a salidas:
     1 transceptor RF C1101, 1 Driver Board L298N (para dos motores max 2A )
      
  

  FECHA :26/10/2018
  AUTOR José María Mejuto
  
  Modified day month year
  By author's name

*/

#include <ELECHOUSE_CC1101.h>/*
LICENCIA LIBRERÍA:
 This library was originally copyright of Michael at elechouse.com but permision was
    granted by Wilson Shen on 2016-10-23 for me (Simon Monk) to update the code for Arduino 1.0+
    and release the code on github under the MIT license.
Wilson Shen <elechouse@elechouse.com> 23 October 2016 at 02:08
To: Simon Monk <srmonk@gmail.com>
Thanks for your email.
You are free to put it in github and to do and change.
On Oct 22, 2016 10:07 PM, "Simon Monk" <srmonk@gmail.com> wrote:
  Hi,
  I'm Simon Monk, I'm currently writing the Electronics Cookbook for O'Reilly. I use your 
  ELECHOUSE_CC1101 library in a 'recipe'. Your library is by far the easiest to use of 
  the libraries for this device, but the .h and .cpp file both reference WProgram.h which 
  as replaced by Arduino.h in Arduino 1.0.
  Rather than have to talk my readers through applying a fix to your library, I'd like 
  your permission to put the modified lib into Github and add an example from the book. 
  I would of course provide a link to your website in the book and mention that you can buy 
  the modules there. If its ok, I'd give the code an MIT OS license, to clarify its use.
  Thanks for a great library,
  Kind Regards,
  Simon Monk.
  
  
*/

    //parte del joystick
    
char *control;       /* declara la variable para poder enviar la 
                     //  información del joystick a través del transceptor */
int xPin = A5;       /* declara la variable del pin VRx del joystick 
                      en el pin analógico A5 de arduino */ 
int yPin = A0;       /* declara la variable del pin VRy del joystick 
                      en el pin analógico A0 de arduino */
int xPosicion;       /* declara la variable para la posicion del joystick 
                      en el eje coordenada de las x */
int yPosicion;       /* declara la variable para la posicion del joystick 
                      en el eje coordenada de las y */

    //parte del potenciómetro deslizante
    
char dataPot[4];     /* declara la variable para poder enviar la 
                     información del potenciómetro a través del transceptor */
const int potIn = A2;/* potenciómetro deslizante,
                     declara la variable para acelerar los 
                     motores y le asigna el pin analógico A2
                     en la placa de arduino */
int valorAnalogico;  /*declara la variable para el valor análogico recibido 
                     desde el potenciómetro deslizante*/
int valorPwm;        /*escala la variable valorAnalógico (0,1023 )a valores de pulse 
                     width modulation (PWM), es decir, valores de 0 a 255*/
int envioPwm;        /*escala la variable valorAnalógico (0,1023 )a valores de entre 0 y 9*/
float tension = 0;   /*declara la variable para calcular el voltaje a través
                     del valor análogico recibido*/

/* Conexión de los transceptores CC1101
 
 These examples are from the Electronics Cookbook by Simon Monk
 Connections (for an Arduino Uno)
 Arduino          CC1101
 GND              GND
 3.3V             VCC
 10               CSN/SS   **** Must be level shifted to 3.3V
 11               SI/MOSI  **** Must be level shifted to 3.3V
 12               SO/MISO
 13               SCK      **** Must be level shifted to 3.3V
 2                GD0
*/

void setup() {
  
  Serial.begin(9600);
  
  ELECHOUSE_cc1101.Init(F_433); //set frequency - F_433, F_868, F_965 MHz
  
   pinMode(xPin, INPUT);        //declara xPin como entrada. Aqui se conecta el pin de datos del eje x del joystick
   pinMode(yPin, INPUT);        //declara yPin como entrada. Aqui se conecta el pin de datos del eje y del joystick
   pinMode(potIn, INPUT);       //declara potPin como entrada. Aquí se conecta el pin de datos del potenciómetro

}

void loop() {  
  
  //PARTE POTENCIÓMETRO
  
  valorAnalogico = analogRead(potIn); 
  tension = (valorAnalogico * 5.0)/1024.0;        // hace la conversión a voltios para mostrar la tensión en el monitor Puerto de Serie
  valorPwm = map(valorAnalogico, 0, 1023, 0, 255);// hace la conversión a valores válidos para PWM (0-255)
  envioPwm = map(valorAnalogico, 0, 1023, 0, 9);  // hace la conversión a valores entre 0 y 9 para enviar al receptor como char
 sprintf(dataPot, "%d", envioPwm);                /* sirve para poder enviar el valor analógico al 
                                                  receptor y lo muestre correctamente en el monitor*/

  Serial.println("");
  Serial.print(" Valor Analógico = " );                      
  Serial.print(valorAnalogico);      // muestra el valor analógico (0-1023) del potenciómetro 
  Serial.print("\t\t Valor PWM = " );                      
  Serial.print(valorPwm);            // muestra el valor PWM (0-255) del potenciómetro
  Serial.println("");
  Serial.print(" Valor Potenciómetro 0-9 = " );                  
  Serial.print(envioPwm);            // muestra el valor mapeado de 0-9 del potenciómetro
  Serial.print("\t Tensión= ");    
  Serial.print(tension,3);           // muestra la tensión en voltios con tres decimales
  Serial.print(" V ");
  Serial.println("");
if ((xPosicion > 610) && (yPosicion > 610))
  {
  control="a" ; //avante babor
  }

  else if ((424 < xPosicion < 600) && (yPosicion > 1000)) 
  {
  control= "b" ; //motores avante
  }

  
 //PARTE JOYSTICK
 
  xPosicion = analogRead(xPin);
  yPosicion = analogRead(yPin);
  
  Serial.print("X: ");
  Serial.print(xPosicion);
  Serial.print(" | Y: ");
  Serial.print(yPosicion);

  if ((xPosicion > 610) && (yPosicion > 610))
  {
  control="a" ; //avante babor
  }

  else if ((424 < xPosicion < 600) && (yPosicion > 1000)) 
  {
  control= "b" ; //motores avante
  }

  else if ((xPosicion < 414 ) && (yPosicion > 610)) 
  {
  control="c" ; //avante estribor
  }

  else if ((xPosicion < 23) && (424 < yPosicion < 600)) 
  {
  control="d" ; //avante estribor, atrás babor
  }
  
  else if (( xPosicion < 414) && (yPosicion < 414))
  {
  control="e" ; //atrás babor
  } 

  else  if ((424 < xPosicion < 600) && (yPosicion < 23))
  {
  control="f" ; //motores atrás
  }

  else  if ((xPosicion > 610) && (yPosicion < 414))
  {
  control="g" ; //atrás estribor
  }
 
  else  if ((xPosicion > 1000) && (424 < yPosicion < 600 )) 
  {
  control="h" ; //atrás estribor, avante babor
  }
  
  else if ((324 < xPosicion < 700) && (324 < yPosicion < 700))
  {
  control="i" ; //motores parados
  }
  
  
  Serial.print(" | Emitiendo: ");
  Serial.println(control);
  Serial.println();
  
  ELECHOUSE_cc1101.SendData ((uint8_t *)control, strlen(control));
  
  ELECHOUSE_cc1101.SendData ((uint8_t *)dataPot, strlen(dataPot)); //funciona
 
  /*delay(250);*/    /*hace una pausa para que el autoscroll en el 
                 Puerto de Serie no corra demasiado y se pueda leer
                 los datos con claridad*/
}

/*Creado por José María Mejuto Ferro siguiendo lecciones de los tutoriales de arduino online
Agradecimientosa todos los que colaboran por extender el conocimiento y especialmente a mis camaradas rojos 
que dan su vida por nosotros luchando contra el sistema según sus posibilidades y rangos de acción.

Octubre 2018*/
