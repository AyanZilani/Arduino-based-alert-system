#include <GPRS_Shield_Arduino.h>
#include <sim900.h>

/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ReadAnalogVoltage
*/
// Configure software serial port
SoftwareSerial SIM900(7, 8);

#include <SoftwareSerial.h>

bool resend = true;
bool recall = true;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
  // Make sure that corresponds to the baud rate of your module
  SIM900.begin(19200);
  // Give time to your GSM shield log on to network
  delay(5000);   
  
  /*// Send the SMS
  sendSMS();*/


  /*// Make the phone call
  callSomeone();*/
}




// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.println(voltage);

  
  if (voltage < 2 && resend && recall){
    resend = false;
    Serial.println("Sending SMS ....");
    delay (2000);
    sendSMS();
    Serial.println("SMS Done....");
    delay (2000);

    recall = false;
    Serial.println("Ongoing 1st call ....");
    delay (2000);
    callSomeone();
    Serial.println("1st call done....");
    delay (2000);
    
    Serial.println("Ongoing 2nd call ....");
    delay (2000);
    callSomeone();
    Serial.println("2nd call done....");
    delay (2000);
    
    Serial.println("Ongoing 3rd call ....");
    delay (2000);
    callSomeone();
    Serial.println("3rd call done....");
    delay (2000);
    
  }
  if(voltage >=2 ){
    resend = true;
    recall = true;
  }
  
}



void sendSMS() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT + CMGS = \"+601137332108\""); 
  delay(100);
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Message example from Arduino Uno."); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000); 
}

void callSomeone() {
  // REPLACE THE X's WITH THE NUMER YOU WANT TO DIAL
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("ATD + +601137332108;");
  delay(100);
  SIM900.println();
  
 // In this example, the call only last 6 seconds
 // You can edit the phone call duration in the delay time
  delay(20000);
  // AT command to hang up
  SIM900.println("ATH"); // hang up
}
