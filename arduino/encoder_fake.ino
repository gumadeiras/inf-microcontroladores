
int A = 9;
int B = 10;
int L1 = 2;
int L2 = 3;

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  Serial.begin(9600);
}

int dly = 1;
int cc = 0;
void loop() {
  digitalWrite(L1, HIGH);
  digitalWrite(L2, HIGH);
  if (cc == 500)
  {
    digitalWrite(L1, LOW);
    Serial.print("L1 low\n");
    delay(10);
    digitalWrite(L1, HIGH);
  } else if (cc == 1000)
  {
    digitalWrite(L2, LOW);
    Serial.print("L2 low\n");
    delay(10);
    digitalWrite(L2, HIGH);
    cc = 0;
  }
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(A, HIGH);
  delay(dly);
  digitalWrite(B, HIGH);
  delay(dly);
  digitalWrite(A, LOW);
  delay(dly);
  digitalWrite(B, LOW);
  delay(dly);
  cc = cc + 1;
  if(cc % 50 == 0)
  {
   Serial.print(cc);
   Serial.print("\n"); 
  }
}
