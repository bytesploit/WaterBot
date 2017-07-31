# Espressif ESP32 WaterBot Controller

The Waterbot Controller connects in STA mode to an Access Point and starts a UDP Server. The UDP Server listens on port 6789 for commands incoming from the client application. The commands are then parsed and evaluated for moving the bot in the desired direction. Most of the examples in GitHub for the ESP32 microcontroller are integrated with an Arduino sketch, which isn't incredibly helpful for developers trying to write code directly on the ESP32. Hopefully, this simple UDP server will be useful for the non-Arduino developers.

## Getting Started

Setup the ESP32 development enviornment.

[ESP-IDF Programming Guide](http://esp-idf.readthedocs.io/en/latest/get-started/index.html)

## Configure Serial Port

```sh
$ cd ~/esp
$ git clone https://github.com/bytesploit/WaterBot.git
$ cd water_bot
$ make menuconfig
```

### Setup Menu

In the menu, navigate to `Serial flasher config > Default serial port` to configure the serial port, where project will be loaded to. Confirm selection by pressing enter, save configuration by selecting `< Save >` and then exit application by selecting `< Exit >`.

## Build and Flash

Flash the code to the ESP32

```sh
$ make flash
```

Flash the code and view console output

```sh
$ make flash monitor
```

## WaterBot Project Page

[Robot Sprinkler](https://hackaday.io/project/25565-water-bot)

## TODO

- Implement a TCP/IP heart beat task
- Implement low water sensor logic
- Implement mapping logic for autonomous operation

## License

This project is licensed under the GNU General Public License

## Acknowledgements

Early code inspired by the [UDP Perf Example](https://github.com/espressif/esp-idf/tree/master/examples/performance/udp_perf)
