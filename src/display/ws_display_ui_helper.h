#ifndef WS_DISPLAY_UI_HELPER_H
#define WS_DISPLAY_UI_HELPER_H

#include "ws_drv_display.h"

#define SYMBOL_CODE "\xEF\x87\x89"
#define SYMBOL_WIFI "\xEF\x87\xAB"
#define SYMBOL_TURTLE30PX "\xEF\x9C\xA6"
#define SYMBOL_CLOUD "\xEF\x83\x82"
#define SYMBOL_CHECKMARK "\xEF\x81\x98"
#define SYMBOL_ERROR_TRIANGLE "\xEF\x81\xB1"

// images
LV_IMG_DECLARE(ws_icon_100px);
// FA fonts
LV_FONT_DECLARE(errorTriangle);
LV_FONT_DECLARE(file);
LV_FONT_DECLARE(wifi_30px);
LV_FONT_DECLARE(cloud_30px);
LV_FONT_DECLARE(turtle_30px);
LV_FONT_DECLARE(circle_30px);

// loading bar icons
static lv_obj_t *lblIconFile, *lblIconWiFi;

// styles used by the loading screen, need to be global or static
static lv_style_t styleIconFile, styleIconWiFi, styleIconTurtle30px,
    styleIconCloud, styleIconCheckmark;

// used by set_load_bar_icon_complete()
enum loadBarIcons { loadBarIconFile, loadBarIconWifi, loadBarIconCloud, loadBarIconTurtle, loadBarIconCheckmark };

class ws_display_ui_helper : public ws_drv_display {
public:
  ws_display_ui_helper(){};
  ~ws_display_ui_helper(){};

  void set_bg_black();

  void show_scr_load();
  void set_load_bar_icon_complete(loadBarIcons iconType);
  void clear_scr_load();

  void show_scr_error();
};
#endif // WS_DISPLAY_UI_HELPER_H
