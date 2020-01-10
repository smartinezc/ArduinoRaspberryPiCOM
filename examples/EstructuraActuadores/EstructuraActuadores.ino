/*
  EstructuraActuadores

  Demuestra cómo crear una estructura de actuadores con la librería, agruparlos por nombre
  y manejar los actuadores declarados a través de un JSON con los valores deseados

  Información disponible en:
  https://github.com/smartinezc/ArduinoRaspberryPiCOM
*/

#include <ArduinoRaspberryPiCOM.h>

// Crear una variable de tipo ArduinoRaspberryPiCOM, la cual se encarga de la gestión de
// actuadores conectados a Arduino
ArduinoRaspberryPiCOM arCOM = ArduinoRaspberryPiCOM();

// Definir los pines donde estarán conectados los actuadores
int pinBombaAgua = 2;     // El pin 2 será usado para controlar la Bomba de Agua
int pinBombaVacio = 3;    // El pin 3 será usado para controlar la Bomba de Vacío

int pinEncendido = 8;     // El pin 8 será usado por el LED de Encendido
int pinAlarma = 9;        // El pin 9 (Pin PWM) será usado por el LED de Alarma - señal PWM

// Para evitar el uso de la función delay() se empleará las siguientes variables
unsigned long prevTime = 0;  //Guarda el tiempo de la última lectura del JSON 
                             // proveniente del Raspberry Pi
long intervalo = 1000;       //Define en milisegundos el tiempo de espera para la 
                             // actualización de actuadores

// En el setup se añadirán los actuadores a la estructura arCOM
void setup() {
  // Inicia el canal Serial para la comunicacion con el Raspberry Pi a 2400 bauds
  Serial.begin(2400);
  
  // Crear un grupo de actuadores para agrupar los similares. 
  // Parámetros: String:NombreGrupo, int:TipoSeñal(DIGITAL, PWM)
  arCOM.crearGrupoActuador("Bombas", arCOM.PWM);
  arCOM.crearGrupoActuador("LEDs", arCOM.DIGITAL);

  // Añadir a cada grupo sus actuadores, especificando el pin al que se conectan
  // Parámetros: String:NombreActuador, String:NombreGrupo, int:pinActuador
  arCOM.agregarActuador("BombaAgua", "Bombas", pinBombaAgua);
  arCOM.agregarActuador("BombaVacio", "Bombas", pinBombaVacio);

  arCOM.agregarActuador("Encendido", "LEDs", pinEncendido);
  arCOM.agregarActuador("Alarma", "LEDs", pinAlarma);
  // Note que NO SE REQUIERE DEFINIR LOS PINES COMO ENTRADAS/SALIDAS, la librería lo hace
}

void loop() {

  // Durante la ejecución del programa se leerá el JSON enviado por el Raspberry Pi 
  // a una tasa de muestreo deseada (variable intervalo definida al inicio) o bajo 
  // la condición deseada

  // Aquí puede ir el código del programa que correrá en bucle todo el tiempo sin delay()

  // Comprueba si es tiempo de revisar el JSON
  unsigned long actTime = millis();
  if(actTime - prevTime >= intervalo)
  {
    prevTime = actTime;                     //Guarda la última vez que se lee el JSON
    arCOM.actualizarActuadores();           //Actualiza el valor de los actuadores
    // En este momento los actuadores han cambiado su estado al especificado en el JSON
  }
  
}
