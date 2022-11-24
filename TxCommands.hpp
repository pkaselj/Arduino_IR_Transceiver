#ifndef TX_COMMANDS_HPP
#define TX_COMMANDS_HPP

#include <stdint.h>

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
struct ircommand_t
{
  const char *szName;
  const addr_t iAddress;
  const uint8_t iCommand;
};

// FUNCTION DEFINITIONS

// Returns handle to command. If no command is found
// with name matching szInput, returns NULL 
ircommand_t const * get_command(const char* szInput);

#endif