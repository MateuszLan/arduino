#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
int odczytanaWartosc = 0; //Zmienna do przechowywania odczytu ADC
int prog = 0; //Próg włączenia światła - ustawiany potencjometrem
void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  pinMode(8, OUTPUT); //Konfiguracja wyjść pod diodę LED
  Serial.begin(9600); //Ustawienie prędkości transmisji
  lcd.setCursor(0,0);
  lcd.print("Fotorezystor: ");
  lcd.setCursor(0,1);
  lcd.print("Status diody: ");
  lcd.setCursor(13,0);
  lcd.print(odczytanaWartosc);
  lcd.setCursor(13,1);
  lcd.print("OFF");

  pinMode(7, OUTPUT); //Dioda jako wyjście
  pinMode(6, INPUT_PULLUP); //Przycisk jako wejście
  digitalWrite(7, LOW); //Wyłączenie diody
}
 
void loop() {

  if (digitalRead(6) == LOW) { //Jeśli przycisk wciśnięty
    digitalWrite(7, HIGH); //Włącz diodę
  } else { //Jeśli warunek nie został spełniony (przycisk nie jest wciśnięty)
    digitalWrite(7, LOW); //Wyłącz diodę
  }
  odczytanaWartosc = analogRead(A2);//Odczytanie wartości z ADC
  prog = analogRead(A1);//Odczytanie wartości z ADC  
  Serial.print(odczytanaWartosc);
  Serial.print("/");
  Serial.println(prog);
  if (odczytanaWartosc < prog) { //Czy jest ciemniej od ustawionego progu?
     digitalWrite(8, HIGH);//Włączenie diody    
      lcd.setCursor(13,1);
  lcd.print("ON ");
  } else {
     digitalWrite(8, LOW);//Wyłączenie diody    
      lcd.setCursor(13,1);
  lcd.print("OFF");  
  }
   lcd.setCursor(13,0);
  lcd.print(odczytanaWartosc);
  if(odczytanaWartosc<100){
  lcd.setCursor(15,0);
  lcd.print(" ");
  }
  delay(75);
}  
