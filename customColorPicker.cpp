#include "customColorPicker.h"
#include <math.h>

using std::pair;
using std::map;

customColorPicker::customColorPicker(PNG& img)
{
  im = img;
}

HSLAPixel customColorPicker::operator()(int x, int y)
{
    HSLAPixel* p = im.getPixel(x,y);
    HSLAPixel ret;
    ret.h = (double)((180+(int)(p->h))%360);
    ret.s = 1;
    ret.l = 1-(p->l);
    ret.a = p->a;
    return ret;

}
