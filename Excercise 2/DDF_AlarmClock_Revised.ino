//LIBRARIES - all libraries can be installed via Arduino Library Manager
#include <LiquidCrystal_I2C.h> //library for LCD display
#include <Wire.h>              // library for I2C connection
#include <RTClib.h>            // library for real time clock 
#include <Button.h>            // library for easy handling of buttons: https://github.com/madleech/Button



LiquidCrystal_I2C lcd(0x27, 18, 2); //declaration of the Display
RTC_DS1307 rtc;                     //declaration of the RTC device

//PINOUT
#define buzzerPin 12


//Alarm Setting Variables
bool isAlarmSet = false;
bool didItRing = false;
bool alarmRings = false;
short unsigned int AlarmHH = 12; //storing the alarm time setting - hours
short unsigned int AlarmMM = 33;  //storing the alarm time setting - minutes
#define howManyRings 3 //constant defining how many beeps the alarm should make per launch

short unsigned int CurrentHH = 0; //storing the current time - hours
short unsigned int CurrentMM = 0; //storing the current time - minutes
bool ifTimeDisplay = true;  //boolean value to decide if to show time, useful for limiting flickering of the screen

//Button Declarations and Control Variables
Button blueButton(13); 
Button whiteButton(2);
Button yellowButton(10);
Button greenButton(11);

bool whiteButtonState = false;
bool blueButtonState = false;
bool yellowButtonState = false;
bool greenButtonState = false;


//Setup function, executed once after reboot
void setup() {
pinMode(buzzerPin, OUTPUT); 
digitalWrite(buzzerPin,LOW);

Serial.begin(9600); //initialisation of serial monitor

//LCD display initialisation
lcd.init();
lcd.backlight();

//RTC initialisation
rtc.begin();
//rtc.adjust(DateTime(2024, 03, 11, 17, 36, 10)); //this sets the "start" time for the clock - need to be executed only once per unit; then it stores the time itself

//Buttons initialisation
blueButton.begin();
whiteButton.begin();
yellowButton.begin();
greenButton.begin();


}

//timeOnScreen function reads the time from RTC and displays it on the LCD display
void timeOnScreen(){

  DateTime now = rtc.now(); //declaring an object for storing the RTC time
  lcd.setCursor(0,0);
  lcd.print("Time: ");
  if(now.hour()<10) lcd.print('0'); //used to maintain nice format on the display
  lcd.print(now.hour());
  CurrentHH = now.hour();
  lcd.print(":");
  if(now.minute()<10) lcd.print('0');
  lcd.print(now.minute());
  CurrentMM = now.minute();
  lcd.print(":");
  if(now.second()<10) lcd.print('0');
  lcd.print(now.second());
  lcd.print("    ");

  /* serial prints for debugging
  Serial.print("Time:");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.println(now.minute());*/
}

//alarmToggle function switches the setting of the alarm On and Off, using the white button
int alarmToggle(){
  
  // Let Alarm ring until it has been turned off
  if(greenButton.released()){
    alarmRings = false;
  }

  //Snooze function which adds 5 minutes to an alarm
  if(alarmRings == true && yellowButton.released()){
    alarmRings = false;
    isAlarmSet = true;

    if(AlarmMM <= 55){
      if(AlarmHH = 23){
        AlarmHH = 0;
      } else{
        AlarmHH++;
      }
    }
    switch (AlarmMM) {
      case 55:
        AlarmMM = 0;
        break;
      case 56:
        AlarmMM = 1;
        break;
      case 57:
        AlarmMM = 2;
        break;
      case 58:
        AlarmMM = 3;
        break;
      case 59:
        AlarmMM = 4;
        break;
      default:
        AlarmMM + 5
        break;
    }
  }

  // Give a countdown until when the alarm is ringing
  if(isAlarmSet == true){
    lcd.setCursor(0, 1);
    lcd.print("Alarm rings in ");

    if(AlarmHH < 10) lcd.print("0");
    if(AlarmHH < now.hour){
      lcd.print(now.hour - AlarmHH)
    } else{
      lcd.print(AlarmHH - now.hour)
    }

    lcd.print(":");

    if(AlarmMM < 10) lcd.print("0");
    if(AlarmMM < now.hour){
      lcd.print(now.hour - AlarmMM)
    } else{
      lcd.print(AlarmMM - now.hour)
    }
    
  }



  if(whiteButton.released()){
    Serial.print("Alarm clock state: ");
    whiteButtonState = !whiteButtonState;
     //Serial.print("WBS: ");
     //Serial.println(whiteButtonState);

  if(whiteButtonState){
     lcd.setCursor(0, 1);
    lcd.print("Alarm is ON           ");
    isAlarmSet = true;
  }else{
    lcd.setCursor(0, 1);
    lcd.print("Alarm is OFF          ");
    isAlarmSet = false;
    didItRing = false;
  }
}

if(isAlarmSet == 1) return 1;
else return 0;
     
}

//menuToggle function switches the clock view into set-the-alarm view  
void menuToggle(){
  
  if(blueButton.released()) blueButtonState = !blueButtonState;
    //Serial.print("RBS: ");
    //Serial.println(blueButtonState); 

  if(blueButtonState){
    ifTimeDisplay = false;
    setAlarm();
    
    lcd.setCursor(0, 0);
    lcd.print("Alarm set: ");
    if(AlarmHH <10) lcd.print("0");
    lcd.print(AlarmHH);
    lcd.print(":");
    if(AlarmMM <10) lcd.print("0");
    lcd.print(AlarmMM);
           
  } 
    if(!blueButtonState) 
    {
      ifTimeDisplay = true;
      return;
    }
  
 }

//setAlarm function operates Yellow and Green Buttons to set the desired alarm time in the set-the-alarm view
int setAlarm(){
  if(blueButtonState){
    if(yellowButton.released()){
      AlarmHH++;
      if(AlarmHH>23) AlarmHH=0;
      return 1;
    }
    if(greenButton.released()){
      AlarmMM++;
      if(AlarmMM>59) AlarmMM=0;
      return 1;
    }
  }else return 0;
}   

//alarmRing function checks the alarm conditions and enables the buzzer 
void alarmRing(){

if(isAlarmSet==true && CurrentHH == AlarmHH && CurrentMM == AlarmMM && didItRing==false){
  alarmRings = true;

  while(alarmRings == true){
            digitalWrite(buzzerPin, HIGH);
            delay(300);
            digitalWrite(buzzerPin, LOW);
            delay(300);
            lcd.setCursor(0, 1);
            lcd.print("Alarm Rings!          ");
            alarmToggle();
      }
      didItRing=true;
      lcd.setCursor(0, 1);
      lcd.print("");
  }
}






//LOOP - main function of our programme

void loop() {

//delay(20);
  
  if(ifTimeDisplay) timeOnScreen(); //displaying the clock
  alarmToggle();                    //checking if the alarm function is on or off (and handling its input)
  menuToggle();                     //checking if the set-the-alarm view is on or off (and handling its input)
  alarmRing();                      //checking if the the alarm should ring (and executing it if yes)

  //Serial info for debugging
  /*Serial.print("ATime:");
  Serial.print(AlarmHH);
  Serial.print(":");
  Serial.println(AlarmMM);


  Serial.print("CTime:");
  Serial.print(CurrentHH);
  Serial.print(":");
  Serial.println(CurrentMM);

  Serial.print("IsAlarmSet: ");
  Serial.println(isAlarmSet);*/
  
 

        
}




