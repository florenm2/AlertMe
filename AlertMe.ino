
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); // RX, TX pins
const int tempPin = 0;

void setup() {

pinMode(13, OUTPUT); // pin 13 is digital out (LED)
mySerial.begin(4800); // Serial connection, baud rate 4800

}
 
void loop(){
float voltage, deg;

voltage = analogRead(tempPin) * 0.004882814;

deg = ((voltage - 0.5) * 180.0) + 32.0; //converts voltage to degrees in fahrenheit
 
if (deg < 50 ){ // if the temperature drops below 50 degrees fahrenheit
digitalWrite(13, HIGH); // Turn LED on
mySerial.println("AT"); // Send AT command to wake up cell phone

//delays let the phone complete each step before moving on
delay(1000);
mySerial.println("AT+CMGF=1"); // SMS mode
delay(1000); 
mySerial.println("AT+CMGW=\"+16302906004\""); // for now, writes to my cell phone number
delay(1000);

// write the warning contents of the text to be sent
mySerial.print("WARNING: The temperatute in the lake house is below 50 degrees. There may be an issue.");
delay(1500);
mySerial.write(byte(26)); // end of message
delay(1500);
mySerial.println("AT+CMSS=1"); // Sends message at index of 1


delay(1500);
digitalWrite(13, HIGH); // Turn LED on.
delay(10000);
mySerial.println("AT+CMGD=1"); // Deletes message at index of 1
digitalWrite(13, LOW); // Turn LED off.
delay(250);
}

}
