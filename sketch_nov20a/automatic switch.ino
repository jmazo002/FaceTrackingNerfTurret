/*        Your Name & E-mail: Justin Mazon

*          Discussion Section: 023

 *         Assignment: Lab 6  Exercise 1

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *

 *         Demo Link: https://www.youtube.com/watch?v=DyfwGq5idt4&ab_channel=JustinMazon

 */
int red = 4;
int yellow = 2;
int green = 6;
int white = 5;
int blue = 3;
int time;
int time2 = 0;
int stop = 1;

int W = 0;
int N = -1;
int I = -1;

int bothCovered = 0;
int covered1 = 0;
int covered2 = 0;

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);

} task;

int delay_gcd;
const unsigned short tasksNum = 2;
task tasks[tasksNum];

enum SM1_States {start1, nothing, covered, check};
int Sensors(int state1) {
  switch (state1) { // State transitions
    case start1:
      state1 = nothing;
      break;
    case nothing:

      if (analogRead(A0) <= 4 && analogRead(A1) <= 8)
      {
        bothCovered = 1;
      }
      else if (analogRead(A0) >= 4 && analogRead(A1) >= 8 && bothCovered == 1)
      {
        Serial.println("woohooooo");
        state1 = check;
        stop = 0;
        bothCovered = 0;
      }
      break;
    case covered:

      if (analogRead(A0) >= 7 && analogRead(A1) >= 12 && bothCovered == 1)
      {
        Serial.println("Both are covered");
        state1 = check;
        stop = 0;
        bothCovered = 0;
      }
      if (analogRead(A0) >= 7 && covered1 == 1)
      {
        //Serial.println("Left covered");
        state1 = check;
        stop = 0;
        covered1 = 0;
      }
      if (analogRead(A1) >= 12 && covered2 == 1)
      {
        //Serial.println("Right covered");
        state1 = check;
        stop = 0;
        covered2 = 0;
      }
      break;
    case check:
      if (analogRead(A0) <= 4 && analogRead(A1) <= 8)
      {
        stop = 1;
        bothCovered = 1;
        state1 = covered;
        digitalWrite(red, HIGH);
        digitalWrite(yellow, HIGH);
      }
      else if (analogRead(A0) <= 4)
      {
        stop = 1;
        state1 = covered;
        covered1 = 1;
        digitalWrite(red, HIGH);
      }
      if (time % 40 == 0)
      {
        if (analogRead(A1) <= 8)
          {
            stop = 1;
            state1 = covered;
            covered2 = 1;
            digitalWrite(yellow, HIGH);
          }
      }
      break;
    
  }
  switch (state1) { // State Action
    case start1:
      break;
    case covered:
      //Serial.println("Covered state");
      Serial.println(analogRead(A0));
      Serial.println(analogRead(A1));
      Serial.println("covered");
      stop = 1;
      break;
    case check:
      time++;
      stop = 0;
      Serial.println(analogRead(A0));
      Serial.println(analogRead(A1));
      Serial.println("checking");
      digitalWrite(red, LOW);
      digitalWrite(yellow, LOW);
      break;
  }
  return state1;
}
enum SM2_States {start2, off, on};
int Cycle(int state2) {
  switch (state2) { // State transitions
    case start2:
      state2 = off;
      break;
    case off:
      if (stop == 0)
        {
          state2 = on;
        }
      break;
    case on:
      if (stop == 1)
      {
        state2 = off;
      }
      if (time2 >= 70 && W != -1)
      {
        digitalWrite(blue, HIGH);
        time2 = 0;
      }
      if (time2 >= 50 && N != -1)
      {
        digitalWrite(white, HIGH);
        time2 = 0;
      }
      if (time2 >= 10 && I != -1)
      {
        digitalWrite(green, HIGH);
        time2 = 0;
      }

      
      //to transition each LED state
      if (W == 300) {
        W = -1;
        N = 0;
        
      }
      if (N == 500) {
        N = -1;
        I = 0;
        
      }
      if (I == 200) {
        I = -1;
        W = 0;
        
      }
      break;

  }
  switch (state2) { // State Action
    case start2:
      break;
    case off:
      digitalWrite(blue, LOW);
      digitalWrite(white, LOW);
      digitalWrite(green, LOW);
      break;
    case on:
      time2++;
      //Serial.println(time2);
      if (time2 <= 5)
      {

      }
      else if (W >= 0)
      {
        W++;
        digitalWrite(blue, LOW);
        digitalWrite(white, LOW);
        digitalWrite(green, LOW);
      }
      if (time2 <= 5)
      {

      }
      if (N >= 0)
      {
        N++;
        digitalWrite(blue, LOW);
        digitalWrite(white, LOW);
        digitalWrite(green, LOW);
      }
      if (time2 <= 5)
      {

      }
      if (I >= 0)
      {
        I++;
        digitalWrite(blue, LOW);
        digitalWrite(white, LOW);
        digitalWrite(green, LOW);
      }
      break;
  }

  return state2;
}


void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(white, OUTPUT);
  pinMode(blue, OUTPUT);

  unsigned char i = 0;
  tasks[i].state = start1;
  tasks[i].period = 50;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = Sensors;
  i++;
  tasks[i].state = start2;
  tasks[i].period = 10;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = Cycle;

  delay_gcd = 1000; // GCD
  Serial.begin(9600);
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