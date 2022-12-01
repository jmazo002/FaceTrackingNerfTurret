#include <LiquidCrystal.h>
#include <DHT.h>
#define DHTPIN A0     
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int blue = 8;
int yellow = 9;
int white = 10;
int red = 11;
int JS_X = A1;
int JS_Y = A2;
int JS_BTN = 12;
int selector = 0;
float hic,  f;

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);

} task;

const unsigned short tasksNum = 3;
task tasks[tasksNum];

bool machineOn = false;
bool buttonPressed = false;
int setTemp = 75, setHumid = 30;
int time = 0;
int B = 0, Y = 0, W = 0, R = 0;





enum SM1_States { SM1_INIT, off1, on1};
int SM1_Tick(int state1) {
  switch (state1) { // State transitions
    case SM1_INIT:
      state1 = off1;
      break;
    case off1:
      if (machineOn)
      {
        state1 = on1;
      }
      break;
    case on1:



      float h = dht.readHumidity();
      float t = dht.readTemperature();
      f = dht.readTemperature(true);
      float hif = dht.computeHeatIndex(f, h);
      hic = dht.computeHeatIndex(t, h, false);


      if (selector == 0)
      {
        lcd.setCursor(9,1);
        lcd.print(" ");
        lcd.setCursor(8,0);
        lcd.print("^");
      }
      else {
        lcd.setCursor(8,0);
        lcd.print(" ");
        lcd.setCursor(9,1);
        lcd.print("v");
      }

      lcd.setCursor(0,0);
      lcd.print("Temp:");
      lcd.print(round(f));

      lcd.setCursor(9,0);
      lcd.print("STmp:");
      lcd.print(setTemp);

      lcd.setCursor(10,1);
      lcd.print("SHm:");
      lcd.print(setHumid);

      lcd.setCursor(0,1);
      lcd.print("Humid:");
      lcd.print(round(hic));

      if (!machineOn)
      {
        state1 = off1;
      }
      break;
  }
  switch (state1) { // State Action
    case SM1_INIT:
      break;
    case off1:
      lcd.clear();
      break;
  }
  return state1;
}

enum SM2_States { SM2_INIT, off2, on2};
int SM2_Tick(int state2) {
  switch (state2) { // State transitions
    case SM2_INIT:
      state2 = off1;
      break;
    case off2:
      if (digitalRead(JS_BTN) == 0)
      {
        buttonPressed = true;
      }
      if (digitalRead(JS_BTN) == 1 && buttonPressed)
      {
        state2 = on2;
        machineOn = true;
        buttonPressed = false;
        //Serial.println("On");
      }
      break;
    case on2:

      int x = analogRead(JS_X);
      int y = analogRead(JS_Y);

      if (x > 800)
      {
        if (selector == 0)
          setTemp += 1;
        else
          setHumid += 1;
      }
      if (x < 300)
      {
        if (selector == 0)
          setTemp -= 1;
        else
          setHumid -= 1;
      }
      if (y < 300)
      {
        selector = 1;
      }
      if (y > 700)
      {
        selector = 0;
      }



      if (digitalRead(JS_BTN) == 0)
      {
        buttonPressed = true;
      }
      if (digitalRead(JS_BTN) == 1 && buttonPressed)
      {
        state2 = off2;
        machineOn = false;
        buttonPressed = false;
        Serial.println("Off");
      }
      break;

  }
  switch (state2) { // State Action
    case SM2_INIT:
      state2 = on2;
      break;
    case on2:
    break;
  }

  return state2;
}

enum SM3_States { SM3_INIT, off3, on3};
int SM3_Tick(int state3) {
  switch (state3) { // State transitions
    case SM3_INIT:
      state3 = off3;
      break;
    case off3:
      if (machineOn)
      {
        state3 = on3;
      }
      break;
    case on3:


    B++;
    if (setHumid > round(hic) && B == 1)
    {
      digitalWrite(blue, LOW);
    }
    else if (setHumid > round(hic) && B >= 160)
    {
      digitalWrite(blue, HIGH);
      B = 0;
    }


    Y++;
    if (setHumid < round(hic) && Y == 1)
    {
      digitalWrite(yellow, LOW);
    }
    else if (setHumid < round(hic) && Y >= 300)
    {
      digitalWrite(yellow, HIGH);
      Y = 0;
    }

    W++;
    if (setTemp < round(f) && W == 1)
    {
      digitalWrite(white, LOW);
    }
    else if (setTemp < round(f) && W >= 120)
    {
      digitalWrite(white, HIGH);
      W = 0;
    }

    R++;
    if (setTemp > round(f) && R == 1)
    {
      digitalWrite(red, LOW);
    }
    else if (setTemp > round(f) && R >= 5)
    {
      digitalWrite(red, HIGH);
      R = 0;
    }




    if (setHumid == round(hic))
      {
        digitalWrite(blue, LOW);
        digitalWrite(yellow, LOW);
      }
    if (setTemp == round(f))
      {
        digitalWrite(red, LOW);
        digitalWrite(white, LOW);
      }
    if (setTemp > round(f))
      digitalWrite(white, LOW);
    if (setTemp < round(f))
      digitalWrite(red, LOW);
    if (setHumid < round(hic))
      digitalWrite(blue, LOW);
    if (setHumid > round(hic))
      digitalWrite(yellow, LOW);


    

    if (!machineOn)
    {
        state3 = off3;
    }
    break;
  }
  switch (state3) { // State Action
    case SM3_INIT:
      break;
    case off3:
      break;
    case on2:
      break;
  }

  return state3;
}









void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(blue, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(white, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(JS_BTN, INPUT_PULLUP);

  // put your setup code here, to run once:
  unsigned char i = 0;
  tasks[i].state = SM1_INIT;
  tasks[i].period = 500;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  i++;
  tasks[i].state = SM2_INIT;
  tasks[i].period = 300;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;
  i++;
  tasks[i].state = SM3_INIT;
  tasks[i].period = 1;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM3_Tick;


  Serial.begin(9600);
  dht.begin();
}

void loop() {
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elapsedTime = millis(); // Last time this task was ran
    }
  }



}