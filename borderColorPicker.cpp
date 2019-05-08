#include "borderColorPicker.h"

borderColorPicker::borderColorPicker(HSLAPixel fillColor, PNG & img, double tolerance,HSLAPixel center)
{
  ctr = center;
  im = img;
  tol = tolerance;
  color = fillColor;
}

HSLAPixel borderColorPicker::operator()(int x, int y)
{
  for(int i = -3; i <=3; i++){
    for(int j = -3; j <=3; j++){
      if(x+i >= im.width() || (x+i) < 0 || (y+j) >= im.height() || (y+j) < 0){
        return color;
      }
        HSLAPixel* checkPixel = im.getPixel(x + i, y + j);
        if(i*i + j*j <= 9){
          if(ctr.dist(*checkPixel) > tol){
            return color;
        }
      }
    }
  }
  return *(im.getPixel(x,y));
}
