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

void halt_and_tick(void) {
  while (1)
    lv_task_handler(); // Call LittleVGL task handler periodically
  delay(5);
}

void runNetFSM() {
  // // WS.feedWDT();
  // Initial state
  fsm_net_t fsmNetwork;
  fsmNetwork = FSM_NET_CHECK_MQTT;
  int maxAttempts;
  while (fsmNetwork != FSM_NET_CONNECTED) {
    switch (fsmNetwork) {
    case FSM_NET_CHECK_MQTT:
      Serial.println("checking MQTT");
      // everything seems working after the iram fix?
      if (Wippersnapper_WiFi.isMQTTConnected()) {
        Serial.println("Connected to Adafruit IO!");
        ui_helper.set_label_status("Connected to MQTT!");
        ui_helper.set_load_bar_icon_complete(loadBarIconCloud);
        ui_helper.remove_tip_timer();
        delay(10);
        lv_task_handler();
        fsmNetwork = FSM_NET_CONNECTED;
        return;
      }
      fsmNetwork = FSM_NET_CHECK_NETWORK;
      break;
    case FSM_NET_CHECK_NETWORK:
      if (Wippersnapper_WiFi.networkStatus() == WS_NET_CONNECTED) {
        Serial.println("Connected to WiFi!");
        ui_helper.set_label_status("Connected to WiFi!");
        ui_helper.set_load_bar_icon_complete(loadBarIconWifi);
        delay(10);
        lv_task_handler();
        fsmNetwork = FSM_NET_ESTABLISH_MQTT;
        break;
      }
      fsmNetwork = FSM_NET_ESTABLISH_NETWORK;
      break;
    case FSM_NET_ESTABLISH_NETWORK:
      // digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Attempting to connect to WiFi");
      ui_helper.set_label_status("Connecting to WiFi...");
      delay(10);
      lv_task_handler();
      // Perform a WiFi scan and check if SSID within
      // secrets.json is within the scanned SSIDs
      if (!Wippersnapper_WiFi.check_valid_ssid()) {
        Serial.println("ERROR: Unable to find WiFi network...");
        ui_helper.show_scr_error(
            "Network Error!",
            "Unable to find your WiFi network, [SSID]. Please ensure the "
            "network is 2.4GHz and you are in range.");
        halt_and_tick();
      }
      lv_task_handler();
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
        lv_task_handler();
        // WS.feedWDT();
        // blink to simulate a delay to allow wifi connection to process
        // statusLEDBlink(WS_LED_STATUS_WIFI_CONNECTING);
        // did we connect?
        ws_status_t networkStatus = Wippersnapper_WiFi.networkStatus();
        if (networkStatus == WS_NET_CONNECTED) {
          Serial.println("Connected..");
          digitalWrite(LED_BUILTIN, LOW);
          break;
        }
        maxAttempts--;
      }
      // Validate connection
      if (Wippersnapper_WiFi.networkStatus() != WS_NET_CONNECTED) {
        Serial.println("Unable to connect to WiFi, rebooting in 5s...");
        ui_helper.show_scr_error(
            "Network Error!",
            "Unable to connect to [SSID]. Please check if your network is "
            "2.4GHz and if the network password you entered in secrets.json is "
            "correct.");
        halt_and_tick();
      }
      fsmNetwork = FSM_NET_CHECK_NETWORK;
      break;
    case FSM_NET_ESTABLISH_MQTT:
      Serial.println("Attempting to connect to Adafruit IO...");
      ui_helper.set_label_status("Connecting to Adafruit.IO...");
      delay(10);
      lv_task_handler();
      maxAttempts = 5; // set max connection attempts
      while (maxAttempts > 0) {
        int8_t mqttRC = Wippersnapper_WiFi.connectMQTT();
        Serial.print("Connection RC: ");
        Serial.println(mqttRC);
        // did we connect successfully?
        if (mqttRC == 0) {
          fsmNetwork = FSM_NET_CHECK_MQTT;
          break;
        }
        Serial.println("Unable to connect, retrying");
        delay(3000);
        lv_task_handler();
        maxAttempts--;
      }
      if (fsmNetwork != FSM_NET_CHECK_MQTT) {
        // halt
        // NOTE: This is still hanging... why!
        Serial.println("Unable to connect to IO...");
        ui_helper.show_scr_error(
            "Connection Error",
            "Unable to connect to Adafruit IO. Please check your IO_USERNAME "
            "and IO_KEY in the secrets.json file.");
        halt_and_tick();
      }
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
  tft_st7789.enableLogging();
  while (!Serial)
    delay(10);

  // parse display configuration from filesystem
  // fileSystem->parseDisplayConfig();

  // parse secrets file
  ui_helper.set_label_status("Validating secrets file...");
  fileSystem->parseSecrets();
  Wippersnapper_WiFi.set_ssid_pass(fileSystem->network_ssid,
                                   fileSystem->network_pass);

  // call task handler
  ui_helper.set_load_bar_icon_complete(loadBarIconFile);

  Wippersnapper_WiFi.setupMQTTClient("wsDisplayDevice", fileSystem->username,
                                     fileSystem->key);

  // run net FSM
  runNetFSM();
  Serial.println("going into application loop()");
}

void loop(void) {
  lv_task_handler(); // Call LittleVGL task handler periodically
  delay(5);
}