#ifndef WS_DISPLAY_UI_HELPER_H
#define WS_DISPLAY_UI_HELPER_H

#include "ws_drv_display.h"

// TODO: Push all the symbols elsewhere!

// lvgl
// FA symbol glyphs
#define SYMBOL_CODE "\xEF\x87\x89"
#define SYMBOL_WIFI "\xEF\x87\xAB"
#define SYMBOL_TURTLE30PX "\xEF\x9C\xA6"
#define SYMBOL_CLOUD "\xEF\x83\x82"
#define SYMBOL_CHECKMARK "\xEF\x81\x98"
#define SYMBOL_ERROR_TRIANGLE "\xEF\x81\xB1"

// FA symbol properties
extern lv_font_t errorTriangle, circle_30px, cloud_30px, turtle_30px, wifi_30px,
    file_code;

// images
LV_IMG_DECLARE(ws_icon_100px);

// loading bar icons
static lv_obj_t *lblIconFile, *lblIconWiFi;

// styles used by the loading screen, need to be global or static
static lv_style_t styleIconFile, styleIconWiFi, styleIconTurtle30px,
    styleIconCloud, styleIconCheckmark;

/* Sets the lvgl default background to black */
void set_bg_black() {
  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), LV_STATE_DEFAULT);
}

// TODO: Can we make this type of thing reusable whenever we need to set up an error?
void buildScreenError(char *errorHeader, char *errorInstructions) {

  // Add circle checkmark
  lv_obj_t *labelErrorTriangle = lv_label_create(lv_scr_act());
  lv_label_set_text(labelErrorTriangle, SYMBOL_ERROR_TRIANGLE);

  static lv_style_t styleErrorTriangle;
  lv_style_init(&styleErrorTriangle);
  lv_style_set_text_color(&styleErrorTriangle, lv_color_white());
  lv_style_set_text_font(&styleErrorTriangle, &errorTriangle); 
  lv_obj_add_style(labelErrorTriangle, &styleErrorTriangle, LV_PART_MAIN);
  lv_obj_align(labelErrorTriangle, LV_ALIGN_TOP_MID, 0, 30);


  // Label (error heading)
  lv_obj_t *labelErrorHeader = lv_label_create(lv_scr_act());
  lv_label_set_text(labelErrorHeader, errorHeader);

  static lv_style_t styleTextBig;
  lv_style_init(&styleTextBig);
  lv_style_set_text_color(&styleTextBig, lv_color_white());
  lv_style_set_text_font(&styleTextBig, &lv_font_montserrat_16); 
  lv_obj_add_style(labelErrorHeader, &styleTextBig, LV_PART_MAIN);
  lv_obj_align(labelErrorHeader, LV_ALIGN_CENTER, 0, 10);


  // Label (error text box)
  lv_obj_t *labelErrorBody = lv_label_create(lv_scr_act());
  lv_label_set_long_mode(labelErrorBody, LV_LABEL_LONG_WRAP);
  lv_label_set_text(labelErrorBody, errorInstructions);

  static lv_style_t styleErrorText;
  lv_style_init(&styleErrorText);
  lv_style_set_text_color(&styleErrorText, lv_color_white());
  lv_style_set_text_font(&styleErrorText, &lv_font_montserrat_12); 
  lv_obj_add_style(labelErrorBody, &styleErrorText, LV_PART_MAIN);
  // small width to allow LABEL_LONG_WRAP
  lv_obj_set_width(labelErrorBody, 220);
  lv_obj_align(labelErrorBody, LV_ALIGN_CENTER, 0, 65);
}

void delete_load_screen() {
    lv_obj_del(lblIconFile);
    lv_obj_del(lblIconWiFi);
    // TODO: More! 
    //lv_obj_del(labelTurtleBar);
}

/* Dynamically builds and shows the loading screen */
void build_load_screen() {
  // adding loading screen image
  lv_obj_t *icon = lv_img_create(lv_scr_act());
  lv_img_set_src(icon, &ws_icon_100px);
  lv_obj_align(icon, LV_ALIGN_TOP_MID, 0, 5);

  // Icon bar
  const lv_coord_t iconBarXStart = 28;
  const lv_coord_t iconBarYOffset = -45; // gives us room for text, too
  const int iconBarXSpaces = 33;         // +10 exactly between icons

  // add symbol_code (30px) to represent settings.json
  lblIconFile = lv_label_create(lv_scr_act());
  lv_label_set_text(lblIconFile, SYMBOL_CODE);
  // formatting
  lv_style_init(&styleIconFile);
  lv_style_set_text_color(&styleIconFile, lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconFile, &file_code);
  lv_obj_add_style(lblIconFile, &styleIconFile, LV_PART_MAIN);
  lv_obj_align(lblIconFile, LV_ALIGN_BOTTOM_LEFT, iconBarXStart,
               iconBarYOffset);

  // add symbol_wifi (30px) to represent wifi connect
  lblIconWiFi = lv_label_create(lv_scr_act());
  lv_label_set_text(lblIconWiFi, SYMBOL_WIFI);
  lv_style_init(&styleIconWiFi);
  lv_style_set_text_color(&styleIconWiFi, lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconWiFi, &wifi_30px);
  lv_obj_add_style(lblIconWiFi, &styleIconWiFi, LV_PART_MAIN);
  lv_obj_align(lblIconWiFi, LV_ALIGN_BOTTOM_LEFT,
               iconBarXStart + (iconBarXSpaces * 1), iconBarYOffset);

  // Add symbol turtle 30px
  lv_obj_t *labelTurtleBar = lv_label_create(lv_scr_act());
  lv_label_set_text(labelTurtleBar, SYMBOL_TURTLE30PX);

  lv_style_init(&styleIconTurtle30px);
  lv_style_set_text_color(&styleIconTurtle30px,
                          lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconTurtle30px, &turtle_30px);
  lv_obj_add_style(labelTurtleBar, &styleIconTurtle30px,
                   LV_PART_MAIN); // 28+(33*2) = 94
  lv_obj_align(labelTurtleBar, LV_ALIGN_BOTTOM_LEFT, 106, iconBarYOffset);

  // Add cloud
  lv_obj_t *labelCloudBar = lv_label_create(lv_scr_act());
  lv_label_set_text(labelCloudBar, SYMBOL_CLOUD);

  lv_style_init(&styleIconCloud);
  lv_style_set_text_color(&styleIconCloud, lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconCloud, &cloud_30px);
  lv_obj_add_style(labelCloudBar, &styleIconCloud, LV_PART_MAIN);
  lv_obj_align(labelCloudBar, LV_ALIGN_BOTTOM_LEFT, iconBarXStart + (106 + 13),
               iconBarYOffset);

  // Add circle checkmark
  lv_obj_t *labelCircleBar = lv_label_create(lv_scr_act());
  lv_label_set_text(labelCircleBar, SYMBOL_CHECKMARK);

  lv_style_init(&styleIconCheckmark);
  lv_style_set_text_color(&styleIconCheckmark,
                          lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconCheckmark, &circle_30px);
  lv_obj_add_style(labelCircleBar, &styleIconCheckmark, LV_PART_MAIN);
  lv_obj_align(labelCircleBar, LV_ALIGN_BOTTOM_LEFT, 160 + 33, iconBarYOffset);
}

#endif // WS_DISPLAY_UI_HELPER_H
