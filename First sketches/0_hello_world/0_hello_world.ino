int count = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("Hello world!");
}

void loop()
{
  Serial.println(count);
  delay(1000);
  count++;
}