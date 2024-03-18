#include<string.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(5, 4, 3, 2, A4, A5);

String ssid     = "Simulator Wifi";  
String password = ""; 
String host     = "api.thingspeak.com"; 
const int httpPort   = 80;
String uri     = "/channels/1212200/fields/1.json?api_key=C1L2SHVVMW3W6K24&results=2";

char str[70];
String gpsString;

char *test="$GPGGA";

String latitude="No Range      ";
String longitude="No Range     ";

int temp=0,i;
boolean gps_status=0;

int setupESP8266(void) {
  Serial.begin(115200);   
  Serial.println("AT");   
  delay(10);        
  if (!Serial.find("OK")) return 1;
    
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(10);        
  if (!Serial.find("OK")) return 2;
  
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(50);        
  if (!Serial.find("OK")) return 3;
  
  return 0;
}

void anydata(void) {
  
  
  String httpPacket = "GET " + uri + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  int length = httpPacket.length();
  https://api.thingspeak.com/channels/1104800/fields/1.json?api_key=CX5ZHR91RBPV0RSW&results=2";
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(10); 
  Serial.print(httpPacket);
  delay(10); 
  String ch;
  ch = Serial.readString();
  Serial.println(ch);
  
  for(int i=369;i<453;i++)
  {
    gpsString += ch[i];
  }
  
  Serial.println(gpsString);
  
  gps_status=0;
   int x=0;
   while(gps_status==0)
   {
    int str_lenth=81;
    latitude="";
    longitude="";
    int comma=0;
     
    while(x<81)
    {
      if(gpsString[x]==','){
      comma++;
      
      }
      if(comma==2)        
      latitude+=gpsString[x+1];     
      else if(comma==4)        
      longitude+=gpsString[x+1];
      
      x++;
    }
    int l1=latitude.length();
    latitude[l1-1]=' ';
    l1=longitude.length();
    longitude[l1-1]=' ';
    
    lcd.clear();
    lcd.print("Lat:"); 
    lcd.print(latitude);
    lcd.setCursor(0,1);
    lcd.print("Long:");
    lcd.print(longitude);
   
    Serial.print("Lat:  ");
    Serial.print(latitude);
    Serial.print("\tLong:  ");
    Serial.println(longitude); 
    
    
    i=0;x=0;
    str_lenth=0;
    delay(2000);
   }
  if (!Serial.find("SEND OK\r\n")) return;
  
  
}

void setup() {
  
  
  lcd.begin(16,2);
  Serial.begin(9600);
  
  lcd.print("Baggage Tracking");
  lcd.setCursor(0,1);
  lcd.print("    System      ");
  delay(4000);
  lcd.clear();
  delay(2000);
  setupESP8266();
  anydata();

               
}

void loop() {
  
 anydata();

}
