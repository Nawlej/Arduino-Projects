#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "image.h"
#include "fonts.h"

void setup()
{
  Config_Init();
  LCD_Init();
  LCD_Clear(0xffff);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(WHITE);

  String string1 = "HELLO WORLD. I'm Arduino. I can word wrap captions very well.";
  sFONT fontsize = Font24;
  
  display(string1, fontsize);

}
void loop()
{
  
}

String returnNextWord(int index,String string) {
  return string.substring(index, string.indexOf(" ", index+1));
}

void display(String string1, sFONT fontsize) {
  int maxChar = LCD_WIDTH / fontsize.Width;
  int rows = int(ceil(float(string1.length()) / float(maxChar)))+1;
  String arr[rows];

  if (rows > 1) {
    int spaceIndex = 0;
    String nextWord = returnNextWord(spaceIndex, string1);

    for (int i = 0; i < rows; i++) {   
      while (spaceIndex > -1 && (arr[i].length() + returnNextWord(spaceIndex, string1).length()) <= maxChar) {
        arr[i].concat(string1.substring(spaceIndex, string1.indexOf(" ", spaceIndex+1))) ;
        spaceIndex = string1.indexOf(" ", spaceIndex+1);
      }   
    }
    if (spaceIndex > 0 && returnNextWord(spaceIndex, string1) != NULL) {
      int i = 0;
      while (arr[i] != NULL && i < sizeof(arr)) {
        i++;
      }
    arr[i].concat(returnNextWord(spaceIndex, string1));
      }
  }
  for (int i = 0; i < rows; i++) {
    int xstart = LCD_WIDTH/2 - (arr[i].length()*fontsize.Width/2);
    if (xstart < 0) {xstart = 7;}
    Paint_DrawString_EN(xstart, LCD_HEIGHT/2 + (fontsize.Height*i), arr[i].c_str(), &fontsize, BLACK, WHITE);
  }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
