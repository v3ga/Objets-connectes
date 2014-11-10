int luminosite = 0;
int choc = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  //pinMode(A5, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}



void loop()
{
  luminosite = analogRead(A0);
  choc = analogRead(A5);
  //Serial.println("l="+luminosite);
  if (choc>10)
    Serial.println(choc);
  if ( luminosite > 300)
  {
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
  }
  else
  {
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);  
  }




}






