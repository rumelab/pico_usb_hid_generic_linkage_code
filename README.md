# Pico USB HID Generic Linkage Code

This is the code for linkage study between RP2040 and USB port (on Raspberry Pi Pico) to become a Generic HID device.
This is done with the aid of [Pico SDK](https://github.com/raspberrypi/pico-sdk) and [TinyUSB](https://github.com/hathach/tinyusb).
It receives any array of bytes with the length of 64 and return the message "Received!".

## Execute the code

This project is build as a conventional CMake project.

```sh
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

Then, `pico_usb_hid_generic_linkage_code.elf.uf2` should exist in the `build` directory.
Upload the `.uf2` file to Raspberry Pi Pico, by pressing the `BOOTSEL` button while plugging in the USB port and drop the file into the `RPI-RP2` disk.

The testing code is prepared in `misc/usb_hid_test` as a Node.js project.

```sh
$ cd misc/usb_hid_test
$ npm install
$ npm run test
```

The test script would send a random message (specifically "Hello world!") to the Raspberry Pi Pico as Generic HID.
It should receive "Recieved!" message.
