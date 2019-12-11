// Different premade libraries that allows the use of certain functions
#include <FastLED.h>      
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>     
// Definition of the NEOPIXEL type
#define CHIPSET     WS2811
// Nnumberof LEDS used
#define NUM_LEDS_PER_STRIP 56
// Output of signal from the Neopixel to arduino
#define LED_PIN 6
#define COLOR_ORDER GRB
#define BRIGHTNESS  255
CRGB leds[NUM_LEDS_PER_STRIP];
// Farvetemperaturer
int color1 = 0xFF9329; // Candle
int color2 = 0xFFC58F; // Tungsten40W
int color3 = 0xFFD6AA; // Tungsten100W
int color4 = 0xFFF1E0; // Halogen
int color5 = 0xFFFAF4; // CarbonArc
int color6 = 0xFFFFFB; // HighNoonSUN
int color7 = 0xFFFFFF; // DirectSunlight
int color8 = 0xC9E2FF; // OvercastSky
int color9 = 0x409CFF; // ClearBlueSky
//OnOffSwitch
int LEDState;
int tLEDState;
int btn1Pin=2;
int tbtnlPin=11;
int buttonNew;
int buttonOld=1;
int currentColor;
boolean lastState = false;
boolean tlastState = false;
int tbuttonNew;
int tbuttonOld=1;
int colorState = 0;
// Potentiometer
int lastPotValue;
int potPin = A0; 
int Mapped;
int newMapped;
// Time
tmElements_t tm;
int currentTimedColor;
const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

void setup() {
  bool parse=false;
  bool config=false;
  pinMode (btn1Pin, INPUT_PULLUP);
  pinMode(potPin, INPUT);
  pinMode(tbtnlPin, INPUT_PULLUP);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS_PER_STRIP).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( BRIGHTNESS );
  for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
  leds[i]=CRGB::Black; 
  FastLED.show();
  }
  
  // get the date and time the compiler was run
  if (getDate(__DATE__) && getTime(__TIME__)) {
    parse = true;
    // and configure the RTC with this info
    if (RTC.write(tm)) {
      config = true;
    }
  }
  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor
  delay(200);
  if (parse && config) {
    Serial.print("DS1307 configured Time=");
    Serial.print(__TIME__);
    Serial.print(", Date=");
    Serial.println(__DATE__);
  } else if (parse) {
    Serial.println("DS1307 Communication Error :-{");
    Serial.println("Please check your circuitry");
  } else {
    Serial.print("Could not parse info from the compiler, Time=\"");
    Serial.print(__TIME__);
    Serial.print("\", Date=\"");
    Serial.print(__DATE__);
    Serial.println("\"");
  }
}

bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}

void lightadjust() {
int potValue = analogRead(potPin);
Mapped = map(potValue, 0, 1023, 0, 2000);
newMapped = Mapped / 250;
if (newMapped != lastPotValue) {
  switch(newMapped) {
  case 0:
    for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
    leds[i]=color1;
    currentColor = color1;
    colorState = 1;
    FastLED.show(); }
    Serial.println("0");
    Serial.print(colorState);
    break;
  case 1:
    for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
    leds[i]=color2;
    currentColor = color2;
    colorState = 2;
    FastLED.show(); }
    Serial.println("1");
    Serial.print(colorState);
    break;
  case 2:
    Serial.println("2");
    for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
    leds[i]=color3;
    currentColor = color3;
    colorState = 3;
    Serial.print(colorState);
    FastLED.show(); }
    break;
  case 3:
    for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
    leds[i]=color4;
    currentColor = color4;
    colorState = 4;
    FastLED.show(); }
    Serial.println("3");
    Serial.print(colorState);
    break;
  case 4:
      for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
    leds[i]=color5;
    currentColor = color5;
    colorState = 5;
    FastLED.show(); }
    Serial.println("4");
    Serial.print(colorState);
    break;
  case 5:
      for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
    leds[i]=color6;
    currentColor = color6;
    colorState = 6;
    FastLED.show(); }
    Serial.println("5");
    Serial.print(colorState);
    break;
  case 6:
    for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
    leds[i]=color7;
    currentColor = color7;
    colorState = 7;
    FastLED.show(); }
    Serial.println("6");
    Serial.print(colorState);
    break;
  case 7:
    for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
    leds[i]=color8;
    currentColor = color8;
    colorState = 8;
    FastLED.show(); }
    Serial.println("7");
    Serial.print(colorState);
    break;
  default:
    Serial.println("Error");
    break;  
    }
  lastPotValue = potValue;
    }
}

void timedLightOn(){
  RTC.read(tm);
      if(tm.Hour == 20 && tm.Minute >= 27 && tm.Minute <= 28)
      {
        Serial.println("I WORK1");
      }
      if(tm.Hour == 20 && tm.Minute >= 29 && tm.Minute <= 30)
      {
        Serial.println("I WORK2");
      }
      if(tm.Hour == 20 && tm.Minute >= 31 && tm.Minute <= 32)
      {
        Serial.println("I WORK3");
      }
      if(tm.Hour == 20 && tm.Minute >= 26 && tm.Minute <= 27)
      {
        Serial.println("I WORK4");
}
}


void timedLightRead(){
  tmElements_t tm;
  if (RTC.read(tm)) {
    Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
  }
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

void loop(){
int potValue = analogRead(potPin);
Mapped = map(potValue, 0, 1023, 0, 2000);
newMapped = Mapped / 250;
tbuttonNew = digitalRead(tbtnlPin);
buttonNew = digitalRead(btn1Pin);
timedLightRead();
RTC.read(tm);

if (tLEDState == 0) {
  RTC.read(tm);
  timedLightOn();
}


//Timed
boolean tbtnPressed = digitalRead(11);
 if (tbtnPressed == true && tlastState == false) {
    if (tLEDState==1){
      RTC.read(tm);
      timedLightOn();
      Serial.println("Timed Lights On");
      digitalWrite(LED_PIN,HIGH);
      for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
      leds[i]=CRGB::Blue;
      FastLED.show(); }
      tLEDState=0;
      LEDState=0;
      }
      else if (tLEDState == 0) {
      Serial.println("Timed Lights Off");
      digitalWrite(LED_PIN, LOW);
      for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
      leds[i]=CRGB::Black;
      FastLED.show(); }
      tLEDState=1;
      }
    }
tlastState = tbtnPressed;


// ON OFFSWITCH

boolean btnPressed = digitalRead(2);
if (LEDState == 1){
  int potValue = analogRead(potPin);
  Mapped = map(potValue, 0, 1023, 0, 2000);
  newMapped = Mapped / 250;
  lightadjust();
}

 if (btnPressed == true && lastState == false)
    {
    if (LEDState==0){
      digitalWrite(LED_PIN,HIGH);
      Serial.println("Potentiometer Lights On");
      for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
      int potValue = analogRead(potPin);
      Mapped = map(potValue, 0, 1023, 0, 2000);
      newMapped = Mapped / 250;
      leds[i]=currentColor;
      Serial.print(colorState);
      FastLED.show(); }
      LEDState=1;
      }
     else if(LEDState == 1) {
      Serial.println("Potentiometer Lights Off");
      digitalWrite(LED_PIN, LOW);
      for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
      leds[i]=CRGB::Black;
      FastLED.show(); }
      LEDState=0;
      }
    }
  lastState = btnPressed;
}
