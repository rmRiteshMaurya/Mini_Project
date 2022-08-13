#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#include <SD.h>                           // include SD module library
#include <TMRpcm.h>   

#define SD_ChipSelectPin 10  

TMRpcm tmrpcm;   

LiquidCrystal_I2C lcd (0x27 ,16,2);             // interfacing LCD with I2C 
SoftwareSerial mySerial (2, 3);   //(RX, TX);

String val = "No Data";            // initially message
String oldval;
String newval = "No Data";
//int length;
int i = 0;

void setup() 
{
  
  lcd.init();
  lcd.backlight();
  tmrpcm.speakerPin = 9; 

  if (!SD.begin(SD_ChipSelectPin)) {      //see if the card is present and can be initialized
    return;                               //don't do anything more if not
  }
  tmrpcm.setVolume(5); 
  
  
  lcd.begin(16,2);
  mySerial.begin(9600);
  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print("Wireless Notice");
  lcd.setCursor(0, 1);
  lcd.print("     Board     ");
  delay(3000);
  lcd.clear();
  lcd.print("Welcome!");
}

void loop() 
{
  val = mySerial.readString();
  val.trim();
  Serial.println(val);
  if(val != oldval)
  {
    newval = val;
    tmrpcm.play("2.wav");    // Music file
    delay(8500);
    tmrpcm.play("3.wav");
  }
  val = oldval;
 Serial.println(val);
lcd.clear();
lcd.setCursor(16, 1);
lcd.print(newval);
lcd.setCursor(16, 0);
lcd.print("Notice:");
for(int counter = 0; counter < 24; counter++)    // Loop for displaying the message
{
lcd.scrollDisplayLeft();
delay(300);
}
}
