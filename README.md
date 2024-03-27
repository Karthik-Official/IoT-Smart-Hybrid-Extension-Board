<h1 align="center">
Smart Extension Board
</h1>
<div align="center">
A IoT based Smart Extension Board Using ESP Module
</div>

---

## Introduction

This Smart Extension Board is a Smart Home Automation Project using a famous Microcontrollers known as Espressif's chips, modules and development boards are widely deployed in such products as home appliances, light bulbs, smart speakers, consumer electronics and payment terminals
<br><br>Technologies Used:
- The popular and widely used ESP Modules are ESP32 and ESP8266.
- The ESP Modules are low-cost, low-power system on a chip series of microcontrollers with Wi-Fi and Bluetooth capabilities.

---

## Demo video
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/iKBKzcNNChQ/hqdefault.jpg)](https://www.youtube.com/watch?v=iKBKzcNNChQ)
---

## Schematics and Project

### ESP8266 Based:



<table>
  <tr>
    <img src="https://github.com/Karthik-Official/IoT-Smart-Extension-Board/assets/88947048/5f7441b6-cafc-4e7e-b13d-e8c369ce04ba">
  </tr>
  <tr>
    <td>
      <img src="https://github.com/Karthik-Official/IoT-Smart-Extension-Board/assets/88947048/eb953156-3c45-4f22-9b48-39f15fb07f4f" alt="Project Demo Picture" title="Project Demo">
    </td>
    <td>
      <img src="https://github.com/Karthik-Official/IoT-Smart-Extension-Board/assets/88947048/92a75ab0-6893-42d2-a7b7-8f4069294944" alt="Project Internal Wiring" title="Project Internal Wiring">
    </td>
  </tr>

  <tr>
    <td align= 'center'>Project Demo Picture</td>
    <td align= 'center'>Project Internal Wiring</td>
  </tr>
</table>
### ESP32 Based:

Coming Soon ...

---

## Prerequisites

1. ESP32 or ESP8266 Module
2. 4-Channel Relay Module 
3. Touch Sensor TTP223 or Push Button Switch
3. Arduino IDE Packages - `ESP8266 Library`, `Wifimanager Library by tzapu`

---

## Installation
### Quickstart
1. Download the Package and Extract it
2. Connect the ESP Module to your computer and Upload the sketch
3. Using the given `Schematic Diagram` connect all GPIO pins and wire.
4. Turn on `wi-fi config Mode` by pressing the wi-fi toggle switch and then the wi-fi led will glow indicating the `wi-fi config mode` has been activated.
5. Using a Smartphone or any devices that have wifi and browser, connect to the Wireless Access Point named as `Smart-ExtBoard-AP`
6. After connecting to the wi-fi Access Point, It will go to the IP Address of `192.168.4.1`
7. Select the wi-fi and enter password to connect the ESP to your wi-fi
8. After connecting successfully the Wifi Indicator will turn off itself 
9. Now you can use any device connected to the Wi-fi to control the Smart Extension Board switches by going to the IP Address of ESP Module.

> [!IMPORTANT]  
> To know the IP Address of the ESP Module, just enter to the Wi-fi config mode again and you will see the IP address of the ESP that connected to your wi-fi like `192.168.x.x`, and then click `Exit`.

10. You can also control it using manual Switches (Push Button or Touch Sensor) and yes, it can also work in offline.

> [!CAUTION]
> Working with Ac Current Is Highly Dangerous, Take Proper Precautions While Working With High Voltage. Do It At Your Own Risk.

### How to tweak the project for your own use case
- You can use either Touch sensor or Push button for manual control, while the touch sensor `TTP223 Module` requires power, push button does not need any.

---

## Usage

```
- Smart Home Automation
- Office Automation
- Voice Assitance based control
- Google Assistant and Amazon Alexa
```

---

## Challenges Faced and Lessons Learned

- The GPIO pins that I selected in ESP8266 are the only GPIO pins that an ESP8266 Module can be allow to be used to create this Smart Extension Board. 
- None other combination of GPIO Pins will work properly in ESP8266, because of some GPIO Pins are not recommended to use, and others have very specific functions.
- Even though I already read various PDF Manuals of the ESP8266. To find those right ESP8266 GPIO Pins, it literally took me Days.
- So No matter how many Documentations we read, there will always be a thing that will make us confusing and irritating while doing the Real Project.
- Therefore always `Keep Learning and be Enthusiastic` to break down those hard walls.

---

## Known Issues

- The Webpage used to control the Smart Extension Board is very simple and doesn't give much information except the ON and OFF status.
- I have made this project in a way that it can be only controlled by the webpage in a LAN. 
- Google Assistant and Alexa control are very time consuming to implement properly.

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.
- Any changes in webpage that controlling the Smart Extension Board are great.
- Any Opensourced Google Assistant and Alexa Implementation are welcome.

## License

[MIT](https://choosealicense.com/licenses/mit/) - License 
