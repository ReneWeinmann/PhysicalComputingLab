#include <SoftwareSerial.h>  

  int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
  int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3
char State=126;
char State_End=48;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);  // Begin the serial monitor at 9600bps


  
  bluetooth.begin(115200);  // Start bluetooth serial at 
  Serial.print("$$$");
  delay(100);
  Serial.println("SM,1");  delay(100);
  Serial.println("C,00067663A052");
  delay(100);
  Serial.println("---");
  //bluetooth.begin(9600);  // Start bluetooth serial at 9600
  


}

void loop() {
if(bluetooth.available())  // If the bluetooth sent any characters
  {
    // Send any characters the bluetooth prints to the serial monitor
    Serial.print((char)bluetooth.read());  
    
  }
  delay(500);
    bluetooth.print(State);
    delay(500);
    bluetooth.print(State_End);
  
  if(Serial.available())  // If stuff was typed in the serial monitor
  {
    
    // Send any characters the Serial monitor prints to the bluetooth
   // bluetooth.print(126);
   // delay(500);
  }

}
