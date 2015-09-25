#include <Wire.h> 
#include <Servo.h> 
#include <LiquidCrystal_I2C.h>

Servo Aservo;
Servo Bservo;
Servo Cservo;
Servo Dservo;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int value_X, value_Y;
int val = 1, prev = 1;
int A = 0, B = 0, C = 0, D = 0;
int point = 0;

void setup()
{
  lcd.init();
  lcd.backlight();
  pinMode(2, INPUT);
  Aservo.attach(5);
  Bservo.attach(6);
  Cservo.attach(9);
  Dservo.attach(10);
}

void loop()
{
  value_X = analogRead(0);
  value_Y = analogRead(1);
  val = digitalRead(2);
  
  lcd.clear();
  
  lcd.setCursor(1,0);
  lcd.print("A");
  lcd.setCursor(5,0);
  lcd.print("B");
  lcd.setCursor(9,0);
  lcd.print("C");
  lcd.setCursor(13,0);
  lcd.print("D");
  
  if(val == 0 && prev == 1){
	prev = 0;
	
	if(point < 3){
		point++;
	}else{
		point = 0;
	}
  }else if(val == 1 && prev == 0){
	prev = 1;
  }
  
  lcd.setCursor(2+point*4,0);
  lcd.print("0");
  
  if(point == 0){
    if(value_Y > 520){
      A = A - (value_Y-500)/100;
      if(A < 0){
        A = 0;
      }
    }else if(value_Y < 480){
      A = A + (500-value_Y)/100;
      if(A > 45){
        A = 45;
      }
    }
  }else if(point == 1){
    if(value_Y > 520){
      B = B - (value_Y-500)/100;
      if(B < 0){
        B = 0;
      }
    }else if(value_Y < 480){
      B = B + (500-value_Y)/100;
      if(B > 180){
        B = 180;
      }
    }
  }else if(point == 2){
    if(value_Y > 520){
      C = C - (value_Y-500)/100;
      if(C < 0){
        C = 0;
      }
    }else if(value_Y < 480){
      C = C + (500-value_Y)/100;
      if(C > 180){
        C = 180;
      }
    }
  }else if(point == 3){
    if(value_Y > 520){
      D = D - 1;
      if(D < 0){
        D = 0;
      }
    }else if(value_Y < 480){
      D = D + 1;
      if(D < 0){
        D = 0;
      }
    }
  }
  
  lcd.setCursor(1,1);
  lcd.print(A);
  lcd.setCursor(5,1);
  lcd.print(B);
  lcd.setCursor(9,1);
  lcd.print(C);
  lcd.setCursor(13,1);
  lcd.print(D);
  
  Aservo.write(A); 
  Bservo.write(B); 
  Cservo.write(C); 
  Dservo.write(D); 
  
  delay(50);
}
