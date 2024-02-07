#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
const char* ssid = "Kirill";
const char* password = "00000000";
const int ledPin = D3;
// IPAddress ip(192,168,1,17);  //статический IP
// IPAddress gateway(192,168,1,1);
// IPAddress subnet(255,255,255,0);

void handleRootPath(){
    String html ="<html><head><style>";
    html +="body{background-color: #9dc8e7;} button{padding: 10px 20px; margin: 5px; border: none; border-radius: 5px; cursor: pointer;}";
    html +="#onBtn { background-color: #4a90e2; color: white; }" ;
    html +="#offBtn { background-color: #f2d600; color: white; }";
    html +="</style></head><body>";
    html +="<h1> Zagolovok)0)) </h1>";
    html +="<p><a href=\"/on\"><button id=\"onBtn\">Turn ON</button></a></p>";
    html +="</br>";
    html +="<p><a href=\"/off\"><button id=\"offBtn\">Turn OFF</button></a></p>";
    html +="</body></html>";
    String HTML_MAIN ="<html><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><style>body{background-color: #9dc8e7;}button{padding: 10px 20px; margin: 5px; border: none; border-radius: 5px; cursor: pointer;}#onBtn { background-color: #4a90e2; color: white; }#offBtn { background-color: #f2d600; color: white; }</style></head><body><h1> Хардвере стартрап </h1><h1> Курування тягі </h1><p><a href=\"/on\"><button id=\"onBtn\">Саня включи тягу, ЗАЇБАВ В НАУШНИКАХ З ШУМОДАВОМ СИДІТЬ</button></a></p></br><p><a href=\"/off\"><button id=\"offBtn\">Саня вирубай тягу</button></a></p></body></html>";


    server.send(200,"text/html",html);
}

void handleON(){
  digitalWrite(ledPin,1);
  server.sendHeader("Location","/");
  server.send(302, "text/plain", "Redirecting to root.....");
}
void handleOFF(){
  digitalWrite(ledPin,0);
  server.sendHeader("Location","/");
  server.send(302, "text/plain", "Redirecting to root.....");
}



void setup() {
  Serial.begin(9600);
  pinMode(D3,OUTPUT);

  WiFi.mode(WIFI_STA); // AP - access point / STA-station mode
  WiFi.begin(ssid,password);
  // WiFi.config(ip, gateway, subnet);


  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());

  server.on("/",HTTP_GET,handleRootPath);
  server.on("/on",HTTP_GET,handleON);
  server.on("/off",HTTP_GET,handleOFF);
  server.begin();
  Serial.println("Server is ready");
}

void loop() {
  server.handleClient();
}