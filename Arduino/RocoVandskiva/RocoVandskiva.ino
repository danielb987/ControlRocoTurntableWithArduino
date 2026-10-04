/*
 * Flatkabel till Roco vändskiva
 * Svart:  Räl hytt
 * Brun:   
 * Röd:    Detektering spårläge
 * Orange: Motor
 * Gul:    Detektering spårläge
 * Grön:   Motor
 * Blå:    
 * Lila:   Räl ej hytt
 * 
 * 
 * Svart: GND
 * Blå:   +5v
 * Röd:   A0, 14, Relä på/av
 * Grön:  A1, 15, Relä riktning
 * 
 * Sladd till strömbrytare och lysdiod
 * Svart:  GND
 * Grön:   A2, D16
 * Gul:    A3, D17
 * Orange: A4, D18
 */




const int INTERNAL_LED = 13;               // PB5
const int RELAY_ON_OFF = 14;      // PC0, Röd
const int RELAY_DIRECTION = 15;   // PC1, Grön
const int RELAY_ON = LOW;
const int RELAY_OFF = HIGH;
const bool LEFT = true;
const bool RIGHT = false;

const int BUTTON_LEFT = 16;
const int BUTTON_RIGHT= 17;
const int LED_BUTTON = 18;
const int TRACK_DETECTION = 19;

const long MAX_UNSIGNED_LONG = 0xFFFFFFFFL;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // put your setup code here, to run once:
  digitalWrite(INTERNAL_LED, LOW);
  pinMode(INTERNAL_LED, OUTPUT);
  digitalWrite(RELAY_ON_OFF, RELAY_OFF);
  digitalWrite(RELAY_DIRECTION, RELAY_OFF);
  pinMode(RELAY_ON_OFF, OUTPUT);
  pinMode(RELAY_DIRECTION, OUTPUT);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(LED_BUTTON, OUTPUT);
  pinMode(TRACK_DETECTION, INPUT_PULLUP);
}




bool buttonLeftIsDown = false;
bool buttonRightIsDown = false;
bool trackDetectionInput = false;
long buttonLeftCount = 0;
long buttonRightCount = 0;
long trackDetectionInputCount = 0;

bool isRunning = false;
bool isRunningLeft = true;
unsigned long counter = 0;
unsigned long lastCounter = 0;
bool waitForTrackDetectionOff = false;

bool ledIsOn = false;
int ledCount = 0;



long timeDiff(long first, long second) {
  return second - first;
}


void checkKeys() {
  if (digitalRead(BUTTON_LEFT) == LOW) {
    buttonLeftIsDown = true;
    buttonLeftCount = counter;
  } else if (timeDiff(buttonLeftCount,counter) > 5) {   // 50 ms
    buttonLeftIsDown = false;
  }

  if (digitalRead(BUTTON_RIGHT) == LOW) {
    buttonRightIsDown = true;
    buttonRightCount = counter;
  } else if (timeDiff(buttonRightCount,counter) > 5) {   // 50 ms
    buttonRightIsDown = false;
  }

  if (digitalRead(TRACK_DETECTION) == LOW) {
    trackDetectionInput = true;
    trackDetectionInputCount = counter;
  } else if (timeDiff(trackDetectionInputCount,counter) > 50) {   // 500 ms
    trackDetectionInput = false;
  }
}



char lastChar = 0;

void printChar(int ch) {
  if (lastChar == ch) return;
  Serial.write(ch);
  lastChar = ch;
}



void startTurntable(bool direction) {
  
  digitalWrite(RELAY_DIRECTION, direction ? RELAY_OFF : RELAY_ON);
  
  delay(10);  // Give some time before turning on power after the relay for the direction has been set.
  
  digitalWrite(RELAY_ON_OFF, RELAY_ON);
  
  isRunning = true;
  isRunningLeft = direction;
  waitForTrackDetectionOff = true;
  ledIsOn = false;
  ledCount = 0;
  
  digitalWrite(LED_BUTTON, LOW);
}


void stopTurntable() {
  digitalWrite(RELAY_ON_OFF, RELAY_OFF);
  isRunning = false;
  delay(10);
}


void setLed() {
  ledCount++;
  if (ledCount > 25) {
    if (ledIsOn) {
      ledIsOn = false;
      digitalWrite(LED_BUTTON, LOW);
    } else {
      ledIsOn = true;
      digitalWrite(LED_BUTTON, HIGH);
    }
    ledCount = 0;
  }
}


bool getTrackDetection() {
  bool trackDetection = trackDetectionInput;
  
  if (!trackDetection) {
    waitForTrackDetectionOff = false;
  }
  
  if (waitForTrackDetectionOff) {
    trackDetection = false;
  }

  return trackDetection;
}


void loop() {

  delay(10);  // 10 ms
  counter++;

  checkKeys();

  if (buttonLeftIsDown || buttonRightIsDown) {
    waitForTrackDetectionOff = true;
  }
  
  if (isRunning) {

    setLed();

    if (!buttonLeftIsDown && !buttonRightIsDown && getTrackDetection()) {
      stopTurntable();
    } else if (buttonLeftIsDown && !isRunningLeft) {
      stopTurntable();
    } else if (buttonRightIsDown && isRunningLeft) {
      stopTurntable();
    }
    
  } else {  // !isRunning
    
    if (buttonLeftIsDown) {
      startTurntable(LEFT);
    } else if (buttonRightIsDown) {
      startTurntable(RIGHT);
    }
  }
  
}
