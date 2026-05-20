## Observation and documentation for excercise 2, Digital Design & Fabrication

## Sub-circuit 1

The first sub-circuit can be seen in image 1. After changing the buzzer pin the test code from 4 to 12 and adding a one second delay after turning the buzzer pin off to the code the buzzer did ring. Adding a delay here after turning the buzzer off is important as otherwise it would just instantly turn on again, giving you the illusion that it never turned off.

<img src="sub-circuit-1.jpg" width="300" />

**Image 1**

## Sub-circuit 2 & 3

The reading of the address for the LED-screen here showed 0x27 and for the RTC module it reported the addresses 0x50 and 0x68. The RTClib library had to be installed through the library manager inside the Arduino IDE as the provided library .zip file was missing something, which resulted in error occuring trying to run the code.

<img src="sub-circuit-2.jpg" width="300" />

**Image 2**


As can be seen in image 3 both the LED screen module and the RTC module are sharing the SCL, SDA, power, and ground pin of the Arduino Uno board through the breadboard as the Arduino only has one SCL, SDA, and power pin that can be ultilized for these modules.

<img src="sub-circuit-3.jpg" width="300" />

**Image 3**

In row 40 of the breadboard all of the SCL wires can be seen with purple being the wire that connects to the SCL pin of the Arduino. Rows 35 (SDA) and 30 (power) follow a similar approach with the brown cable in row 35 and the left-most white cable in row 30 connecting to the Arduino. Row 25 (ground) is a bit special in regards that the left-most cable is not directly connected to the Arduino but rather the buzzer above in row 50. The reasons for it will be explained in the next paragraph.

## Sub-circuit 4

As all buttons need to be connected to ground but the Arduino Uno not having enough dedicated ground pins, all buttons were connected with wires that led to Row 25 and from row 25 one single wire (the left-most wire) then to row 50 above to the same row the buzzer was using earlier to ground itself as the left red wire was connected to the Arduino's ground pin. To connect the buttons the Arduino (other than grounding them) the suggested pins for each button was then looked up in the provided AlarmClock.ino file, properly connected, and able to get a reaction out of all the buttons.

## Build an alarm clock

After everything was properly wired and the RTC module was once properly initialized with rtc.adjust(), the provided code ran without a problem and it was possible to set an alarm and hear it too. This can be seen in the demo video.

[Demo video of working alarm clock](https://youtu.be/Epw30OeKFN8) **<-- Link redirects directly to YouTube**

To further enhance the alarm clock three extra functions were added and will be named increased difficulty to implement.

## Alarm keeps ringing until turned off

In the provided file the alarm would automatically turn off after a prior specified number of rings has been reached. However, this cannot ensure that the user also woke up, is awake, and won't slumber off again. To fix this, the for-loop in the alarmRing() function has been changed to a while-loop which will be looped through until the user will press the green button.

## Countdown to the next alarm

Once the alarm has been activated, users would have to switch inside the alarm menu again to see when the alarm is ringing. With this function that won't be necessary anymore as the remaining time until the alarm rings will be shown right beneath the current time. For this the time of the alarm will be subtracted from the current time and then be displayed.

## Snooze function

To give users this "five more minutes" feeling, a snooze function has been implemented. It turns the current alarm off and turns a new alarm on for five minutes in the future. Here switch-cases have been used to ensure proper minute overflow from such minutes as 56 into 01 and not 61.

## Other functions

These three functions, though simple, ensure not only that the user of the alarm clock won't be overwhelmed and/or confused when interacting with the alarm clock but also proper maintainance of the code. Other functions, which have been thought about but not realized due to time constraints and feasibility, have been for instance the capability to set multiple alarms with multiple different alarm tones, possibly even audio files from the internet.

## Alarm Clock code and changes

The Arduino code for the alarm clock can be found [here](DDF_AlarmClock_Revised.ino) and the lines of code for the above mentioned changes are the following:

**Alarm keeps ringing**: LoC 92 - 95 and 229 - 240

**Countdown until next alarm**: LoC 132 - 152

**Snooze function**: LoC 98 - 127