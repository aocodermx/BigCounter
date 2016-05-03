#include <pebble.h>
#include "BigCounter.h"
#include "SystemSelector.h"

#include "nsystems/nsystems.h"
#include "../utils.h"

static int s_count;
static int s_base;
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

static void U1_click_handler  ( ClickRecognizerRef, void * );
static void U2_click_handler  ( ClickRecognizerRef, void * );
static void M1_click_handler  ( ClickRecognizerRef, void * );
static void M2_click_handler  ( ClickRecognizerRef, void * );
static void D1_click_handler  ( ClickRecognizerRef, void * );
static void D2_click_handler  ( ClickRecognizerRef, void * );
static void tap_handler       ( AccelAxisType, int32_t );

static void click_config_provider_principal ( void * );
static void click_config_provider_secondary ( void * );
static void set_click_config_provider_principal ( void * );
static void set_click_config_provider_secondary ( void * );


static void window_load ( Window *window ) {
  APP_LOG ( APP_LOG_LEVEL_INFO, "Loading window_big_counter" );
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

  s_base = persist_exists ( KEY_PERSIST_NSYSTEM ) ? persist_read_int ( KEY_PERSIST_NSYSTEM ) : 10;
  APP_LOG ( APP_LOG_LEVEL_INFO, "Base: %d", s_base );

  s_count_layer = layer_create ( GRect ( 0, 0, bounds.size.w - ACTION_BAR_WIDTH, bounds.size.h ) );
  layer_set_update_proc ( s_count_layer, update_count_layer );

  layer_add_child ( window_layer, s_count_layer );
}

static void window_unload ( Window *window ) {
  APP_LOG ( APP_LOG_LEVEL_INFO, "Unloading window_big_counter" );
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
  APP_LOG ( APP_LOG_LEVEL_INFO, "Appear window_big_counter" );
  s_base = persist_exists ( KEY_PERSIST_NSYSTEM ) ? persist_read_int ( KEY_PERSIST_NSYSTEM ) : 10;
  APP_LOG ( APP_LOG_LEVEL_INFO, "Base Returned: %d", s_base );

  s_version     = persist_exists ( KEY_PERSIST_VERSION     ) ? persist_read_int ( KEY_PERSIST_VERSION     ) : 1;
  s_count       = persist_exists ( KEY_PERSIST_COUNT       ) ? persist_read_int ( KEY_PERSIST_COUNT       ) : 0;
  s_tap_enabled = persist_exists ( KEY_PERSIST_TAP_ENABLED ) ? persist_read_int ( KEY_PERSIST_TAP_ENABLED ) : 0;
  if ( s_tap_enabled ) accel_tap_service_subscribe ( tap_handler );
  layer_mark_dirty ( s_count_layer );
}

static void window_disappear ( Window *window ) {
  APP_LOG ( APP_LOG_LEVEL_INFO, "Disappear window_big_counter" );
  accel_tap_service_unsubscribe ( );
  persist_write_int ( KEY_PERSIST_COUNT      , s_count       );
  persist_write_int ( KEY_PERSIST_TAP_ENABLED, s_tap_enabled );
  if ( !persist_exists ( KEY_PERSIST_VERSION ) ) {
    persist_write_int ( KEY_PERSIST_VERSION, 1 );
  }
}


static void update_count_layer ( Layer *layer, GContext *ctx ) {
  GRect bounds = layer_get_bounds ( s_count_layer );

  graphics_context_set_stroke_color ( ctx, GColorBlack );
  graphics_context_set_fill_color   ( ctx, GColorWhite );

  // draw_number_decimal ( ctx, bounds, s_count );

  draw_decimal_to_base ( ctx, bounds, s_count, s_base, draw_base_callback );
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
  if ( s_count != 0)
    s_count--;
  layer_mark_dirty ( s_count_layer );
}

static void U2_click_handler ( ClickRecognizerRef recognizer, void *context ) {
  app_timer_reschedule ( s_action_bar_timer, TIME_ACTION_BAR );
  s_count = 0;
  layer_mark_dirty ( s_count_layer );
}

static void M2_click_handler ( ClickRecognizerRef recognizer, void *context ) {
  window_systemselector_init ( );
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
  APP_LOG ( APP_LOG_LEVEL_INFO, "Init window_big_counter" );
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
  APP_LOG ( APP_LOG_LEVEL_INFO, "Deinit window_big_counter" );
  window_destroy ( window );
}
