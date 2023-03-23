#ifndef WIPPERSNAPPER_DISPLAY_2_H
#define WIPPERSNAPPER_DISPLAY_2_H

#include "ws_drv_display.h"
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
LV_IMG_DECLARE(ws_logo_200px);

// splash screen image
static lv_obj_t *splashImg;

// loading bar icons
static lv_obj_t *lblIconFile, *lblIconWiFi;

// styles used by the loading screen, need to be global or static
static lv_style_t styleIconFile, styleIconWiFi, styleIconTurtle30px,
    styleIconCloud, styleIconCheckmark;

void set_bg_black() {
  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), LV_STATE_DEFAULT);
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

#endif // WIPPERSNAPPER_DISPLAY_2_H
