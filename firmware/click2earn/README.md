# Click 2 earn example for w3bstream

A simple example that shows how to communicate with a w3bstream node from an Arduino Nano 33 IoT or an ESP32.  

## What it does

The sketch will detect when a button was pressed and send an event to a w3bstream node.  

## Usage

First clone this project usng git, or download the contents as zip and extract the zip contents to your machine.  

### Configure the sketch

Open the `secrets.h` file and replace the definitions to suit your application.  

### Compile and flash the sketch

#### Using PlatformIO

Make sure that PlatformIO is installed and in your path. You can check if it is by running `pio --version` in your terminal. It will return your platformio version if it is installed.  

Ensure that your device is connected to a USB port and recognized by your pc. If your PC doesn't recognize the device, then check that you have the proper driver installed for your board.  

On a terminal, change directory to the folder where the `platformio.ini` file is located.  

If you just want to compile the sketch, run the following command:

`pio run -e <esp32 or nano_33_iot>`  

If you want to compile, run and monitor the sketch over a serial port, run the following command:  

`pio run -e <esp32 or nano_33_iot> -t upload -t monitor`  

#### Using Arduino IDE

##### Install Arduino core

Install the required Arduino core for the board you are using ([Nano 33 IoT](https://docs.arduino.cc/software/ide-v1/tutorials/getting-started/cores/arduino-samd) or [ESP32](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/installing.html)).  

##### Install Arduino libraries

Then you need to install some library dependencies through the library manager.  

The following libraries are required:  

- [PubSubClient](https://www.arduino.cc/reference/en/libraries/pubsubclient/) for MQTT.  
- [Arduino_JSON](https://www.arduino.cc/reference/en/libraries/arduino_json/) for JSON serializing.  
- [NTPClient](https://www.arduino.cc/reference/en/libraries/ntpclient/) for getting the current unixtime.  

Additionally, for Nano 33 IoT, the following libraries are also required:  

- [WiFiNINA](https://www.arduino.cc/reference/en/libraries/wifinina/) for WiFi.  
- [ArduinoHttpClient](https://www.arduino.cc/reference/en/libraries/arduinohttpclient/) for HTTP.  

##### Flash the sketch

Once done with the previous steps, click the Upload button to compile and flash the sketch.  
You can then open the serial monitor to see the serial port log.  

### Trigger an event

The sketch detects when the pin `BUTTON_PIN` has been pressed. By default, the pin is configured as an input with a pullup resistor.  
In the default state, this pin must be wired to GND. You can use a dupont wire for this.  
Whenever you want to trigger an event, disconnect the pin from GND an reconnect it.  
The serial monitor will print a log indicating whther the event has been sent successfully or if there has been an error.  
If the event was sent successfully, you should now be able to see it in your w3bstream node.  

If your particular board has a button or switch, you can change the value of `BUTTON_PIN` to suit your board.  
Depending on how the button is wired, you may also need to change the pin from `PULLUP` to `PULLDOWN` and also modify `isPressed()` to return true when the pin value is `LOW`.  
