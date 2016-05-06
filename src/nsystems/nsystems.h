#pragma once

#define MAX_NUMBERS_PER_LINE  6
#define MAX_ROWS              6

typedef void ( * DigitCallback ) ( GContext *, GRect, int );

int draw_decimal_to_base ( GContext *, GRect, int, int, DigitCallback );

void draw_base_callback    ( GContext *, GRect, int ); // Any base from 1 - 16
void draw_binary_callback  ( GContext *, GRect, int ); // Base 2
void draw_bars_callback    ( GContext *, GRect, int ); // Base 5
void draw_decimal_callback ( GContext *, GRect, int ); // Base 10
