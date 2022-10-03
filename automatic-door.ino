#include <Servo.h>

Servo myservo;


void setup() {
  myservo.attach(9);
  myservo.write(90);
  int ADS_measure();
  LED_setup();
  ADS_measure();
  ADS_setup();
  Serial.begin(9600);
}

const int LED_PIN_BLUE = 12;
const int LED_PIN_GREEN = 11;
const int LED_PIN_RED = 13;
void LED_setup()
{
  pinMode(LED_PIN_BLUE, OUTPUT);
  pinMode(LED_PIN_GREEN, OUTPUT);
  pinMode(LED_PIN_RED, OUTPUT);
}
/** Set LED on or off */
void LED_change(bool value)
{
  auto mode = value ? HIGH : LOW;
  digitalWrite(LED_PIN_BLUE, mode);
  digitalWrite(LED_PIN_GREEN, mode);
  digitalWrite(LED_PIN_RED, mode);
}

const double speed_of_sound = 331.5 + 0.6 * 25 * 1e-12;

const int ADS_TRIG = 3;
const int ADS_ECHO = 2;

int ADS_measure()
{
  digitalWrite(ADS_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(ADS_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ADS_TRIG, LOW);
  double duration = pulseIn(ADS_ECHO, HIGH); // round-trip-time in usec.
  double distance = 0.5 * duration * speed_of_sound / 1000.0;
  return (int)distance;
}
bool isOpen = false;

/** servo motor control */
void open() {
    myservo.write(200);
    delay(120);
    myservo.write(90);
}

void close() {
    delay(3);
    myservo.write(0);
    delay(140);
}

void loop() {
  int distance = ADS_measure();
  bool isSomebodyClose = distance < 70;
  Serial.println(distance);
  delay(1000);
  if(isSomebodyClose && !isOpen) {
    open();
    digitalWrite(LED_PIN_BLUE, HIGH);
    digitalWrite(LED_PIN_RED, HIGH);
    digitalWrite(LED_PIN_GREEN, HIGH);
    isOpen = true;
    Serial.println("somebody");
    delay(1000);

  }
  if(!isSomebodyClose && isOpen) {
    close();
    myservo.write(90);
    digitalWrite(LED_PIN_BLUE, LOW);
    digitalWrite(LED_PIN_RED, LOW);
    digitalWrite(LED_PIN_GREEN, LOW);
    isOpen = false;
    Serial.println("nobody");
    delay(1000);
  }
}

void ADS_setup()
{
  pinMode(ADS_ECHO, INPUT);
  pinMode(ADS_TRIG, OUTPUT);
}
