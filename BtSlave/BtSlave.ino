
#include <SoftwareSerial.h>  

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3
int ledPin = 12;      // select the pin for the LED
char dataFromBt ='0';


SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup() { 
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

    if(bluetooth.available()){

      //Serial.print((char)bluetooth.read()); //beide Befhle nicht möglich. Wenn serial.pint kein dataFromBt
      dataFromBt=((char)bluetooth.read());
       
      
     if(dataFromBt==126){
       digitalWrite(ledPin, HIGH); 
      }
     if(dataFromBt == 48){
       digitalWrite(ledPin, LOW); 
      }
      
    }

  

    if(Serial.available())  // If stuff was typed in the serial monitor
  {
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.print((char)Serial.read());
  }

}
