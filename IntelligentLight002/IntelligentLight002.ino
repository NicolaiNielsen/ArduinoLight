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
int LEDState=0;
int btn1Pin=2;
int buttonNew;
int buttonOld=1;
int dt=100;
int currentColor;
int colorState = 0;
// Potentiometer
int lastPotValue;
int potPin = A0; 
int Mapped;
int newMapped;

void setup() {
  Serial.begin(9600);
  pinMode (btn1Pin, INPUT);
  pinMode(potPin, INPUT);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS_PER_STRIP).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( BRIGHTNESS );
  for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
  leds[i]=CRGB::Black; 
  FastLED.show();
  }
}

void loop(){
int potValue = analogRead(potPin);
Serial.print("Original Value =  ");
Serial.println(potValue);
Mapped = map(potValue, 0, 1023, 0, 2000);
newMapped = Mapped / 250;
Serial.print("Mapped Value =  ");
Serial.println(Mapped);
Serial.println(" ");

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
    Serial.println("on");
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
    Serial.println("off");
    for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
    leds[i]=CRGB::Black;
    FastLED.show(); }
  }
}
buttonOld=buttonNew;
}


void lightadjust() {
int potValue = analogRead(potPin);
Serial.print("Original Value =  ");
Serial.println(potValue);
Mapped = map(potValue, 0, 1023, 0, 2000);
newMapped = Mapped / 250;
Serial.print("Mapped Value =  ");
Serial.println(Mapped);
Serial.println(" ");
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
