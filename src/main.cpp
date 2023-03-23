#include "display/ws_drv_display.h"
#include "display/ws_display_ui_helper.h"
#include "tinyusb/Wippersnapper_FS.h" // adafruit_wippersnapper

ws_drv_display tft_st7789(TFT_CS, TFT_DC, TFT_RESET);

#define ERR_NO_JSON_HEADER "Secrets.json file not found!"
#define ERR_NO_JSON_INSTRUCTIONS                                               \
  "1. Visit adafru.it/123456 to generate a settings.json file.\n2.Drag and "   \
  "drop the secrets.json file to the WIPPER drive.\n3. Press RESET on your "   \
  "board."

void provision() {
    Serial.println("provision...");
    // create FS
    Wippersnapper_FS *fileSystem = new Wippersnapper_FS();
    // Does secrets.json file exist on the filesystem?
    // configFileExists()
    // for now, we'll mock it as false since we need the alert screen to appear
    bool configFileExists = false;
    if (! configFileExists) {
        // TODO
        delete_load_screen();
        buildScreenError(ERR_NO_JSON_HEADER, ERR_NO_JSON_INSTRUCTIONS);
    }
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

  provision();

  Serial.println("going into loop()");
}

void loop(void) {
  lv_task_handler(); // Call LittleVGL task handler periodically
  delay(5);
}