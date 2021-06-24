int V_ultraS = A0;

// SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);

void setup(void)
{
  Cellular.off();

  delay(5000); // to see response from begin command

  Serial.begin(9600);
  Serial.println("Maxbotix Test");

}

void loop(void)
{
  
  Serial.print("Distance(in): ");
  //Counts * (V range/count range) * (Inch range/V range)
  Serial.print(analogRead(V_ultraS)*(3.3/2048)*(254/3.3)); 

//   float distanceInches = distance * 0.0393701;
//   float distanceFeet = distanceInches / 12.0;

//   Serial.print(", Distance(ft): ");
//   Serial.print(distanceFeet, 2);

  Serial.println();

  delay(1000);
}
