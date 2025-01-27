#include "ESP32-HUB75-MatrixPanel-I2S-DMA-1-4.h"


// Different small font for our small rez
//#include <Fonts/TomThumb.h>
//#include <Fonts/Picopixel.h>
//#include <Fonts/Org_01.h>
//#include <Fonts/FreeMonoBold9pt7b.h>
#include <muHeavy8ptBold.h>
#include <muMatrix8ptRegular.h>

#include "icon_lib.h"

// Panel configuration
#define PANEL_RES_X 96
#define PANEL_RES_Y 16

MatrixPanel_I2S_DMA *dma_display = nullptr;
ShittyBoard *oSB = nullptr;

// Color palette
uint16_t myBLACK = dma_display->color565(0, 0, 0);
uint16_t myWHITE = dma_display->color565(255, 255, 255);
uint16_t myRED = dma_display->color565(255, 0, 0);
uint16_t myCRIMSON = dma_display->color565(178,34,34);
uint16_t myGREEN = dma_display->color565(80, 255, 80);
uint16_t myBLUE = dma_display->color565(0, 0, 255);
uint16_t myPINK = dma_display->color565(255, 100, 100);
uint16_t myYELLOW = dma_display->color565(150, 150, 0);
uint16_t myORANGE = dma_display->color565(255, 150, 50);
uint16_t myVIOLET = dma_display->color565(255, 0, 255);

void setup() {

  delay(250);

  HUB75_I2S_CFG mxconfig(
    PANEL_RES_X*2,              // DO NOT CHANGE THIS
    PANEL_RES_Y/2,              // DO NOT CHANGE THIS
    1
  );

  mxconfig.clkphase = false; 
  
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  dma_display->setBrightness8(50);    // range is 0-255, 0 - 0%, 255 - 100%

  // Allocate memory and start DMA display
  if( not dma_display->begin() )
    Serial.println("****** !KABOOM! I2S memory allocation failed ***********");

  dma_display->clearScreen();
  delay(500);

  oSB = new ShittyBoard((*dma_display), 1, 1, PANEL_RES_X, PANEL_RES_Y);
  oSB->setPhysicalPanelScanRate(FOUR_SCAN_16PX_HIGH);

  oSB->setTextWrap(false);

  oSB->setFont(&muMatrix8ptRegular);
  oSB->setTextSize(1);
  oSB->setTextColor(myBLUE);
  oSB->setCursor(28, 7);
  oSB->println("Rebelles du");
  oSB->setCursor(28, 15);  
  oSB->print("Bas du fleuve");


  oSB->fillRect(24,0,2,16, myCRIMSON);

  oSB->setFont(&muHeavy8ptBold);
  oSB->setTextSize(1);
  oSB->setTextColor(myWHITE);
  oSB->setCursor(1, 8);
  oSB->print("M21");
  oSB->setCursor(3, 16);
  oSB->print(" AA");
  

}

void loop() {
  // put your main code here, to run repeatedly:

}