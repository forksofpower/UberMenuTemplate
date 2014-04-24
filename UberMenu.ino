/*********************
  Name: UberMenu Template
  Version: v0.5
  
  A simple 2 dimensional menu template for Arduino and
  the Adafruit RGB LCD Shield
  
  Created by Patrick Jones 2014
  
  *This code is free to use and free to distribute,
  just be sure to thank Adafruit for their kickass
  products!*
**********************/
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>


#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();


const int NUM_MENUS = 3;                  // Update with real number of menu items
int subMenuCounts[NUM_MENUS]= {2, 3, 2};  // and with submenu items for each.
boolean buttonPressed = false;
int menu = 1, subMenu =1, color = 1;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0,0);                    
  
  lcd.print("UberMenu v0.5");            
  lcd.setCursor(0,1);                    
  lcd.print("Press any button");      
}

void loop() {
  buttonPressed = false;
  
  uint8_t buttons = lcd.readButtons();
  if (buttons) {
    lcd.clear();
    lcd.setCursor(0,0);
    if (buttons & BUTTON_UP) {
      menu = (menu + 1);
      subMenu = 1;
      buttonPressed = true;
    }
    if (buttons & BUTTON_DOWN) {
      menu = (menu - 1);
      subMenu = 1;
      buttonPressed = true;
    }
    if (buttons & BUTTON_LEFT) {
      subMenu = (subMenu - 1);
      buttonPressed = true;
    }
    if (buttons & BUTTON_RIGHT) {
      subMenu = (subMenu + 1);
      buttonPressed = true;
    }
    if (buttons & BUTTON_SELECT) {
      buttonPressed = true;
      color = (color%7)+1;
      lcd.setBacklight(color);
    }
  }
  // Clean up values
  if (menu < 1) {
    menu = NUM_MENUS; 
  }
  else if (menu > NUM_MENUS){
    menu = 1;
  }
  if (subMenu < 1) {
    subMenu = subMenuCounts[menu-1]; 
  }
  if (subMenu > subMenuCounts[menu-1]) {
    subMenu = 1; 
  }
  if(buttonPressed == true) {
    buttonPressed = false;
    updateScreen(menu, subMenu, subMenuCounts[menu-1]);
    delay(50); // make it smooth like butta, yo
  }
  buttonPressed = false;
}
void updateScreen(int menu, int subMenu, int count) {
  lcd.setCursor(0,0);
  lcd.print("Menu: ");
  lcd.print(menu);
  lcd.print(" of ");
  lcd.print(NUM_MENUS);
  lcd.setCursor(0,1);
  lcd.print("Submenu: ");
  lcd.print(subMenu);
  lcd.print(" of ");
  lcd.print(subMenuCounts[menu - 1]); 
}
