#include <SoftwareSerial.h> 

 #define SCALE_PAUSE_PULSE 4
 #define SCALE 60*125

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3
int motorPin = 4;      // select the pin for the LED
int dataFromBt=70;
int i2 = 0;
String Data = "";
//char char_arr[3];
int frequency = 60;


SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup() { 
  pinMode(motorPin,OUTPUT);
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$");  // Print three times individually
  bluetooth.print("$");
  bluetooth.print("$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
   bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
  }

void loop() {
  // put your main code here, to run repeatedly:


    if(bluetooth.available()>0){  
         frequency = (int)bluetooth.read();
    }
     digitalWrite(motorPin, HIGH);
     delay((1./frequency)*SCALE);
     digitalWrite(motorPin, LOW); 
     delay((1./frequency)*SCALE);
     digitalWrite(motorPin, HIGH);
     delay((1./frequency)*SCALE);
     digitalWrite(motorPin, LOW); 
     delay((1./frequency)*SCALE*SCALE_PAUSE_PULSE);

}
