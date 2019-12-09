#include <ArduinoRaspberryPiCOM.h>
#include <Arduino.h>
#include <string>

ArduinoRaspberryPiCOM::ArduinoRaspberryPiCOM(int numGruposSensores, int numGruposActuadores)
{
  for(int n=0; n<8; n++)
  {
    for(int j=0; j<10; j++)
    {
      sensores[j][n] = "";
      valSenso[j][n][0] = 0;
      valSenso[j][n][1] = 0;

      actuador[j][n] = "";
      valActua[j][n][0] = 0;
      valActua[j][n][1] = 0;
    }
  }
}

void ArduinoRaspberryPiCOM::crearGrupoSensor(string nombreGrupo, int tipoSeñal)
{
  for(int n=0; n<8; n++)
  {
    if(sensores[0][n].compare("") == 0)
    {
      sensores[0][n] = nombreGrupo;
      valSenso[0][n][0] = tipoSeñal;
    }
  }
}

void ArduinoRaspberryPiCOM::agregarSensor(string nombreSensor, string nombreGrupo, int pinSensor)
{
  for(int n=0; n<8; n++)
  {
    if(sensores[0][n].compare(nombreGrupo) == 0)
    {
      for(int j=0; j<10; j++)
      {
        if(sensores[j][n].compare("") == 0)
        {
          sensores[j][n] = nombreSensor;
          valSenso[j][n][1] = pinSensor;
          pinMode(pinSensor, INPUT);
        }
      }
    }
  }
}

void ArduinoRaspberryPiCOM::crearGrupoActuador(string nombreGrupo, int tipoSeñal)
{
  for(int n=0; n<8; n++)
  {
    if(actuador[0][n].compare("") == 0)
    {
      actuador[0][n] = nombreGrupo;
      valActua[0][n][0] = tipoSeñal;
    }
  }
}

void ArduinoRaspberryPiCOM::agregarActuador(string nombreActuador, string nombreGrupo, int pinActuador)
{
  for(int n=0; n<8; n++)
  {
    if(actuador[0][n].compare(nombreGrupo) == 0)
    {
      for(int j=0; j<10; j++)
      {
        if(actuador[j][n].compare("") == 0)
        {
          actuador[j][n] = nombreSensor;
          valActua[j][n][1] = pinSensor;
          pinMode(pinActuador, OUTPUT);
        }
      }
    }
  }
}

void ArduinoRaspberryPiCOM::leerSensores()
{
  for(int n=0; n<8; n++)
  {
    if(valSenso[0][n][0] == DIGITAL && sensores[0][n].compare("") != 0)
    {
      for(int j=1; j<10; j++)
      {
        if(sensores[j][n].compare("") != 0)
        {
          valSenso[j][n][0] = digitalRead(valSenso[j][n][1]);
        }
      }
    }
    else if(valSenso[0][n][0] == ANALOGO && sensores[0][n].compare("") != 0)
    {
      for(int j=1; j<10; j++)
      {
        if(sensores[j][n].compare("") != 0)
        {
          valSenso[j][n][0] = analogRead(valSenso[j][n][1]);
        }
      }
    }
  }
}

string ArduinoRaspberryPiCOM::darJSON()
{
  string json = '{"Sensores" : {';

  bool acabo = false;
  for(int n=0; n<8 && !acabo; n++)
  {
    if(sensores[0][n].compare("") != 0)
    {
      json += '"' + sensores[0][n] + '" : {';

      bool sigGrupo = false;
      for(int j=1; j<10 && !sigGrupo; j++)
      {
        if(sensores[j][n].compare("") != 0)
        {
          json += '"' + sensores[j][n] + '" : ' + to_string(valSenso[j][n][0]);
          if(j + 1 < 10)
          {
            if(sensores[j+1][n].compare("") != 0)
            {
              json += ',';
            }
          }
        }
        else
        {
          sigGrupo = true;
        }
      }
      json += '}';
      if(n + 1 < 8)
      {
        if(sensores[0][n+1].compare("") != 0)
        {
          json += ',';
        }
      }
    }
    else
    {
      acabo = true;
    }
  }
  json += '}}';

  return json;
}
