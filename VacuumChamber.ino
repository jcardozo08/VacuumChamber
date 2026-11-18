#include <Wire.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_BMP280.h>


// =====================================================
// CONFIGURATIONS
// =====================================================
#define SCREEN_ON 0
#define DEBUG_PRINTS 0

// =====================================================
// DISPLAY
// =====================================================
MCUFRIEND_kbv tft;

#define TFT_ID 0x7783

#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F
#define YELLOW  0xFFE0
#define CYAN    0x07FF
#define MAGENTA 0xF81F


// =====================================================
// BUTTONS
// =====================================================
#define BTN_LEFT   22
#define BTN_CENTER 23
#define BTN_RIGHT  24

// =====================================================
// MOTOR
// =====================================================
#define MOTOR_PIN 3

uint8_t motorPWM = 255;
bool motorRunning = false;

// =====================================================
// BMP280
// =====================================================
Adafruit_BMP280 bmp;

bool bmpOK = false;

float pressurePa = 0.0f;
float temperatureC = 0.0f;
float heightM = 0.0f;
float referencePressurePa = 101325.0f;

unsigned long lastSensorUpdate = 0;
const unsigned long SENSOR_PERIOD_MS = 200;

// =====================================================
// DISPLAY / ANIMATION UPDATE
// =====================================================
unsigned long lastRunValuesUpdate = 0;
const unsigned long RUN_VALUES_PERIOD_MS = 200;

unsigned long lastAnimationUpdate = 0;
const unsigned long ANIMATION_PERIOD_MS = 42;

// =====================================================
// BUTTON DEBOUNCE
// =====================================================
unsigned long lastButtonTime = 0;
const unsigned long BUTTON_DEBOUNCE_MS = 150;

// =====================================================
// SCREEN STATES
// =====================================================
enum Screen {
  SCREEN_CONFIG = 0,
  SCREEN_MAIN   = 1,
  SCREEN_RUN    = 2
};

Screen currentScreen = SCREEN_MAIN;
// Different initial value forces MAIN to be drawn after splash.
Screen previousScreen = SCREEN_CONFIG;

// =====================================================
// FUNCTION PROTOTYPES
// =====================================================
void readButtons();
void readSerialControl();
void processInput(char input);

void enterScreen(Screen screen);
void mainScreen();
void configScreen();
void runScreen();

void updateSensors();
void updateRunTextBuffers();
void updateRunValuesOnScreen();

void updateMotor();
void sendStart();
void sendConfirmation();

// =========================
// LOPAKA GENERATED CODE
// =========================

void drawMain1(void) {
    tft.fillScreen(0x0);
}

// [BEGIN lopaka generated]
#include "FreeMono12pt7b.h"
#include "FreeMonoBold9pt7b.h"

static const unsigned char PROGMEM image_ButtonRightSmall_bits[] = {0xf8,0x00,0xf8,0x00,0xf8,0x00,0xf8,0x00,0xf8,0x00,0xff,0xc0,0xff,0xc0,0xff,0xc0,0xff,0xc0,0xff,0xc0,0xff,0xfe,0xff,0xfe,0xff,0xfe,0xff,0xfe,0xff,0xfe,0xff,0xc0,0xff,0xc0,0xff,0xc0,0xff,0xc0,0xff,0xc0,0xf8,0x00,0xf8,0x00,0xf8,0x00,0xf8,0x00,0xf8,0x00};

void drawConfig(void) {
    tft.fillScreen(0x0);
    // string 4
    tft.setTextColor(0xFFFF);
    tft.setTextWrap(false);
    tft.setCursor(249, 229);
    tft.print("SW by: john");
    // ButtonRightSmall
    tft.drawBitmap(295, 114, image_ButtonRightSmall_bits, 15, 25, 0xFFFF);
    // Title
    tft.setFont(&FreeMono12pt7b);
    tft.setCursor(57, 29);
    tft.print("Configuration");
    // string 16
    tft.setFont(&FreeMonoBold9pt7b);
    tft.setCursor(718, 74);
    tft.print("Height:");
    // string 29
    tft.setCursor(12, 76);
    tft.print("Flight Mode");
    // string 29
    tft.setCursor(9, 186);
    tft.print("Control Mode");
}


