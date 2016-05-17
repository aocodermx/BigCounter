#include <pebble.h>
#include "utils.h"

int myPow ( int base, int power ) {
  if ( power == 0 ) return 1;
  int result = base;
  for ( int i = 1; i<power; i++ ) {
    result *= base;
  }
  return result;
}

int get_digits_for ( int decimal, int dst_base ) {
  int i = 0;
  if ( decimal == 0 ) return 1;
  while ( myPow ( dst_base, i ) <= decimal ) i++;
  return i;
}

int get_stroke_width ( int no_digits ) {
  switch ( no_digits ) {
    case 1:
      return 20;
    case 2:
    case 3:
    case 4:
    case 5:
      return 30;
    default:
      return 25;
  }
}


// Draw line with width
// (Based on code found here http://rosettacode.org/wiki/Bitmap/Bresenham's_line_algorithm#C)
void graphics_draw_line2(GContext *ctx, GPoint p0, GPoint p1, int8_t width) {
  // Order points so that lower x is first
  int16_t x0, x1, y0, y1;
  if (p0.x <= p1.x) {
    x0 = p0.x; x1 = p1.x; y0 = p0.y; y1 = p1.y;
  } else {
    x0 = p1.x; x1 = p0.x; y0 = p1.y; y1 = p0.y;
  }

  // Init loop variables
  int16_t dx = x1-x0;
  int16_t dy = abs(y1-y0);
  int16_t sy = y0<y1 ? 1 : -1;
  int16_t err = (dx>dy ? dx : -dy)/2;
  int16_t e2;

  // Calculate whether line thickness will be added vertically or horizontally based on line angle
  int8_t xdiff, ydiff;

  if (dx > dy) {
    xdiff = 0;
    ydiff = width/2;
  } else {
    xdiff = width/2;
    ydiff = 0;
  }

  // Use Bresenham's integer algorithm, with slight modification for line width, to draw line at any angle
  while (true) {
    // Draw line thickness at each point by drawing another line
    // (horizontally when > +/-45 degrees, vertically when <= +/-45 degrees)
    graphics_draw_line(ctx, GPoint(x0-xdiff, y0-ydiff), GPoint(x0+xdiff, y0+ydiff));

    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0++; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}
