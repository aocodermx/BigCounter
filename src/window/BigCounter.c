#include <pebble.h>
#include "BigCounter.h"

#include "nsystems/nsystems.h"

static int s_count;
static int s_version;
static int s_tap_enabled;
static Window         *window;
static Layer          *s_count_layer;
static GBitmap        *s_icon_action_U1;
static GBitmap        *s_icon_action_U2;
static GBitmap        *s_icon_action_M1;
static GBitmap        *s_icon_action_M2;
static GBitmap        *s_icon_action_D1;
static GBitmap        *s_icon_action_D2;
static AppTimer       *s_action_bar_timer;
static ActionBarLayer *s_action_bar;

static void window_load        ( Window * );
static void window_unload      ( Window * );
static void window_appear      ( Window * );
static void window_disappear   ( Window * );
static void update_count_layer ( Layer *, GContext * );
static int  get_digits_no      ( int, int );

static void U1_click_handler  ( ClickRecognizerRef, void * );
static void U2_click_handler  ( ClickRecognizerRef, void * );
static void M1_click_handler  ( ClickRecognizerRef, void * );
static void M2_click_handler  ( ClickRecognizerRef, void * );
static void D1_click_handler  ( ClickRecognizerRef, void * );
static void D2_click_handler  ( ClickRecognizerRef, void * );
static void tap_handler       ( AccelAxisType, int32_t );
static int  myPow             ( int, int );

static void click_config_provider_principal ( void * );
static void click_config_provider_secondary ( void * );
static void set_click_config_provider_principal ( void * );
static void set_click_config_provider_secondary ( void * );


static void window_load ( Window *window ) {
  Layer *window_layer = window_get_root_layer ( window );
  GRect bounds = layer_get_bounds ( window_layer );

  s_action_bar = action_bar_layer_create          ( );
  action_bar_layer_add_to_window                  ( s_action_bar, window );
  s_icon_action_U1 = gbitmap_create_with_resource ( RESOURCE_ID_ICON_ACTION_U1 );
  s_icon_action_U2 = gbitmap_create_with_resource ( RESOURCE_ID_ICON_ACTION_U2 );
  s_icon_action_M1 = gbitmap_create_with_resource ( RESOURCE_ID_ICON_ACTION_M1 );
  s_icon_action_M2 = gbitmap_create_with_resource ( RESOURCE_ID_ICON_ACTION_M2 );
  s_icon_action_D1 = gbitmap_create_with_resource ( RESOURCE_ID_ICON_ACTION_D1 );
  s_icon_action_D2 = gbitmap_create_with_resource ( RESOURCE_ID_ICON_ACTION_D2 );

  set_click_config_provider_principal ( NULL );

  s_count_layer = layer_create ( GRect ( 0, 0, bounds.size.w - ACTION_BAR_WIDTH, bounds.size.h ) );
  layer_set_update_proc ( s_count_layer, update_count_layer );

  layer_add_child ( window_layer, s_count_layer );
}

static void window_unload ( Window *window ) {
  layer_destroy      ( s_count_layer    );
  gbitmap_destroy    ( s_icon_action_U1 );
  gbitmap_destroy    ( s_icon_action_U2 );
  gbitmap_destroy    ( s_icon_action_M1 );
  gbitmap_destroy    ( s_icon_action_M2 );
  gbitmap_destroy    ( s_icon_action_D1 );
  gbitmap_destroy    ( s_icon_action_D2 );
  action_bar_layer_destroy ( s_action_bar );
}

static void window_appear    ( Window *window ) {
  s_version     = persist_exists ( KEY_PERSIST_VERSION     ) ? persist_read_int ( KEY_PERSIST_VERSION     ) : 1;
  s_count       = persist_exists ( KEY_PERSIST_COUNT       ) ? persist_read_int ( KEY_PERSIST_COUNT       ) : 0;
  s_tap_enabled = persist_exists ( KEY_PERSIST_TAP_ENABLED ) ? persist_read_int ( KEY_PERSIST_TAP_ENABLED ) : 0;
  if ( s_tap_enabled ) accel_tap_service_subscribe ( tap_handler );
  layer_mark_dirty ( s_count_layer );
}

static void window_disappear ( Window *window ) {
  persist_write_int ( KEY_PERSIST_COUNT      , s_count       );
  persist_write_int ( KEY_PERSIST_TAP_ENABLED, s_tap_enabled );
  if ( !persist_exists ( KEY_PERSIST_VERSION ) ) {
    persist_write_int ( KEY_PERSIST_VERSION, 1 );
  }
}


static void update_count_layer ( Layer *layer, GContext *ctx ) {
  GRect bounds = layer_get_bounds ( s_count_layer );
  int digits = get_digits_no ( s_count, 10 );
  int digitWitdh = bounds.size.w / digits;
  int digitHeight = bounds.size.h;
  int tmp_count = s_count;

  graphics_context_set_stroke_color ( ctx, GColorBlack );
  graphics_context_set_fill_color   ( ctx, GColorWhite );

  // APP_LOG ( APP_LOG_LEVEL_INFO, "Update count layer: %d, digits: %d", s_count, digits );

  for ( int a = 0; a < digits; a++) {
    int digit = tmp_count / myPow ( 10, digits - a - 1 );
    draw_digit_decimal ( ctx, GRect ( a * digitWitdh, 0, digitWitdh, digitHeight ), digit, digits );
    tmp_count -= digit * myPow ( 10, digits - a - 1 );
  }
}

