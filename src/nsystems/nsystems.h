#pragma once

#define MAX_NUMBERS_PER_LINE 5

typedef void ( * DigitCallback ) ( GContext *, GRect, int, int );

void draw_decimal_to_base ( GContext *, GRect, int, int, DigitCallback );

void draw_base_callback    ( GContext *, GRect, int, int ); // Any base from 1 - 16
void draw_binary_callback  ( GContext *, GRect, int, int ); // Base 2
void draw_bars_callback    ( GContext *, GRect, int, int ); // Base 5
void draw_decimal_callback ( GContext *, GRect, int, int ); // Base 10
