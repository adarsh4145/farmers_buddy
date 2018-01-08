#include <dht.h>
#include <SoftwareSerial.h>
#include <string.h>
SoftwareSerial gprsSerial(7, 8);

int di=1;
char mn[]="8824510148";
char l[]="uit-audi-kota";

int DHT11_PIN = 4;
int soil_sensor_pin = A0;
int rainSensePin = A1;
int relay_pin = 2;
int response;
int ledPin=12;
 
dht DHT;
int temperature,air_humidity,soil_moisture,rain;

void setup() {
  //Serial.begin(9600);
  pinMode(DHT11_PIN, INPUT);
  pinMode(soil_sensor_pin, INPUT);
  pinMode(rainSensePin, INPUT);
  pinMode(relay_pin, OUTPUT);
  digitalWrite(relay_pin,HIGH);
  delay(1000);
  gprsSerial.begin(19200);
  Serial.begin(19200);
  Serial.println("Config SIM900...");
  delay(6000);
  Serial.println("Done!...");
  gprsSerial.flush();
  Serial.flush();
  // attach or detach from GPRS service 
  gprsSerial.println("AT+CGATT?");
  delay(2000);
  toSerial();
  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(2000);
  toSerial();
  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"APN\",\"rcomnet\"");
  delay(2000);
  toSerial();
  // bearer settings
  gprsSerial.println("AT+SAPBR=1,1");
  delay(2000);
  toSerial();
}

void loop() {
  readdata();
  //digitalWrite(relay_pin,LOW);
  char last[123];
  gprsSerial.println("AT+HTTPINIT");
  delay(2000); 
  toSerial();
  sprintf(last,"AT+HTTPPARA=\"URL\",\"http://rtuproject.co.nf/write_data.php?di=%d&mn=%s&l=%s&t=%d&ah=%d&sm=%d&r=%d\"",di,mn,l,temperature,air_humidity,soil_moisture,rain);
  
  gprsSerial.println(last);
  delay(2000);
  toSerial();
   
  // set http action type 0 = GET, 1 = POST, 2 = HEAD
  gprsSerial.println("AT+HTTPACTION=0");
  delay(2000);
  toSerial();
  // read server response
  gprsSerial.println("AT+HTTPREAD"); 
  delay(2000);
  toSerial();
  gprsSerial.println("");
  gprsSerial.println("AT+HTTPTERM");
  toSerial();
  delay(300);
  gprsSerial.println("");
   
  //Serial.println(response);
  delay (1000);
  int i,c=15*4*5;
  String o="0";
  for(i=0;i<c;i++){
    gprsSerial.println("AT+HTTPINIT");
    delay(2000); 
    toSerial();
    // set http param value
    
    char lastx[100];
    sprintf(lastx,"AT+HTTPPARA=\"URL\",\"http://rtuproject.co.nf/app_response/%d.txt\"",di);
    gprsSerial.println(lastx);
    delay(1000);
    toSerial();
   
    // set http action type 0 = GET, 1 = POST, 2 = HEAD
    gprsSerial.println("AT+HTTPACTION=0");
    delay(2000);
    toSerial();
   
    // read server response
    gprsSerial.println("AT+HTTPREAD"); 
    delay(1000);
    toSerial();
    gprsSerial.println("AT+HTTPREAD");
    delay(500);
    int z;
    while(gprsSerial.available()!=0){
      Serial.write(gprsSerial.read());
      z=gprsSerial.read();
      delay(500);
      }
    Serial.println(".......");
    Serial.println(z);
    if(z!=-1){
    do{
      digitalWrite(relay_pin,LOW);
      Serial.println("relay is on");
      
      gprsSerial.println(lastx);
      delay(1000);
      toSerial();
   
      // set http action type 0 = GET, 1 = POST, 2 = HEAD
      gprsSerial.println("AT+HTTPACTION=0");
      delay(2000);
      toSerial();
      gprsSerial.println("AT+HTTPREAD");
      delay(500);
      while(gprsSerial.available()!=0){
        Serial.write(gprsSerial.read());
        z=gprsSerial.read();
        delay(500);
        }
      Serial.println(".......");
      Serial.println(z);
      }while(z!=-1);
    digitalWrite(relay_pin,HIGH);
    Serial.println("reloay is off now");
    }
    //Serial.println("app response: ");
   
    gprsSerial.println("");
    gprsSerial.println("AT+HTTPTERM");
    toSerial();
    delay(500);
    gprsSerial.println("");
    }
  //delay(1000*60*2);
}

void readdata(){
  //getting temperature and air humidity data
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  temperature=DHT.temperature;
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  air_humidity=DHT.humidity;
  delay(500);
  
  //getting soil moisture data
  soil_moisture= analogRead(soil_sensor_pin);
  soil_moisture= map(soil_moisture,0,1024,0,100);
  soil_moisture= 100-soil_moisture;
  Serial.print("Soil Moisture: ");
  Serial.print(soil_moisture);
  Serial.println(" \%");
  delay(500);

  //rain snsor data
  rain = analogRead(rainSensePin);
  rain = map(rain,0,1024,0,100);
  rain = 100-rain;
  Serial.print("rain data: ");
  Serial.println(rain); 
  delay(500);
}

void toSerial()
{
  while(gprsSerial.available()!=0){
    Serial.write(gprsSerial.read());
    delay(50);
  }
}

