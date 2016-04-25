#include <pebble.h>
#include "window/BigCounter.h"

// TODO: Set indicator when accelerometer tap is enabled.
// TODO: Improve accelerometer tap sensibility.
// TODO: Change ... icon for a GEAR.
// TODO: Add Configuration Window.
// TODO: Render Big Numbers.
// TODO: Render Big Numbers for other numbering systems.

int main(void) {
  window_bigcounter_init();
  app_event_loop();
  window_bigcounter_deinit();
}
