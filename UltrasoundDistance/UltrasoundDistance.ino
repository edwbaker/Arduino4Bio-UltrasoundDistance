#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
#define LEDPin 13 // Onboard LED

int maximumRange = 20; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, count, time; // Duration used to calculate distance
float distance, cumulative;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
  count = 0;
  time = 0;
}

void loop() {
  /* The following trigPin/echoPin cycle is used to determine the
     distance of the nearest object by bouncing soundwaves off of it. */ 

  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
 
  delay(1000);
 
  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration/58.2;
 
  if (distance >= maximumRange || distance <= minimumRange){
  /* Send a negative number to computer and Turn LED ON 
     to indicate "out of range" */
  Serial.println("-1");
  digitalWrite(LEDPin, HIGH); 
  }
  else {
  /* Send the distance to the computer using Serial protocol, and
     turn LED OFF to indicate successful reading. */
  cumulative += distance;
  count++;
 }
 
  if (millis() > time + 300000) {
    distance = cumulative / (float)count;
    Serial.println(distance);
    digitalWrite(LEDPin, LOW);
    cumulative = 0.0;
    count = 0;
    time = millis();
  } 
 
 //Delay 50ms before next reading.
 delay(50);
}
