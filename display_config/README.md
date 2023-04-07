# Display Configuration Files

Displays are configured by a JSON file, `display_config.json`, that sits on the WIPPER file system.

This folder includes an explanation of the schema and sample `display_config.json` files within `examples/`.


SPI Display Example:
```
{
  "dispDriver": "Adafruit_ST7789",
  "dispWidth": "240",
  "dispHeight": "240",
  "dispRotation": "0",
  "dispSPI": {
    "spiMode": 1,
    "pin_cs": 0,
    "pin_dc": 0,
    "pin_mosi": 0,
    "pin_sck": 0,
    "pin_rst": -1,
  }
}
```