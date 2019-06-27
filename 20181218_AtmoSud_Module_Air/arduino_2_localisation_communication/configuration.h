/**
 * Modulair Firmware
 *
 *
 */

//==============================================================================
//================================ URLS ========================================
//==============================================================================

// URL recup
#define URL_RCV "https://apigeoloc.herokuapp.com/getpollution" 
//#define URL_RCV "http://apigeoloc.atmosud.org/getpollution"

// URL envoi
#define URL_SND "http://vps345683.ovh.net:9876/import"
//#define URL_SND "http://vps345683.ovh.net:9876/import?"


//==============================================================================
//============================= SHIELD TYPE ====================================
//==============================================================================
#define BOARD_SIM908  1 // 
#define BOARD_FONA808 2 // Adafruit fona808

#define BOARD BOARD_FONA808





//==============================================================================
//============================== INCLUDES ======================================
//==============================================================================

#define MB(board) (BOARD==BOARD_##board)

#if MB(SIM908)
  #include "shield_sim908.h"
#elif MB(FONA808)
  #include "shield_fona808.h"
#endif