static int get_digits_no ( int number, int base ) {
  int position = 0;
  if ( number == 0 ) return 1;
  while ( number / myPow ( base, position ) != 0  ) {
    position ++;
  }
  return position;
}

static void U1_click_handler ( ClickRecognizerRef recognizer, void *context ) {
  s_count++;
  layer_mark_dirty ( s_count_layer );
}

static void M1_click_handler ( ClickRecognizerRef recognizer, void *context ) {
  set_click_config_provider_secondary ( NULL );
  s_action_bar_timer = app_timer_register ( TIME_ACTION_BAR, set_click_config_provider_principal, NULL );
}

static void D1_click_handler ( ClickRecognizerRef recognizer, void *context ) {
  s_count--;
  layer_mark_dirty ( s_count_layer );
}

static void U2_click_handler ( ClickRecognizerRef recognizer, void *context ) {
  app_timer_reschedule ( s_action_bar_timer, TIME_ACTION_BAR );
  s_count = 0;
  layer_mark_dirty ( s_count_layer );
}

static void M2_click_handler ( ClickRecognizerRef recognizer, void *context ) {
  // Call Settings Window
}

static void D2_click_handler ( ClickRecognizerRef recognizer, void *context ) {
  app_timer_reschedule ( s_action_bar_timer, TIME_ACTION_BAR );
  s_tap_enabled ^= 1;

  if ( s_tap_enabled )
    accel_tap_service_subscribe ( tap_handler );
  else
    accel_tap_service_unsubscribe ( );

  layer_mark_dirty ( s_count_layer );
}

static void tap_handler ( AccelAxisType axis, int32_t direction ) {
  s_count++;
  /*
  switch ( axis ) {
    case ACCEL_AXIS_Y:
      s_count--;
      break;
    case ACCEL_AXIS_X:
      s_count++;
      break;
    default:
      break;
  }
  */
  layer_mark_dirty ( s_count_layer );
}

static int myPow ( int base, int power ) {
  if ( power == 0 ) return 1;
  int result = base;
  for ( int i = 1; i<power; i++ ) {
    result *= base;
  }
  return result;
}

static void click_config_provider_principal ( void *context ) {
  window_single_click_subscribe ( BUTTON_ID_UP    , U1_click_handler );
  window_single_click_subscribe ( BUTTON_ID_SELECT, M1_click_handler );
  window_single_click_subscribe ( BUTTON_ID_DOWN  , D1_click_handler );
}

static void click_config_provider_secondary ( void *context ) {
  window_single_click_subscribe ( BUTTON_ID_UP    , U2_click_handler );
  window_single_click_subscribe ( BUTTON_ID_SELECT, M2_click_handler );
  window_single_click_subscribe ( BUTTON_ID_DOWN  , D2_click_handler );
}

static void set_click_config_provider_principal ( void *data ) {
  window_set_click_config_provider ( window, click_config_provider_principal );

  action_bar_layer_clear_icon ( s_action_bar, BUTTON_ID_UP );
  action_bar_layer_clear_icon ( s_action_bar, BUTTON_ID_SELECT );
  action_bar_layer_clear_icon ( s_action_bar, BUTTON_ID_DOWN );

  action_bar_layer_set_icon ( s_action_bar, BUTTON_ID_UP    , s_icon_action_U1 );
  action_bar_layer_set_icon ( s_action_bar, BUTTON_ID_SELECT, s_icon_action_M1 );
  action_bar_layer_set_icon ( s_action_bar, BUTTON_ID_DOWN  , s_icon_action_D1 );

  action_bar_layer_set_click_config_provider ( s_action_bar, ( ClickConfigProvider ) click_config_provider_principal );
}
static void set_click_config_provider_secondary ( void *data ) {
  window_set_click_config_provider ( window, click_config_provider_secondary );

  action_bar_layer_clear_icon ( s_action_bar, BUTTON_ID_UP );
  action_bar_layer_clear_icon ( s_action_bar, BUTTON_ID_SELECT );
  action_bar_layer_clear_icon ( s_action_bar, BUTTON_ID_DOWN );

  action_bar_layer_set_icon ( s_action_bar, BUTTON_ID_UP, s_icon_action_U2 );
  action_bar_layer_set_icon ( s_action_bar, BUTTON_ID_SELECT, s_icon_action_M2 );
  action_bar_layer_set_icon ( s_action_bar, BUTTON_ID_DOWN, s_icon_action_D2 );

  action_bar_layer_set_click_config_provider ( s_action_bar, ( ClickConfigProvider ) click_config_provider_secondary );
}


void window_bigcounter_init ( void ) {
  window = window_create ( );
  //window_set_click_config_provider ( window, click_config_provider );
  window_set_window_handlers ( window, ( WindowHandlers ) {
    .load      = window_load     ,
    .unload    = window_unload   ,
    .appear    = window_appear   ,
    .disappear = window_disappear,
  } );

  window_stack_push ( window, true );
}

void window_bigcounter_deinit ( void ) {
  window_destroy ( window );
}
