const byte interruptPin = 2;
const byte temp_on = 7;
int temp_count;

void setup() {
  Serial.begin(9600);
  pinMode(temp_on, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), tempcount, RISING );
}

void loop() {
  digitalWrite(temp_on,HIGH);
  delay(104);
  digitalWrite(temp_on,LOW);
  //temp_count=((((float)temp_count/4096)*256)-50);Umrechnung in Grad
  Serial.print(temp_count);
  temp_count=0;
  delay(100);
}

void tempcount() {
  temp_count=temp_count+1;
}
