#ifndef ArduinoRaspberryPiCOMHEADER
#define ArduinoRaspberryPiCOMHEADER

#include <Arduino.h>

class ArduinoRaspberryPiCOM
{

private:
  String sensores[5][5];
  int valSenso[5][5][2];
  String actuador[5][5];
  int valActua[5][5][2];

public:
  int DIGITAL = 44;
  int ANALOGO = 42;
  int PWM = 24;

  ArduinoRaspberryPiCOM();
  void crearGrupoSensor(String nombreGrupo, int tipoSenal);
  void agregarSensor(String nombreSensor, String nombreGrupo, int pinSensor);
  void crearGrupoActuador(String nombreGrupo, int tipoSenal);
  void agregarActuador(String nombreActuador, String nombreGrupo, int pinActuador);

  void leerSensores();
  String darJSON();
};

#endif
