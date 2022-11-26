# Arduino IR Transceiver

Arudino UNO rev3 code that uses infrared recevier and transmitter/diode to simultaneously receive, decode, encode and send IR commands.

## Table of Contents
- [Arduino IR Transceiver](#arduino-ir-transceiver)
  - [Table of Contents](#table-of-contents)
  - [Wiring](#wiring)
  - [Configuration (`#define`s)](#configuration-defines)
    - [Pins (*IR\_RX\_TX.ino*)](#pins-ir_rx_txino)
    - [Serial Communication (*IR\_RX\_TX.ino*)](#serial-communication-ir_rx_txino)
    - [Task Execution (*IR\_RX\_TX.ino*)](#task-execution-ir_rx_txino)
    - [IR Settings / Command Sets (*TxCommands.hpp*)](#ir-settings--command-sets-txcommandshpp)
  - [Adding New Commands](#adding-new-commands)
  - [License](#license)
  - [References](#references)


## Wiring

- Connect IR diode anode to **IR_SEND_PIN** pin (defualt: pin 5)
  - Alternatively, connect **IR_SEND_PIN** to transistor switch *Gate/Base* for increased transmission range
- Connect IR receiver's (e.g. **[TSOP38238][4]**) *OUT* pin to **IR_RECEIVE_PIN** (default: pin 2)

## Configuration (`#define`s)

### Pins (*[IR_RX_TX.ino](IR_RX_TX.ino)*)

- **IR_SEND_PIN** - Arduino pin which the IR LED anode is connected to
- **IR_RECEIVE_PIN** - Arudino pin which the IR receiver IC output is connected to

### Serial Communication (*[IR_RX_TX.ino](IR_RX_TX.ino)*)

- **SERIAL_BAUDRATE**

### Task Execution (*[IR_RX_TX.ino](IR_RX_TX.ino)*)

- **MAIN_LOOP_WAIT_TIME_MS** - Time in milliseconds during which *loop()* sleeps at the end of an iteration

### IR Settings / Command Sets (*[TxCommands.hpp](TxCommands.hpp)*)

Define **only one** of these at the top of the file:
- **COMMANDS_LED** - IR Commands for a generic LED strip from Alixpress
- **COMMANDS_TV** - IR Commands for a generic Hisense TV
- **COMMANDS_PURIFIER** - IR Commands for a generic air purifier

## Adding New Commands

To add new commands, alter or extend existing ones:

- In [TxCommands.cpp](TxCommands.cpp) add new entries to the array of commands (`lstCommands` array) *(Commands are defined as `struct ircommand_t` in [TxCommands.hpp](TxCommands.hpp))*

e.g. 
```
static const ircommand_t lstCommands[] =
{
// (...)
#elif defined(COMMANDS_TV)
  { .szName = "ON",   .iAddress = 0xBF00, .iCommand = 0x0D },
  { .szName = "OFF",  .iAddress = 0xBF00, .iCommand = 0x0D },
// (...)
};
```

- In [TxCommands.hpp](TxCommands.hpp) `typedef` correct type for the custom `addr_t` type that holds IR [NEC protocol][1] address value. NOTE: Some devices use 16 bit addresses while some use 8 bit.

e.g.
```
// Define addr_t type for NEC addresses
#if defined(COMMANDS_TV) || defined(COMMANDS_LED)
  // TV uses 16-bit addresses
  typedef uint16_t addr_t;
#else
  // Others use 8-bit address
  typedef uint8_t addr_t;
#endif
```

## License

This code uses *[IRRemote Arduino library][2]* as well as code snippets from the examples provided by the mentioned library. The library is distributed under MIT license which can be viewed at the library's [repository site][2] or using a direct link to the [license file][3].

```
MIT License

Copyright (c) 2022 Petar Kaselj

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## References

- [\[1\] NEC Protocol][1]
- [\[2\] IRRemote Arduino Library][2]
- [\[3\] IRRemote Arduino Library License][3]
- [\[4\] TSOP38238][4]

[1]: https://techdocs.altium.com/display/FPGA/NEC+Infrared+Transmission+Protocol
[2]: https://github.com/Arduino-IRremote/Arduino-IRremote
[3]: https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/LICENSE
[4]: https://www.sparkfun.com/products/10266