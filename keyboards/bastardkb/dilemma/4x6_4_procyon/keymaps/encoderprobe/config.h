#pragma once

/*
 * Encoder-probe configuration.
 *
 * Flashed onto the LEFT half with the right half disconnected. Listens
 * for HIGH->LOW transitions on every free GPIO and prints them, so we
 * can identify which pins the left rotary encoder is wired to.
 *
 * Reuse the bring-up master detection and handedness so the half
 * enumerates as USB even without the right side; matrix scanning is
 * preserved (we still need it for typing the probe output).
 */
#undef USB_VBUS_PIN
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 10000

#undef SPLIT_HAND_PIN
#undef SPLIT_HAND_PIN_LOW_IS_LEFT
#define MASTER_RIGHT // honored as "the USB-connected half is right" --
                      // when we only plug into the left half, that half
                      // becomes master regardless. Good enough for probe.

#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#undef DIODE_DIRECTION
#define MATRIX_ROW_PINS       { GP15, GP6,  GP12, GP18, GP17 }
#define MATRIX_COL_PINS       { GP10, GP8,  GP7,  GP5,  GP13, GP9 }
#define MATRIX_ROW_PINS_RIGHT { GP15, GP12, GP13, GP17, GP18 }
#define MATRIX_COL_PINS_RIGHT { GP5,  GP6,  GP7,  GP8,  GP9,  GP10 }
#define DIODE_DIRECTION ROW2COL

// Park QMK's split serial on an unused pin so the driver compiles
// without touching candidates we want to observe.
#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN GP25
