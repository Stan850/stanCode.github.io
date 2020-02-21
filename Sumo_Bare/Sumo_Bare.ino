int trig = 7;
int echo = 8;

int dist = 0;

int distance(){   //uses the ultrasonic distance sensor, as a function
  digitalWrite(trig, LOW);
  delayMicroseconds (2);
  digitalWrite(trig, HIGH);
  delayMicroseconds (10);
  digitalWrite(trig, LOW);

  int duration = pulseIn (echo, HIGH);
  return duration*0.034/2;
}


//-------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}

void loop() {
  dist = distance(); // calls function above

  if (dist < 50) {
   Serial.print("CHARGE: Distance: ");
   Serial.println(dist);
  }

  else if (analogRead(A0)<200){ //sensor in the front triggered by edge, once light reflects value goes very low
    Serial.println("Front sensor triggered: go BACK");
  }

  else if (analogRead(A1)<200){ //sensor in back triggered
    Serial.println("Rear sensor triggered: go FWD");
  }

  else {
    Serial.println("STAY");
  }
  
}
