#include <Wire.h>
#include <Keypad.h>
#include<LiquidCrystal_I2C.h>
#include<EEPROM.h>
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7);
char password[4];
char pass[4],pass1[4];
int i=0;
char customKey=0;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char hexaKeys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2};   //connect to the column pinouts of the keypad
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
int led;
int buzzer = 10;
void setup()
{
  Serial.begin(9600);
  Serial.write(254);
  Serial.write(0x01);
  delay(200);
  pinMode(11, OUTPUT); //GREEN LIGHT
  pinMode(12, OUTPUT); //RED LIGHT

  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.begin(16,2);
  pinMode(buzzer, OUTPUT);
  lcd.print("    WELCOME ");
  Serial.print("    WELCOME ");
  lcd.setCursor(0,1);
  lcd.print("   BIENVENIDO ");
  Serial.print("  BIENVENIDO ");
  delay(4000);
  lcd.clear();
  lcd.print("CHANGE PASSWORD");
  Serial.println("CHANGE PASSWORD");
  lcd.setCursor(0,1);
  lcd.print("BY PRESSING #");
  Serial.print("BY PRESSING #");
  delay(4000);
  lcd.clear();
  lcd.print("ENTER PASSWORD:");
  Serial.println("ENTER PASSWORD:");
  lcd.setCursor(0,1);
  for(int j=0;j<4;j++)
    EEPROM.write(j, j+49);
  for(int j=0;j<4;j++)
    pass[j]=EEPROM.read(j);
}

void loop()
{
  digitalWrite(11, LOW);
  customKey = customKeypad.getKey();
  if(customKey=='#')
    change();
  if (customKey)
  {
    password[i++]=customKey;
    lcd.print(customKey);
    Serial.print(customKey);
    beep();
  }
  if(i==4)
  {
    delay(200);
    for(int j=0;j<4;j++)
      pass[j]=EEPROM.read(j);
    if(!(strncmp(password, pass,4)))
    {
      digitalWrite(11, HIGH);
      beep();
      lcd.clear();
      lcd.print("ACCESS GRANTED");
      Serial.println("ACCESS GRANTED");
      digitalWrite(11, HIGH);
      delay(5000);
      digitalWrite(11, LOW);
      lcd.clear();
      lcd.print("ENTER PASSWORD:");
      Serial.println("ENTER PASSWORD:");
      lcd.setCursor(0,1);
      i=0;
      //digitalWrite(11, LOW);
    }
    else
    {
      digitalWrite(12, HIGH);
      digitalWrite(buzzer, HIGH);
      lcd.clear();
      lcd.print("ACCESS DENIED");
      Serial.println("ACCESS DENIED");
      delay(1000);
      digitalWrite(12, LOW);
      lcd.clear();
      lcd.print("ENTER PASSWORD:");
      Serial.println("ENTER PASSWORD:");
      lcd.setCursor(0,1);
      i=0;
      digitalWrite(buzzer, LOW);
    }
  }
}
void change()
{
  int j=0;
  lcd.clear();
  lcd.print("CURRENT PASSWORD:");
  Serial.println("CURRENT PASSWORD:");
  lcd.setCursor(0,1);
  while(j<4)
  {
    char key=customKeypad.getKey();
    if(key)
    {
      pass1[j++]=key;
      lcd.print(key);
      Serial.print(key);
      beep();
    }
    key=0;
  }
  delay(500);

  if((strncmp(pass1, pass, 4)))
  {
    lcd.clear();
    lcd.print("WRONG PASSWORD");
    Serial.println("WRONG PASSWORD");
    delay(1000);
  }
  else
  {
    j=0;
    lcd.clear();
    lcd.print("NEW PASSWORD:");
    Serial.println("NEW PASSWORD:");
    lcd.setCursor(0,1);
    while(j<4)
    {
      char key=customKeypad.getKey();
      if(key)
      {
        pass[j]=key;
        lcd.print(key);
        Serial.print(key);
        EEPROM.write(j,key);
        j++;
        beep();
      }
    }
    lcd.print("    [[SET]]");
    Serial.print("    [[SET]]");
    delay(1000);
  }
  lcd.clear();
  lcd.print("ENTER PASSWORD:");
  Serial.println("ENTER PASSWORD:");
  lcd.setCursor(0,1);
  customKey=0;
}
void beep()
{
  digitalWrite(buzzer, HIGH);
  delay(20);
  digitalWrite(buzzer, LOW);
}
