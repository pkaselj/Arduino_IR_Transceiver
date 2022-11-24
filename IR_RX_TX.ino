#include <Arduino.h>

#include <IRremote.hpp>
#include "TxCommands.hpp"

// IR diode pin
#define IR_SEND_PIN 5
// IR receiver pin
#define IR_RECEIVE_PIN 6

// Time between loop() calls (Loop sleeps after every iteration)
#define MAIN_LOOP_WAIT_TIME_MS 1000

// Baudrate for serial port used for command&control
#define SERIAL_BAUDRATE 9600

// IRRemote options
#define DISABLE_CODE_FOR_RECEIVER // Saves 450 bytes program memory and 269 bytes RAM if receiving functions are not used.
//#define SEND_PWM_BY_TIMER         // Disable carrier PWM generation in software and use (restricted) hardware PWM.
//#define USE_NO_SEND_PWM           // Use no carrier PWM, just simulate an active low receiver signal. Overrides SEND_PWM_BY_TIMER definition

void setup() {

    Serial.begin(SERIAL_BAUDRATE);

    pinMode(IR_SEND_PIN, OUTPUT);

    IrSender.begin(IR_SEND_PIN, DISABLE_LED_FEEDBACK); // Start with IR_SEND_PIN as send pin and disable feedback LED at default feedback LED pin

    Serial.print(F("Send IR signals at pin "));
    Serial.println(IR_SEND_PIN);

}


// Buffer for commands read from serial port
static String sInput;

void loop() {
    if(Serial.available())
    {
      sInput = Serial.readString();
      sInput.trim();
      
      Serial.println("Read: '" + sInput + "'");

      ircommand_t const * pCommand = get_command(sInput.c_str());
      if(NULL == pCommand)
      {
        Serial.println("Invalid command: '" + sInput + "'");
      }
      else
      {
        Serial.print("Matched command: ");
        Serial.println(pCommand->szName);
        IrSender.sendNEC(pCommand->iAddress, pCommand->iCommand, 0);
      }

    }

    delay(MAIN_LOOP_WAIT_TIME_MS);
}