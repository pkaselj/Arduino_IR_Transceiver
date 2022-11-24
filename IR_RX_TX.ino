// #include <IRremote.h>


// const int TX_PIN = 5;
// IRsend irsend(TX_PIN);

// void setup(){
//   Serial.begin(9600);
//   irrecv.enableIRIn();
//   irsend.enableIROut();
//   irrecv.blink13(true);
// }

// void loop(){
//   if (irrecv.decode(&results)){
//         Serial.println(results.value, HEX);
//         irrecv.resume();
//   }
// }

/*
 * SimpleSender.cpp
 *
 *  Demonstrates sending IR codes in standard format with address and command
 *  An extended example for sending can be found as SendDemo.
 *
 *  Copyright (C) 2020-2022  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This file is part of Arduino-IRremote https://github.com/Arduino-IRremote/Arduino-IRremote.
 *
 *  MIT License
 */
#include <Arduino.h>

#include <IRremote.hpp>
#include "TxCommands.hpp"

// const int RECV_PIN = 6;
// IRrecv irrecv(RECV_PIN);
// decode_results results;


#define IR_SEND_PIN 5
#define MAIN_LOOP_WAIT_TIME_MS 1000
#define SERIAL_BAUDRATE 9600
#define DISABLE_CODE_FOR_RECEIVER // Saves 450 bytes program memory and 269 bytes RAM if receiving functions are not used.
//#define SEND_PWM_BY_TIMER         // Disable carrier PWM generation in software and use (restricted) hardware PWM.
//#define USE_NO_SEND_PWM           // Use no carrier PWM, just simulate an active low receiver signal. Overrides SEND_PWM_BY_TIMER definition

void setup() {

    Serial.begin(SERIAL_BAUDRATE);

    pinMode(IR_SEND_PIN, OUTPUT);

    /*
     * The IR library setup. That's all!
     */
    // IrSender.begin(); // Start with IR_SEND_PIN as send pin and if NO_LED_FEEDBACK_CODE is NOT defined, enable feedback LED at default feedback LED pin
    IrSender.begin(IR_SEND_PIN, DISABLE_LED_FEEDBACK); // Start with IR_SEND_PIN as send pin and disable feedback LED at default feedback LED pin
    // irrecv.enableIRIn();
    Serial.print(F("Send IR signals at pin "));
    Serial.println(IR_SEND_PIN);

}

String sInput;

void loop() {
    if(Serial.available())
    {

      sInput = Serial.readString();
      sInput.trim();
      
      Serial.print("Read: '");
      Serial.print(sInput);
      Serial.println("'");

      ircommand_t const * pCommand = get_command(sInput.c_str());
      if(NULL == pCommand)
      {
        Serial.print("Invalid command: '");
        Serial.print(sInput);
        Serial.println("'");
      }
      else
      {
        Serial.print("Matched command: ");
        Serial.println(pCommand->szName);
        IrSender.sendNEC(pCommand->iAddress, pCommand->iCommand, 0);
      }

    }

    delay(MAIN_LOOP_WAIT_TIME_MS);  // delay must be greater than 5 ms (RECORD_GAP_MICROS), otherwise the receiver sees it as one long signal
}