
#include <SoftwareSerial.h>  

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3
int ledPin = 12;      // select the pin for the LED
char dataFromBt ='0';


SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup() {
 //Slave code
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("SM,0");
  delay(100);
  bluetooth.println("---");
  //bluetooth.begin(9600);
  pinMode(ledPin, OUTPUT);
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
