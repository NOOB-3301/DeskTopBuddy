#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- SYSTEM STATES ---
enum State { STATE_IDLE, STATE_MENU };
State currentState = STATE_IDLE; // Start in Idle Mode

// Menu items configuration
const char* menuItems[] = {
  "Sys Info",
  "Timer",
  "Weather",
  "Music"
};
const int TOTAL_ITEMS = 4;
int selectedMenuIndex = 0;



//Button state -> It is pin now
const int inputStatePin = 2;

//CENTERED BUTTON MENU FUNCTION
void drawCenteredMenu(int selectedIndex) {
  display.clearDisplay();
  
  int yOffset = 4;
  int itemHeight = 14;
  int buttonWidth = 90; // Reduced border width
  int buttonRadius = 3;
  int buttonX = (SCREEN_WIDTH - buttonWidth) / 2;

  for (int i = 0; i < TOTAL_ITEMS; i++) {
    int yPos = yOffset + (i * itemHeight);

    if (i == selectedIndex) {
      display.fillRoundRect(buttonX, yPos, buttonWidth, itemHeight - 2, buttonRadius, SSD1306_WHITE);
      display.setTextColor(SSD1306_BLACK);
    } else {
      display.drawRoundRect(buttonX, yPos, buttonWidth, itemHeight - 2, buttonRadius, SSD1306_WHITE);
      display.setTextColor(SSD1306_WHITE);
    }

    int textWidth = strlen(menuItems[i]) * 6;
    int textX = (SCREEN_WIDTH - textWidth) / 2;
    int textY = yPos + 2;

    display.setCursor(textX, textY);
    display.print(menuItems[i]);
  }

  display.display();
}

// --- 2. EILIK IDLE EXPRESSIONS ---
void drawHappyUWU() {
  display.fillCircle(40, 26, 12, SSD1306_WHITE);
  display.fillCircle(40, 30, 12, SSD1306_BLACK);
  display.fillCircle(88, 26, 12, SSD1306_WHITE);
  display.fillCircle(88, 30, 12, SSD1306_BLACK);
  display.drawCircle(58, 42, 6, SSD1306_WHITE);
  display.drawCircle(70, 42, 6, SSD1306_WHITE);
  display.fillRect(52, 36, 24, 6, SSD1306_BLACK);
}

void drawAnnoyed() {
  display.fillTriangle(26, 18, 48, 28, 26, 34, SSD1306_WHITE);
  display.fillTriangle(26, 22, 42, 28, 26, 30, SSD1306_BLACK);
  display.fillTriangle(102, 18, 80, 28, 102, 34, SSD1306_WHITE);
  display.fillTriangle(102, 22, 86, 28, 102, 30, SSD1306_BLACK);
  display.drawRoundRect(50, 42, 28, 12, 3, SSD1306_WHITE);
  display.drawLine(50, 48, 77, 48, SSD1306_WHITE);
  display.drawLine(59, 42, 59, 53, SSD1306_WHITE);
  display.drawLine(68, 42, 68, 53, SSD1306_WHITE);
}

void drawShy() {
  display.fillRoundRect(32, 22, 22, 16, 8, SSD1306_WHITE);
  display.fillRoundRect(74, 22, 22, 16, 8, SSD1306_WHITE);
  display.drawLine(30, 42, 42, 42, SSD1306_WHITE);
  display.drawLine(86, 42, 98, 42, SSD1306_WHITE);
  display.drawCircle(64, 40, 5, SSD1306_WHITE);
  display.fillRect(58, 35, 12, 5, SSD1306_BLACK);
}

void drawAngry() {
  display.fillRoundRect(30, 22, 24, 18, 6, SSD1306_WHITE);
  display.fillTriangle(30, 22, 54, 22, 30, 32, SSD1306_BLACK);
  display.fillRoundRect(74, 22, 24, 18, 6, SSD1306_WHITE);
  display.fillTriangle(74, 22, 98, 22, 98, 32, SSD1306_BLACK);
  display.drawCircle(64, 52, 8, SSD1306_WHITE);
  display.fillRect(52, 52, 24, 10, SSD1306_BLACK);
}

void drawCrying() {
  display.fillRoundRect(30, 22, 22, 16, 8, SSD1306_WHITE);
  display.fillRoundRect(76, 22, 22, 16, 8, SSD1306_WHITE);
  display.fillCircle(35, 46, 3, SSD1306_WHITE);
  display.fillCircle(93, 46, 3, SSD1306_WHITE);
  display.drawLine(56, 44, 64, 42, SSD1306_WHITE);
  display.drawLine(64, 42, 72, 44, SSD1306_WHITE);
}

void drawSleepy() {
  display.fillRoundRect(30, 24, 24, 16, 8, SSD1306_WHITE);
  display.fillRect(30, 24, 24, 8, SSD1306_BLACK);
  display.fillRoundRect(74, 24, 24, 16, 8, SSD1306_WHITE);
  display.fillRect(74, 24, 24, 8, SSD1306_BLACK);
  display.fillCircle(64, 46, 6, SSD1306_WHITE);
  display.setCursor(102, 12);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("zZ");
}

void drawPlayfulWink() {
  display.fillRoundRect(30, 20, 24, 20, 10, SSD1306_WHITE);
  display.fillCircle(36, 24, 3, SSD1306_BLACK);
  display.drawLine(74, 30, 98, 30, SSD1306_WHITE);
  display.drawLine(74, 31, 98, 31, SSD1306_WHITE);
  display.drawCircle(60, 40, 7, SSD1306_WHITE);
  display.fillRect(52, 33, 16, 7, SSD1306_BLACK);
}

void drawNormal() {
  display.fillRoundRect(30, 18, 24, 22, 10, SSD1306_WHITE);
  display.fillRoundRect(74, 18, 24, 22, 10, SSD1306_WHITE);
  display.fillCircle(64, 44, 3, SSD1306_WHITE);
}

void drawEilikIdleAnimation(unsigned long idleTimeMs) {
  display.clearDisplay();
  int animationStep = (idleTimeMs / 3500) % 8;

  switch (animationStep) {
    case 0: drawHappyUWU();     break;
    case 1: drawAnnoyed();      break;
    case 2: drawNormal();       break;
    case 3: drawShy();          break;
    case 4: drawPlayfulWink();  break;
    case 5: drawSleepy();       break;
    case 6: drawAngry();        break;
    case 7: drawCrying();       break;
  }
  display.display();
}


// --- SETUP & MAIN LOOP ---
void setup() {
  pinMode(inputStatePin, INPUT_PULLUP);
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.println("Oled initialized");
  delay(1000);
  display.display();
  display.clearDisplay();
}

int currentPinState;
int lastPinState =HIGH;
int stateIndex=0;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50; 

bool changeDetected= false;
void loop() {
  currentPinState = digitalRead(inputStatePin);
  if (lastPinState == HIGH && currentPinState == LOW) {
    lastDebounceTime = millis();
    changeDetected= true;
  }

  if (changeDetected && (millis()-lastDebounceTime) > debounceDelay) {

    if( currentPinState == LOW) {
      Serial.println("State Changed");
      stateIndex ++;
      if(stateIndex > TOTAL_ITEMS-1){
        stateIndex=0;
      }
      drawCenteredMenu(stateIndex);
      changeDetected = true;
    }
    // stateIndex = initialState;
    drawCenteredMenu(stateIndex);
    changeDetected= false;
    // delay(1000);
    
  }
  lastPinState = currentPinState;
}