// [BEGIN lopaka generated]
#include "FreeMono12pt7b.h"
#include "FreeMonoBold9pt7b.h"

static const unsigned char PROGMEM image_ButtonLeftSmall_bits[] = {0x00,0x3e,0x00,0x3e,0x00,0x3e,0x00,0x3e,0x00,0x3e,0x07,0xfe,0x07,0xfe,0x07,0xfe,0x07,0xfe,0x07,0xfe,0xff,0xfe,0xff,0xfe,0xff,0xfe,0xff,0xfe,0xff,0xfe,0x07,0xfe,0x07,0xfe,0x07,0xfe,0x07,0xfe,0x07,0xfe,0x00,0x3e,0x00,0x3e,0x00,0x3e,0x00,0x3e,0x00,0x3e};


void drawMain2(void) {
    tft.fillScreen(0x0);
    // string 4
    tft.setTextColor(0xFFFF);
    tft.setTextWrap(false);
    tft.setCursor(249, 229);
    tft.print("SW by: john");
    // ButtonRightSmall
    tft.drawBitmap(295, 114, image_ButtonRightSmall_bits, 15, 25, 0xFFFF);
    // ButtonLeftSmall
    tft.drawBitmap(6, 114, image_ButtonLeftSmall_bits, 15, 25, 0xFFFF);
    // Title
    tft.setFont(&FreeMono12pt7b);
    tft.setCursor(-318, 29);
    tft.print("URD Vacuum Chamber");
    // Title
    tft.setCursor(34, 29);
    tft.print("URD Vacuum Chamber");
    // string 13
    tft.setFont(&FreeMonoBold9pt7b);
    tft.setCursor(30, 131);
    tft.print("Config");
    // string 13
    tft.setCursor(253, 131);
    tft.print("Run");
}


// [BEGIN lopaka generated]
#include "FreeMono12pt7b.h"
#include "FreeMonoBold9pt7b.h"


#include "pause_64_64_28f.h"
char height_text[18]   = "0.0 m";
char pressure_text[20] = "0 Pa";
char pwm_text[10]      = "0";
char temp_text[16]     = "0.0 C";

void updateAnimations() {
    pause_64_64_28f_frame = millis() / 42 % 28;
}

void drawAnimation_pause_64_64_28f(void) {
    tft.drawBitmap(255, 87, pause_64_64_28f_frames[pause_64_64_28f_frame], 64, 64, 0xFFFF, 0x0);
}

void drawAnimations() {
    updateAnimations();
    drawAnimation_pause_64_64_28f();
}


void drawRun(void) {
    tft.fillScreen(0x0);
    // string 4
    tft.setTextColor(0xFFFF);
    tft.setTextWrap(false);
    tft.setCursor(249, 229);
    tft.print("SW by: john");
    // ButtonLeftSmall
    tft.drawBitmap(6, 114, image_ButtonLeftSmall_bits, 15, 25, 0xFFFF);
    // Title
    tft.setFont(&FreeMono12pt7b);
    tft.setCursor(106, 29);
    tft.print("Running");
    // press_text
    tft.setFont(&FreeMonoBold9pt7b);
    tft.setCursor(6, 49);
    tft.print("Pressure:");
    // height_text
    tft.setCursor(7, 67);
    tft.print("Height:");
    // temp_text
    tft.setCursor(219, 49);
    tft.print("Temp:");
    // pwm_text
    tft.setCursor(220, 67);
    tft.print("PWM:");
    // pressure
    tft.setTextColor(0xFFFF, 0x24BE);
    tft.setCursor(105, 50);
    tft.print(pressure_text);
    // pwm
    tft.setTextColor(0xFFFF, 0xCEE7);
    tft.setCursor(265, 68);
    tft.print(pwm_text);
    // height
    tft.setTextColor(0xFFFF, 0x61D6);
    tft.setCursor(84, 69);
    tft.print(height_text);
    // temp
    tft.setTextColor(0xFFFF, 0xE8EC);
    tft.setCursor(271, 51);
    tft.print(temp_text);
    // line 24
    tft.drawLine(-708, -278, -708, -278, 0xCEE7);
    // line 25
    tft.drawLine(54, 85, 54, 222, 0xCEE7);
    // line 26
    tft.drawLine(37, 200, 253, 200, 0xCEE7);
    // triangle 27
    tft.fillTriangle(54, 78, 50, 85, 58, 85, 0xCEE7);
}

