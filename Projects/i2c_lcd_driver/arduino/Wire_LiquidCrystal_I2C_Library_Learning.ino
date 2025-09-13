#include <Wire.h>
#include <stdint.h>
#include <LiquidCrystal_I2C.h>

uint8_t addr, error;
uint8_t lcd_addr = 0x27; // fallback if scan fails

uint8_t address_sniffer() {
  Wire.begin();  //You can put an address inside, this will make the MCU a slave with the address and if no address the MCU is a controller joined to the I2C bus
  for (addr = 0; addr < 128; addr++) {  // Loop through all the possible addresses and begin transmision,
    Wire.beginTransmission(addr);             // This initiates the connection between the master and slave with that address
    //Wire.write(); // This is where the data is stored to be sent
    error = Wire.endTransmission();  // This sends the stored information and also returns status code like succcess, ACK/NACK...
    if (error== 0) {
      Serial.println(addr);
      Wire.end();
      return addr;
    }
  }
  Wire.end(); // Disables the library
}

LiquidCrystal_I2C lcd(lcd_addr,16,2); //Using LiquidCrystal_I2C library, defines the lcd screen at the address which was found 

void setup() {
  Serial.begin(9600);
  uint8_t found_lcd = address_sniffer();
  
  lcd = LiquidCrystal_I2C(found_lcd, 16, 2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Nikola Vukas");
  lcd.setCursor(0, 1);
  lcd.print("Embedded Systems");
}

void loop() {
  // lcd.scrollDisplayRight();
  // delay(600);
}
