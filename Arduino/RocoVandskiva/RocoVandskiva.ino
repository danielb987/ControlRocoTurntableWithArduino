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

const int BUTTON_LEFT = 16;
const int BUTTON_RIGHT= 17;
const int LED_BUTTON = 18;


void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // put your setup code here, to run once:
  pinMode(INTERNAL_LED, OUTPUT);
  digitalWrite(RELAY_ON_OFF, HIGH);
  digitalWrite(RELAY_DIRECTION, HIGH);
  pinMode(RELAY_ON_OFF, OUTPUT);
  pinMode(RELAY_DIRECTION, OUTPUT);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(LED_BUTTON, OUTPUT);
  digitalWrite(INTERNAL_LED, LOW);
  digitalWrite(INTERNAL_LED, HIGH);
}

void loop() {
  digitalWrite(INTERNAL_LED, HIGH);
  delay(5000);
  digitalWrite(INTERNAL_LED, LOW);
  delay(5000);
}

void loop11() {
  if (digitalRead(BUTTON_LEFT) == LOW) {
    digitalWrite(LED_BUTTON, LOW);
  } else if (digitalRead(BUTTON_RIGHT) == LOW) {
    digitalWrite(LED_BUTTON, LOW);
  } else {
    digitalWrite(LED_BUTTON, HIGH);
  }
//  digitalWrite(INTERNAL_LED, LOW);
//  digitalWrite(LED_BUTTON, LOW);
//  digitalWrite(RELAY_ON_OFF, LOW);
//  digitalWrite(RELAY_DIRECTION, LOW);
//  Serial.write("-");
/*
  if (digitalRead(BUTTON_LEFT) == LOW) {
    Serial.write("L");
  } else {
//    Serial.write("l");
  }

  if (digitalRead(BUTTON_RIGHT) == LOW) {
    Serial.write("R");
  } else {
//    Serial.write("r");
  }
*/
//  delay(500);
//  digitalWrite(INTERNAL_LED, HIGH);
//  digitalWrite(LED_BUTTON, HIGH);
//  digitalWrite(RELAY_ON_OFF, HIGH);
//  digitalWrite(RELAY_DIRECTION, HIGH);
//  Serial.write("+");
//  delay(500);

}
