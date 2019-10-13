//Libraries
#include <DHT.h>


//Constants
#define tempL 20
#define tempH 28
#define humL 20
#define humH 50
#define DHTPIN 2     
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);

//variables
int activ = 0; //Stores activity status 
float temp; //Stores temperature value
float hum;  //Stores humidity value

void setup() {
    Serial.begin(9600);
    dht.begin();
    pinMode(3, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
 //Variable Read
 temp= dht.readTemperature();
 hum = dht.readHumidity();

 //Active Switch
 if (digitalRead(3) == HIGH and activ == 0) {
    activ = 1;
    Serial.println("Bright System Activated");
    delay(6000);  //delay stops the activity switch being flipped multiple times from one motion
 }
 else if (digitalRead(3) == HIGH and activ == 1) {
    activ = 0;
    Serial.println("Bright System Deactivated");
    delay(20000); //see note above
 }

 //Light Control
 if (activ == 1) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Lights turned on");
 }
 else {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Lights turned off");
 }

//Temperature Control
 if (activ == 1 and temp > tempH) {
    Serial.println("Temperature high, turning on airconditioning.");
 }
 else if (activ == 1 and temp < tempL) {
    Serial.println("Temperature low, turning on heating.");
 }
 else if (activ == 0) {
    Serial.println("Temperature control turned off");
 }

//Humidity control 
 if (activ == 1 and hum > humH) {
    Serial.println("Humidity high, turning on dehumidifier");
 }
 else if (activ == 1 and hum < humL) {
    Serial.println("Humidity low, turning on humidifier");
 }
 else if (activ == 0) {
    Serial.println("Humidity control turned off");
 }
 
delay(1000);  
}
