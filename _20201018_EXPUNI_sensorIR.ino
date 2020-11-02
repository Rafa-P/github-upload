#include <Servo.h>    // Librería control servo




// Declaración de los servos
// NOTA: servo rotación continua: ángulo 0 dirección izq, ángulo 180 dirección derecha
Servo servorampa;  // servo tracción rampa elevadora
Servo servocinta;  // servo tracción cinta transportadora
int velrampa = 90;   // velocidad de la rampa elevadora = 0
int velcinta = 90;   // velocidad de la cinta transportadora = 0
Servo brazoelevador; // servo brazo elevador
int brazoinicial; //Posición inicial del brazo
int brazofinal; // Posición final del brazo

// Sensor IR para piezas en la cinta transportadora
const int sensorPin = 2;
int medida;     //Medición del sensor
int sumatorio;  //Sumatorio de detecciones del sensor

// Inicialización de variables
void setup() {

    Serial.begin(9600);     // Monitor serie
    
    servorampa.attach(9);  // servo rampa elevadora
    servocinta.attach(10); // servo cinta transportadora
    brazoelevador.attach(11); // servo brazo elevador

    brazoinicial = 177;
    brazofinal = 90;
    brazoelevador.write(brazoinicial); // ponemos el brazo elevador en su posición inicial

    // Entrada del sensor IR
    pinMode(sensorPin , INPUT);  //definir pin como entrada
    sumatorio = 0;
}
 
void loop() {
   // rampa en marcha sentido hacia arriba
   velrampa = 80;
   servorampa.write(velrampa);                 

   //cinta transportadora sentido derecha
   velcinta = 98;
   servocinta.write(velcinta);              

   // Detección de objeto en la cinta transportadora

  medida = digitalRead(sensorPin );  //lectura digital de pin
  if (medida == LOW)
    {
      sumatorio = sumatorio +1;
      }

  if (sumatorio > 4)
    {
      devolverpiezaalcircuito();
      }
  
  
  // **** SALIDA POR EL MONITOR SERIE PARA CONTROL
  Serial.print("Ping: ");
  Serial.print(medida); 
  Serial.print(" cm. Sumatorio: ");
  Serial.println(sumatorio);   
   
}

void devolverpiezaalcircuito()
  {
  
   //paramos la rampa
   velrampa = 90;
   servorampa.write(velrampa); 
   //cinta transportadora unos segundos funcionando
   velcinta = 98;
   servocinta.write(velcinta);   
   delay(2500);
   //paramos la cinta
   velcinta = 90;
   servocinta.write(velcinta); 
   //ponemos en marcha la rampa de nuevo
   velrampa = 80;
   servorampa.write(velrampa); 
   delay(1000);
   //movemos el brazo elevador para devolver la pieza al circuito
   brazoelevador.write(brazofinal);
   delay(1500);
   brazoelevador.write(brazoinicial);
   //ponemos el contador del detector a cero
   sumatorio = 0;
  }
