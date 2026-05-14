#pragma once

/*
 * Split-pin probe configuration.
 *
 * Both halves run the same firmware but behave differently based on
 * is_keyboard_master(). USB-connected half = master (right). The master
 * listens on a set of candidate pins; the slave drives them LOW one at a
 * time on a fixed schedule. By correlating the master's observation to
 * the slave's schedule we identify which physical pin (if any) is
 * actually wired through the USB-C interhalf cable.
 *
 * Carry over the working bring-up config: USB VBUS detect, MASTER_RIGHT.
 * QMK split serial is redirected to an unused pin (GP25) so the vendor
 * PIO driver compiles, but no candidate pin is touched by the split
 * protocol while we probe.
 */
#undef USB_VBUS_PIN
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 10000

#undef SPLIT_HAND_PIN
#undef SPLIT_HAND_PIN_LOW_IS_LEFT
#define MASTER_RIGHT

#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN GP25
