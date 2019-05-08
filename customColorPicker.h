#ifndef CUSTOMCOLORPICKER_H
#define CUSTOMCOLORPICKER_H

#include <stdint.h>
#include <map>
#include <utility>
#include "colorPicker.h"

/**
 * customColorPicker: a functor that determines the color that should be used
 * given an x and a y coordinate using a custom pattern.
 *
 */
class customColorPicker : public colorPicker
{
  public:
    /**
     * Constructs a new customColorPicker.
     *
     * @param freq_ Frequency at which to cycle colors
     */
    customColorPicker(PNG& img);

    /**
     * Picks the color for pixel (x, y).
     *
     * @param x The x coordinate to pick a color for.
     * @param y The y coordinat to pick a color for.
     * @return The color chosen for (x, y).
     */
    virtual HSLAPixel operator()(int x, int y);

  private:
    PNG im;
};

#endif
