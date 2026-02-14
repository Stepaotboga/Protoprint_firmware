/**
 * M325.cpp - Spindle Control
 */

#include "../../inc/MarlinConfig.h"
#include "../gcode.h"

/**
 * M325: Control spindle relay
 * S0 = OFF, S1 = ON
 */
void GcodeSuite::M325() {
  #ifndef SPINDLE_RELAY_PIN
    #define SPINDLE_RELAY_PIN PA15
  #endif
  
  static bool initialized = false;
  if (!initialized) {
    SET_OUTPUT(SPINDLE_RELAY_PIN);
    WRITE(SPINDLE_RELAY_PIN, LOW);
    initialized = true;
  }
  
  if (parser.seen('S')) {
    const bool state = parser.value_bool();
    WRITE(SPINDLE_RELAY_PIN, state);
    SERIAL_ECHO_MSG("Spindle relay: ", state ? "ON" : "OFF");
  }
  else {
    SERIAL_ECHO_MSG("M325: Spindle control");
    SERIAL_ECHO_MSG("Usage: M325 S<0|1>");
  }
}