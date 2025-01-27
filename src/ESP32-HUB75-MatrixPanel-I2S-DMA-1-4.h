#include "ESP32-VirtualMatrixPanel-I2S-DMA.h"

/**** Class ShittyBoard **********************************************************
 *    
 *    Author:  David Cuerrier
 *    Email:   david.cuerrier@gmail.com
 *    Version: 1.0 (Jan 24th 2025)
 *    
 *    This class is to be used with P10  chinese board which is not  supported 
 *    by ESP32_HUB75_LED_MATRIX_PANEL_DMA_Display  library. To use this class, 
 *    YOU MOST have installed ESP32_HUB75_LED_MATRIX_PANEL_DMA_Display and all 
 *    its prerequisites.
 *    
 *    In a nutshell, only the  getCoords function is overrided so it can remap 
 *    pixel in the right  pattern, using the VirtualMatricPanel class. P10 are 
 *    splitted  in 4  row and 4  col,  but they  are unaligned compared to the 
 *    coordinates comming from the native lib.
 *    
 *********************************************************************************/
 
class ShittyBoard : public VirtualMatrixPanel
{

  public:
      ShittyBoard(MatrixPanel_I2S_DMA &disp, int _vmodule_rows, int _vmodule_cols, int _panelResX, int _panelResY) : VirtualMatrixPanel(disp, _vmodule_rows, _vmodule_cols, _panelResX, _panelResY) {}
      VirtualCoords getCoords(int16_t virt_x, int16_t virt_y);   // overwrite adafruit implementation
      void drawIcon(uint16_t *ico, int16_t x, int16_t y, int16_t cols, int16_t rows);
      void drawIcon(uint16_t *ico, int16_t x, int16_t y, int16_t cols, int16_t rows, uint16_t fColor, uint16_t bColor = 0x0000);
  private:
    uint8_t getVirtColFromVirtX(uint8_t x);
    uint8_t getVirtRowFromVirtY(uint8_t y);
    uint8_t getPhysicalCoordX(uint8_t x, uint8_t virtRow, uint8_t virtCol);
    uint8_t getPhysicalCoordY(uint8_t y, uint8_t virtRow, uint8_t virtCol);
    
};


inline uint8_t ShittyBoard::getVirtColFromVirtX(uint8_t x) {
    if (x >= 0 && x <= 7)
      return 0;
    else if (x >= 8 && x <= 15)
      return 1;
    else if (x >= 16 && x <= 23)
      return 2;
    else if (x >= 24 && x <= 31)
      return 3;
    else if (x >= 32 && x <= 39)
      return 4;
    else if (x >= 40 && x <= 47)
      return 5;
    else if (x >= 48 && x <= 55)
      return 6;
    else if (x >= 56 && x <= 63)
      return 7;
    else if (x >= 64 && x <= 71)
      return 8;
    else if (x >= 72 && x <= 79)
      return 9;
    else if (x >= 80 && x <= 87)
      return 10;
    else if (x >= 88 && x <= 95)
      return 11;
    else
      return -1;
}

inline uint8_t ShittyBoard::getVirtRowFromVirtY(uint8_t y) {
    if (y >= 0 && y <= 3)
      return 0;
    else if (y >= 4 && y <= 7)
      return 1;
    else if (y >= 8 && y <= 11)
      return 2;
    else if (y >= 12 && y <= 15)
      return 3;
    else
      return -1;
}

inline uint8_t ShittyBoard::getPhysicalCoordX(uint8_t x, uint8_t virtRow, uint8_t virtCol) {

  switch (virtRow) {  
    case 0:
    case 2:
      return x+(virtCol*8);
      break;
    case 1:
    case 3:
      return x+((virtCol+1)*8);
      break;
  }

  return -1;
}

inline uint8_t ShittyBoard::getPhysicalCoordY(uint8_t y, uint8_t virtRow, uint8_t virtCol) {

  switch (virtRow) {  
    case 0:
      return y;
    case 1:
    case 2:
      return y-(1*4);
      break;
    case 3:
      return y-(2*4);
      break;
  }

  return -1;
}

inline VirtualCoords ShittyBoard::getCoords(int16_t virt_x, int16_t virt_y)
{
    uint8_t phy_X = getPhysicalCoordX(virt_x, getVirtRowFromVirtY(virt_y),getVirtColFromVirtX(virt_x));
    uint8_t phy_Y = getPhysicalCoordY(virt_y, getVirtRowFromVirtY(virt_y),getVirtColFromVirtX(virt_x));

    coords.x = phy_X;
    coords.y = phy_Y;

    return coords;
}

inline void ShittyBoard::drawIcon(uint16_t *ico, int16_t x, int16_t y, int16_t cols, int16_t rows)
 {
   int i, j;
   for (i = 0; i < rows; i++)
   {
     for (j = 0; j < cols; j++)
     {
       this->drawPixel(x + j, y + i, (uint16_t)ico[i * cols + j]);
     }
   }
 }

inline void ShittyBoard::drawIcon(uint16_t *ico, int16_t x, int16_t y, int16_t cols, int16_t rows, uint16_t fColor, uint16_t bColor)
 {
  this->fillRect(x, y, cols, rows, bColor);
   int i, j;
   for (i = 0; i < rows; i++)
   {
     for (j = 0; j < cols; j++)
     {
      if ((uint16_t)ico[i * cols + j] != 0x0000)
      this->drawPixel(x + j, y + i, fColor);
     }
   }
 }

 
