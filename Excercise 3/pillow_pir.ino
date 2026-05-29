// PIR sensor implementation being inspired by this code:
// https://learn.adafruit.com/pir-passive-infrared-proximity-motion-sensor/using-a-pir-w-arduino

// Pin definitions
const int valvePin = 2;
const int inflatePumpPin = 3;
const int deflatePumpPin = 4;
const int pirPin = 10; 

int pirState = LOW;  
int val = 0;
int personSleeps = false;

Button sleepButton(5); 

void setup() {
  // Set pins as outputs
  pinMode(valvePin, OUTPUT);
  pinMode(inflatePumpPin, OUTPUT);
  pinMode(deflatePumpPin, OUTPUT);
  pinMode(pirPin, INPUT);

  // Makes sure everything starts OFF
  digitalWrite(valvePin, LOW);
  digitalWrite(inflatePumpPin, LOW);
  digitalWrite(deflatePumpPin, LOW);
  digitalWrite(pirPin, LOW);

  sleepButton.begin();

  Serial.begin(9600);
}

void loop() {

  if (sleepButton.released()){
    if(personSleeps == false;){       // When pillow volume is acceptable, keep pillow from further inflating
      personSleeps == true;
    } else{                           // If pillow should be further inflated
      personSleeps == false;
    }
  }

val = digitalRead(pirPin);  // read input value
  if (val == HIGH && personSleeps == false) {       // check if the input is HIGH and the person is NOT currently sleeping
    digitalWrite(inflatePumpPin, HIGH);  // turn inflation pump ON
    delay(2000);

    digitalWrite(inflatePumpPin, LOW);    // turn inflation pump OFF again
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
    delay(60000);                           // Keep pillow from further inflating for a time being, give user time to decide if the pillow volume is acceptable
  } else if (val == LOW) {
    digitalWrite(valvePin, HIGH);           // turn on valve
    digitalWrite(deflatePumpPin, HIGH);     // turn on deflation pump
    delay(2000);

    digitalWrite(valvePin, HIGH);           // turn valve off again
    digitalWrite(deflatePumpPin, HIGH);     // turn deflation pump off again
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
      personSleeps = false;          //Makes it so that when a person is detected again in the future, the pillow will inflate without the state having to be manually changed
    }
    delay(60000);        // Keep pillow from further deflating for a time being
  }
  
}