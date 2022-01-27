#include <dht.h>
dht DHT;
#define DHT22_PIN 11
float hum;
float hum2;
float temp;
int relay_pin= 10;
int vent_on = 0;
int vent_off = 0;
int vent_on_btn = 2;
int vent_off_btn = 4;
int vent_on_btn_state = 0;
int vent_off_btn_state = 0;
unsigned long vent_on_period = 1000000;
unsigned long vent_off_period = 1000000;
unsigned long time_now_on = 0;
unsigned long time_now_off = 0;
int vent_hum = 0;

void setup() {
  pinMode(relay_pin, OUTPUT);
  pinMode(vent_on_btn, INPUT);
  pinMode(vent_off_btn, INPUT);
  digitalWrite(vent_on_btn, HIGH);
  digitalWrite(vent_off_btn, HIGH);
  //Serial.begin(9600);
}

void loop() { 
  vent_on_btn_state = digitalRead(vent_on_btn);
  if (vent_on_btn_state == LOW) {
    time_now_on = millis();
    vent_on = 1;
    vent_off = 0;
    //Serial.println("VENT ON BUTTON PRESSED");  
  } else {
    if(vent_on == 1) {
      if(millis() >= time_now_on + vent_on_period){
        //time_now_on += vent_on_period;
        vent_on = 0;
        //Serial.println("VENT ON PERIOD EXPIRED");
      }
    } 
  }
  if (vent_on == 1) {
    digitalWrite(relay_pin, LOW);
  }
  vent_off_btn_state = digitalRead(vent_off_btn);
  if (vent_off_btn_state == LOW) {
    time_now_off = millis();
    vent_on = 0;
    vent_off = 1;
    //Serial.println("VENT OFF BUTTON PRESSED");
  } else {
    if(vent_off == 1){
      if(millis() >= time_now_off + vent_off_period){
        vent_off = 0;
        //Serial.println("VENT OFF PERIOD EXPIRED");
      }
    } 
  } 
    
    delay(300);
    int chk = DHT.read22(DHT22_PIN);
    hum = DHT.humidity;
    temp= DHT.temperature;
    /*Serial.print("H:");
    Serial.print(hum);
    Serial.print("%,T:");
    Serial.print(temp);
    Serial.print("C;V_off:");
    Serial.print(vent_off);
    Serial.print(";V_on:");
    Serial.print(vent_on);
    Serial.print(";V_hum:");
    Serial.print(vent_hum);
    Serial.println("");
    digitalWrite(relay_pin, HIGH);
    */
    if(vent_off == 1 && hum > 75){
      //Serial.println("VENT OFF PRESSED! DO NOTHING / TURN OFF EVERYTHING");
      digitalWrite(relay_pin, HIGH);
    }  
    if ( vent_on == 0 && vent_off == 0 && hum >75){
      while (hum >65 && vent_off_btn_state == HIGH) {
        vent_off_btn_state = digitalRead(vent_off_btn);
        int chk = DHT.read22(DHT22_PIN);
        hum = DHT.humidity;
        delay(300);
        digitalWrite(relay_pin, LOW);
        //Serial.println("HUMIDITY RELAY ON!");
        //Serial.println(hum);
        }
     } 
}
