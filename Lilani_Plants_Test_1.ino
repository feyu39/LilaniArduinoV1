int blue = 0;  // for incoming serial data
String readString;
int moisture_sensor  = A0; //set to pin A0 on arduino
int moisture;
int limit = 700; //if soil moisture gets below this . . .run pump
int pump = 3; //pin D3 on arduino set to pump
int led = 13; //set to pin 13 on arduino
const long pump_time = 18000; // FACTOR IN DELAY TIMES, SO DO YOUR TIME YOU WANT +DELAY TIMES pump interval till it runs again
const long sensor_time = 6000; //delay the sensor from reading for this long
unsigned long previousPumpTime = 0;
unsigned long previousSensorTime = 0;
unsigned long currentMillis();
int pump_status = 0;
void setup() //runs when uploading arduino, then that's it
{
  
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(moisture_sensor,INPUT); //sets sensor to input
  pinMode(pump,OUTPUT); //sets pump and led to output
  pinMode(led,OUTPUT);
  //digitalWrite(pump,LOW); don't need this: turns pump off in begenning
  //digitalWrite(led,LOW);
  
}

void loop() //continously loops
{
   //maybe use millis() instead of delay
 // digitalWrite(led,LOW); turns pump and led off in begenning
  //digitalWrite(pump,LOW);
  unsigned long currentMillis = millis();
 // gets number of milliseconds since program started
  Serial.print("Beginning of loop");
  Serial.println();
 // if (currentMillis - previousSensorTime >= sensor_time) 
// {
  
  //previousSensorTime = currentMillis; // save the last time you checked soil
   
 // }
 //5 second delay for moisture sensor and run pump for 5 seconds

  
  if (Serial.available())
  {
    //digitalWrite(led, HIGH);
    //digitalWrite(pump, HIGH);
    delay(1000);  
    char c = Serial.read();
    readString += c; 
  
    if (readString.length() >0) 
    {
      Serial.println(readString);
      if (readString == "o")     
      {
        digitalWrite(pump, HIGH);
        Serial.println("Pump ON");
        pump_status = 1;
        delay(5000);
      }
      if (readString == "f")
      {
        digitalWrite(pump, LOW);
        Serial.println("Pump OFF");
        pump_status = 0;
        delay(5000);
      }
      readString=""; 
     }
  }

  if (Serial.available() == false)
  {
    delay(2000);
  moisture = analogRead(moisture_sensor);//analog read the moisture sensor
  Serial.print("Moisture=");
  Serial.print(moisture);
  Serial.println();
     // check to see if it's time to run the Pump; that is, if the difference
  // between the current time and last time you ran pump is bigger than
  // the interval at which you want to run pump.
    if(moisture<limit && currentMillis - previousPumpTime >= pump_time)
    {
      previousPumpTime = currentMillis;
      if (pump_status == 1)
      {
        digitalWrite(pump,LOW);
        digitalWrite(led, LOW);
        Serial.println("Pump OFF");  
        pump_status = 0;
      } 
      else 
      {
        digitalWrite(led, HIGH);
        digitalWrite(pump, HIGH);
        Serial.println("Pump ON");
        pump_status = 1;
        delay(5000); // runs pump for this long + the delay of the soil moisture sensor
      }   
        
    }
    else
    { 
        digitalWrite(pump,LOW);
        digitalWrite(led, LOW);
        Serial.println("Pump OFF");  
        pump_status = 0;
    }
  
}

int Bluetooth() //maybe will need to optimize this for my bluetooth chip
{
   // send data only when you receive data:
   if(Serial.available() > 0) 
   {
    // read the incoming byte:
    blue = Serial.read();

    // say what you got:
    Serial.print("Bluetooth");
    Serial.println(blue);
    if(blue == 48)
      {
      return 0;
      }
    if(blue == 49)
      {
      return 1;
      }
  }
  else 
  return 0;
}

/* 
void Pump(int stat)
{
  if(stat == 0) //should be 0, turn pump off
  {
    digitalWrite(pump,LOW);
    digitalWrite(led, LOW);
    Serial.println("Pump OFF");
    pump_status = 0;
  }
  if(stat == 1) //should be 1, turn pump on
  {
    
    digitalWrite(led, HIGH);
    digitalWrite(pump, HIGH);
    Serial.println("Pump ON");
    pump_status = 1;
    //delay(7000); //run pump for this long 
    
    
  }
} 
 */
