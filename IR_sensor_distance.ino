int pd = 8; //Photodiode to digital pin 2
int buzz = 13; //piezo buzzer to digital pin 13  
int senRead = A0; //Readings from sensor to analog pin 0  
int limit = 66; //Threshold range of an obstacle  
int sensorLow = 1023;
int sensorHigh = 0;
int TX_PIN = 6;
int RX_PIN = 7;
int duration;
int distance;

void setup() {
  pinMode(TX_PIN, OUTPUT);
  pinMode(RX_PIN, INPUT);
  pinMode(pd, OUTPUT);
  pinMode(buzz, OUTPUT);
  digitalWrite(pd, HIGH); //supply 5 volts to photodiode  
  digitalWrite(buzz, LOW); //set the buzzer in off mode (initial condition)  
  Serial.begin(9600); //setting serial monitor at a default baund rate of 9600  
}
void loop() {
  int val = analogRead(senRead); //variable to store values from the photodiode  
  Serial.println(val); // prints the values from the sensor in serial monitor  
  //Haseeb's Code
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TX_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TX_PIN, LOW);

  duration = pulseIn(RX_PIN, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance:");
  Serial.println(distance);

  if (distance <= limit) //If obstacle is nearer than the Threshold range  
  {
    Serial.println("Object detected");
    //beep(val);
    delay(1000);
  } else if (distance > limit) //If obstacle is not in Threshold range  
  {

    Serial.println("No objects in sight");
    delay(1000);
  }

}

void beep(int sensorValue) {
  int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 4000);
  tone(buzz, pitch, 1000);
  delay(1000);
}
