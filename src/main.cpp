#include "display/ws_drv_display.h"
#include "display/ws_display_ui_helper.h"
#include "tinyusb/Wippersnapper_FS.h" // adafruit_wippersnapper

ws_drv_display tft_st7789(TFT_CS, TFT_DC, TFT_RESET);

void provision() {
    Serial.println("provision...");
    // create FS
    Wippersnapper_FS *fileSystem = new Wippersnapper_FS();
    // parse out the secrets file
//    fileSystem->parseSecrets();
}


void setup(void) {
  Serial.begin(115200);
  // while (!Serial) delay(10);

  tft_st7789.setResolution(240, 240);
  tft_st7789.enableLogging();
  tft_st7789.begin();

  // set screen background to black
  set_bg_black();


  // build the load screen first
  build_load_screen();

  //  provision();

  Serial.println("going into loop()");
}

void loop(void) {
  lv_task_handler(); // Call LittleVGL task handler periodically
  delay(5);
}