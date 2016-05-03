#include <pebble.h>
#include "nsystems.h"
#include "../utils.h"


void draw_decimal_to_base ( GContext * ctx, GRect bounds, int decimal, int dst_base, DigitCallback draw_digit_callback ) {
  int digits_no = get_digits_for ( decimal, dst_base );
  int * result  = malloc         ( digits_no * sizeof ( int ) );
  int no_cols = ( digits_no > MAX_NUMBERS_PER_LINE ) ? ( digits_no + MAX_NUMBERS_PER_LINE - 1 ) / MAX_NUMBERS_PER_LINE : 1;
  int no_rows = ( digits_no > MAX_NUMBERS_PER_LINE ) ? MAX_NUMBERS_PER_LINE : digits_no;
  int digitWitdh  = bounds.size.w / no_rows;
  int digitHeight = bounds.size.h / no_cols;

  if ( decimal == 0 ) {
    draw_digit_callback ( ctx, GRect ( 0, 0, digitWitdh, digitHeight ), 0, 1 );
    return;
  }

  // Convert decimal in dst base
  for ( int i = 0; decimal != 0; i++ ) {
    result [i] = decimal % dst_base;
    // fprintf ( stdout, "> %d %% %d = %d \n", decimal, dst_base, decimal % dst_base );
    // APP_LOG ( APP_LOG_LEVEL_INFO, "> %d %% %d = %d", decimal, dst_base, decimal % dst_base );
    decimal /= dst_base;
  }

  // APP_LOG ( APP_LOG_LEVEL_INFO, "ditigs_no: %d, no_cols: %d, no_rows:%d, digitWitdh: %d, digitHeight: %d", digits_no, no_cols, no_rows, digitWitdh, digitHeight );

  // fprintf ( stdout, "Number in base %d is: ", dst_base );
  int index = digits_no - 1;
  for ( int y = 0; y < no_cols; y++ ) {
    for ( int x = 0; x < no_rows ; x++ ) {
      // fprintf ( stdout, "%d,", result [index] );
      // CALLBACK TO FUNCTION DRAW_DIGIT with result [index]
      // APP_LOG ( APP_LOG_LEVEL_INFO, "( x:%d, y:%d, w:%d, h:%d ): %d", x * digitWitdh, y * digitHeight, digitWitdh, digitHeight, index );
      draw_digit_callback ( ctx, GRect ( x * digitWitdh, y * digitHeight, digitWitdh, digitHeight ), result[index], no_rows );
      index--;
      if ( index < 0)
        break;
    }
  }

  free ( result );
}



void draw_base_callback ( GContext * ctx, GRect box, int digit, int no_digits ) {
  GPoint p1, p2;

  graphics_context_set_stroke_width ( ctx, ( get_stroke_width ( no_digits ) * box.size.w ) / 100 );

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