// [END lopaka generated]


// =====================================================
// SETUP
// =====================================================
void setup() {
  Serial.begin(115200);
  delay(300);

  Serial.println();
  Serial.println(F("================================"));
  Serial.println(F(" URD Vacuum Chamber"));
  Serial.println(F(" Mega + MCUFRIEND 0x7783"));
  Serial.println(F("================================"));

  // -------------------------
  // Buttons
  // -------------------------
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_CENTER, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);

  // -------------------------
  // Motor PWM
  // -------------------------
  pinMode(MOTOR_PIN, OUTPUT);
  analogWrite(MOTOR_PIN, 0);

  // -------------------------
  // BMP280 / I2C
  // Mega: SDA = 20, SCL = 21
  // -------------------------
  Wire.begin();

  bmpOK = bmp.begin(0x76);

  if (!bmpOK) {
    bmpOK = bmp.begin(0x77);
  }

  if (bmpOK) {
    // Moderate filtering/oversampling for a stable chamber reading.
    bmp.setSampling(
      Adafruit_BMP280::MODE_NORMAL,
      Adafruit_BMP280::SAMPLING_X2,
      Adafruit_BMP280::SAMPLING_X16,
      Adafruit_BMP280::FILTER_X16,
      Adafruit_BMP280::STANDBY_MS_63
    );

    delay(150);

    referencePressurePa = bmp.readPressure();

    Serial.print(F("[BMP280] OK | P0 = "));
    Serial.print(referencePressurePa, 1);
    Serial.println(F(" Pa"));
  } else {
    Serial.println(F("[BMP280] NOT FOUND at 0x76 or 0x77"));
  }

  // -------------------------
  // TFT
  // -------------------------

  uint16_t detectedID = tft.readID();

  Serial.print(F("[TFT] detected ID = 0x"));
  Serial.println(detectedID, HEX);

  // The tested shield reports 0x7783.
  tft.begin(TFT_ID);
  tft.setRotation(3);
  tft.fillScreen(BLACK);

  // -------------------------
  // Splash
  // -------------------------
  drawMain1();
  delay(2000);

  // Force initial MAIN draw.
  previousScreen = SCREEN_CONFIG;
  currentScreen = SCREEN_MAIN;

  Serial.println(F("[SERIAL] E=left | C=center | D=right"));
}


// =====================================================
// MAIN LOOP
// =====================================================
void loop() {
  readButtons();
  readSerialControl();

  updateSensors();
  updateMotor();

  if (currentScreen != previousScreen) {
    enterScreen(currentScreen);
    previousScreen = currentScreen;
  }

  switch (currentScreen) {
    case SCREEN_CONFIG:
      configScreen();
      break;

    case SCREEN_MAIN:
      mainScreen();
      break;

    case SCREEN_RUN:
      runScreen();
      break;
  }
}


