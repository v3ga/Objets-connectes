int choc = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}



void loop()
{
  choc = analogRead(A5);
  //Serial.println("l="+luminosite);
  if (choc>10)
  {
    digitalWrite(13, HIGH);
  }
  else
  {
    digitalWrite(13, LOW);
  }




}






