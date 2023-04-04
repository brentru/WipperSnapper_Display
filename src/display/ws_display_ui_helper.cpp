#include "ws_display_ui_helper.h"



static void my_event_cb(lv_event_t * event)
{
    Serial.println("eventcb called!");
    const char** charPtr{ static_cast<const char**>(lv_event_get_param(event)) };
    Serial.print("text: ");
    Serial.println(*charPtr);
    lv_label_set_text(lblStatusText, *charPtr);
    //lv_label_set_text(lblStatusText, NULL);
    //lv_obj_update_layout(lblStatusText);
}

// try propigating the event to the callback, for the app code
void ws_display_ui_helper::set_label_text(const char *text) {
  Serial.print("set_label_text (text): "); Serial.println(text);
  // lblText = text;
  lv_event_send(lblStatusText, LV_EVENT_REFRESH, &text);
}

void ws_display_ui_helper::set_bg_black(){
  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), LV_STATE_DEFAULT);
}


void ws_display_ui_helper::set_load_bar_icon_complete(loadBarIcons iconType) {
    lv_style_t *iconStyle;
    switch (iconType)
    {
    case loadBarIconFile:
        lv_style_set_text_color(&styleIconFile, lv_palette_main(LV_PALETTE_GREEN));
        lv_obj_refresh_style(lblIconFile, LV_PART_MAIN, LV_STYLE_PROP_ANY);
        break;
    case loadBarIconWifi:
        lv_style_set_text_color(&styleIconWiFi, lv_palette_main(LV_PALETTE_GREEN));
        lv_obj_refresh_style(lblIconWiFi, LV_PART_MAIN, LV_STYLE_PROP_ANY);
        break;
    case loadBarIconCloud:
        iconStyle = &styleIconCloud;
        break;
    case loadBarIconTurtle:
        iconStyle = &styleIconTurtle30px;
        break;
    case loadBarIconCheckmark:
        iconStyle = &styleIconCheckmark;
        break;
    default:
        return;
    }
    lv_task_handler();
}

void ws_display_ui_helper::show_scr_load(){
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
  lv_style_set_text_font(&styleIconFile, &file);
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

  // Add status text label
  lblStatusText = lv_label_create(lv_scr_act());
  // lv_label_set_long_mode(lblStatusText, LV_LABEL_LONG_WRAP);
  lv_obj_set_style_text_font(lblStatusText, &lv_font_montserrat_18, 0);
  lv_obj_set_style_text_color(lblStatusText, lv_color_white(), LV_PART_MAIN);
  lv_label_set_text(lblStatusText, "\0");
  lv_obj_align(lblStatusText, LV_ALIGN_BOTTOM_LEFT, 0, -5);
  lv_obj_add_event_cb(lblStatusText, my_event_cb, LV_EVENT_REFRESH, NULL);
}

/* Sets the loading screen's text label */
void ws_display_ui_helper::set_status_label(const char *text) {
  lv_label_set_text(lblStatusText, text);
  //lv_obj_refresh_style(lblStatusText, LV_PART_MAIN, LV_STYLE_PROP_ANY);
  lv_obj_refresh_style(lblStatusText, LV_PART_ANY, LV_STYLE_PROP_ANY);
  lv_task_handler();
}

void ws_display_ui_helper::clear_scr_load(){}
void ws_display_ui_helper::show_scr_error(){}