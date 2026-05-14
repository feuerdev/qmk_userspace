#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 6
#define TAPPING_TERM 250
#define PERMISSIVE_HOLD
#define FLOW_TAP_TERM 150
#define CHORDAL_HOLD
#define SPECULATIVE_HOLD
#define COMBO_TERM 50
#define COMBO_TERM_PER_COMBO
#define COMBO_SHOULD_TRIGGER

#define COMBO_TERM_FAST 24
#define COMBO_TERM_SLOW 40

/*
 * USB master detection: this PCB does not match upstream USB_VBUS_PIN GP19.
 * Use QMK's polled detect with a longer timeout.
 */
#undef USB_VBUS_PIN
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 10000

/*
 * Handedness: upstream uses SPLIT_HAND_PIN GP29 (low = left). This clone
 * does not appear to wire GP29, so the right half misidentifies as left.
 * Drop pin-based detection and declare the USB-connected half as the right
 * half. The left half will be the secondary when both are connected.
 */
#undef SPLIT_HAND_PIN
#undef SPLIT_HAND_PIN_LOW_IS_LEFT
#define MASTER_RIGHT

/*
 * Matrix, mapped from pin-probe v3 on both halves.
 *
 * The two halves are wired asymmetrically: same RP2040 pins, different
 * matrix role per side. Default MATRIX_*_PINS apply to the LEFT half;
 * MATRIX_*_PINS_RIGHT overrides for the RIGHT half.
 *
 * Both halves: row 0 is a phantom row to pad upstream's 5-row LAYOUT; the
 * clone only has 3 alpha rows + 1 thumb row. BastardKB LAYOUT convention
 * places col[0] at the outer pinky on each side.
 *
 * LEFT half (probed outer pinky -> inner index):
 *   rows: phantom, top, middle, bottom, thumb = GP15, GP6, GP12, GP18, GP17
 *   cols 0..5 (outer pinky -> inner index)    = GP10, GP8, GP7, GP5, GP13, GP9
 *
 * RIGHT half (probed inner index -> outer pinky, reversed for LAYOUT):
 *   rows: phantom, top, middle, bottom, thumb = GP15, GP12, GP13, GP17, GP18
 *   cols 0..5 (outer pinky -> inner index)    = GP5, GP6, GP7, GP8, GP9, GP10
 *
 * Diodes on both halves are anode-on-row, cathode-on-col (ROW2COL),
 * inverted from upstream Procyon.
 */
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#undef DIODE_DIRECTION
#define MATRIX_ROW_PINS       { GP15, GP6,  GP12, GP18, GP17 }
#define MATRIX_COL_PINS       { GP10, GP8,  GP7,  GP5,  GP13, GP9 }
#define MATRIX_ROW_PINS_RIGHT { GP15, GP12, GP13, GP17, GP18 }
#define MATRIX_COL_PINS_RIGHT { GP5,  GP6,  GP7,  GP8,  GP9,  GP10 }
#define DIODE_DIRECTION ROW2COL

/*
 * Split serial: identified via splitprobe that the interhalf cable carries
 * exactly two crossed data wires:
 *   slave (left) GP0 <-> master (right) GP1
 *   slave (left) GP1 <-> master (right) GP0
 *
 * Full-duplex maps onto this cleanly: each side drives its TX pin and
 * listens on its RX pin, and the cable's crossover delivers one side's
 * TX onto the other side's RX. Both halves are compiled with the same
 * pin macros; the swap happens in copper, not config.
 *
 * Upstream sets SOFT_SERIAL_PIN=GP1 (half-duplex). Undef and replace.
 */
#undef SOFT_SERIAL_PIN
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

/*
 * Rotary encoders: identified via encoderprobe. Both halves use the same
 * pins (GP14 = A, GP16 = B). Upstream's keyboard.json declares a single
 * encoder at GP25/GP24, which propagates to both sides via the default
 * ENCODERS_PAD_*_RIGHT fallback. Override with the clone's actual pins;
 * no _RIGHT override needed because the halves are symmetric here.
 */
// keyboard.json generates ENCODER_A_PINS / ENCODER_B_PINS directly from
// its "rotary" array, so undef those (not the legacy ENCODERS_PAD_*) to
// reuse the same name for our override.
#undef ENCODER_A_PINS
#undef ENCODER_B_PINS
#define ENCODER_A_PINS { GP14 }
#define ENCODER_B_PINS { GP16 }

/*
 * Trackpad (Procyon module, MaxTouch chip over I2C).
 *
 * Inherited from upstream config.h: I2C1 on GP2 (SDA) and GP3 (SCL).
 * Both pins are free on this clone, so we leave the I2C wiring alone
 * and only undef the motion pin -- upstream uses GP12 there, which the
 * clone reuses as a matrix row.
 *
 * With DIGITIZER_MOTION_PIN undefined, the digitizer layer falls back
 * to continuous polling instead of waiting for an interrupt. A bit less
 * efficient, but works without knowing the motion pin (or whether the
 * clone routes one at all).
 */
#undef DIGITIZER_MOTION_PIN
#undef DIGITIZER_MOTION_PIN_ACTIVE_LOW
