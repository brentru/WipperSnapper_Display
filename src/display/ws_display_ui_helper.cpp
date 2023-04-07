/*!
 * @file ws_display_ui_helper.cpp
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

#include "ws_display_ui_helper.h"

/**************************************************************************/
/*!
    @brief    Callback for updating the status label on the loading screen.
    @param    event
              Callback data.
*/
/**************************************************************************/
static void label_status_cb(lv_event_t * event)
{
    Serial.println("eventcb called!");
    const char** charPtr{ static_cast<const char**>(lv_event_get_param(event)) };
    Serial.print("text: ");
    Serial.println(*charPtr);
    lv_label_set_text(lblStatusText, *charPtr);
}

/**************************************************************************/
/*!
    @brief    Sets the text of the status label on the loading screen.
    @param    text
              Desired text to write to the status label.
*/
/**************************************************************************/
void ws_display_ui_helper::set_label_status(const char *text) {
  Serial.print("set_label_status (text): "); Serial.println(text);
  lv_event_send(lblStatusText, LV_EVENT_REFRESH, &text);
}

/**************************************************************************/
/*!
    @brief    Sets the screen's background to a black color.
*/
/**************************************************************************/
void ws_display_ui_helper::set_bg_black(){
  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), LV_STATE_DEFAULT);
}

/**************************************************************************/
/*!
    @brief    Sets the color of an icon on the loading screen to green.
    @param    iconType
              Desired icon.
*/
/**************************************************************************/
void ws_display_ui_helper::set_load_bar_icon_complete(loadBarIcons iconType) {
    lv_style_t *iconStyle;
    switch (iconType)
    {
    case loadBarIconFile:
        // TODO: can we just call this below the switch, and use iconStyle ptr. instead?
        lv_style_set_text_color(&styleIconFile, lv_palette_main(LV_PALETTE_GREEN));
        // TODO: Do we need this? 
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
    lv_task_handler(); // TODO: do we need this?
}

/**************************************************************************/
/*!
    @brief    Builds and displays the loading screen.
*/
/**************************************************************************/
void ws_display_ui_helper::show_scr_load(){
  // adding loading screen image
  imgWSLogo = lv_img_create(lv_scr_act());
  lv_img_set_src(imgWSLogo, &ws_icon_100px);
  lv_obj_align(imgWSLogo, LV_ALIGN_TOP_MID, 0, 5);

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
  labelTurtleBar = lv_label_create(lv_scr_act());
  lv_label_set_text(labelTurtleBar, SYMBOL_TURTLE30PX);

  lv_style_init(&styleIconTurtle30px);
  lv_style_set_text_color(&styleIconTurtle30px,
                          lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconTurtle30px, &turtle_30px);
  lv_obj_add_style(labelTurtleBar, &styleIconTurtle30px,
                   LV_PART_MAIN); // 28+(33*2) = 94
  lv_obj_align(labelTurtleBar, LV_ALIGN_BOTTOM_LEFT, 106, iconBarYOffset);

  // Add cloud
  labelCloudBar = lv_label_create(lv_scr_act());
  lv_label_set_text(labelCloudBar, SYMBOL_CLOUD);

  lv_style_init(&styleIconCloud);
  lv_style_set_text_color(&styleIconCloud, lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconCloud, &cloud_30px);
  lv_obj_add_style(labelCloudBar, &styleIconCloud, LV_PART_MAIN);
  lv_obj_align(labelCloudBar, LV_ALIGN_BOTTOM_LEFT, iconBarXStart + (106 + 13),
               iconBarYOffset);

  // Add circle checkmark
  labelCircleBar = lv_label_create(lv_scr_act());
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
  lv_obj_add_event_cb(lblStatusText, label_status_cb, LV_EVENT_REFRESH, NULL);
}

/**************************************************************************/
/*!
    @brief    Deletes all objects/styles off the load screen and frees
              their resources. 
*/
/**************************************************************************/
void ws_display_ui_helper::clear_scr_load(){
    // Delete all objects on the loading screen
    lv_obj_del(imgWSLogo);
    lv_obj_del(lblStatusText);
    lv_obj_del(lblIconFile);
    lv_obj_del(lblIconWiFi);
    lv_obj_del(labelTurtleBar);
    lv_obj_del(labelCloudBar);
    lv_obj_del(labelCircleBar);
    // Clear all properties from styles and free all allocated memory
     lv_style_reset(&styleIconWiFi);
    lv_style_reset(&styleIconCloud);
    lv_style_reset(&styleIconTurtle30px);
    lv_style_reset(&styleIconCheckmark);
}


/**************************************************************************/
/*!
    @brief    Build and display an error screen.
    @param    lblError
              The generic error.
    @param    lblDesc
              Instructions or steps to resolve the error.
*/
/**************************************************************************/
void ws_display_ui_helper::show_scr_error(const char *lblError, const char *lblDesc){
  Serial.println("ws_display_ui_helper");
  // clear the active loading screen (for now, will eventually expand to take in a scr obj.)
  clear_scr_load();

  // Create error symbol
  labelErrorTriangle = lv_label_create(lv_scr_act());
  lv_label_set_text(labelErrorTriangle, SYMBOL_ERROR_TRIANGLE);

  lv_style_init(&styleErrorTriangle);
  lv_style_set_text_color(&styleErrorTriangle, lv_color_white());
  lv_style_set_text_font(&styleErrorTriangle, &errorTriangle); 
  lv_obj_add_style(labelErrorTriangle, &styleErrorTriangle, LV_PART_MAIN);
  lv_obj_align(labelErrorTriangle, LV_ALIGN_TOP_MID, 0, 5);


  // Add error label (large)
  labelErrorHeader = lv_label_create(lv_scr_act());
  lv_label_set_text(labelErrorHeader, lblError);

  lv_style_init(&styleLabelErrorLarge);
  lv_style_set_text_color(&styleLabelErrorLarge, lv_color_white());
  lv_style_set_text_font(&styleLabelErrorLarge, &lv_font_montserrat_18); 
  lv_obj_add_style(labelErrorHeader, &styleLabelErrorLarge, LV_PART_MAIN);
  lv_obj_align(labelErrorHeader, LV_ALIGN_CENTER, 0, -5);


  // Add error label (small)
  labelErrorBody = lv_label_create(lv_scr_act());
  lv_label_set_long_mode(labelErrorBody, LV_LABEL_LONG_WRAP);
  lv_label_set_text(labelErrorBody, lblDesc);

  lv_style_init(&styleLabelErrorSmall);
  lv_style_set_text_color(&styleLabelErrorSmall, lv_color_white());
  lv_style_set_text_font(&styleLabelErrorSmall, &lv_font_montserrat_12); 
  lv_obj_add_style(labelErrorBody, &styleLabelErrorSmall, LV_PART_MAIN);
  // set_width used by LABEL_LONG_WRAP
  lv_obj_set_width(labelErrorBody, 220);
  lv_obj_align(labelErrorBody, LV_ALIGN_CENTER, -3, 55);
}