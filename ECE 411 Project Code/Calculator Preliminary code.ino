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



#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int row1 = ;
int row2 = ;
int row3 = ;
int row4 = ;
int row5 = ;
int col1 = ;
int col2 = ;
int col3 = ;
int col4 = ;
int col5 = ;

LiquidCrystal_I2C lcd(FIND THE LCD DISPLAY ADDRESS,20,4);  // set the LCD address to blank for a 20 chars and 4 line display (need to determine for our LCD)


char charOutput;
//variables needed for the math, max of 20 digits
char operation = '0';
char value0[18];
char value1[18];
char result[20];
int numType = 0;



int val# = 0;
int numCount;

//trash variable to hold things use with strtoul https://www.tutorialspoint.com/c_standard_library/c_function_strtoul.htm
char *garbage;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  //Here we put the button array gpio ports
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);




  //variables

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //LCD gpio ports
  pinMode(row1, OUTPUT);
  pinMode(row2, OUTPUT);
  pinMode(row3, OUTPUT);
  pinMode(row4, OUTPUT);
  pinMode(row5, OUTPUT);
  pinMode(col1, INPUT);
  pinMode(col2, INPUT);
  pinMode(col3, INPUT);
  pinMode(col4, INPUT);
  pinMode(col5, INPUT);

  haveInput = 0;
  delay(50);
  if(val# == 1)
  {
    lcd.setCursor(2,1);
  }
  else
  {
    lcd.setCursor(1,0);
  }
  //check which button
  while(haveInput == 0)
  {
    if(digitalRead(col1) == 1)
    {
      //change ROWS and COLUMNS 
      switchIO();

      if(digitalRead(row1) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row2) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row3) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row4) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row5) == 1)
      {
        charOutput = ;
      }
      haveInput = 1;
    }
    if(digitalRead(col2) == 1)
    {
      //change ROWS and COLUMNS 
      switchIO();

      if(digitalRead(row1) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row2) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row3) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row4) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row5) == 1)
      {
        charOutput = ;
      }
      haveInput = 1;
    }

    if(digitalRead(col3) == 1)
    {
      //change ROWS and COLUMNS 
      switchIO();

      if(digitalRead(row1) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row2) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row3) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row4) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row5) == 1)
      {
        charOutput = ;
      }
      haveInput = 1;
    }

    if(digitalRead(col4) == 1)
    {
      //change ROWS and COLUMNS 
      switchIO();

      if(digitalRead(row1) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row2) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row3) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row4) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row5) == 1)
      {
        charOutput = ;
      }
      haveInput = 1;
    }

    if(digitalRead(col5) == 1)
    {
      //change ROWS and COLUMNS 
      switchIO();

      if(digitalRead(row1) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row2) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row3) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row4) == 1)
      {
        charOutput = ;
      }
      else if(digitalRead(row5) == 1)
      {
        charOutput = ;
      }
      haveInput = 1;
    }
  }

  //write into the saved number values
  if(operation != '0')
  {
    lcd.setCursor(1,1);
    lcd.print(operation);
    val# = 1;
    return;
  }

  if(numType == 0)
  {
    if(val# == 0)
    {
      value0[numCount] = charOutput;
      numCount++;
      lcd.print(value0);
    }
    else if(val# == 1)
    {
      value1[numCount] = charOutput;
      numCount++;
      lcd.print(value1);
    }
  }
  else if(numType == 1)
  {
    if(val# == 0)
    {
      value0[numCount] = charOutput;
      numCount++;
      lcd.print(value0, BIN);
    }
    else if(val# == 1)
    {
      value1[numCount] = charOutput;
      numCount++;
      lcd.print(value1,BIN);
    }
  }

  else if(numType == 2)
  {
    if(val# == 0)
    {
      value0[numCount] = charOutput;
      numCount++;
      lcd.print(value0, HEX);
    }
    else if(val# == 1)
    {
      value1[numCount] = charOutput;
      numCount++;
      lcd.print(value1, HEX);
    }
  }



  
}

void switchIO() {
  pinMode(row1, INPUT);
  pinMode(row2, INPUT);
  pinMode(row3, INPUT);
  pinMode(row4, INPUT);
  pinMode(row5, INPUT);
  pinMode(col1, OUTPUT);
  pinMode(col2, OUTPUT);
  pinMode(col3, OUTPUT);
  pinMode(col4, OUTPUT);
  pinMode(col5, OUTPUT);
  return;
}


