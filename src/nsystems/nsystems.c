#include <pebble.h>
#include "nsystems.h"
#include "../utils.h"


void draw_decimal_to_base ( GContext * ctx, GRect bounds, int decimal, int dst_base, DigitCallback draw_digit_callback ) {
  int digits_no = get_digits_for ( decimal, dst_base );
  int * result  = malloc         ( digits_no * sizeof ( int ) );
  int digitHeight = bounds.size.h;
  int digitWitdh  = bounds.size.w / digits_no;

  if ( decimal == 0 ) {
    draw_digit_callback ( ctx, GRect ( 0, 0, digitWitdh, digitHeight ), 0, 1 );
    return;
  }

  // Convert decimal in dst base
  for ( int position = 0; decimal != 0; position++ ) {
    result [position] = decimal % dst_base;
    // fprintf ( stdout, "> %d %% %d = %d \n", decimal, dst_base, decimal % dst_base );
    decimal /= dst_base;
  }

  // fprintf ( stdout, "Number in base %d is: ", dst_base );
  for ( int position = digits_no - 1, i = 0; position >= 0; position--, i++ ) {
    // fprintf ( stdout, "%d,", result [position] );
    // CALLBACK TO FUNCTION DRAW_DIGIT with result [position]
    draw_digit_callback ( ctx, GRect ( i * digitWitdh, 0, digitWitdh, digitHeight ), result[position], digits_no );
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
