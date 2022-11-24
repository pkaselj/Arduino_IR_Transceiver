#ifndef TX_COMMANDS_HPP
#define TX_COMMANDS_HPP

// Select which set of commands to define
// Possible settings:
// COMMANDS_TV - commands for TV
// COMMANDS_PURIFIER - commands for air purifier
#define COMMANDS_PURIFIER

// Define addr_t type for NEC addresses
#ifdef COMMANDS_TV
  // TV uses 16-bit addresses
  typedef uint16_t addr_t;
#else
  // Others use 8-bit address
  typedef uint8_t addr_t;
#endif

// Struct which holds information about command
typedef struct {
  const char *szName;
  const addr_t iAddress;
  const uint8_t iCommand;
} ircommand_t;

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

// FUNCTION DEFINITIONS

// Returns handle to command. If no command is found
// with name matching szInput, returns NULL 
ircommand_t const * get_command(const char* szInput);

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



#endif