#include <Wire.h>
#include "rgb_lcd.h"

int loserLength = 2;
int winnerLength = 8;
char lose[] = "Dg";
char win[] = "cggag bc";
int loseBeat[] = {2, 3};
int winBeat[] = {3, 2, 1, 3, 3, 3, 3, 3};
int loseTempo = 300;
int winTempo = 100;

int buzz = 5;

rgb_lcd lcd;

int left = 2;
int right = 3;
int playerPoints;
int CPUPoints;

void setup() {
  // put your setup code here, to run once:
  playerPoints = 9;
  CPUPoints = 9;
  pinMode(buzz, OUTPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.write("Hello there!");
  delay(2000);
  lcd.setCursor(0,0);
  lcd.write("I'm thinking of");
  lcd.setCursor(0,1);
  lcd.write("a game...");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Click any button");
  lcd.setCursor(0,1);
  lcd.write("to play.");
}

void loop() {
  // put your main code here, to run repeatedly:
  int leftState = digitalRead(left);
  int rightState = digitalRead(right);
  if (leftState == 1 || rightState == 1) {
    headsOrTailsSetup();
  }
}

void headsOrTailsSetup() {
  lcd.clear();
  delay(1000);
  lcd.print("Muahaha...");
  delay(1000);
  for (int i = 0; i < 16; i++) {
    lcd.scrollDisplayRight();
    delay(100);
  }
  headsOrTails();
}

void headsOrTails() {
  if (CPUPoints >= 10)
    closingCeremony();
  if (playerPoints >= 10)
    closingCeremony();
  lcd.clear();
  lcd.setRGB(255, 255, 255);
    lcd.write(" Left or right?");
    int guess = rand() % 2;
    for (int k = 10; k >= 0; k--) {
      int leftState = digitalRead(left);
      int rightState = digitalRead(right);
      lcd.setCursor(6, 1);
      lcd.print((String)k + "...");
      delay(1000);
      if (k == 0) {
        lcd.clear();
        lcd.setRGB(255, 0, 0);
        lcd.setCursor(3, 0);
        lcd.print("Too late!!");
        lcd.setCursor(3, 1);
        lcd.print("My point!!");
        CPUPoints++;
        delay(3000);
        scoreboard();
        delay(5000);
        headsOrTails();
      } else if (leftState == 1 && rightState == 1) {
        lcd.clear();
        lcd.setRGB(255, 0, 0);
        lcd.setCursor(0,0);
        lcd.print("One button only!");
        lcd.setCursor(3,1);
        lcd.print("My point!!");
        CPUPoints++;
        delay(3000);
        scoreboard();
        delay(5000);
        headsOrTails();
      } else if (leftState == 1 && guess == 0){
        playerPoints++;
        lcd.clear();
        lcd.setRGB(0, 255, 0);
        lcd.setCursor(4, 0);
        lcd.print("Congrats!");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("You guessed it!!");
        lcd.setCursor(0,1);
        lcd.print("Your Guess: left");
        delay(3000);
        scoreboard();
        delay(5000);
        headsOrTails();
      } else if (rightState == 1 && guess == 1) {
        playerPoints++;
        lcd.clear();
        lcd.setRGB(0, 255, 0);
        lcd.setCursor(4, 0);
        lcd.print("Congrats!");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("You guessed it!!");
        lcd.setCursor(0,1);
        lcd.print("Your Guess:right");
        delay(3000);
        scoreboard();
        delay(5000);
        headsOrTails();
      } else if ((leftState == 1 && guess == 1)||
                 (rightState == 1 && guess == 0)){
        lcd.clear();
        lcd.setRGB(255, 0, 0);
        lcd.setCursor(1, 0);
        lcd.print("You are wrong!");
        lcd.setCursor(3, 1);
        lcd.print("My point!!");
        CPUPoints++;
        delay(3000);
        scoreboard();
        delay(5000);
        headsOrTails();
      } else {
        continue;
      }
    }
}

void scoreboard() {
  String player = "Your Points:";
  String cpu = "CPU Points:";
  if(playerPoints > 9)
    player += "  " + (String)playerPoints;
  else
    player += "   " + (String)playerPoints;    
  if(CPUPoints > 9)
    cpu += "  " + (String)CPUPoints;
  else
    cpu += "   " + (String)CPUPoints;
  lcd.clear();
  lcd.setRGB(255, 255, 255);
  if (playerPoints > CPUPoints)
    lcd.setRGB(0, 255, 0);
  else if (playerPoints == CPUPoints)
    lcd.setRGB(0, 0, 255);
  else
    lcd.setRGB(255, 0, 0);
  lcd.setCursor(0,0);
  lcd.print(player);
  lcd.setCursor(1,1);
  lcd.print(cpu);
}

void closingCeremony() {
  if (CPUPoints > playerPoints) {
    lcd.clear();
    lcd.setRGB(255, 0 ,0);
    lcd.setCursor(2, 0);
    lcd.print("You LOSE!!!!");
    lcd.setCursor(0,1);
    lcd.print("HAHAHAHAHAHA!!!!");
    delay(2000);
    for (int k = 0; k < 16; k++){
      lcd.scrollDisplayLeft();
      delay(50);
    }
    lcd.clear();
    loser();
    lcd.setCursor(0,0);
    lcd.print("The CPU beat you"); 
    lcd.setCursor(1,1);
    lcd.print("to 10 points!!");
    delay(5000);
    setup();
  } else {
    lcd.clear();
    lcd.setRGB(0, 255, 0);
    lcd.setCursor(2, 0);
    lcd.print("You WIN?????");
    lcd.setCursor(5,1);
    lcd.print("HOW???");
    delay(4000);
    for (int k = 0; k < 16; k++){
      lcd.scrollDisplayRight();
      delay(50);
    }
    lcd.clear();
    winner();
    lcd.setCursor(0,0);
    lcd.print("You beat the CPU"); 
    lcd.setCursor(1,1);
    lcd.print("to 10 points!!");
    delay(5000);
    setup();
  }
}

void winner() {
  for (int i = 0; i < winnerLength; i++) {
    if (win[i] == ' ') {
      delay(winBeat[i] * winTempo);
    } else {
      playNote(win[i], winBeat[i] * winTempo);
    }
    delay(winTempo / 2);
  }
}

void loser() {
  for (int i = 0; i < loserLength; i++) {
    playNote(lose[i], loseBeat[i] * loseTempo);
    delay(loseTempo / 2);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'g', 'a', 'b', 'c', 'D', 'd' };
  int tones[] = { 2551, 2273, 2033, 1915, 1805, 1706 };

  for (int i = 0; i < 6; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(buzz, HIGH);
    delayMicroseconds(tone);
    digitalWrite(buzz, LOW);
    delayMicroseconds(tone);
  }
}


