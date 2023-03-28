#include "display/ws_display_ui_helper.h"
#include "display/ws_drv_display.h"
#include "tinyusb/Wippersnapper_FS.h" // adafruit_wippersnapper

ws_drv_display tft_st7789(TFT_CS, TFT_DC, TFT_RESET);
ws_display_ui_helper ui_helper;

Wippersnapper_FS *fileSystem = nullptr;

void setup(void) {

  tft_st7789.setResolution(240, 240);
  tft_st7789.begin();

  // set screen background to black
  ui_helper.set_bg_black();
  // build the load screen first
  ui_helper.show_scr_load();
  // call task handler
  lv_task_handler();

  // init USB-MSC and FS
  fileSystem = new Wippersnapper_FS();

  // begin serial comm.
  Serial.begin(115200);
  tft_st7789.enableLogging();
  // while (!Serial) delay(10);

  // fileSystem->parseSecrets();
  // call task handler
  ui_helper.greenFile();
  lv_task_handler();

  // Serial.println("going into loop()");
}

void loop(void) {
  lv_task_handler(); // Call LittleVGL task handler periodically
  delay(5);
}