#include <pebble.h>
#include "nsystems.h"
#include "../utils.h"


int draw_decimal_to_base ( GContext * ctx, GRect bounds, int decimal, int dst_base, DigitCallback draw_digit_callback ) {
  if ( myPow ( dst_base, MAX_ROWS * MAX_NUMBERS_PER_LINE ) == decimal && decimal != 0 )
    dst_base ++;

  int digits_no = get_digits_for ( decimal, dst_base );
  int no_cols = ( digits_no > MAX_NUMBERS_PER_LINE ) ? ( digits_no + MAX_NUMBERS_PER_LINE - 1 ) / MAX_NUMBERS_PER_LINE : 1;
  int no_rows = ( digits_no > MAX_NUMBERS_PER_LINE ) ? MAX_NUMBERS_PER_LINE : digits_no;
  int digitWitdh  = bounds.size.w / no_rows;
  int digitHeight = bounds.size.h / no_cols;

  if ( decimal == 0 ) {
    #if defined ( PBL_SDK_3 )
      graphics_context_set_stroke_width ( ctx, ( get_stroke_width ( 1 ) * digitWitdh ) / 100 );
    #endif
    draw_digit_callback ( ctx, GRect ( 0, 0, digitWitdh, digitHeight ), 0 );
    return dst_base;
  }

  #if defined ( PBL_SDK_3 )
    graphics_context_set_stroke_width ( ctx, ( get_stroke_width ( no_rows ) * digitWitdh ) / 100 );
  #endif

  // APP_LOG ( APP_LOG_LEVEL_INFO, "ditigs_no: %d, no_cols: %d, no_rows:%d, digitWitdh: %d, digitHeight: %d", digits_no, no_cols, no_rows, digitWitdh, digitHeight );
  for ( int y = no_cols - 1, index = 0; y >= 0; y-- ) {
    for ( int x = no_rows -1; x >= 0; x--, index++ ) {
      // APP_LOG ( APP_LOG_LEVEL_INFO, "[%d]( x:%d, y:%d, w:%d, h:%d ): %d", index, x * digitWitdh, y * digitHeight, digitWitdh, digitHeight, decimal % dst_base );
      draw_digit_callback ( ctx, GRect ( x * digitWitdh, y * digitHeight, digitWitdh, digitHeight ), decimal % dst_base );
      decimal /= dst_base;
      if ( index >= digits_no - 1 )
        break;
    }
  }
  return dst_base;
}

void draw_line_fallback ( GContext * ctx, GPoint p1, GPoint p2, int width ) {
  #if defined ( PBL_SDK_3 )
    draw_line_fallback ( ctx, p1, p2, line_width );
  #else
    graphics_draw_line2 ( ctx, p1, p2, width );
  #endif
}


void draw_base_callback ( GContext * ctx, GRect box, int digit ) {
  GPoint p1, p2;
  int line_width = ( 15 * box.size.w ) / 100;

  switch ( digit ) {
    case 0:
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + box.size.h / 10;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + box.size.h / 10;
      draw_line_fallback ( ctx, p1, p2, line_width );
      break;
    case 1:
      p1.x = box.origin.x + box.size.w / 2;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + box.size.w / 2;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      break;
    case 2:
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + box.size.h / 10;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      break;
    case 3:
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + box.size.h / 10;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      break;
    case 4:
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      break;
    case 5:
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + box.size.h / 10;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      break;
    case 6:
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + box.size.h / 10;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      break;
    case 7:
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + box.size.h / 10;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      break;
    case 8:
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + box.size.h / 10;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + box.size.h / 10;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      break;
    case 9:
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + box.size.h / 10;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      break;
    case 10: // A
      p1.x = box.origin.x + ( box.size.w / 4 );
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      p2.x = box.origin.x + ( box.size.w / 4 );
      p2.y = box.origin.y + box.size.h / 10;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 );
      draw_line_fallback ( ctx, p1, p2, line_width );
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w / 4 );
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      break;
    case 11:
      p1.x = box.origin.x + ( box.size.w /  4 );
      p1.y = box.origin.y + ( box.size.h / 10 );
      p2.x = box.origin.x + ( box.size.w /  4 );
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p2.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w /  4 );
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      break;
    case 12:
      p1.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 );
      p2.x = box.origin.x + ( box.size.w /  4 );
      p2.y = box.origin.y + ( box.size.h / 10 );
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w /  4 );
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p2.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      break;
    case 13:
      p1.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 );
      p2.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w /  4 );
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p2.x = box.origin.x + ( box.size.w /  4 );
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      break;
    case 14:
      p1.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 );
      p2.x = box.origin.x + ( box.size.w /  4 );
      p2.y = box.origin.y + ( box.size.h / 10 );
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w /  4 );
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p2.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w /  4 );
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      p2.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      break;
    case 15:
      p1.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 );
      p2.x = box.origin.x + ( box.size.w /  4 );
      p2.y = box.origin.y + ( box.size.h / 10 );
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w /  4 );
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      draw_line_fallback ( ctx, p1, p2, line_width );
      p1.x = box.origin.x + ( box.size.w /  4 );
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      p2.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      draw_line_fallback ( ctx, p1, p2, line_width );
      break;
    default:
      APP_LOG ( APP_LOG_LEVEL_ERROR, "Invalid digit in decimal system %d", digit );
      break;
  }
}
