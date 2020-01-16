#include <ArduinoRaspberryPiCOM.h>
#include <Arduino.h>

ArduinoRaspberryPiCOM::ArduinoRaspberryPiCOM()
{
  for(int n=0; n<5; n++)
  {
    for(int j=0; j<5; j++)
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

void ArduinoRaspberryPiCOM::crearGrupoSensor(String nombreGrupo, int tipoSenal)
{
  bool acabo = false;
  for(int n=0; n<5 && !acabo; n++)
  {
    if(sensores[0][n].compareTo("") == 0)
    {
      sensores[0][n] = nombreGrupo;
      valSenso[0][n][0] = tipoSenal;
      acabo = true;
    }
  }
}

void ArduinoRaspberryPiCOM::agregarSensor(String nombreSensor, String nombreGrupo, int pinSensor)
{
  bool acabo = false;
  for(int n=0; n<5 && !acabo; n++)
  {
    if(sensores[0][n].compareTo(nombreGrupo) == 0)
    {
      for(int j=0; j<5 && !acabo; j++)
      {
        if(sensores[j][n].compareTo("") == 0)
        {
          sensores[j][n] = nombreSensor;
          valSenso[j][n][1] = pinSensor;
          pinMode(pinSensor, INPUT);
          acabo = true;
        }
      }
    }
  }
}

void ArduinoRaspberryPiCOM::crearGrupoActuador(String nombreGrupo, int tipoSenal)
{
  bool acabo = false;
  for(int n=0; n<5 && !acabo; n++)
  {
    if(actuador[0][n].compareTo("") == 0)
    {
      actuador[0][n] = nombreGrupo;
      valActua[0][n][0] = tipoSenal;
      acabo = true;
    }
  }
}

void ArduinoRaspberryPiCOM::agregarActuador(String nombreActuador, String nombreGrupo, int pinActuador)
{
  bool acabo = false;
  for(int n=0; n<5 && !acabo; n++)
  {
    if(actuador[0][n].compareTo(nombreGrupo) == 0)
    {
      for(int j=0; j<5 && !acabo; j++)
      {
        if(actuador[j][n].compareTo("") == 0)
        {
          actuador[j][n] = nombreActuador;
          valActua[j][n][1] = pinActuador;
          pinMode(pinActuador, OUTPUT);
          acabo = true;
        }
      }
    }
  }
}

void ArduinoRaspberryPiCOM::leerSensores()
{
  for(int n=0; n<5; n++)
  {
    if(valSenso[0][n][0] == DIGITAL && sensores[0][n].compareTo("") != 0)
    {
      for(int j=1; j<5; j++)
      {
        if(sensores[j][n].compareTo("") != 0)
        {
          valSenso[j][n][0] = digitalRead(valSenso[j][n][1]);
        }
      }
    }
    else if(valSenso[0][n][0] == ANALOGO && sensores[0][n].compareTo("") != 0)
    {
      for(int j=1; j<5; j++)
      {
        if(sensores[j][n].compareTo("") != 0)
        {
          valSenso[j][n][0] = analogRead(valSenso[j][n][1]);
        }
      }
    }
  }
}

void ArduinoRaspberryPiCOM::actualizarActuadores()
{
  if(Serial.available() > 0)
  {
    String json = Serial.readString();

    for(int n=0; n<5; n++)
    {
      if(valActua[0][n][0] == DIGITAL && actuador[0][n].compareTo("") != 0)
      {
        for(int j=1; j<5; j++)
        {
          if(actuador[j][n].compareTo("") != 0)
          {
            valActua[j][n][0] = leerJSON(json, actuador[j][n]);
            digitalWrite(valActua[j][n][1], valActua[j][n][0]);
          }
        }
      }
      else if(valActua[0][n][0] == PWM && actuador[0][n].compareTo("") != 0)
      {
        for(int j=1; j<5; j++)
        {
          if(actuador[j][n].compareTo("") != 0)
          {
            valActua[j][n][0] = leerJSON(json, actuador[j][n]);
            analogWrite(valActua[j][n][1], valActua[j][n][0]);
          }
        }
      }
    }
  }
}

String ArduinoRaspberryPiCOM::darJSON()
{
  String json = "{\"Sensores\" : {";

  bool acabo = false;
  for(int n=0; n<8 && !acabo; n++)
  {
    if(sensores[0][n].compareTo("") != 0)
    {
      json += "\"" + sensores[0][n] + "\" : {";

      bool sigGrupo = false;
      for(int j=1; j<10 && !sigGrupo; j++)
      {
        if(sensores[j][n].compareTo("") != 0)
        {
          json += "\"" + sensores[j][n] + "\" : " + ((String) valSenso[j][n][0]);
          if(j + 1 < 10)
          {
            if(sensores[j+1][n].compareTo("") != 0)
            {
              json += ",";
            }
          }
        }
        else
        {
          sigGrupo = true;
        }
      }
      json += "}";
      if(n + 1 < 8)
      {
        if(sensores[0][n+1].compareTo("") != 0)
        {
          json += ",";
        }
      }
    }
    else
    {
      acabo = true;
    }
  }

  json += "},\"Actuadores\" : {";

  bool acabo = false;
  for(int n=0; n<5 && !acabo; n++)
  {
    if(actuador[0][n].compareTo("") != 0)
    {
      json += "\"" + actuador[0][n] + "\" : {";

      bool sigGrupo = false;
      for(int j=1; j<10 && !sigGrupo; j++)
      {
        if(actuador[j][n].compareTo("") != 0)
        {
          json += "\"" + actuador[j][n] + "\" : " + ((String) valActua[j][n][0]);
          if(j + 1 < 10)
          {
            if(actuador[j+1][n].compareTo("") != 0)
            {
              json += ",";
            }
          }
        }
        else
        {
          sigGrupo = true;
        }
      }
      json += "}";
      if(n + 1 < 8)
      {
        if(actuador[0][n+1].compareTo("") != 0)
        {
          json += ",";
        }
      }
    }
    else
    {
      acabo = true;
    }
  }

  json += "}}";
  return json;
}

int ArduinoRaspberryPiCOM::leerJSON(String json, String nombreABuscar)
{
  int valor = 0;

  int ini = json.indexOf(nombreABuscar) + nombreABuscar.length() + 4;
  int fin = json.indexOf(",", ini);

  if(fin == -1 || json.indexOf("}", ini) < fin)
  {
    fin = json.indexOf("}", ini);
  }

  String subS = json.substring(ini, fin);
  subS.trim();
  if(subS.equalsIgnoreCase("TRUE") || subS.equalsIgnoreCase("1") || subS.equalsIgnoreCase("HIGH"))
  {
    valor = 1;
  }
  else if(subS.equalsIgnoreCase("FALSE") || subS.equalsIgnoreCase("0") || subS.equalsIgnoreCase("LOW"))
  {
    valor = 0;
  }
  else
  {
      valor = subS.toInt();
  }

  return valor;
}
