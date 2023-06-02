#include <Servo.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

 

#define I2C_ADDR    0x27 // Adresse des Displays
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

 

Servo schranke;
LiquidCrystal_I2C  lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

 

int ampelRotPin = 12;
int ampelGelbPin = 11;
int ampelGruenPin = 10;
int ampel2RotPin = 9;
int ampel2GelbPin = 8;
int ampel2GruenPin = 7;
int fgRotPin = 4;
int fgGruenPin = 3;
int schrankePin = 13;
int signalTon = 5;

 

unsigned long countdownStartTime = 0;
const unsigned long countdownDuration = 3000; // 10 Sekunden Countdown

 

void setup() {
  pinMode(ampelRotPin, OUTPUT);
  pinMode(ampelGelbPin, OUTPUT);
  pinMode(ampelGruenPin, OUTPUT);
  pinMode(ampel2RotPin, OUTPUT);
  pinMode(ampel2GelbPin, OUTPUT);
  pinMode(ampel2GruenPin, OUTPUT);
  pinMode(fgRotPin, OUTPUT);
  pinMode(fgGruenPin, OUTPUT);
  pinMode(schrankePin, OUTPUT);
  pinMode(signalTon, OUTPUT);

 

  schranke.attach(schrankePin);
  schranke.write(0); // Schranke initial schließen

 

  lcd.begin(16, 2); // Initialisiere das LCD-Display
  lcd.setCursor(0, 0);
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.print("Fussgaenger");
}

 

void loop() {
  // gruen Ampel 1
  digitalWrite(ampelRotPin, LOW);
  digitalWrite(ampelGelbPin, LOW);
  digitalWrite(ampelGruenPin, HIGH);
  digitalWrite(ampel2RotPin, HIGH);
  digitalWrite(ampel2GelbPin, LOW);
  digitalWrite(ampel2GruenPin, LOW);
  digitalWrite(fgRotPin, HIGH);
  digitalWrite(fgGruenPin, LOW);
  schranke.write(0); // Schranke schliessen
  lcd.setCursor(0, 1);
  lcd.print("------STOP------");
  delay(5000);

 

  // gelb Übergang zu Ampel2
  digitalWrite(ampelRotPin, LOW);
  digitalWrite(ampelGelbPin, HIGH);
  digitalWrite(ampelGruenPin, LOW);
  digitalWrite(ampel2RotPin, HIGH);
  digitalWrite(ampel2GelbPin, HIGH);
  digitalWrite(ampel2GruenPin, LOW);
  digitalWrite(fgRotPin, HIGH);
  digitalWrite(fgGruenPin, LOW);
  lcd.setCursor(0, 1);
  lcd.print("Stehen bleiben!!!"); // Text-Ausgabe
  delay(2000);

 

  // grün Ampel2
  digitalWrite(ampelRotPin, HIGH);
  digitalWrite(ampelGelbPin, LOW);
  digitalWrite(ampelGruenPin, LOW);
  digitalWrite(ampel2RotPin, LOW);
  digitalWrite(ampel2GelbPin, LOW);
  digitalWrite(ampel2GruenPin, HIGH);
  digitalWrite(fgRotPin, HIGH);
  digitalWrite(fgGruenPin, LOW);
  lcd.setCursor(0, 1);
  lcd.print("Stehen bleiben!!!"); // Leert die zweite Zeile
  delay(5000);

 

  // gelb Übergang zu fgAmpel
  digitalWrite(ampelRotPin, HIGH);
  digitalWrite(ampelGelbPin, LOW);
  digitalWrite(ampelGruenPin, LOW);
  digitalWrite(ampel2RotPin, LOW);
  digitalWrite(ampel2GelbPin, HIGH);
  digitalWrite(ampel2GruenPin, LOW);
  digitalWrite(fgRotPin, HIGH);
  digitalWrite(fgGruenPin, LOW);
  lcd.setCursor(0, 1);
  lcd.print("Stehen bleiben!!!"); // Text-Ausgabe
  delay(2000);

 

// Schranke schnell öffnen
for (int angle = 0; angle <= 90; angle += 2) {
  schranke.write(angle); // Schranke schrittweise öffnen (angepasster Schritt)
  delay(50); // Wartezeit zwischen den Schritten (angepasster Wert)
}
digitalWrite(ampelRotPin, HIGH);
digitalWrite(ampelGelbPin, LOW);
digitalWrite(ampelGruenPin, LOW);
digitalWrite(ampel2RotPin, HIGH);
digitalWrite(ampel2GelbPin, LOW);
digitalWrite(ampel2GruenPin, LOW);
digitalWrite(fgRotPin, LOW);
digitalWrite(fgGruenPin, HIGH);
countdownStartTime = millis();
while (millis() - countdownStartTime < countdownDuration) {
  tone(signalTon, 500);
  delay(50);
  noTone(signalTon);
  delay(50);
  lcd.setCursor(0, 1);
  unsigned long timeRemaining = (countdownDuration - (millis() - countdownStartTime)) / 3000;
  lcd.print("Gehen! Zeit: " + String(timeRemaining) + "s ");
}

 

// Schranke langsam schließen
for (int angle = 90; angle >= 0; angle -= 2) {
  schranke.write(angle); // Schranke schrittweise schließen (angepasster Schritt)
  delay(50); // Wartezeit zwischen den Schritten (angepasster Wert)
}
}
