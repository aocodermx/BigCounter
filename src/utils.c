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
      return 10;
    case 2:
      return 20;
    case 3:
      return 30;
    case 4:
      return 20;
    case 5:
      return 15;
    default:
      return 20;
  }
}
