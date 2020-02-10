#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C Lcd(0x27,16,2);

int count = 0;
int gamecount = 10;
double time1 = millis();
double time2;
long trtime = 0;
long randNum = 0;
int ButtonSt = 12;
int Button1 = 2;
int Button2 = 3;
int Button3 = 4;
int Button4 = 5;
int Button5 = 6;
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;
int buttonStateSt = 0;
long fulltime = 0;
float avg = 0;
int fractional;
int pressed = 0;

void refrainwin() {
  
  tone(11,196);
  delay(300);
  tone(11,147);
  delay(300);
  tone(11,87);
  delay(300);
  tone(11,98);
  delay(300);
  noTone(11);
  delay(1000); 
}

void refrainlose() {

  tone(11,196);
  delay(250);
  noTone(11);
  delay(300);
  tone(11,196);
  delay(250);
  noTone(11);
  delay(300);
  tone(11,196);
  delay(250);
  noTone(11);
  delay(300);
  tone(11,156);
  delay(250);
  noTone(11);
  delay(300);
  tone(11,175);
  delay(250);
  noTone(11);
  delay(300);
  tone(11,175);
  delay(250);
  noTone(11);
  delay(300);
  tone(11,175);
  delay(250);
  noTone(11);
  delay(300);
  tone(11,147);
  delay(600);
  noTone(11);
  delay(1000);
}

void refraincomplete() {

  tone(11,196);
  delay(300);
  tone(11,147);
  delay(300);
  tone(11,87);
  delay(300);
  tone(11,98);
  delay(300);
  tone(11,98);
  delay(300);
  tone(11,116);
  delay(300);
  tone(11,116);
  delay(300);
  tone(11,207);
  delay(300);
  tone(11,196);
  delay(300);
  tone(11,147);
  delay(300);
  tone(11,87);
  delay(300);
  tone(11,98);
  delay(500);
  noTone(11);
  delay(1000);
}

void setup() {
  
  randomSeed(analogRead(A1));
  
  pinMode(Button1, INPUT);
  digitalWrite(Button1, LOW);
  pinMode(Button2, INPUT);
  digitalWrite(Button2, LOW);
  pinMode(Button3, INPUT);
  digitalWrite(Button3, LOW);
  pinMode(Button4, INPUT);
  digitalWrite(Button4, LOW);
  pinMode(Button5, INPUT);
  digitalWrite(Button5, LOW);
  pinMode(ButtonSt, INPUT_PULLUP);
  digitalWrite(ButtonSt, HIGH);

  pinMode(13, OUTPUT);

  Serial.begin(9600);
  Lcd.init(); 
  Lcd.clear();
  Lcd.backlight();
  randNum = random(1,6);
  Serial.println(randNum);
}

