// LED sequencer and brightness with potentiometer

// constants:
const int ledPinR = 11;
const int ledPinG = 10;
const int ledPinB = 9;
const int buttonPin = 8;
const int intervalPin = A4;
const int brightnessPin = A5;
const bool isCommonCathode = false;

// globale variables:
bool ledOnR = false;
bool ledOnG = false;
bool ledOnB = false;
bool buttonPressed = false;

int flashState = 0;
int mode =  0;
unsigned long lastTime = 0;
int brightness = 255;

void setup() {
  // initialize the digital pins as an output.
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  
  digitalWrite(buttonPin, HIGH);
  Serial.begin(115200);

  setRed(false);
  setGreen(false);
  setBlue(false);
  
  for ( int i = 0; i < 3; i++) {
    setGreen(true);
    delay(250);
    setGreen(false);
    delay(250);
  }
  delay(500); 
}


void loop() {
  int interval = 100 + analogRead(intervalPin);
  unsigned long currentTime = millis();
  if (currentTime - lastTime < interval) return;
  // save 
  lastTime = currentTime;

  Serial.print("interval = ");
  Serial.print(interval);
  
  brightness = map(analogRead(brightnessPin), 0, 1023, 0, 255);
  Serial.print(", brightness = ");
  Serial.print(brightness);

  switch (getMode()) {
    case 0:  mode0(); break;
    case 1:  mode1(); break;
  }
  Serial.println();
}

void mode0() {
  Serial.print( ", flashState = ");
  Serial.print( flashState);
  switch (flashState) {
    case 0:
      setBlue(false);
      setRed(true);
      break;
    case 1:
      setRed(false);
      setGreen(true);
      break;
    case 2:
      setGreen(false);
      setBlue(true);
      break;
  }
  flashState = (flashState + 1) % 3;
}

void mode1() {
  Serial.print( ", flashState = ");
  Serial.print( flashState);
  switch (flashState) {
    case 0:
      setRed(true);
      break;
    case 1:
      setRed(false);
      break;
    case 2:
      setGreen(true);
      break;
    case 3:
      setGreen(false);
      break;
    case 4:
      setBlue(true);
      break;
    case 5:
      setBlue(false);
      break;
  }
  flashState = (flashState + 1) % 6;
}

void setRed(bool on) {
  Serial.print(" red ");
  Serial.print(on);
  ledOnR = on;
  if ( on)  analogWrite(ledPinR, isCommonCathode ? brightness : 255 - brightness);
  else      analogWrite(ledPinR, isCommonCathode ? 0 : 255);
  //  if (on)  digitalWrite(ledPinR, isCommonCathode ? HIGH : LOW);
  //  else      digitalWrite(ledPinR, isCommonCathode ? LOW : HIGH);
}

void setGreen(bool on) {
  Serial.print(" green ");
  Serial.print(on);
  ledOnG = on;
  if ( on)  analogWrite(ledPinG, isCommonCathode ? brightness : 255 - brightness);
  else      analogWrite(ledPinG, isCommonCathode ? 0 : 255);
  //  if (on)  digitalWrite(ledPinG, isCommonCathode ? HIGH : LOW);
  //  else      digitalWrite(ledPinG, isCommonCathode ? LOW : HIGH);
}

void setBlue(bool on) {
  Serial.print(" blue ");
  Serial.print(on);
  ledOnB = on;
  if ( on)  analogWrite(ledPinB, isCommonCathode ? brightness : 255 - brightness);
  else      analogWrite(ledPinB, isCommonCathode ? 0 : 255);
  //  if (on)  digitalWrite(ledPinB, isCommonCathode ? HIGH : LOW);
  //  else      digitalWrite(ledPinB, isCommonCathode ? LOW : HIGH);
}

int getMode() {
  if (!digitalRead(buttonPin)) {
    if (! buttonPressed) {
      mode = (mode + 1) % 2;
      flashState = 0;
      buttonPressed = true;
      delay(10);
    }
  }
  else {
    buttonPressed = false;
  }
  Serial.print( ", mode = "); 
  Serial.print( mode);
  return mode;
}
