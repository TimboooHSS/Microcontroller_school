#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define MAX_ROUNDS 10 

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int ledPins[] = {2, 3, 4};
const int buttonPins[] = {8, 9, 10};
const int buzzerPin = 11;
const int gameTones[] = {262, 330, 392};
const int resetButton = 6;
int sequence[MAX_ROUNDS];
int gameStep = 0;

void(* resetFunc) (void) = 0;


void setup() {
  if(!display.begin(0x3C, true)) for(;;);
  
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(buzzerPin, OUTPUT);
  pinMode(resetButton, INPUT_PULLUP);
  randomSeed(analogRead(0));
  
  showMsg("READY?", 2);
}

void loop() {
  
  if (gameStep >= MAX_ROUNDS) {
    victory();
    return; 
  }

  int newLed;
  do {
    newLed = random(0, 3);
  } while (gameStep > 0 && newLed == sequence[gameStep - 1]);
  
  sequence[gameStep++] = newLed;
  
  displayRound(gameStep);
  delay(800);

  for (int i = 0; i < gameStep; i++) {
    playLevel(sequence[i]);
    delay(200);
  }

  for (int i = 0; i < gameStep; i++) {
    if (waitForButton() != sequence[i]) {
      gameOver();
      return;
    }
  }

  if (gameStep == MAX_ROUNDS) {
    victory();
  } else {
    delay(1000); 
  }

  if (digitalRead(resetButton) == LOW) {
    delay(50); 
    resetFunc(); 
  }
}

void displayRound(int roundNum) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(20, 20);
  display.print("Round ");
  display.print(roundNum);
  display.display();
}

void victory() {
  display.clearDisplay();
  display.setCursor(15, 20);
  display.print("YOU WIN!");
  display.display();
  
  for(int i=0; i<3; i++) {
    tone(buzzerPin, 523, 200); delay(250);
    tone(buzzerPin, 659, 200); delay(250);
  }
  
  gameStep = 0; 
  delay(3000);
  showMsg("NEW GAME", 2);
}

void showMsg(String msg, int size) {
  display.clearDisplay();
  display.setTextSize(size);
  display.setCursor(10, 25);
  display.print(msg);
  display.display();
  delay(1000);
}

void playLevel(int index) {
  digitalWrite(ledPins[index], HIGH);
  tone(buzzerPin, gameTones[index]);
  delay(300);
  digitalWrite(ledPins[index], LOW);
  noTone(buzzerPin);
}

int waitForButton() {
  while (true) {
    if (digitalRead(resetButton) == LOW) {
      resetFunc();
    }

    for (int i = 0; i < 3; i++) {
      if (digitalRead(buttonPins[i]) == LOW) {
        playLevel(i);
        while(digitalRead(buttonPins[i]) == LOW);
        return i;
      }
    }
  }
}

void gameOver() {
  display.clearDisplay();
  display.setCursor(10, 25);
  display.print("WRONG!");
  display.display();
  tone(buzzerPin, 150, 800);
  gameStep = 0;
  delay(2000);
  showMsg("TRY AGAIN", 1);
}




