#ifndef __PINS_H__
#define __PINS_H__

#if MB(DEFAULT)
  #include "pins_DEFAULTL.h"
#elif MB(FABSCAN_SHIELD)
 #include "pins_FABSCAN_SHIELD.h"
#endif

#endif
