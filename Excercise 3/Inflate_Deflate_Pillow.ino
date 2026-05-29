// Pin definitions
const int valvePin = 2;
const int inflatePumpPin = 3;
const int deflatePumpPin = 4;

void setup() {
  // Set pins as outputs
  pinMode(valvePin, OUTPUT);
  pinMode(inflatePumpPin, OUTPUT);
  pinMode(deflatePumpPin, OUTPUT);

  // Make sure everything starts OFF
  digitalWrite(valvePin, LOW);
  digitalWrite(inflatePumpPin, LOW);
  digitalWrite(deflatePumpPin, LOW);
}

void loop() {

  // =========================
  // INFLATE
  // =========================

  // Set valve for inflate direction
  digitalWrite(valvePin, LOW);

  // Turn on inflate pump
  digitalWrite(inflatePumpPin, HIGH);

  // Make sure deflate pump is off
  digitalWrite(deflatePumpPin, LOW);

  // Inflate for 2 seconds
  delay(2000);

  // Stop inflate pump
  digitalWrite(inflatePumpPin, LOW);

  // Wait 2 seconds
  delay(2000);


  // =========================
  // DEFLATE
  // =========================

  // Set valve for deflate direction
  digitalWrite(valvePin, HIGH);

  // Turn on deflate pump
  digitalWrite(deflatePumpPin, HIGH);

  // Make sure inflate pump is off
  digitalWrite(inflatePumpPin, LOW);

  // Deflate for 2 seconds
  delay(2000);

  // Stop deflate pump
  digitalWrite(deflatePumpPin, LOW);

  // Turn off valve
  digitalWrite(valvePin, LOW);

  // Wait 2 seconds before repeating
  delay(2000);
}