// =====================================================
// INPUT PROCESSING
// =====================================================
void processInput(char input) {
  // LEFT
  if (input == 'E') {
    Serial.println(F("[INPUT] LEFT"));

    if (currentScreen == SCREEN_RUN) {
      currentScreen = SCREEN_MAIN;
    } else if (currentScreen == SCREEN_MAIN) {
      currentScreen = SCREEN_CONFIG;
    }

    return;
  }

  // RIGHT
  if (input == 'D') {
    Serial.println(F("[INPUT] RIGHT"));

    if (currentScreen == SCREEN_CONFIG) {
      currentScreen = SCREEN_MAIN;
    } else if (currentScreen == SCREEN_MAIN) {
      currentScreen = SCREEN_RUN;
    }

    return;
  }

  // CENTER
  if (input == 'C') {
    Serial.println(F("[INPUT] CENTER"));

    if (currentScreen == SCREEN_RUN) {
      sendStart();
    } else if (currentScreen == SCREEN_CONFIG) {
      sendConfirmation();
    }

    return;
  }
}


// =====================================================
// PHYSICAL BUTTONS
// =====================================================
void readButtons() {
  if ((millis() - lastButtonTime) < BUTTON_DEBOUNCE_MS) {
    return;
  }

  if (digitalRead(BTN_LEFT) == LOW) {
    lastButtonTime = millis();
    processInput('E');
    return;
  }

  if (digitalRead(BTN_CENTER) == LOW) {
    lastButtonTime = millis();
    processInput('C');
    return;
  }

  if (digitalRead(BTN_RIGHT) == LOW) {
    lastButtonTime = millis();
    processInput('D');
    return;
  }
}


// =====================================================
// SERIAL CONTROL
// =====================================================
void readSerialControl() {
  while (Serial.available() > 0) {
    char c = Serial.read();

    if (c >= 'a' && c <= 'z') {
      c = c - ('a' - 'A');
    }

    if (c == 'E' || c == 'C' || c == 'D') {
      processInput(c);
    }
  }
}


// =====================================================
// SCREEN ENTRY
// =====================================================
void enterScreen(Screen screen) {
  tft.fillScreen(BLACK);
  tft.setFont(NULL);
  tft.setTextWrap(false);

  switch (screen) {
    case SCREEN_CONFIG:
      Serial.println(F("[SCREEN] CONFIG"));
      drawConfig();
      break;

    case SCREEN_MAIN:
      Serial.println(F("[SCREEN] MAIN"));
      drawMain2();
      break;

    case SCREEN_RUN:
      Serial.println(F("[SCREEN] RUN"));
      updateRunTextBuffers();
      drawRun();

      // Force immediate first dynamic refresh.
      lastRunValuesUpdate = 0;
      lastAnimationUpdate = 0;
      break;
  }
}


// =====================================================
// SCREEN LOGIC
// =====================================================
void mainScreen() {
  // Static screen: draw only on entry.
}

void configScreen() {
  // Static for now.
  // sendConfirmation() is the placeholder for future parameter editing.
}

void runScreen() {
  unsigned long now = millis();

  // Only redraw the value areas, not the whole screen.
  if ((now - lastRunValuesUpdate) >= RUN_VALUES_PERIOD_MS) {
    lastRunValuesUpdate = now;
    updateRunTextBuffers();
    updateRunValuesOnScreen();
  }

  // Lopaka pause/resume animation.
  if ((now - lastAnimationUpdate) >= ANIMATION_PERIOD_MS) {
    lastAnimationUpdate = now;
    drawAnimations();
  }
}


// =====================================================
// SENSOR ACQUISITION
// =====================================================
void updateSensors() {
  if (!bmpOK) {
    return;
  }

  unsigned long now = millis();

  if ((now - lastSensorUpdate) < SENSOR_PERIOD_MS) {
    return;
  }

  lastSensorUpdate = now;

  pressurePa = bmp.readPressure();
  temperatureC = bmp.readTemperature();

  // Relative barometric "height" referenced to pressure at startup.
  // Useful here as an equivalent pressure altitude change.
  if (pressurePa > 0.0f && referencePressurePa > 0.0f) {
    heightM =
      44330.0f *
      (1.0f - pow(pressurePa / referencePressurePa, 0.1903f));
  }

  Serial.print(F("[SENSOR] P="));
  Serial.print(pressurePa, 0);
  Serial.print(F(" Pa | T="));
  Serial.print(temperatureC, 1);
  Serial.print(F(" C | H="));
  Serial.print(heightM, 1);
  Serial.print(F(" m | PWM="));
  Serial.print(motorRunning ? motorPWM : 0);
  Serial.print(F(" | MOTOR="));
  Serial.println(motorRunning ? F("ON") : F("OFF"));
}


