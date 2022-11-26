#include <Arduino.h>

// Code snippets taken from IRRemote MinimalReceiver example

#include <IRremote.hpp>
#include "TinyIRReceiver.hpp"
#include "TxCommands.hpp"
#include "Utils.hpp"

// IR diode pin
#define IR_SEND_PIN 5
// IR receiver pin
#define IR_RECEIVE_PIN 2

// Time between loop() calls (Loop sleeps after every iteration)
#define MAIN_LOOP_WAIT_TIME_MS 100

// Baudrate for serial port used for command&control
#define SERIAL_BAUDRATE 9600

/*
 * Helper macro for getting a macro definition as string
 */
#if !defined(STR_HELPER)
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif


void task_ir_send_handler();
void task_ir_receive_handler();

// TinyIRReceiver.hpp :: initPCIInterruptForTinyReceiver() requires that
// IR input interrupt handler is named 'handleReceivedTinyIRData'
void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat);

void setup() {

    Serial.begin(SERIAL_BAUDRATE);

    pinMode(IR_SEND_PIN, OUTPUT);
    pinMode(IR_RECEIVE_PIN, INPUT);

    IrSender.begin(IR_SEND_PIN, DISABLE_LED_FEEDBACK); // Start with IR_SEND_PIN as send pin and disable feedback LED at default feedback LED pin
    // IrReceiver.enableIRIn();

    Serial.println(F("Send IR signals at pin " STR(IR_SEND_PIN)));

    if(!initPCIInterruptForTinyReceiver())
    {
        Serial.println(F("No interrupt available for pin " STR(IR_RECEIVE_PIN))); // optimized out by the compiler, if not required :-)
    }
    Serial.println(F("Ready to receive NEC IR signals at pin " STR(IR_RECEIVE_PIN)));
}


// Buffer for commands read from serial port
static String sInput;

// Buffer for received IR data
// Volatile because it is populated in interrupt handler
volatile static struct TinyIRReceiverCallbackDataStruct sCallbackData;

void loop() {

  task_ir_receive_handler();
  task_ir_send_handler();

  delay(MAIN_LOOP_WAIT_TIME_MS);
}


void task_ir_receive_handler()
{
    if (sCallbackData.justWritten)
    {
        sCallbackData.justWritten = false;
        Serial.print(F("Address=0x"));
        Serial.print(sCallbackData.Address, HEX);
        Serial.print(F(" Command=0x"));
        Serial.print(sCallbackData.Command, HEX);
        if (sCallbackData.isRepeat)
        {
            Serial.print(F(" Repeat"));
        }
        Serial.println();
    }
}

void task_ir_send_handler()
{
    if(Serial.available())
    {
      sInput = Serial.readString();
      sInput.trim();
      
      Serial.println(F("Read: '") + sInput + F("'"));

      ircommand_t const * pCommand = get_command(sInput.c_str());
      if(NULL == pCommand)
      {
        Serial.println(F("Invalid command: '") + sInput + F("'"));
      }
      else
      {
        Serial.print(F("Matched command: "));
        Serial.println(pCommand->szName);
        IrSender.sendNEC(pCommand->iAddress, pCommand->iCommand, 0);
      }

    }
}

void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat)
{
    sCallbackData.Address = aAddress;
    sCallbackData.Command = aCommand;
    sCallbackData.isRepeat = isRepeat;
    sCallbackData.justWritten = true;
}
