#include "TxCommands.hpp"

#include <Arduino.h>

// PRIVATE list of all commands
static const ircommand_t lstCommands[] =
{
#if defined(COMMANDS_PURIFIER)
  { .szName = "ON",             .iAddress = 0x00,   .iCommand = 0x00 },
  { .szName = "OFF",            .iAddress = 0x00,   .iCommand = 0x00 },
  { .szName = "INTERMITTENT",   .iAddress = 0x00,   .iCommand = 0x01 },
  { .szName = "CONTINUOUS",     .iAddress = 0x00,   .iCommand = 0x02 },
  { .szName = "TIMING",         .iAddress = 0x00,   .iCommand = 0x08 },
  { .szName = "BIG/SMALL",      .iAddress = 0x00,   .iCommand = 0x09 },
  { .szName = "LIGHTS",         .iAddress = 0x00,   .iCommand = 0x0A },
#elif defined(COMMANDS_TV)
  { .szName = "ON",             .iAddress = 0xBF00, .iCommand = 0x0D },
  { .szName = "OFF",            .iAddress = 0xBF00, .iCommand = 0x0D },
#elif defined(COMMANDS_LED)
  { .szName="OFF",              .iAddress=0xFBE2,   .iCommand=0x25 },
  { .szName="AUTO",             .iAddress=0xFBE2,   .iCommand=0x2D },
  { .szName="ON",               .iAddress=0xFBE2,   .iCommand=0x26 },
  { .szName="PRESET1",          .iAddress=0xFBE2,   .iCommand=0x0B },
  { .szName="PRESET2",          .iAddress=0xFBE2,   .iCommand=0x0A },
  { .szName="PRESET3",          .iAddress=0xFBE2,   .iCommand=0x0F },
  { .szName="1H",               .iAddress=0xFBE2,   .iCommand=0x5B },
  { .szName="2H",               .iAddress=0xFBE2,   .iCommand=0x5C },
  { .szName="3H",               .iAddress=0xFBE2,   .iCommand=0x6E },
  { .szName="SPEED+",           .iAddress=0xFBE2,   .iCommand=0x06 },
  { .szName="MODE+",            .iAddress=0xFBE2,   .iCommand=0x08 },
  { .szName="BRIGHTNESS+",      .iAddress=0xFBE2,   .iCommand=0x5A },
  { .szName="SPEED-",           .iAddress=0xFBE2,   .iCommand=0x09 },
  { .szName="MODE-",            .iAddress=0xFBE2,   .iCommand=0x8A },
  { .szName="BRIGHTNESS-",      .iAddress=0xFBE2,   .iCommand=0x10 },
  { .szName="R",                .iAddress=0xFBE2,   .iCommand=0x1C },
  { .szName="G",                .iAddress=0xFBE2,   .iCommand=0x52 },
  { .szName="B",                .iAddress=0xFBE2,   .iCommand=0x53 },
  { .szName="YELLOW",           .iAddress=0xFBE2,   .iCommand=0x0C },
  { .szName="GREEN",            .iAddress=0xFBE2,   .iCommand=0x1A },
  { .szName="BLUE",             .iAddress=0xFBE2,   .iCommand=0x1F },
  { .szName="RED",              .iAddress=0xFBE2,   .iCommand=0x01 },
  { .szName="PURPLE",           .iAddress=0xFBE2,   .iCommand=0x00 },
  { .szName="W",                .iAddress=0xFBE2,   .iCommand=0x02 },
#else
  #error "Invalid command set value defined!"
#endif
};

// FUNCTION IMPLEMENTATIONS

ircommand_t const * get_command(const char* szInput)
{
    for(int i = 0; i < sizeof(lstCommands)/sizeof(ircommand_t); i++)
    {
      if(strcmp(szInput, lstCommands[i].szName) == 0)
      {
        return &lstCommands[i];
      }
    }

    return NULL;
}