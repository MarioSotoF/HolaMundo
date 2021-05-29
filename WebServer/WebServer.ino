/*************************************************************************************************
  ESP32 Web Server
  Ejemplo de creación de Web server 
  Basándose en los ejemplos de: 
  https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
  https://electropeak.com/learn
**************************************************************************************************/

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "MARIO SOTO_EXT";  // Enter your SSID here
const char* password = "eunice21";  //Enter your Password here

uint8_t parqueos[4];
uint8_t n_Parqueos = 0;
WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

uint8_t LED1pin = 2;
bool LED1status = LOW;


void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  pinMode(LED1pin, OUTPUT);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_OnConnect); // 192.168.1.13
  server.on("/leer", handle_Data); // 

  
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}

void loop() {
  server.handleClient();          
  if (Serial2.available())        
    {   
      digitalWrite(2, 1);         
        for (int i = 0; i<=3; i++)
        {
          parqueos[i] = Serial2.read(); 
        }
        n_Parqueos = (((4 - parqueos[0])- parqueos[1])- parqueos[2])- parqueos[3]; 

    }
    digitalWrite(2, 0);         

}

void handle_OnConnect() {
  server.send(200, "text/html", SendHTML());
}

void handle_Data() {                          
   String dato_json = "{\"parqueo1\":";
          dato_json += parqueos[0];
          dato_json += ",";
          dato_json += "\"parqueo2\":";
          dato_json += parqueos[1];
          dato_json += ",";
          dato_json += "\"parqueo3\":";
          dato_json += parqueos[2];
          dato_json += ",";
          dato_json += "\"parqueo4\":";
          dato_json += parqueos[3];
          dato_json += ",";
          dato_json += "\"lugares\":";
          dato_json += n_Parqueos;
          dato_json += "}";
  server.send(200, "application/json", dato_json);
}


String SendHTML(void) {
  String ptr = "<!DOCTYPE html>\n";
  ptr = "<html>\n";
  ptr += "<head>\n";
  ptr += "<style>\n";
  ptr += "body {font-family: Helvetica, sans-serif;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>Zona de Parqueos</h1>\n";
  ptr += "<h3>Mario Soto 18351</h3>\n";
  ptr += "<canvas id=\"Cantidad\" width=\"200\" height=\"40\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"Parqueo 1\" width=\"200\" height=\"100\" style=\"border:2px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"Parqueo 2\" width=\"200\" height=\"100\" style=\"border:2px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"Parqueo 3\" width=\"200\" height=\"100\" style=\"border:2px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"Parqueo 4\" width=\"200\" height=\"100\" style=\"border:2px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<script>\n";
  ptr += "function Sensor(n_parqueo, ){\n";
  ptr += "var canvas = document.getElementById(n_parqueo);\n";
  ptr += "var ctx = canvas.getContext(\"2d\");\n";
  ptr += "if (sense == 0){\n";
  ptr += "ctx.fillStyle = \"#33ffa5\";\n";
  ptr += "};\n";
  ptr += "if (sense == 1){\n";
  ptr += "ctx.fillStyle = \"#ff4c33\";\n";
  ptr += "};\n";
  ptr += "ctx.fillRect(0,0,200,100);\n";
  ptr += "ctx.fillStyle = \"#000000\";\n";
  ptr += "ctx.font = \"30px Arial\";\n";
  ptr += "ctx.fillText(n_parqueo, 28, 60);\n";
  ptr += "};\n";
  ptr += "function Parqueos(cantidad){\n";
  ptr += "var canvas = document.getElementById(\"Cantidad\");\n";
  ptr += "var ctx = canvas.getContext(\"2d\");\n";
  ptr += "ctx.fillStyle = \"#FFFFFF\";\n";
  ptr += "ctx.fillRect(0,0,825,40);\n";
  ptr += "ctx.fillStyle = \"#000000\";\n";
  ptr += "ctx.font = \"20px Arial\";\n";
  ptr += "ctx.fillText(\"Cantidad de parqueos disponibles: \" + cantidad.toString(), 0,30);\n";
  ptr += "};\n";
  ptr += "Parqueos(4);\n";
  ptr += "Sensor(\"Parqueo 1\", 0);\n";
  ptr += "Sensor(\"Parqueo 2\", 0);\n";
  ptr += "Sensor(\"Parqueo 3\", 0);\n";
  ptr += "Sensor(\"Parqueo 4\", 0);\n";
  ptr += "var sendHttpRequest = function(){\n";
  ptr += "var xhr = new XMLHttpRequest();\n";
  ptr += "xhr.open(\"GET\", \"http://192.168.1.173/leer\");\n";
  ptr += "xhr.responseType = \'json\';\n";
  //ptr += "var receive = xhr.responseText;\n";
  ptr += "xhr.onload = function() {\n";
  ptr += "  console.log(xhr.response);\n";
  ptr += "xhr.send();\n"; 
  ptr += "return xhr.response;\n";
  ptr += "};\n"; 
  ptr += "setInterval(function(){\n";
  ptr += "sendHttpRequest();\n";
  ptr += "},1);\n";
  ptr += "</script>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}


String data_json(void){
  String dato_json = "{\"parqueo1\":";
          dato_json += parqueos[0];
          dato_json += ",";
          dato_json += "\"parqueo2\":";
          dato_json += parqueos[1];
          dato_json += ",";
          dato_json += "\"parqueo3\":";
          dato_json += parqueos[2];
          dato_json += ",";
          dato_json += "\"parqueo4\":";
          dato_json += parqueos[3];
          dato_json += ",";
          dato_json += "\"lugares\":";
          dato_json += n_Parqueos;
          dato_json += "}";
  return dato_json;
}
