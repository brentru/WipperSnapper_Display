/*!
 * @file ws_display_ui_helper.h
 *
 * LVGL "helper" class for WipperSnapper.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Copyright (c) Brent Rubell 2023 for Adafruit Industries.
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */

#ifndef WS_DISPLAY_UI_HELPER_H
#define WS_DISPLAY_UI_HELPER_H

#include "ws_drv_display.h"
#include "ws_loading_tooltips.h"

// External Fonts
#define SYMBOL_CODE "\xEF\x87\x89"
#define SYMBOL_WIFI "\xEF\x87\xAB"
#define SYMBOL_TURTLE30PX "\xEF\x9C\xA6"
#define SYMBOL_CLOUD "\xEF\x83\x82"
#define SYMBOL_CHECKMARK "\xEF\x81\x98"
#define SYMBOL_ERROR_TRIANGLE "\xEF\x81\xB1"
LV_FONT_DECLARE(errorTriangle);
LV_FONT_DECLARE(file);
LV_FONT_DECLARE(wifi_30px);
LV_FONT_DECLARE(cloud_30px);
LV_FONT_DECLARE(turtle_30px);
LV_FONT_DECLARE(circle_30px);

// Images
LV_IMG_DECLARE(ws_icon_100px);

/* Screen: Loading */
// Objects
static lv_obj_t *imgWSLogo;
static lv_obj_t *lblIconFile;
static lv_obj_t *lblIconWiFi;
static lv_obj_t *labelTurtleBar;
static lv_obj_t *labelCloudBar;
static lv_obj_t *labelCircleBar;
static lv_obj_t *lblStatusText;
static lv_obj_t *lblTipText;
// Styles
static lv_style_t styleIconFile;
static lv_style_t styleIconWiFi;
static lv_style_t styleIconTurtle30px;
static lv_style_t styleIconCloud;
static lv_style_t styleIconCheckmark;

/* Screen: Error */
// Objects
static lv_obj_t *labelErrorTriangle;
static lv_obj_t *labelErrorHeader;
static lv_obj_t *labelErrorBody;
// Styles
static lv_style_t styleErrorTriangle;
static lv_style_t styleLabelErrorLarge;
static lv_style_t styleLabelErrorSmall;

// used by set_load_bar_icon_complete()
enum loadBarIcons {
  loadBarIconFile,
  loadBarIconWifi,
  loadBarIconCloud,
  loadBarIconTurtle,
  loadBarIconCheckmark
};

// holds all the loading tips
static const char* loading_tips[4] = { WS_LOADING_TIP_1, WS_LOADING_TIP_2, WS_LOADING_TIP_3, WS_LOADING_TIP_4 };

static lv_timer_t * timerLoadTips;

/**************************************************************************/
/*!
    @brief    Helps build and manage the LVGL objects and screens for
                the application code.
*/
/**************************************************************************/
class ws_display_ui_helper : public ws_drv_display {
public:
  ws_display_ui_helper(){};
  ~ws_display_ui_helper(){};

  void set_bg_black();

  void show_scr_load();
  void clear_scr_load();
  void set_load_bar_icon_complete(loadBarIcons iconType);
  void set_label_status(const char *text); // callback ui help?

  void show_scr_error(const char *lblError, const char *lblDesc);
};
#endif // WS_DISPLAY_UI_HELPER_H
