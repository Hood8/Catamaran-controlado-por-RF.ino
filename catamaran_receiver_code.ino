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
#include <ELECHOUSE_CC1101.h>  /*esta librería sirve para que los 
                               transceptores CC1101 se comuniquen 
                               https://github.com/simonmonk/CC1101_arduino 
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
                               https://github.com/simonmonk/CC1101_arduino 
                               
*Conexión de los transceptores CC1101: 
                               
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
const int n = 61;

int atBabor=3;        //declara la variable atBabor y le asigna el pin 3 conectado a ENA2 en el driver L298N
int avBabor=4;        //declara la variable avBabor y le asigna el pin 4 conectado a ENA1 en el driver L298N
int avEstribor=7;     //declara la variable avEstribor y le asigna el pin 7 conectado a ENB1 en el driver L298N
int atEstribor=8;     //declara la variable atEstribor y le asigna el pin 8 conectado a ENB2 en el driver L298N

int pwmBabor=5;       /*declara la variable pwmBabor y le asigna el pin 5 de 
                      arduino que se conecta con el pin EnA del L298N y que 
                      servirá para regular la velocidad del motor de babor*/                     
int pwmEstribor=6;    /*declara la variable atBabor y le asigna el pin 6 de
                      arduino que se conecta con el pin EnB del L298N y que 
                      servirá para regular la velocidad del motor de estribor*/


void setup()
{ 
  pinMode(atBabor, OUTPUT);      //declara atBabor como pin de salida
  pinMode(avBabor, OUTPUT);      //declara avBabor como pin desalida
  pinMode(avEstribor, OUTPUT);   //declara avEstribor como pin de salida 
  pinMode(atEstribor, OUTPUT);   //declara atEstribor como pin de salida
  pinMode(pwmBabor, OUTPUT);     //declara pwmBabor como pin de salida
  pinMode(pwmEstribor, OUTPUT);  //declara pwmEstribor como pin de salida

  //pinMode(potencia, OUTPUT);   //declara atEstribor como pin de salida
   
  Serial.begin(9600);            //inicia el Puerto en Serie con una velocidad de 9600 bauds por segundo
  Serial.println("Rx");          //imprime la palabra 'Rx' en el monitor del Puerto de Serie
  ELECHOUSE_cc1101.Init(F_433);  //fija la frecuencia - F_433, F_868, F_965 MHz
  ELECHOUSE_cc1101.SetReceive(); //le dice al arduino que aplique los datos recibidos 
 
}

 
byte buffer[61] = {0};


