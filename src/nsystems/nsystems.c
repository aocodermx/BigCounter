#include <pebble.h>
#include "nsystems.h"
#include "../utils.h"


void draw_decimal_to_base ( GContext * ctx, GRect bounds, int decimal, int dst_base, DigitCallback draw_digit_callback ) {
  int digits_no = get_digits_for ( decimal, dst_base );
  int no_cols = ( digits_no > MAX_NUMBERS_PER_LINE ) ? ( digits_no + MAX_NUMBERS_PER_LINE - 1 ) / MAX_NUMBERS_PER_LINE : 1;
  int no_rows = ( digits_no > MAX_NUMBERS_PER_LINE ) ? MAX_NUMBERS_PER_LINE : digits_no;
  int digitWitdh  = bounds.size.w / no_rows;
  int digitHeight = bounds.size.h / no_cols;

  if ( decimal == 0 ) {
    graphics_context_set_stroke_width ( ctx, ( get_stroke_width ( 1 ) * digitWitdh ) / 100 );
    draw_digit_callback ( ctx, GRect ( 0, 0, digitWitdh, digitHeight ), 0 );
    return;
  }

  graphics_context_set_stroke_width ( ctx, ( get_stroke_width ( no_rows ) * digitWitdh ) / 100 );

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
}



void draw_base_callback ( GContext * ctx, GRect box, int digit ) {
  GPoint p1, p2;

  switch ( digit ) {
    case 0:
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + box.size.h / 10;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + box.size.h / 10;
      graphics_draw_line ( ctx, p1, p2 );
      break;
    case 1:
      p1.x = box.origin.x + box.size.w / 2;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + box.size.w / 2;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      break;
    case 2:
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + box.size.h / 10;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      break;
    case 3:
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + box.size.h / 10;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      break;
    case 4:
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      break;
    case 5:
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + box.size.h / 10;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      break;
    case 6:
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + box.size.h / 10;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      break;
    case 7:
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + box.size.h / 10;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      break;
    case 8:
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + box.size.h / 10;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + box.size.h / 10;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      break;
    case 9:
      p1.x = box.origin.x + box.size.w / 4;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + box.size.h / 10;
      graphics_draw_line ( ctx, p1, p2 );
      p2.x = box.origin.x + box.size.w / 4;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + box.size.h / 10;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      break;
    case 10: // A
      p1.x = box.origin.x + ( box.size.w / 4 );
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      p2.x = box.origin.x + ( box.size.w / 4 );
      p2.y = box.origin.y + box.size.h / 10;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 );
      graphics_draw_line ( ctx, p1, p2 );
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w / 4 );
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      p2.x = box.origin.x + ( box.size.w / 4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      break;
    case 11:
      p1.x = box.origin.x + ( box.size.w /  4 );
      p1.y = box.origin.y + ( box.size.h / 10 );
      p2.x = box.origin.x + ( box.size.w /  4 );
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p2.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w /  4 );
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      break;
    case 12:
      p1.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 );
      p2.x = box.origin.x + ( box.size.w /  4 );
      p2.y = box.origin.y + ( box.size.h / 10 );
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w /  4 );
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p2.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      break;
    case 13:
      p1.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 );
      p2.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w /  4 );
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p2.x = box.origin.x + ( box.size.w /  4 );
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      break;
    case 14:
      p1.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 );
      p2.x = box.origin.x + ( box.size.w /  4 );
      p2.y = box.origin.y + ( box.size.h / 10 );
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w /  4 );
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p2.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w /  4 );
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      p2.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      break;
    case 15:
      p1.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p1.y = box.origin.y + ( box.size.h / 10 );
      p2.x = box.origin.x + ( box.size.w /  4 );
      p2.y = box.origin.y + ( box.size.h / 10 );
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w /  4 );
      p1.y = box.origin.y + ( box.size.h / 10 ) * 9;
      graphics_draw_line ( ctx, p1, p2 );
      p1.x = box.origin.x + ( box.size.w /  4 );
      p1.y = box.origin.y + ( box.size.h / 10 ) * 5;
      p2.x = box.origin.x + ( box.size.w /  4 ) * 3;
      p2.y = box.origin.y + ( box.size.h / 10 ) * 5;
      graphics_draw_line ( ctx, p1, p2 );
      break;
    default:
      APP_LOG ( APP_LOG_LEVEL_ERROR, "Invalid digit in decimal system %d", digit );
      break;
  }
}
