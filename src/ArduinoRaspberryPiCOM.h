#ifndef ArduinoRaspberryPiCOMHEADER
#define ArduinoRaspberryPiCOMHEADER

#include <Arduino.h>
#include <string>

class ArduinoRaspberryPiCOM
{

private:
  string sensores[10][8];
  int valSenso[10][8][2];
  string actuador[10][8];
  int valActua[10][8][2];

public:
  int DIGITAL = 44;
  int ANALOGO = 42;
  int PWM = 24;

  ArduinoRaspberryPiCOM(int numGruposSensores, int numGruposActuadores);
  void crearGrupoSensor(string nombreGrupo, int tipoSeñal);
  void agregarSensor(string nombreSensor, string nombreGrupo, int pinSensor);
  void crearGrupoActuador(string nombreGrupo, int tipoSeñal);
  void agregarActuador(string nombreActuador, string nombreGrupo, int pinActuador);

  void leerSensores();
  string darJSON();

};

#endif
