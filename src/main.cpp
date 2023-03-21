#include <Arduino.h>
// Minimal "Hello" example for LittlevGL on Adafruit Funhouse. Requires
// LittlevGL, Adafruit_LvGL_Glue, Adafruit_GFX and Adafruit_ST7735
// libraries.

// Prior Adafruit_LvGL_Glue users: see hello_changes example for updates!

#include <Adafruit_LvGL_Glue.h> // Always include this BEFORE lvgl.h!
#include <Adafruit_ST7789.h>
#include <lvgl.h>

// FA symbol glyphs
#define SYMBOL_CODE "\xEF\x87\x89"
#define SYMBOL_WIFI "\xEF\x87\xAB"
#define SYMBOL_TURTLE30PX "\xEF\x9C\xA6"
#define SYMBOL_CLOUD "\xEF\x83\x82"
#define SYMBOL_CHECKMARK "\xEF\x81\x98"
#define SYMBOL_ERROR_TRIANGLE "\xEF\x81\xB1"

// images
LV_IMG_DECLARE(ws_icon_100px);
LV_IMG_DECLARE(ws_logo_200px);

// FA symbol properties
extern lv_font_t errorTriangle, circle_30px, cloud_30px, turtle_30px, wifi_30px,
    file_code;

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RESET);
Adafruit_LvGL_Glue glue;

// Styles used by the loading screen, need to be global or static
static lv_style_t styleIconFile, styleIconWiFi, styleIconTurtle30px, styleIconCloud, styleIconCheckmark;


void my_log_cb(const char * buf)
{
  Serial.printf(buf);
}


lv_timer_t* splashTask;
lv_obj_t *splashImg;

  // Icon bar offset and spacing
  const lv_coord_t iconBarXStart = 28;
  const lv_coord_t iconBarYOffset = -45; // gives us room for text, too
  const int iconBarXSpaces = 33;         // +10 exactly between icons

void load_task(lv_timer_t * timer) {
  Serial.printf("load_task()");
  // clear out the splash screen
  Serial.printf("load_task(): clearing splash screen");
  lv_obj_add_flag(splashImg, LV_OBJ_FLAG_HIDDEN);

  Serial.printf("load_task(): building load screen");
  // adding loading screen image
  lv_obj_t *icon = lv_img_create(lv_scr_act());
  lv_img_set_src(icon, &ws_icon_100px);
  lv_obj_align(icon, LV_ALIGN_TOP_MID, 0, 5);

  // add symbol_code (30px) to represent settings.json
  lv_obj_t *labelIconFile = lv_label_create(lv_scr_act());
  lv_label_set_text(labelIconFile, SYMBOL_CODE);
  // formatting
  lv_style_init(&styleIconFile);
  lv_style_set_text_color(&styleIconFile, lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconFile, &file_code);
  lv_obj_add_style(labelIconFile, &styleIconFile, LV_PART_MAIN);
  lv_obj_align(labelIconFile, LV_ALIGN_BOTTOM_LEFT, iconBarXStart,
               iconBarYOffset);
}

void splash_task(lv_timer_t * timer) {
  Serial.printf("splash_task()");
  // create and load splash screen 
  
  // create and center the full logo (200px
  splashImg = lv_img_create(lv_scr_act());
  lv_img_set_src(splashImg, &ws_logo_200px);
  lv_obj_align(splashImg, LV_ALIGN_CENTER, 0, 0);

  lv_timer_del(timer); // one-shot task, delete

  // add load_task to timer handler
  lv_timer_create(load_task, 5000, NULL);
}


void setup(void) {
  Serial.begin(115200);
  //while (!Serial) delay(10);

  // Initialize display BEFORE glue setup
  tft.init(240, 240);
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH);

  // Initialize glue, passing in address of display
  LvGLStatus status = glue.begin(&tft);
  if (status != LVGL_OK) {
    Serial.printf("Glue error %d\r\n", (int)status);
    for (;;)
      ;
  }

  lv_log_register_print_cb(my_log_cb);

  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), LV_STATE_DEFAULT);
  // task 1
  Serial.printf("Setup");
  splashTask = lv_timer_create(splash_task, 0, NULL);


}

void loop(void) {
  lv_task_handler(); // Call LittleVGL task handler periodically
  delay(5);
}