//Written by Angelo Maldonado-Liu
//10/28/2022
//PSU ECE 411
//
//
//
/* To do:
      assign values to each row/column pair
      for the equals sign, add in an LCD clear and then output the answer.
      Hex to Binary to Decimal converter.
      need to decide if i have say, 10 in the buffer, when I hit the convert button, does it become 0b1010, and then become 0xA, because if so, then I need to change the size of acceptable values, so that I can fit a D, B, H symbol to signify what type of values we are getting.
      */


//#include <pico/stdlib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <gpio.h>
#include <i2c_api.h>
#include <i2c.h>




LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to blank for a 20 chars and 4 line display (need to determine for our LCD)


char charOutput;
//variables needed for the math, max of 20 digits
char operation = '0';
char value0[14];
char value1[14];
char result[16];
int numType = 0;
int haveInput = 0;

int LCD_address = 0x27;



int screen_on = 0;

int val = 0;
int numCount;
int readval = 0;

//trash variable to hold things use with strtoul https://www.tutorialspoint.com/c_standard_library/c_function_strtoul.htm
char *garbage;
i2c_inst_t *i2c = i2c0;
void setup() {
  Serial.begin(9600);
   _i2c_init(i2c,400*1000);
  // put your setup code here, to run once:
  //gpio_set_function(16,GPIO_FUNC_I2C);
 // gpio_set_function(17,GPIO_FUNC_I2C);
 // Wire.setSDA(16);
  //Wire.setSCL(17);
  MbedI2C(16,17);
  Wire.begin();
  Wire.beginTransmission(LCD_address);
  Wire.write(0b0000001000);
  Wire.endTransmission();
  while(1)
  {
    readval = Wire.read();
    readval = readval & 0b0110000000;
    if(readval == 0b0100000000)
    {
      break;
    }
    Serial.print(readval);
  }
  Wire.beginTransmission(LCD_address);

  Wire.write(0b0000000111);
  Wire.endTransmission();



  //variables

}

void loop() {
  // put your main code here, to run repeatedly:
  
  


  haveInput = 0;
  delay(1000);
  lcd.blink();
  delay(2000);
  Wire.beginTransmission(LCD_address);
  Wire.write(0b0000001000);
  Serial.println("here");
  Wire.endTransmission();
  delay(1000);
  Wire.beginTransmission(LCD_address);
  Wire.write(0b0000001100);
  Wire.endTransmission();
/*  if(val# == 1)
  {
    lcd.setCursor(2,1);
  }
  else
  {
    lcd.setCursor(1,0);
  }
*/  //check which button
/*  while(haveInput == 0)
  {
    if(digitalRead(col1) == 1)
    {
      //change ROWS and COLUMNS 
      switchIO();

      if(digitalRead(row1) == 1)
      {
        Wire.beginTransmission(LCD_address);
        if(screen_on = 0)
        {
          Wire.write(0b1000001100);
        }
        if(screen_on = 1)
        {
          Wire.write(0b1000001000);
        }
        Wire.endTransmission();
      }
      else if(digitalRead(row2) == 1)
      {
        
        charOutput = '1';
        Wire.beginTransmission(LCD_address);
        Wire.write(0b1000110001);
        Wire.endTransmission();
      }
      haveInput = 1;
    }
    if(digitalRead(col2) == 1)
    {
      //change ROWS and COLUMNS 
      switchIO();

      if(digitalRead(row1) == 1)
      {
        charOutput = '2';
        Wire.beginTransmission(LCD_address);
        Wire.write(0b1000110010);
        Wire.endTransmission();
      }
      else if(digitalRead(row2) == 1)
      {
        charOutput = '3';
        Wire.beginTransmission(LCD_address);
        Wire.write(0b1000110011);
        Wire.endTransmission();
      }

      haveInput = 1;
    }

  }

  //write into the saved number values
/*  if(operation != '0')
  {
    val# = 1;
    return;
  }

  if(numType == 0)
  {
    if(val# == 0)
    {
      value0[numCount] = charOutput;
      numCount++;
    }
    else if(val# == 1)
    {
      value1[numCount] = charOutput;
      numCount++;
    }
  }
  else if(numType == 1)
  {
    if(val# == 0)
    {
      value0[numCount] = charOutput;
      numCount++;
    }
    else if(val# == 1)
    {
      value1[numCount] = charOutput;
      numCount++;
    }
  }

  else if(numType == 2)
  {
    if(val# == 0)
    {
      value0[numCount] = charOutput;
      numCount++;
    }
    else if(val# == 1)
    {
      value1[numCount] = charOutput;
      numCount++;
    }
  }
*/



}
/*
void switchIO() {
  pinMode(row1, INPUT);
  pinMode(row2, INPUT);

  pinMode(col1, OUTPUT);
  pinMode(col2, OUTPUT);

  return;
}
*/


