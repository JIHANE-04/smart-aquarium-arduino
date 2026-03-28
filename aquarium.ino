#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

#define SensorPin A1      // Capteur pH
#define sensor_pin A0     // Capteur turbidité
#define trigPin 5         // HC-SR04 TRIG
#define echoPin 6         // HC-SR04 ECHO
#define Motor_Pin 7       // Relais pompe

int buf[10];
bool Motor;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(Motor_Pin, OUTPUT);

  lcd.begin(16, 4);
  lcd.clear();
  lcd.print("   Welcome To   ");
  lcd.setCursor(0, 1);
  lcd.print("Smart  Aquarium ");
  delay(2000);
  lcd.clear();
}

// Lecture du pH (moyenne sur 10 échantillons)
float readPH() {
  int avgValue = 0;
  for (int i = 0; i < 10; i++) {
    buf[i] = analogRead(SensorPin);
    delay(10);
  }
  for (int i = 2; i < 8; i++) {
    avgValue += buf[i];
  }
  float phValue = (float)avgValue * 5.0 / 1024 / 6;
  return 3.5 * phValue;
}

// Lecture de la turbidité (0 = très sale, 300 = très clair)
int readTurbidity() {
  int read_ADC = analogRead(sensor_pin);
  if (read_ADC > 208) read_ADC = 208;
  return map(read_ADC, 0, 208, 300, 0);
}

// Lecture du niveau d'eau via HC-SR04 (0–100%)
int readWaterLevel() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return map(distance, 0, 1106, 0, 100);
}

// Affichage sur LCD 16x4
void displayInfo(float phValue, int waterLevel, int turbidity) {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("pH: ");
  lcd.print(phValue, 2);

  lcd.setCursor(0, 1);
  lcd.print("Water: ");
  lcd.print(waterLevel);
  lcd.print("%     ");

  lcd.setCursor(0, 2);
  lcd.print("Turbidity: ");
  lcd.print(turbidity);
  lcd.print("  ");

  lcd.setCursor(0, 3);
  if (turbidity < 10)
    lcd.print("Water Very Clean");
  else if (turbidity < 30)
    lcd.print("Water Norm Clean");
  else
    lcd.print("Water Very Dirty");

  delay(200);
}

void loop() {
  float phValue   = readPH();
  int waterLevel  = readWaterLevel();
  int turbidity   = readTurbidity();

  displayInfo(phValue, waterLevel, turbidity);

  // Pompe automatique : ON si niveau < 30%
  Motor = (waterLevel < 30);
  digitalWrite(Motor_Pin, Motor ? HIGH : LOW);
}
