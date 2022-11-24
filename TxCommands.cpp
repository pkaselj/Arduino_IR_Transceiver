#include "TxCommands.hpp"

#include <Arduino.h>

// PRIVATE list of all commands
static const ircommand_t lstCommands[] =
#ifdef COMMANDS_PURIFIER
  {
    { .szName = "ON", .iAddress = 0x00, .iCommand = 0x00 },
    { .szName = "OFF", .iAddress = 0x00, .iCommand = 0x00 },
    { .szName = "LIGHTS", .iAddress = 0x00, .iCommand = 0x0A },
  };
#endif
#ifdef COMMANDS_TV
  {
    { .szName = "ON", .iAddress = 0xBF00, .iCommand = 0x0D },
    { .szName = "OFF", .iAddress = 0xBF00, .iCommand = 0x0D },
  };
#endif

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