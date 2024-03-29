/*
   Sketch: ESP8266_LED_Control_02C
   Now with added CSS and a single button
   Control an LED from a web browser
   Intended to be run on an ESP8266

   connect to the ESP8266 AP then
   use web broswer to go to 192.168.4.1

*/


#include <ESP8266WiFi.h>
const char WiFiPassword[] = "12345678";
const char AP_NameChar[] = "LEDControl" ;

WiFiServer server(80);

String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'/><meta charset='utf-8'><style>body {font-size:140%;} #main {display: table; margin: auto;  padding: 0 10px 0 10px; } h2,{text-align:center; } .button { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;}</style><title>LED Control</title></head><body><div id='main'><h2>LED Control</h2>";
String html_2 = "";
String html_4 = "</div></body></html>";

String request = "";
int LED_Pin = D1;

void setup()
{
  pinMode(LED_Pin, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D3, OUTPUT);

  boolean conn = WiFi.softAP(AP_NameChar);
  server.begin();

} // void setup()



void loop()
{
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)  {
    return;
  }

  // Read the first line of the request
  request = client.readStringUntil('\r');

  if       ( request.indexOf("LEDON") > 0 )  {
    //digitalWrite(LED_Pin, HIGH);
    digitalWrite(D3, HIGH);
  }
  else if  ( request.indexOf("LEDOFF") > 0 ) {
    //digitalWrite(LED_Pin, LOW);
    digitalWrite(D4, LOW);
  }


  // Get the LED pin status and create the LED status message
  if (digitalRead(D4) == HIGH)//(digitalRead(LED_Pin) == HIGH)
  {
    // the LED is on so the button needs to say turn it off
    html_2 = "<form id='F1' action='LEDOFF'><input class='button' type='submit' value='Turn of the LED' ></form><br>";
  }
  else
  {
    // the LED is off so the button needs to say turn it on
    html_2 = "<form id='F1' action='LEDON'><input class='button' type='submit' value='Turn on the LED' ></form><br>";
  }


  client.flush();

  client.print( header );
  client.print( html_1 );
  client.print( html_2 );
  client.print( html_4);

  delay(5);
  // The client will actually be disconnected when the function returns and 'client' object is detroyed

} // void loop()
