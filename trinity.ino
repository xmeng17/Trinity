#define PWMA 3
#define PWMB 11

#define DIRA 12
#define DIRB 13

#define ENCA 3
#define ENCB 2

volatile int count1;
volatile int count2;

void onDetect1(){
  count1++;
  Serial.println(count1);
}

void onDetect2(){
  count2++;
  Serial.println(count2);
}

void drive(byte spd1, boolean dir1, byte spd2, boolean dir2){
  digitalWrite(DIRA, dir1);
  analogWrite(PWMA, spd1); 
  digitalWrite(DIRB, dir2);
  analogWrite(PWMB, spd2); 
}
 
void setup()
{
  Serial.begin(9600);
  attachInterrupt(0, onDetect1, RISING);
  attachInterrupt(1, onDetect2, RISING);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRA, OUTPUT);
  
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}

void loop()//Measure RPM
{
 // if (count < 8){
  //  drive(200,1,200,1);
   // delay(1);
 // } else{
 //   drive(0,1,0,1);
 //   count = 0;
 //   delay(1000);
 // }
}

