#include "display/ws_drv_display.h"
#include "display/ws_display_ui_helper.h"
#include "tinyusb/Wippersnapper_FS.h" // adafruit_wippersnapper

ws_drv_display tft_st7789(TFT_CS, TFT_DC, TFT_RESET);

Wippersnapper_FS *fileSystem = nullptr;

#define ERR_NO_JSON_HEADER "Secrets.json file not found!"
#define ERR_NO_JSON_INSTRUCTIONS                                               \
  "1. Visit adafru.it/123456 to generate a settings.json file.\n2.Drag and "   \
  "drop the secrets.json file to the WIPPER drive.\n3. Press RESET on your "   \
  "board."


void setup(void) {

  tft_st7789.setResolution(240, 240);
  
  tft_st7789.begin();

  // set screen background to black
  set_bg_black();
  // build the load screen first
  build_load_screen();
  // call task handler
  lv_task_handler();


  // init USB-MSC and FS
  fileSystem = new Wippersnapper_FS();

  // begin serial comm.
  Serial.begin(115200);
  tft_st7789.enableLogging();
  //while (!Serial) delay(10);

  fileSystem->parseSecrets();


  // Serial.println("going into loop()");
}

void loop(void) {
  lv_task_handler(); // Call LittleVGL task handler periodically
  delay(5);
}