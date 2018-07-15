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
double avg_visibility = 850;  // Arbitrarily chosen value

void setup() {
  pinMode(TX_PIN, OUTPUT);
  pinMode(RX_PIN, INPUT);
  pinMode(pd, OUTPUT);
  pinMode(buzz, OUTPUT);
  digitalWrite(pd, HIGH); //supply 5 volts to photodiode  
  digitalWrite(buzz, LOW); //set the buzzer in off mode (initial condition)  
  Serial.begin(9600); //setting serial monitor at a default baund rate of 9600

  // determine basic lighting value that makes use of IR sensor appropriate
  int samples = 200;
  for (int i =0; i < samples; i++) {
	avg_visibility=avg_visibility+analogRead(senRead);
  }
  avg_visibility=avg_visibility/samples;

}
void loop() {
  int visibility = analogRead(senRead); //variable to store values from the photodiode
  Serial.println(visibility); // prints the values from the sensor in serial monitor
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

	/* Pseudo code*/
	// Case1: Check if IR values are within suitable range to make decision
	if(avg_visibility - 50 < visibility < avg_visibility + 50) {
		// use visibility value in feedback decision
		// a) compare visibility to ultrasound distance
		//		and find a correlation in values
		// b) Decide whether one or the other is erroneous
		//		and neglect using that param to control sound
		//
		//  eg) beep(distance*(visibility/avg_visibility));
	}

	// Case2: Use ultrasound distance only
	//      eg) beep(distance);

	// remove delays
    delay(10);
  }
  else if (distance > limit) //If obstacle is not in Threshold range
  {
    Serial.println("No objects in sight");
    delay(10);
  }

}

// Make the volume of sound proportional to distance (not light intensity)
void beep(int sensorValue) {
  int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 4000);
  tone(buzz, pitch, 1000);
  delay(1000);
}
