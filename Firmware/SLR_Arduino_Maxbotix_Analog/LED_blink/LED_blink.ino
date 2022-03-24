
const int led1Pin =  12;      // the number of the LED pin (choose 12, 11, 10, 9)
const int led2Pin =  10; 

void setup() {
  // put your setup code here, to run once:
  // initialize the LED pin as an output:
  pinMode(led1Pin, OUTPUT);

  pinMode(led2Pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(led1Pin, HIGH); // turn LED on
    delay(5000); //milli-seconds
    
    digitalWrite(led1Pin, LOW); // turn LED off
    delay(500);  //milli-seconds

    digitalWrite(led2Pin, HIGH); // turn LED on
    delay(1000); //milli-seconds
    
    digitalWrite(led2Pin, LOW); // turn LED on
   delay(1000);  //milli-seconds
}