// =====================================================
// CONVERT VALUES TO LOPAKA TEXT BUFFERS
// =====================================================
void updateRunTextBuffers() {
  if (bmpOK) {
    char numberBuffer[14];

    dtostrf(pressurePa, 1, 0, numberBuffer);
    snprintf(pressure_text, sizeof(pressure_text), "%s Pa", numberBuffer);

    dtostrf(heightM, 1, 1, numberBuffer);
    snprintf(height_text, sizeof(height_text), "%s m", numberBuffer);

    dtostrf(temperatureC, 1, 1, numberBuffer);
    snprintf(temp_text, sizeof(temp_text), "%s C", numberBuffer);
  } else {
    strncpy(pressure_text, "SENSOR ERR", sizeof(pressure_text));
    pressure_text[sizeof(pressure_text) - 1] = '\0';

    strncpy(height_text, "--.- m", sizeof(height_text));
    height_text[sizeof(height_text) - 1] = '\0';

    strncpy(temp_text, "--.- C", sizeof(temp_text));
    temp_text[sizeof(temp_text) - 1] = '\0';
  }

  snprintf(
    pwm_text,
    sizeof(pwm_text),
    "%u",
    motorRunning ? motorPWM : 0
  );
}


// =====================================================
// PARTIAL RUN-SCREEN REFRESH
// =====================================================
void updateRunValuesOnScreen() {
  tft.setFont(&FreeMonoBold9pt7b);

  // Pressure
  tft.fillRect(100, 34, 115, 20, 0x24BE);
  tft.setTextColor(WHITE, 0x24BE);
  tft.setCursor(105, 50);
  tft.print(pressure_text);

  // PWM
  tft.fillRect(260, 52, 60, 20, 0xCEE7);
  tft.setTextColor(WHITE, 0xCEE7);
  tft.setCursor(265, 68);
  tft.print(pwm_text);

  // Height
  tft.fillRect(80, 53, 120, 20, 0x61D6);
  tft.setTextColor(WHITE, 0x61D6);
  tft.setCursor(84, 69);
  tft.print(height_text);

  // Temperature
  tft.fillRect(266, 35, 54, 20, 0xE8EC);
  tft.setTextColor(WHITE, 0xE8EC);
  tft.setCursor(271, 51);
  tft.print(temp_text);
}


// =====================================================
// MOTOR
// =====================================================
void updateMotor() {
  analogWrite(
    MOTOR_PIN,
    motorRunning ? motorPWM : 0
  );
}

void sendStart() {
  motorRunning = !motorRunning;

  updateMotor();
  updateRunTextBuffers();

  Serial.print(F("[MOTOR] "));
  Serial.print(motorRunning ? F("ON") : F("OFF"));
  Serial.print(F(" | PWM="));
  Serial.println(motorRunning ? motorPWM : 0);

  // Immediate visible update while on RUN.
  if (currentScreen == SCREEN_RUN) {
    updateRunValuesOnScreen();
  }
}


// =====================================================
// CONFIG CONFIRMATION
// =====================================================
void sendConfirmation() {
  Serial.println(F("[CONFIG] CENTER pressed - dummy confirmation"));
}


// =====================================================
// FUTURE HEIGHT GRAPH FUNCTIONS
// =====================================================
// Add the mini-graph here later without changing the navigation/sensor layer.
