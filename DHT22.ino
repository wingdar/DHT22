
#include <ESP8266WiFi.h>
#include <DHT.h>  
#define DHTPIN 2                    
#define DHTTYPE DHT22           
WiFiServer server(80);
DHT dht(DHTPIN, DHTTYPE);

////////////////////////////////////////////////////////////////////////////////////////
const char *ssid1 = "TD_WIFI";             //"TDIRT";如果要改成 AP 模式的話
const char *password1 = "16584326";
const char *ssid2 = "TD_WIFI-7";           //
const char *password2 = "16584326";
const char *ssid3 = "TD_Mobile";           //
const char *password3 = "66258188";
////////////////////////////////////////////////////////////////////////////////////////

double Fahrenheit(double celsius) {
return ((double)(9 / 5) * celsius) + 32;
}

double Kelvin(double celsius) {
return celsius + 273.15;
}

void setup() {
Serial.begin(115200);
delay(10);
Serial.println();

// Connect to WiFi network
WiFi.mode(WIFI_STA);
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid1);

WiFi.begin(ssid3, password3);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

// Start the server
server.begin();
Serial.println("Server started");

// Print the IP address
Serial.println(WiFi.localIP());

}

void loop() {
float humi = dht.readHumidity();       
float temp = dht.readTemperature(); 

Serial.print("temperature:");
Serial.print(temp);
Serial.print(" & humidity:");
Serial.print(humi);
Serial.println();

//delay(1000);

WiFiClient client = server.available();
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");  
//client.println("Refresh: 10");  
client.println();

client.println("<!DOCTYPE html>");
client.println("<head>\n<meta charset='UTF-8'>");
client.println("<title>ESP8266 Temperature & Humidity DHT22 Sensor</title>");
client.println("</head>\n<body>");
client.println("<H2>ESP8266 & DHT22 Sensor</H2>");
client.println("<H3>Fix by DAR !!!</H3>");
client.println("<pre>");
client.print("濕度 Humidity (%)      : ");
client.println(humi, 2);
client.print("溫度 Temperature (°C)  : ");
client.println(temp, 2);

//client.print("Temperature (°F)  : ");
//client.println(Fahrenheit(temp), 2);
//client.print("Temperature (°K)  : ");
//client.println(Kelvin(temp), 2);
client.println("</pre>");
client.print("</body>\n</html>");
}
