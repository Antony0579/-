/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <LiquidCrystal_I2C.h>
IRsend irsend(4);
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int a3,a4;


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "jkyqvad89YEwegMcLsSp5lSRkXWoQ9m2";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "yik4i";
char pass[] = "cccccccc";

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  digitalWrite(D5,LOW);

  
}


void loop()
{
  if (digitalRead(D3)== HIGH && digitalRead(D4)== LOW && digitalRead(D6)== LOW){    //100 = A
  digitalWrite(D5,HIGH);
  
  lcd.begin(16,2);
  lcd.init();

  lcd.backlight();// Turn on the backlight.
  lcd.setCursor(5, 0);  // Print HELLO to the screen, starting at 5,0.
  lcd.print("KITCHEN");
  lcd.setCursor(5, 1); // Move the cursor characters to the right and  zero characters down (line 1). 
      
  lcd.print("GO");
  }
  
  else  if(digitalRead(D3)== HIGH && digitalRead(D4)== HIGH && digitalRead(D6)== LOW){    //110 = B
  digitalWrite(D5,HIGH);
 
    lcd.begin(16,2);
    lcd.init();

    lcd.backlight();// Turn on the backlight.
    lcd.setCursor(5, 0);  // Print HELLO to the screen, starting at 5,0.
    lcd.print("STUDYROOM");
    lcd.setCursor(5, 1); // Move the cursor characters to the right and  zero characters down (line 1). 
      
    lcd.print("GO");
  }

  else  if (digitalRead(D4)== HIGH && digitalRead(D3)== LOW && digitalRead(D6)== LOW){    //010 = B
  digitalWrite(D5,HIGH);
  lcd.begin(16,2);
  lcd.init();

  lcd.backlight();// Turn on the backlight.
  lcd.setCursor(5, 0);  // Print HELLO to the screen, starting at 5,0.
  lcd.print("STUDYROOM");
  lcd.setCursor(5, 1); // Move the cursor characters to the right and  zero characters down (line 1). 
      
  lcd.print("GO");
  }

  else  if (digitalRead(D4)== LOW && digitalRead(D3)== LOW && digitalRead(D6)== HIGH){    //001 = C
  digitalWrite(D5,HIGH);
  lcd.begin(16,2);
  lcd.init();

  lcd.backlight();// Turn on the backlight.
  lcd.setCursor(5, 0);  // Print HELLO to the screen, starting at 5,0.
  lcd.print("LIVINGROOM");
  lcd.setCursor(5, 1); // Move the cursor characters to the right and  zero characters down (line 1). 
      
  lcd.print("GO");
  }
  
  else  if (digitalRead(D4)== LOW && digitalRead(D3)== HIGH && digitalRead(D6)== HIGH){    //101  = C
  digitalWrite(D5,HIGH);
  lcd.begin(16,2);
  lcd.init();

  lcd.backlight();// Turn on the backlight.
  lcd.setCursor(5, 0);  // Print HELLO to the screen, starting at 5,0.
  lcd.print("LIVINGROOM");
  lcd.setCursor(5, 1); // Move the cursor characters to the right and  zero characters down (line 1). 
      
  lcd.print("GO");
  }

  else  if (digitalRead(D4)== HIGH && digitalRead(D3)== LOW && digitalRead(D6)== HIGH){    //011  = C
  digitalWrite(D5,HIGH);
  lcd.begin(16,2);
  lcd.init();

  lcd.backlight();// Turn on the backlight.
  lcd.setCursor(5, 0);  // Print HELLO to the screen, starting at 5,0.
  lcd.print("LIVINGROOM");
  lcd.setCursor(5, 1); // Move the cursor characters to the right and  zero characters down (line 1). 
      
  lcd.print("GO");
  }

   else  if (digitalRead(D4)== HIGH && digitalRead(D3)== HIGH && digitalRead(D6)== HIGH){    //111 = C
  digitalWrite(D5,HIGH);
  lcd.begin(16,2);
  lcd.init();

  lcd.backlight();// Turn on the backlight.
  lcd.setCursor(5, 0);  // Print HELLO to the screen, starting at 5,0.
  lcd.print("LIVINGROOM");
  lcd.setCursor(5, 1); // Move the cursor characters to the right and  zero characters down (line 1). 
      
  lcd.print("GO");
  }

  
  else  if  (digitalRead(D3)== LOW  &&  digitalRead(D4)== LOW && digitalRead(D6)== LOW){    //000 = 0
    digitalWrite(D5,LOW);
    lcd.noBacklight();
    lcd.setCursor(5, 0);
    lcd.print("LIGHT ");
    lcd.setCursor(5, 1);
    lcd.print("OFF");
  
  }
   Blynk.run();
}
