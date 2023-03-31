// new lvgl classes
#include "display/ws_display_ui_helper.h"
#include "display/ws_drv_display.h"

// from adafruit_wippersnapper
#include "Wippersnapper_ESP32.h"
#include "tinyusb/Wippersnapper_FS.h"
Wippersnapper_ESP32 Wippersnapper_WiFi;

ws_drv_display tft_st7789(TFT_CS, TFT_DC, TFT_RESET);
ws_display_ui_helper ui_helper;

Wippersnapper_FS *fileSystem = nullptr;
Adafruit_MQTT *mqtt = nullptr;

/** Defines the Wippersnapper client's network status */
typedef enum {
  FSM_NET_IDLE,
  FSM_NET_CONNECTED,
  FSM_MQTT_CONNECTED,
  FSM_NET_CHECK_MQTT,
  FSM_NET_CHECK_NETWORK,
  FSM_NET_ESTABLISH_NETWORK,
  FSM_NET_ESTABLISH_MQTT,
} fsm_net_t;

void runNetFSM() {
  // // WS.feedWDT();
  // Initial state
  fsm_net_t fsmNetwork;
  fsmNetwork = FSM_NET_CHECK_MQTT;
  int maxAttempts;
  while (fsmNetwork != FSM_NET_CONNECTED) {
    switch (fsmNetwork) {
    case FSM_NET_CHECK_MQTT:
      /*       if (mqtt->connected()) {
              // Serial.println("Connected to Adafruit IO!");
              fsmNetwork = FSM_NET_CONNECTED;
              return;
            } */
      fsmNetwork = FSM_NET_CHECK_NETWORK;
      break;
    case FSM_NET_CHECK_NETWORK:
      if (Wippersnapper_WiFi.networkStatus() == WS_NET_CONNECTED) {
        Serial.println("Connected to WiFi!");
        ui_helper.set_load_bar_icon_complete(loadBarIconWifi);
        fsmNetwork = FSM_NET_ESTABLISH_MQTT;
        break;
      }
      fsmNetwork = FSM_NET_ESTABLISH_NETWORK;
      break;
    case FSM_NET_ESTABLISH_NETWORK:
      //digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Attempting to connect to WiFi");
      // Perform a WiFi scan and check if SSID within
      // secrets.json is within the scanned SSIDs
      if (!Wippersnapper_WiFi.check_valid_ssid()) {
        Serial.println("ERROR: Unable to find WiFi network...");
        delay(100000000);
      }

      // Attempt to connect to wireless network
      maxAttempts = 5;
      while (maxAttempts > 0) {
        // blink before we connect
        // statusLEDBlink(WS_LED_STATUS_WIFI_CONNECTING);
        // WS.feedWDT();
        // attempt to connect
        Serial.println("Attempting to connect to WiFi...");
        Wippersnapper_WiFi._connect();
        delay(500);
        // WS.feedWDT();
        // blink to simulate a delay to allow wifi connection to process
        // statusLEDBlink(WS_LED_STATUS_WIFI_CONNECTING);
        // did we connect?
        ws_status_t networkStatus = Wippersnapper_WiFi.networkStatus();
        Serial.print("WiFi Status: ");
        Serial.println(networkStatus);
        if (networkStatus == WS_NET_CONNECTED) {
          Serial.println("Connected..");
          digitalWrite(LED_BUILTIN, LOW);
          break;
        }
        maxAttempts--;
      }

      // Validate connection
      if (Wippersnapper_WiFi.networkStatus() != WS_NET_CONNECTED)
        Serial.println("Unable to connect, rebooting...");
    fsmNetwork = FSM_NET_CHECK_NETWORK;
      break;
    case FSM_NET_ESTABLISH_MQTT:
      Serial.println("Attempting to connect to Adafruit IO...");
      /*       WS._mqtt->setKeepAliveInterval(WS_KEEPALIVE_INTERVAL_MS / 1000);
            // Attempt to connect
            maxAttempts = 5;
            while (maxAttempts > 0) {
              // statusLEDBlink(WS_LED_STATUS_MQTT_CONNECTING);
              int8_t mqttRC = WS._mqtt->connect();
              if (mqttRC == WS_MQTT_CONNECTED) {
                fsmNetwork = FSM_NET_CHECK_MQTT;
                break;
              }
              Serial.println("Unable to connect to Adafruit IO MQTT, retrying in
         3 seconds...");
              // statusLEDBlink(WS_LED_STATUS_MQTT_CONNECTING);
              delay(1800);
              maxAttempts--;
            }
            if (fsmNetwork != FSM_NET_CHECK_MQTT)
              haltError(
                  "ERROR: Unable to connect to Adafruit.IO MQTT, rebooting
         soon...", WS_LED_STATUS_MQTT_CONNECTING); */
      break;
    default:
      break;
    }
  }
}

void setup(void) {

  tft_st7789.setResolution(240, 240);
  tft_st7789.begin();

  // set screen background to black
  ui_helper.set_bg_black();
  // build the load screen first
  ui_helper.show_scr_load();
  // call task handler
  lv_task_handler();

  // init USB-MSC and FS
  fileSystem = new Wippersnapper_FS();

  // begin serial comm.
  Serial.begin(115200);
  // tft_st7789.enableLogging();
  while (!Serial)
    delay(10);

  // parse secrets file
  // fileSystem->parseSecrets();
  // call task handler
  ui_helper.set_load_bar_icon_complete(loadBarIconFile);

  // connect wifi
  // TODO!
  // bring in netFSM
  runNetFSM();

  // connect MQTT
  // TODO!

  // connect to WipperSnapper
  // TODO!

  // Serial.println("going into loop()");
}

void loop(void) {
  lv_task_handler(); // Call LittleVGL task handler periodically
  delay(5);
}