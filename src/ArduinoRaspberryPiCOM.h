#ifndef ArduinoRaspberryPiCOMHEADER
#define ArduinoRaspberryPiCOMHEADER

#include <Arduino.h>

class ArduinoRaspberryPiCOM
{

private:
  static const int MAX_GRUPOS = 5;
  static const int MAX_POR_GRUPO = 5;

  String sensores[MAX_GRUPOS][MAX_POR_GRUPO];
  int valSenso[MAX_GRUPOS][MAX_POR_GRUPO][2];
  String actuador[MAX_GRUPOS][MAX_POR_GRUPO];
  int valActua[MAX_GRUPOS][MAX_POR_GRUPO][2];

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
  void actualizarActuadores();

  String darJSON();
  int leerJSON(String json, String nombreABuscar);
};

#endif
