// EKG 
// Lead placement COM->L, "L"->R, "R"->LL

byte EKG;
int  loops;
boolean flipflop;

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {
  loops++;
  if(loops%100==0) flipflop = !flipflop;
  digitalWrite(13,flipflop);
  EKG = analogRead(A0)/4;
  Serial.write(EKG);
//  Serial.println(EKG);
  delay(1);
}
