/*
A code to simulate a simple birthday candle with flickering effect

Items:

- 1 Arduino Nano (ESP32)
- 2 LEDs at pins 2 and 3 (ground with 220 Ohm resistors)
- 1 button connected to pin 7 (ground with 10 kOhm resistor)

Author: Riccardo Finotello
*/

const int buttonPin = 7;
bool buttonState = false;
bool buttonReading = false;
bool buttonReadingLast = false;
unsigned int buttonLastDebounce = 0;  // ms
const unsigned int buttonDebounceDelay = 50;  // ms
const int ledPins[2] = {2, 3};
bool ledStatus = false;

void setup() {
  // Initialize the serial interface
  Serial.begin(9600);
  Serial.print("\n");
  Serial.print("*************************\n");
  Serial.print("  Initializing candle    \n");
  Serial.print("                         \n");
  Serial.print("    auth: thesfinox      \n");
  Serial.print("    ver:  1.0.0          \n");
  Serial.print("*************************\n\n");

  // Initialize the buttons
  pinMode(buttonPin, INPUT);
  for (int i = 0; i < 2; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Read the status of the button
  buttonReading = digitalRead(buttonPin);
  if ((buttonReading == HIGH) && (buttonReadingLast == LOW) && (millis() - buttonLastDebounce > buttonDebounceDelay))
  {
    (ledStatus) ? ledStatus = false : ledStatus = true;
    buttonLastDebounce = millis();
  }

  // Light the leds !
  if (ledStatus)
  {
    for (int i = 0; i < 2; i++)
    { 
      analogWrite(ledPins[i], random(155) + 100);  // use random for flickering effect
    }
  }
  else
  {
    for (int i = 0; i < 2; i++)
    {
      analogWrite(ledPins[i], 0);
    }
  }

  // Random delay for flickering effect
  buttonReadingLast = buttonReading;
  delay(random(100));
}
