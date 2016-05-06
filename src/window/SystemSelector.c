#include <pebble.h>
#include "SystemSelector.h"

static Window * window_system_selector;
static int s_nsystem;

static SimpleMenuLayer   *s_systems_menu;
static SimpleMenuSection  s_systems_sections [1];
static SimpleMenuItem     s_systems [ 15 ];
// static char *s_system_names [ 4 ];

static void window_load ( Window * );
static void window_unload ( Window * );
static void window_appear ( Window * );
static void window_disappear ( Window * );

static void item_selected_handler ( int, void * );


static void window_load ( Window * window ) {
  Layer *window_layer = window_get_root_layer ( window );
  GRect bounds = layer_get_bounds ( window_layer );

  #ifdef PBL_COLOR
    window_set_background_color ( window, GColorPictonBlue );
  #endif

  s_systems [ 0 ] = ( SimpleMenuItem ) {
    .title = "Base 2",
    .subtitle = " - Binary",
    .callback = item_selected_handler,
  };

  s_systems [ 1 ] = ( SimpleMenuItem ) {
    .title = "Base 3",
    .subtitle = " - Ternary",
    .callback = item_selected_handler,
  };

  s_systems [ 2 ] = ( SimpleMenuItem ) {
    .title = "Base 4",
    .subtitle = " - Quaternary",
    .callback = item_selected_handler,
  };

  s_systems [ 3 ] = ( SimpleMenuItem ) {
    .title = "Base 5",
    .subtitle = " - Quinary",
    .callback = item_selected_handler,
  };

  s_systems [ 4 ] = ( SimpleMenuItem ) {
    .title = "Base 6",
    .subtitle = " - Senary",
    .callback = item_selected_handler,
  };

  s_systems [ 5 ] = ( SimpleMenuItem ) {
    .title = "Base 7",
    .subtitle = " - Septenary",
    .callback = item_selected_handler,
  };

  s_systems [ 6 ] = ( SimpleMenuItem ) {
    .title = "Base 8",
    .subtitle = " - Octal",
    .callback = item_selected_handler,
  };

  s_systems [ 7 ] = ( SimpleMenuItem ) {
    .title = "Base 9",
    .subtitle = " - Nonary",
    .callback = item_selected_handler,
  };

  s_systems [ 8 ] = ( SimpleMenuItem ) {
    .title = "Base 10",
    .subtitle = " - Decimal",
    .callback = item_selected_handler,
  };

  s_systems [ 9 ] = ( SimpleMenuItem ) {
    .title = "Base 11",
    .subtitle = " - Undecimal",
    .callback = item_selected_handler,
  };

  s_systems [ 10 ] = ( SimpleMenuItem ) {
    .title = "Base 12",
    .subtitle = " - Duodecimal",
    .callback = item_selected_handler,
  };

  s_systems [ 11 ] = ( SimpleMenuItem ) {
    .title = "Base 13",
    .subtitle = " - Tridecimal",
    .callback = item_selected_handler,
  };

  s_systems [ 12 ] = ( SimpleMenuItem ) {
    .title = "Base 14",
    .subtitle = " - Quatuordecimal",
    .callback = item_selected_handler,
  };

  s_systems [ 13 ] = ( SimpleMenuItem ) {
    .title = "Base 15",
    .subtitle = " - Quindecimal",
    .callback = item_selected_handler,
  };

  s_systems [ 14 ] = ( SimpleMenuItem ) {
    .title = "Base 16",
    .subtitle = " - Hexadecimal",
    .callback = item_selected_handler,
  };

  s_systems_sections [ 0 ] = ( SimpleMenuSection ) {
    .title = "By base",
    .num_items = 15,
    .items     = s_systems,
  };

  s_systems_menu = simple_menu_layer_create ( bounds, window, s_systems_sections , 1, NULL );

  #ifdef PBL_COLOR
    MenuLayer *mlayer = simple_menu_layer_get_menu_layer ( s_systems_menu );
    menu_layer_set_normal_colors ( mlayer, GColorPictonBlue, GColorBlack );
    menu_layer_set_highlight_colors ( mlayer, GColorOxfordBlue, GColorWhite );
  #endif


  layer_add_child ( window_layer, simple_menu_layer_get_layer ( s_systems_menu ) );

}
static void window_unload ( Window * window ) {
  simple_menu_layer_destroy ( s_systems_menu );
}

static void window_appear ( Window * window ) {
  s_nsystem = persist_exists ( KEY_PERSIST_NSYSTEM ) ? persist_read_int ( KEY_PERSIST_NSYSTEM ) : 10;
  simple_menu_layer_set_selected_index ( s_systems_menu, s_nsystem - 2, true );
}

static void window_disappear ( Window * window ) {
  persist_write_int ( KEY_PERSIST_NSYSTEM, s_nsystem );
}

static void item_selected_handler ( int index, void * context ) {
  s_nsystem = index + 2;
  window_stack_remove ( window_system_selector, true );
}




void window_systemselector_init ( void ) {
  window_system_selector = window_create ( );
  window_set_window_handlers ( window_system_selector, ( WindowHandlers ) {
    .load      = window_load     ,
    .unload    = window_unload   ,
    .appear    = window_appear   ,
    .disappear = window_disappear,
  } );

  window_stack_push ( window_system_selector, true );
}

void window_systemselector_deinit ( void ) {
  window_destroy ( window_system_selector );
}