void loop()
{ 
  if (ELECHOUSE_cc1101.CheckReceiveFlag())
  {
    int len = ELECHOUSE_cc1101.ReceiveData(buffer);
    buffer[len] = '\0';
    Serial.println((char *) buffer);
      
 //código jose start

    // Si recibe 'a'  activa  pin 5 (avante babor)
        if(buffer[0]=='a'){
       
        digitalWrite(atBabor,0); 
        digitalWrite(avBabor,1);      //(avante babor)
        digitalWrite(avEstribor,0);
        digitalWrite(atEstribor,0);
        }

    // Si recibe 'b' activa el pin 5 y el pin 6 (motores avante)
        if(buffer[0]=='b'){
       
        digitalWrite(atBabor,0); 
        digitalWrite(avBabor,1);      //avante babor
        digitalWrite(avEstribor,1);   //avante estribor
        digitalWrite(atEstribor,0);
        }
        
    // Si recibe 'c' activa el pin 6 (avante estribor)
        if(buffer[0]=='c'){
       
        digitalWrite(atBabor,0);
        digitalWrite(avBabor,0); 
        digitalWrite(avEstribor,1);   //avante estribor
        digitalWrite(atEstribor,0);
        }  
        
    // Si recibe 'd' activa el pin 4 y el pin 6 (atrás babor, avante estribor)
        if(buffer[0]=='d'){
        
        digitalWrite(atBabor,1);      //atrás babor
        digitalWrite(avBabor,0); 
        digitalWrite(avEstribor,1);   //avante estribor
        digitalWrite(atEstribor,0);
        }
 
    // Si recibe 'e' activa el pin 4 (atrás babor)
        if(buffer[0]=='e'){
        
        digitalWrite(atBabor,1);      //atrás babor
        digitalWrite(avBabor,0); 
        digitalWrite(avEstribor,0); 
        digitalWrite(atEstribor,0);
        }
                
    // Si recibe 'f' activa el pin 4 y el pin 7 (motores atrás)
        if(buffer[0]=='f'){
        
        digitalWrite(atBabor,1);      //atrás babor
        digitalWrite(avBabor,0);
        digitalWrite(avEstribor,0); 
        digitalWrite(atEstribor,1);   //atrás estribor
        } 

    // Si recibe 'g' activa el pin 7 (atrás estribor)
        if(buffer[0]=='g'){
        
        digitalWrite(atBabor,0);
        digitalWrite(avBabor,0);
        digitalWrite(avEstribor,0); 
        digitalWrite(atEstribor,1);   //atrás estribor
        }   

   // Si recibe 'h' activa el pin 4 y el pin 6 (atrás babor, avante estribor)
        if(buffer[0]=='h'){
        
        digitalWrite(atBabor,0);      
        digitalWrite(avBabor,1);      //avante babor
        digitalWrite(avEstribor,0);   
        digitalWrite(atEstribor,1);   //atras estribor
        }
   // Si recibe 'i' no activa ningún pin (motores parados)
   
        if(buffer[0]=='i'){

        digitalWrite(atBabor,0); 
        digitalWrite(avBabor,0);
        digitalWrite(avEstribor,0);
        digitalWrite(atEstribor,0);
        }
        
        // Si recibe '0' activa el pin pwmBabor y el pin pwmEstribor 
        if(buffer[0]=='0'){
        analogWrite(pwmBabor,0);    //Velocidad motor derecho 0 //
        analogWrite(pwmEstribor,0); //Velocidad motor izquierdo 0 //
        }
        
        // Si recibe '1' activa el pin pwmBabor y el pin pwmEstribor 
        if(buffer[0]=='1'){
        analogWrite(pwmBabor,115);    //Velocidad motor derecho 115 //
        analogWrite(pwmEstribor,115); //Velocidad motor izquierdo 115 //
        }
        
        // Si recibe '2' activa el pin pwmBabor y el pin pwmEstribor 
        if(buffer[0]=='2'){ 
        analogWrite(pwmBabor,129);    //Velocidad motor derecho 129 //
        analogWrite(pwmEstribor,129); //Velocidad motor izquierdo 129 //
        } 
        
        // Si recibe '3' activa el pin pwmBabor y el pin pwmEstribor 
        if(buffer[0]=='3'){
        analogWrite(pwmBabor,147);    //Velocidad motor derecho 147 //
        analogWrite(pwmEstribor,147);//Velocidad motor izquierdo 147 //
        }
        
        // Si recibe '4' activa el pin pwmBabor y el pin pwmEstribor 
        if(buffer[0]=='4'){
        analogWrite(pwmBabor,165);    //Velocidad motor derecho 165 //
        analogWrite(pwmEstribor,165); //Velocidad motor izquierdo 165 //
        } 
        
        // Si recibe '5' activa el pin pwmBabor y el pin pwmEstribor 
        if(buffer[0]=='5'){
        analogWrite(pwmBabor,183);  //Velocidad motor derecho 183 //
        analogWrite(pwmEstribor,183); //Velocidad motor izquierdo 183 //
        }
       
        // Si recibe '6' activa el pin pwmBabor y el pin pwmEstribor 
        if(buffer[0]=='6'){
        analogWrite(pwmBabor,201);   //Velocidad motor derecho 201 //
        analogWrite(pwmEstribor,201);//Velocidad motor izquierdo 201 //
        }
         
        // Si recibe '7' activa el pin pwmBabor y el pin pwmEstribor 
        if(buffer[0]=='7'){
        analogWrite(pwmBabor,219);  //Velocidad motor derecho 219 //
        analogWrite(pwmEstribor,219); //Velocidad motor izquierdo 219 //
        } 
        
        // Si recibe '8' activa el pin pwmBabor y el pin pwmEstribor 
        if(buffer[0]=='8'){
        analogWrite(pwmBabor,237);    //Velocidad motor derecho 237 //
        analogWrite(pwmEstribor,237);//Velocidad motor izquierdo 237 //
        }
        
        // Si recibe '9' activa el pin pwmBabor y el pin pwmEstribor 
        if(buffer[0]=='9'){
        analogWrite(pwmBabor,255);    //Velocidad motor derecho 255 //
        analogWrite(pwmEstribor,255); //Velocidad motor izquierdo 255//
        }
        
     }     
      
    ELECHOUSE_cc1101.SetReceive();   
} 


//Creado por José María Mejuto Ferro siguiendo lecciones de los tutoriales de arduino online
//Agradecimientosa todos los que colaboran por extender el conocimiento y especialmente a mis camaradas rojos 
//que dan su vida por nosotros luchando contra el sistema según sus posibilidades y rangos de acción.

//Octubre 2018
