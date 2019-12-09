/*
  EstructuraSensores

  Demuestra cómo crear una estructura de sensores con la librería, agruparlos por nombre
  y obtener un JSON con los valores leídos de los sensores conectados

  Información disponible en:
  https://github.com/smartinezc/ArduinoRaspberryPiCOM
*/

#include <ArduinoRaspberryPiCOM.h>

// Crear una variable de tipo ArduinoRaspberryPiCOM, la cual se encarga de la gestión de
// sensores conectados a Arduino
ArduinoRaspberryPiCOM arCOM = ArduinoRaspberryPiCOM();

// Definir los pines donde estarán conectados los sensores
int pinSenH1 = 4;     // El pin 4 será usado por Sensor de Humedad 1
int pinSenH2 = 5;     // El pin 5 será usado por Sensor de Humedad 2

int pinSenT1 = A0;    // El pin A0 será usado por Sensor de Temperatura 1

// Para evitar el uso de la función delay() se empleará las siguientes variables
unsigned long prevTime = 0;  //Guarda el tiempo de la última lectura de sensores
long intervalo = 1000;       //Define en milisegundos el tiempo de lectura de sensores

// En el setup se añadirán los sensores a la estructura arCOM
void setup() {
  // Inicia el canal Serial para la comunicacion con el Raspberry Pi a 9600 bauds
  Serial.begin(9600);
  
  // Crear un grupo de sensores para agrupar los similares. 
  // Parámetros: String:NombreGrupo, int:TipoSeñal(DIGITAL, ANALOGO)
  arCOM.crearGrupoSensor("Humedad", arCOM.DIGITAL);
  arCOM.crearGrupoSensor("Temperatura", arCOM.ANALOGO);

  // Añadir a cada grupo sus sensores, especificando el pin al que se conectan
  // Parámetros: String:NombreSensor, String:NombreGrupo, int:PinSensor
  arCOM.agregarSensor("Sensor de Humedad 1", "Humedad", pinSenH1);
  arCOM.agregarSensor("Sensor de Humedad 2", "Humedad", pinSenH2);

  arCOM.agregarSensor("Sensor de Temperatura 1", "Temperatura", pinSenT1);
  // Note que NO SE REQUIERE DEFINIR LOS PINES COMO ENTRADAS/SALIDAS, la librería lo hace
}

void loop() {

  // Durante la ejecución del programa se leerá el valor de los sensores a una tasa de
  // muestreo deseada (variable intervalo definida al inicio) o bajo la condición deseada

  // Aquí puede ir el código del programa que correrá en bucle todo el tiempo sin delay()

  // Comprueba si es tiempo de revisar los sensores
  unsigned long actTime = millis();
  if(actTime - prevTime >= intervalo)
  {
    prevTime = actTime;                     //Guarda la última vez que se lee los sensores
    arCOM.leerSensores();                   //Actualiza el valor de los sensores
    String jsonSensores = arCOM.darJSON();  //Obtiene el JSON con información de sensores
    Serial.println(jsonSensores);           //Envía a través del canal Serial el JSON
  }
  

  
}
