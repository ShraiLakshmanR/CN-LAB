int CalibrationTime=30;
long unsigned int lowIn;
long unsigned int pause=5000;
boolean locklow=true;
boolean takelowTime;
int pirPin=4;
int buzzerpin=13;
int analogPin=0;

void setup() {
  Serial.begin(9600);
  pinMode(pirPin,INPUT);
  pinMode(analogPin,INPUT);
  pinMode(buzzerpin,OUTPUT);
  digitalWrite(pirPin,LOW);
  Serial.print("Calibrating the sensor ");
  for(int i=0;i<CalibrationTime;i++)
  {
    Serial.print(".");
    delay(100);
  }
  Serial.println("Done");
  Serial.println("sensor Active");
  delay(10);

}

void loop() {
  int sensedValue=analogRead(analogPin);
  Serial.print("Sensed Value : ");
  Serial.println(sensedValue);
 
  int threshold=500;
  if(digitalRead(pirPin)==HIGH && sensedValue<threshold )
  {
    digitalWrite(buzzerpin,HIGH);
  if(locklow)
  {
    locklow=false;
    Serial.println("---");
    Serial.println("Motion detected at ");
    Serial.println((millis()/1000));
    Serial.println("Sec.");
    delay(50);
  }
  takelowTime=true;
  
  }

if(digitalRead(pirPin)==LOW)
{
  digitalWrite(buzzerpin,LOW);
  if(takelowTime)
  {
    lowIn=millis();
    takelowTime=false;
  }
  if(!locklow && millis()-lowIn>pause)
  {
    locklow=true;
    Serial.print("motion ended at ");
    Serial.print((millis()-pause)/1000);
    Serial.println(" sec");
    delay(50);
  }
}
}