void loop() {

  randomSeed(analogRead(A1));
  Lcd.clear();
  Lcd.setCursor(2,1);
  Lcd.print("Remaining:" + String(gamecount));
  delay(100);
  Lcd.setCursor(3,0);
  Lcd.print("Start Game");
  delay(100);
  Lcd.setCursor(0,0);
   
  buttonState1 = digitalRead(Button1);
  buttonState2 = digitalRead(Button2);
  buttonState3 = digitalRead(Button3);
  buttonState4 = digitalRead(Button4);
  buttonState5 = digitalRead(Button5);
  buttonStateSt = digitalRead(ButtonSt);

  digitalWrite(ButtonSt, HIGH);
  digitalWrite(Button1, LOW);
  digitalWrite(Button2, LOW);
  digitalWrite(Button3, LOW);
  digitalWrite(Button4, LOW);
  digitalWrite(Button5, LOW);
 
  Lcd.clear();
  trtime = 0;
  time1 = millis();
  digitalWrite(13, HIGH);

  if(pressed == 0) {

    if(buttonStateSt == LOW) {

      pressed = 1;
    }
  }
    
  while(pressed == 1){
    
   buttonState1 = digitalRead(Button1);
   buttonState2 = digitalRead(Button2);
   buttonState3 = digitalRead(Button3);
   buttonState4 = digitalRead(Button4);
   buttonState5 = digitalRead(Button5);
   buttonStateSt = digitalRead(ButtonSt);
      
   digitalWrite(Button1, LOW);
   digitalWrite(Button2, LOW);
   digitalWrite(Button3, LOW);
   digitalWrite(Button4, LOW);
   digitalWrite(Button5, LOW);
      
   Lcd.setCursor(5,0);
   Lcd.print("Zahl:");
   Lcd.print(randNum);
   Lcd.setCursor(0,0);
   time2 = millis();
   trtime = (time2-time1) / 1000;
   Lcd.setCursor(3,1);
   Lcd.print("Zeit:");
   Lcd.print(trtime);
    
   /*Lcd.print(".");
      
   fractional = (int)(trtime % 1000);
   if (fractional == 0)
     Lcd.print("000");      // add three zero's
   else if (fractional < 10)    // if fractional < 10 the 0 is ignored giving a wrong time, so add the zeros
     Lcd.print("00");       // add two zeros
   else if (fractional < 100)
     Lcd.print("0");        // add one zero
      
   Lcd.print(fractional);  // print fractional part of time*/

   Lcd.setCursor(12,1);
   Lcd.print("Sek");
      
   Lcd.setCursor(0,0);
   Serial.println(time2);
   Serial.println(time1);
   Serial.println(trtime);
   Serial.println("......");
   delay(100);

   if(buttonState1 == HIGH && (Button1 - 1) == randNum){

    refrainwin();
      
    Lcd.clear();
    Lcd.setCursor(4,0);
    Lcd.print("You Win!");
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Win!");
    delay(100);
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Win!");
    Lcd.setCursor(0,0);
        
    randNum = random(1,6);
    Serial.println(randNum);
    fulltime = fulltime + trtime;
    count = count + 1;
    gamecount = gamecount - 1;
    trtime = 0;
    avg = float(fulltime) / count;
    Serial.println("Total time:" + String(fulltime) + "s");
    Serial.println("Average reaction time:" + String(avg) + "s");
    Serial.println("Round:" + String(count));
    delay(3000);
        
    digitalWrite(Button1, LOW);
    digitalWrite(Button2, LOW);
    digitalWrite(Button3, LOW);
    digitalWrite(Button4, LOW);
    digitalWrite(Button5, LOW);
    digitalWrite(ButtonSt, HIGH);

    if(count == 10) {
        
      Lcd.clear();
      Lcd.setCursor(3,0);
      Lcd.print("Game Over!");
      Lcd.setCursor(0,0);
      delay(3000);
      Lcd.clear();
      Lcd.setCursor(3,0);
      Lcd.print("Total:" + String(fulltime) + "s");
      Lcd.setCursor(2,1);
      Lcd.print("Average:" + String(avg) + "s");
      Lcd.setCursor(0,0);
       
      randNum = random(1,6);
      Serial.println(randNum);
      fulltime = 0;
      count = 0;
      trtime = 0;
      avg = 0;
      gamecount = 10;
      pressed = 0;

      refraincomplete();
      
      delay(15000);
      break;
    }
    pressed = 0;
    break;
  }
    
  else if(buttonState1 == HIGH && (Button1 - 1) != randNum){

    refrainlose();
    
    Lcd.clear();
    Lcd.setCursor(4,0);
    Lcd.print("You Lose!");
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Lose!");
    delay(100);
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Lose!");
    Lcd.setCursor(0,0);
   
    delay(3000);
    
    Lcd.clear();
    Lcd.setCursor(3,0);
    Lcd.print("Game Over!");
    Lcd.setCursor(0,0);
    delay(3000);
    Lcd.clear();
    Lcd.setCursor(3,0);
    Lcd.print("Total:" + String(fulltime) + "s");
    Lcd.setCursor(2,1);
    Lcd.print("Average:" + String(avg) + "s");
    Lcd.setCursor(0,0);
   
    randNum = random(1,6);
    Serial.println(randNum);
    fulltime = 0;
    count = 0;
    trtime = 0;
    avg = 0;
    gamecount = 10;
    pressed = 0;
    delay(5000);
    break;
  }
    
  if(buttonState2 == HIGH && (Button2 - 1) == randNum){

    refrainwin();
    
    Lcd.clear();
    Lcd.setCursor(4,0);
    Lcd.print("You Win!");
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Win!");
    delay(100);
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Win!");
    Lcd.setCursor(0,0);
      
    randNum = random(1,6);
    Serial.println(randNum);
    fulltime = fulltime + trtime;
    count = count + 1;
    gamecount = gamecount - 1;
    trtime = 0;
    avg = float(fulltime) / count;
    Serial.println("Total time:" + String(fulltime) + "s");
    Serial.println("Average reaction time:" + String(avg) + "s");
    Serial.println("Round:" + String(count));
    delay(3000);
      
    digitalWrite(Button1, LOW);
    digitalWrite(Button2, LOW);
    digitalWrite(Button3, LOW);
    digitalWrite(Button4, LOW);
    digitalWrite(Button5, LOW);
    digitalWrite(ButtonSt, HIGH);

    if(count == 10) {

      refraincomplete();
      
      Lcd.clear();
      Lcd.setCursor(3,0);
      Lcd.print("Game Over!");
      Lcd.setCursor(0,0);
      delay(3000);
      Lcd.clear();
      Lcd.setCursor(3,0);
      Lcd.print("Total:" + String(fulltime) + "s");
      Lcd.setCursor(2,1);
      Lcd.print("Average:" + String(avg) + "s");
      Lcd.setCursor(0,0);
     
      randNum = random(1,6);
      Serial.println(randNum);
      fulltime = 0;
      count = 0;
      trtime = 0;
      avg = 0;
      gamecount = 10;
      pressed = 0;
      delay(15000);
      break;
    }
    pressed = 0;
    break;
  }
  
  else if(buttonState2 == HIGH && (Button2 - 1) != randNum){

    refrainlose();
    
    Lcd.clear();
    Lcd.setCursor(4,0);
    Lcd.print("You Lose!");
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Lose!");
    delay(100);
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Lose!");
    Lcd.setCursor(0,0);
  
    delay(3000);
  
    Lcd.clear();
    Lcd.setCursor(3,0);
    Lcd.print("Game Over!");
    Lcd.setCursor(0,0);
    delay(3000);
    Lcd.clear();
    Lcd.setCursor(3,0);
    Lcd.print("Total:" + String(fulltime) + "s");
    Lcd.setCursor(2,1);
    Lcd.print("Average:" + String(avg) + "s");
    Lcd.setCursor(0,0);
 
    randNum = random(1,6);
    Serial.println(randNum);
    fulltime = 0;
    count = 0;
    trtime = 0;
    avg = 0;
    gamecount = 10;
    pressed = 0;
    delay(5000);
    break;
  }

  if(buttonState3 == HIGH && (Button3 - 1) == randNum){

    refrainwin();
    
    Lcd.clear();
    Lcd.setCursor(4,0);
    Lcd.print("You Win!");
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Win!");
    delay(100);
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Win!");
    Lcd.setCursor(0,0);
      
    randNum = random(1,6);
    Serial.println(randNum);
    fulltime = fulltime + trtime;
    count = count + 1;
    gamecount = gamecount - 1;
    trtime = 0;
    avg = float(fulltime) / count;
    Serial.println("Total time:" + String(fulltime) + "s");
    Serial.println("Average reaction time:" + String(avg) + "s");
    Serial.println("Round:" + String(count));
    delay(3000);
      
    digitalWrite(Button1, LOW);
    digitalWrite(Button2, LOW);
    digitalWrite(Button3, LOW);
    digitalWrite(Button4, LOW);
    digitalWrite(Button5, LOW);
    digitalWrite(ButtonSt, HIGH);

    if(count == 10) {
    
      refraincomplete();
      
      Lcd.clear();
      Lcd.setCursor(3,0);
      Lcd.print("Game Over!");
      Lcd.setCursor(0,0);
      delay(3000);
      Lcd.clear();
      Lcd.setCursor(3,0);
      Lcd.print("Total:" + String(fulltime) + "s");
      Lcd.setCursor(2,1);
      Lcd.print("Average:" + String(avg) + "s");
      Lcd.setCursor(0,0);
     
      randNum = random(1,6);
      Serial.println(randNum);
      fulltime = 0;
      count = 0;
      trtime = 0;
      avg = 0;
      gamecount = 10;
      pressed = 0;
      delay(15000);
      break;
    }
    pressed = 0;
    break;
  }
  
  else if(buttonState3 == HIGH && (Button3 - 1) != randNum){

    refrainlose();
    
    Lcd.clear();
    Lcd.setCursor(4,0);
    Lcd.print("You Lose!");
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Lose!");
    delay(100);
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Lose!");
    Lcd.setCursor(0,0); 
  
    delay(3000);
  
    Lcd.clear();
    Lcd.setCursor(3,0);
    Lcd.print("Game Over!");
    Lcd.setCursor(0,0);
    delay(3000);
    Lcd.clear();
    Lcd.setCursor(3,0);
    Lcd.print("Total:" + String(fulltime) + "s");
    Lcd.setCursor(2,1);
    Lcd.print("Average:" + String(avg) + "s");
    Lcd.setCursor(0,0);
 
    randNum = random(1,6);
    Serial.println(randNum);
    fulltime = 0;
    count = 0;
    trtime = 0;
    avg = 0;
    gamecount = 10;
    pressed = 0;
    delay(5000);
    break;
  }

  if(buttonState4 == HIGH && (Button4 - 1) == randNum){

    refrainwin();
    
    Lcd.clear();
    Lcd.setCursor(4,0);
    Lcd.print("You Win!");
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Win!");
    delay(100);
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Win!");
    Lcd.setCursor(0,0);
      
    randNum = random(1,6);
    Serial.println(randNum);
    fulltime = fulltime + trtime;
    count = count + 1;
    gamecount = gamecount - 1;
    trtime = 0;
    avg = float(fulltime) / count;
    Serial.println("Total time:" + String(fulltime) + "s");
    Serial.println("Average reaction time:" + String(avg) + "s");
    Serial.println("Round:" + String(count));
    delay(3000);
      
    digitalWrite(Button1, LOW);
    digitalWrite(Button2, LOW);
    digitalWrite(Button3, LOW);
    digitalWrite(Button4, LOW);
    digitalWrite(Button5, LOW);
    digitalWrite(ButtonSt, HIGH);

    if(count == 10) {
    
      refraincomplete();
      
      Lcd.clear();
      Lcd.setCursor(3,0);
      Lcd.print("Game Over!");
      Lcd.setCursor(0,0);
      delay(3000);
      Lcd.clear();
      Lcd.setCursor(3,0);
      Lcd.print("Total:" + String(fulltime) + "s");
      Lcd.setCursor(2,1);
      Lcd.print("Average:" + String(avg) + "s");
      Lcd.setCursor(0,0);
     
      randNum = random(1,6);
      Serial.println(randNum);
      fulltime = 0;
      count = 0;
      trtime = 0;
      avg = 0;
      gamecount = 10;
      pressed = 0;
      delay(15000);
      break;
    }
    pressed = 0;
    break;
  }
  
  else if(buttonState4 == HIGH && (Button4 - 1) != randNum){

    refrainlose();
    
    Lcd.clear();
    Lcd.setCursor(4,0);
    Lcd.print("You Lose!");
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Lose!");
    delay(100);
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Lose!");
    Lcd.setCursor(0,0);
   
    delay(3000);
  
    Lcd.clear();
    Lcd.setCursor(3,0);
    Lcd.print("Game Over!");
    Lcd.setCursor(0,0);
    delay(3000);
    Lcd.clear();
    Lcd.setCursor(3,0);
    Lcd.print("Total:" + String(fulltime) + "s");
    Lcd.setCursor(2,1);
    Lcd.print("Average:" + String(avg) + "s");
    Lcd.setCursor(0,0);
 
    randNum = random(1,6);
    Serial.println(randNum);
    fulltime = 0;
    count = 0;
    trtime = 0;
    avg = 0;
    gamecount = 10;
    pressed = 0;
    delay(5000);
    break;
  }

  if(buttonState5 == HIGH && (Button5 - 1) == randNum){

    refrainwin();
      
    Lcd.clear();
    Lcd.setCursor(4,0);
    Lcd.print("You Win!");
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Win!");
    delay(100);
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Win!");
    Lcd.setCursor(0,0);
      
    randNum = random(1,6);
    Serial.println(randNum);
    fulltime = fulltime + trtime;
    count = count + 1;
    gamecount = gamecount - 1;
    trtime = 0;
    avg = float(fulltime) / count;
    Serial.println("Total time:" + String(fulltime) + "s");
    Serial.println("Average reaction time:" + String(avg) + "s");
    Serial.println("Round:" + String(count));
    delay(3000);
      
    digitalWrite(Button1, LOW);
    digitalWrite(Button2, LOW);
    digitalWrite(Button3, LOW);
    digitalWrite(Button4, LOW);
    digitalWrite(Button5, LOW);
    digitalWrite(ButtonSt, HIGH);

    if(count == 10) {

      refraincomplete();
      
      Lcd.clear();
      Lcd.setCursor(3,0);
      Lcd.print("Game Over!");
      Lcd.setCursor(0,0);
      delay(3000);
      Lcd.clear();
      Lcd.setCursor(3,0);
      Lcd.print("Total:" + String(fulltime) + "s");
      Lcd.setCursor(2,1);
      Lcd.print("Average:" + String(avg) + "s");
      Lcd.setCursor(0,0);
     
      randNum = random(1,6);
      Serial.println(randNum);
      fulltime = 0;
      count = 0;
      trtime = 0;
      avg = 0;
      gamecount = 10;
      pressed = 0;
      delay(15000);
      break;
    }
    pressed = 0;
    break;
  }
  
  else if(buttonState5 == HIGH && (Button5 - 1) != randNum){

    refrainlose();
    
    Lcd.clear();
    Lcd.setCursor(4,0);
    Lcd.print("You Lose!");
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Lose!");
    delay(100);
    Lcd.setCursor(0,0);
    Lcd.clear();
    delay(100);
    Lcd.setCursor(4,0);
    Lcd.print("You Lose!");
    Lcd.setCursor(0,0);
  
    delay(3000);
  
    Lcd.clear();
    Lcd.setCursor(3,0);
    Lcd.print("Game Over!");
    Lcd.setCursor(0,0);
    delay(3000);
    Lcd.clear();
    Lcd.setCursor(3,0);
    Lcd.print("Total:" + String(fulltime) + "s");
    Lcd.setCursor(2,1);
    Lcd.print("Average:" + String(avg) + "s");
    Lcd.setCursor(0,0);
 
    randNum = random(1,6);
    Serial.println(randNum);
    fulltime = 0;
    count = 0;
    trtime = 0;
    avg = 0;
    gamecount = 10;
    pressed = 0;
    delay(5000);
    break;
  }
  }
}
