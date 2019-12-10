
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <FastLED.h>          
#define CHIPSET     WS2811       // define the led type
#define NUM_LEDS_PER_STRIP 17   // total number of leds per strip
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
int LEDState = 0;
// Pin
int btn1Pin = 2;
//
int buttonNew;
int buttonOld = 1;
int currentColor;
int colorState = 0;
// Potentiometer
int lastPotValue;
// Pin
int potPin = A0; 
//
int Mapped;
int newMapped;
// Clock
int timedPin = 3;
//
int timedBtnOld = 1;
int timedBtnNew;
int timedLedState = 0;
// timedclockcolor var
int currentTimedColor;

// buttonmanagement
int currentTimedValue;
int currentOnOffSwitch;


const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

tmElements_t tm;
void setup() {
  bool parse=false;
  bool config=false;
  pinMode (btn1Pin, INPUT);
  pinMode(potPin, INPUT);
  pinMode(timedPin, INPUT);
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

void timedLightOn()
{


int t = __TIME__;
  tmElements_t tm;
  RTC.read(tm);
      if(tm.Hour == 2 && tm.Minute == 13)
      {
      for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
      // leds[i] = color1;
      // currentTimedColor = color1;
      leds[i]=CRGB::Blue;
      currentTimedColor = CRGB::Blue;
      Serial.println("I WORK");
      Serial.println("I WORK");
      Serial.println("I WORK");
      FastLED.show(); }
      }
      if(tm.Hour = 2 && tm.Minute == 47)
      {
       for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
      leds[i] = color3;
      currentTimedColor = color3;
      FastLED.show(); }
      }
      if(tm.Hour = 11 && tm.Minute == 44)
      {
      for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
      leds[i] = color5;
      currentTimedColor = color5;
      FastLED.show(); }
      }
      if(tm.Hour = 11 && tm.Minute == 31)
      {
      for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
      leds[i] = color7;
      currentTimedColor = color7;
      FastLED.show(); 
}
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
timedLightRead();

//Buttonmanagement
// TIMEDBUTTONMANAGEMENT
// Hvis timedtændt, tændt = sluk
if (currentTimedValue == 0 && currentOnOffSwitch == 0) 
  {
  if(currentTimedValue != currentTimedValue)
   {
  for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
  leds[i] = CRGB::Black;
  FastLED.show(); }
   }
}
// HvisTimedSlukket, tændt = tænd timedlight
if (currentTimedValue == 1 && currentOnOffSwitch == 0)
  {
    if(currentTimedValue != currentTimedValue)
    {
       timedLightOn();
    }
}
// ONOFFSWITCHMANAGEMENT
// HvisTimedtændt, tændt = sluk alt
if (currentTimedValue == 0 && currentOnOffSwitch == 0)
  {
    if(currentTimedValue != currentTimedValue)
      {
      for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
      leds[i] = CRGB::Black;
      FastLED.show(); }
    }
}
// HvisTimedSlukket, tændt = sluk alt
if (currentTimedValue == 1 && currentOnOffSwitch == 0)
  {
    if(currentTimedValue != currentTimedValue)
      {
      for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
      leds[i] = CRGB::Black;
      FastLED.show(); }
    }
}
// HvisTimedtændt, slukket = forhold timedlighttændt
if (currentTimedValue == 1 && currentOnOffSwitch == 1)
  {
    if(currentTimedValue != currentTimedValue)
      {
      for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
      leds[i] = CRGB::Black;
      FastLED.show(); }
      Serial.println("TRUUUUUUUUUUUUUEE");
      }
}

timedBtnNew=digitalRead(timedPin);
if (timedLedState == 1){
  int currentTimedValue = 0;
  for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
  timedLightOn();
  leds[i] = currentTimedColor;
  FastLED.show(); }
  Serial.println("TIMEDCURR000");
    }
if (timedLedState == 0) {
  int currentTimedValue = 1;
  for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
  leds[i] = currentColor;
  Serial.println("TIMEDCURR111");
  FastLED.show(); }
}

if(timedBtnOld==0 && timedBtnNew==1){
  if (timedLedState==0){
    digitalWrite(LED_PIN,HIGH);
    timedLedState=1;
    Serial.print(__TIME__);
    Serial.println("timebuttonon");
  } else{
    digitalWrite(LED_PIN, LOW);
    timedLedState=0;
    Serial.println("timebuttonoff");
    Serial.print(__TIME__);
  }
}
timedBtnOld=timedBtnNew;


/// onOffSwitch();
buttonNew=digitalRead(btn1Pin);
if (LEDState == 1){
  int potValue = analogRead(potPin);
  Mapped = map(potValue, 0, 1023, 0, 2000);
  newMapped = Mapped / 250;
  lightadjust();
   
}

if(buttonOld==0 && buttonNew==1){
  if (LEDState==0){
    digitalWrite(LED_PIN,HIGH);
    LEDState=1;
    currentOnOffSwitch = 0;
    Serial.println("currentOnOffSwitch = 0");
    Serial.println("on");
    Serial.print(__TIME__);
    for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
    int potValue = analogRead(potPin);
    Mapped = map(potValue, 0, 1023, 0, 2000);
    newMapped = Mapped / 250;
    leds[i]=currentColor;
    Serial.print(colorState);
    FastLED.show(); }
    
  } else{
    digitalWrite(LED_PIN, LOW);
    LEDState=0;
    currentOnOffSwitch = 1;
    Serial.println("currentOnOffSwitch = 1");
    Serial.println("off");
    Serial.print(__TIME__);
    for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
    leds[i]=CRGB::Black;
    FastLED.show(); }
  }
}
buttonOld=buttonNew;
}
