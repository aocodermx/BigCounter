#pragma once

int myPow          ( int, int );
int get_digits_for ( int decimal, int dst_base );
int get_stroke_width ( int no_digits );
void graphics_draw_line2(GContext *ctx, GPoint p0, GPoint p1, int8_t width);

// static int  get_digits_no ( int, int );
/*
static int get_digits_no ( int number, int base ) {
  int position = 0;
  if ( number == 0 ) return 1;
  while ( number / myPow ( base, position ) != 0  ) {
    position ++;
  }
  return position;
}*/
