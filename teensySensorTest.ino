/*
 * Project teensySoilTest
 * Description:
 * Author:
 * Date:
 */


int moisture;
unsigned long checkTime;


void setup() {
  pinMode(A2,INPUT);
  Serial.begin(9600);
}

void loop() {
   if ((millis()-checkTime)>1000) {
    moisture = analogRead(A2);
    Serial.printf("moisture = %i\n",moisture);
    checkTime = millis();
  }
}
