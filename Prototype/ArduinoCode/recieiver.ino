// Ultrasonic Sensor Pins
const int trigPin1 = 7;  // Trigger pin for Ultrasonic Sensor
const int echoPin1 = 8;  // Echo pin for Ultrasonic Sensor
const int vibOutPin1 = 6; // Vibration motor pin

// Vibration control variables
bool stopVibration = false; // Track whether the vibration should stop
bool isAccelerating = false; // Track if acceleration starts (based on distance)
bool isDecelerating = false; // Track if deceleration starts (based on distance)
unsigned long vibrationDuration = 1000; // Duration for vibration in milliseconds
unsigned long vibrationStartTime; // Track when to start the vibration
bool vibrationActive = false; // Check if vibration is currently active

// Silence detection variables
unsigned long silenceStartTime = 0;  // Record silence start time
bool silenceStarted = false;         // Track if silence period has started
unsigned long silenceDurationThreshold = 30000; // Silence threshold of 2 minutes (in milliseconds)

// Acceleration detection flags
bool checkAcceleration = false; // Enable or disable acceleration check
bool vibrationStoppedByUser = false; // Track if the user stopped the vibration

// Sound sensor pin
const int soundPin = A0; 

void setup() {
  Serial.begin(9600); // Initialize serial communication

  // Initialize Ultrasonic Sensor
  pinMode(trigPin1, OUTPUT); // Set trigger pin as output
  pinMode(echoPin1, INPUT); // Set echo pin as input
  pinMode(vibOutPin1, OUTPUT); // Set vibration motor pin as output
}

void loop() {
  long duration, cm;
  int soundValue = analogRead(soundPin); 

  // 打印声音传感器的数值
  Serial.print("Sound value: ");
  Serial.println(soundValue);

  // Trigger the ultrasonic sensor
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  // Read the signal from the sensor
  duration = pulseIn(echoPin1, HIGH);
  cm = microsecondsToCentimeters(duration);

  // Print the distance to the Serial Monitor
  Serial.print("Distance 1: ");
  Serial.print(cm);
  Serial.println(" cm");

  // Control the vibration motor based on the measured distance
  if (cm <= 5) {
    stopVibration = false; // Allow vibration to occur again if distance <= 5 cm
    digitalWrite(vibOutPin1, HIGH); // Activate the vibration motor
  } else {
    digitalWrite(vibOutPin1, LOW); // Deactivate the vibration motor
  }

  // Silence detection logic
  if (soundValue == 20 && !silenceStarted) {
    silenceStartTime = millis(); 
    silenceStarted = true;
    Serial.println("Silence start");
  } else if (soundValue > 20) {
    silenceStarted = false; 
  }

  if (silenceStarted && (millis() - silenceStartTime >= silenceDurationThreshold) && !stopVibration) {
    digitalWrite(vibOutPin1, HIGH);
    vibrationStartTime = millis(); 
    vibrationActive = true;
    silenceStarted = false; 
    Serial.println("Vibration activated after 2 minutes of silence.");
  }

  // Manage vibration duration
  if (vibrationActive && (millis() - vibrationStartTime >= vibrationDuration)) {
    digitalWrite(vibOutPin1, LOW);
    vibrationActive = false;
    Serial.println("Vibration motor deactivated.");
  }

  // Check if acceleration detection is enabled
  if (checkAcceleration && !vibrationStoppedByUser) {
    // Check conditions for acceleration and deceleration based only on distance
    if (!isAccelerating && cm < 1200) {
      isAccelerating = true; // Start acceleration condition based on distance
      Serial.println("Acceleration started based on distance.");
    }

    if (isAccelerating && cm < 40) {
      isDecelerating = true; // Start deceleration condition based on distance
      Serial.println("Deceleration started based on distance.");
    }

    if (isDecelerating && cm < 1200) {
      digitalWrite(vibOutPin1, HIGH); // Activate vibration motor
      vibrationStartTime = millis(); // Store the time when vibration starts
      vibrationActive = true; // Set vibration active flag
      Serial.println("Vibration motor activated.");
    }

    // Manage vibration duration
    if (vibrationActive && (millis() - vibrationStartTime >= vibrationDuration)) {
      digitalWrite(vibOutPin1, LOW); // Deactivate vibration motor
      vibrationActive = false; // Reset vibration active flag
      isAccelerating = false; // Reset acceleration status
      isDecelerating = false; // Reset deceleration status
      Serial.println("Vibration motor deactivated.");
    }
  }

  // Check for serial input to control features
  if (Serial.available() > 0) {
    char inputChar = Serial.read();
    if (inputChar == 'K') {
      stopVibration = true; // Stop the vibration when 'K' is pressed
      vibrationStoppedByUser = true; // Set flag to indicate user has stopped the vibration
      digitalWrite(vibOutPin1, LOW); // Ensure vibration motor is off
      Serial.println("Vibration manually stopped by user.");
    }
    if (inputChar == 'A') {
      checkAcceleration = true; // Enable acceleration detection when 'A' is pressed
      isAccelerating = false;  // Reset acceleration flag
      isDecelerating = false;  // Reset deceleration flag
      vibrationActive = false; // Ensure vibration isn't active yet
      stopVibration = false;   // Allow vibration to occur again
      vibrationStoppedByUser = false; // Reset the user stop flag when acceleration is re-enabled
      Serial.println("Acceleration detection enabled and conditions reset.");
    }
  }

  delay(100); // Short delay before the next loop
}

// Function to convert microseconds to centimeters
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2; // Convert to centimeters
}
