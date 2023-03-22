import os

Import("env")

adafruit_usb_config = os.path.join(
    env.subst("$PROJECT_LIBDEPS_DIR"),
    env.subst("$PIOENV"),
    "Adafruit TinyUSB Library",
    "src",
    "tusb_config.h",
)

if os.path.isfile(adafruit_usb_config):
    os.rename(adafruit_usb_config, adafruit_usb_config + "_backup")