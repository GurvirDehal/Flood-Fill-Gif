/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace.
 *
 */
//#include "filler.h"
#include <algorithm>

vector<vector<bool>> visited;

HSLAPixel ctr;
unsigned int k;

animation filler::fillStripeDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq)
{
  stripeColorPicker a(fillColor, stripeSpacing);
  return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillBorderDFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{

  borderColorPicker a(borderColor, img, tolerance, *(img.getPixel(x,y)));
  return fill<Stack>(img,x,y,a, tolerance, frameFreq);
}

animation filler::fillCustomDFS(PNG& img, int x, int y,
                                    double tolerance, int frameFreq)
{

  customColorPicker a(img);
  return fill<Stack>(img,x,y,a, tolerance, frameFreq);
}

animation filler::fillCustomBFS(PNG& img, int x, int y,
                                    double tolerance, int frameFreq)
{

  customColorPicker a(img);
  return fill<Queue>(img,x,y,a, tolerance, frameFreq);
}

/* Given implementation of a DFS rainbow fill. */
animation filler::fillRainDFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
    rainbowColorPicker a(freq);
    return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillStripeBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq)
{
  stripeColorPicker a(fillColor, stripeSpacing);
  return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillBorderBFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
  borderColorPicker a(borderColor, img, tolerance, *(img.getPixel(x,y)));
  return fill<Queue>(img,x,y,a, tolerance, frameFreq);
}

/* Given implementation of a BFS rainbow fill. */
animation filler::fillRainBFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
    rainbowColorPicker a(freq);
    return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       double tolerance, int frameFreq)
{
    animation anim;
    k = 0; // initialize k to 0
    OrderingStructure<pair<int, int>> OS;

    ctr = *(img.getPixel(x,y));  //initialize center to (x,y)
    visited = vector<vector<bool> >(img.width() , vector<bool>(img.height())); // initialize visited to be a y by x matrix


    processPixel(img, x,y, fillColor, tolerance, anim, frameFreq, OS); // process the center pixel
    int array[] = {1,0,-1,-1,-1,0,1,1}; // array of x-coordinate offsets to give the
                                        //correct order when traversing (x,y)'s neightbours

     while(!OS.isEmpty()) {
      pair<int, int> p = OS.remove(); // remove and get the first element (coordinate) on the structure
                                      // store it in pair p, where x = p.first, y = p.second
      for(int i = 0; i<8; i++) {
          // add the offsets in array to (x,y) to process the neighbours in the correct sequence
          // note that the y-coordinate offsets are [-1,-1,-1,0,1,1,1,0], instead of making a new array, we can use
          // the first array along with the modulus operator because this sequence is the same as the x coordinates, just shifted.
          processPixel(img, p.first+array[i],p.second+array[(2+i)%8], fillColor,tolerance, anim, frameFreq, OS);
      }
    }
      anim.addFrame(img); // add the final frame to the animation

    return anim;
}

void filler::processPixel(PNG& img, int x, int y, colorPicker& fillColor,double tolerance,
                          animation& anim, int frameFreq, OrderingStructure<pair<int,int>>& os)
{

  if(((x>=0) && (y>=0) && (x<img.width()) && (y<img.height()))) { //if coordinate is within image
    if (visited[x][y] == 0 ) { // if not already processed
      if(ctr.dist(*(img.getPixel(x,y))) <= tolerance) { // if color of pixel is within tolerance
        *(img.getPixel(x,y)) = fillColor.operator()(x,y); // change color to fill color
        visited[x][y] = 1; // change pixel to processed
        k = ++k%frameFreq; // increment k and then mod it by frameFreq
        if(k == 0) // if k is a multiple of frameFreq, then add img to animation
          anim.addFrame(img);

        os.add(make_pair(x,y)); // add pixel coordiantes to ordered structure
      }
    }
  }
}
