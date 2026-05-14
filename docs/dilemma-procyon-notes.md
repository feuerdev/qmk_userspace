# Dilemma Procyon Clone Firmware Notes

Investigation started: 2026-05-13. Bring-up completed: 2026-05-14.

## Summary

This keyboard is an AliExpress "Dilemma Max" clone, not an official
BastardKB Dilemma target. The working firmware is based on BastardKB's
`4x6_4_procyon` target, with substantial keymap-level overrides for the
clone PCB.

Working as of 2026-05-14:

- Both halves enumerate and type.
- Split communication works over the USB-C interconnect.
- All matrix keys work on both halves.
- Both rotary encoders work.
- The Procyon/MaxTouch trackpad works.
- RP2040 bootloader recovery works on both halves.

The current `feuerdev` keymap is still a bring-up/test keymap. The final
Totem-style layout port has not started.

## Hardware

Observed physical hardware:

- RP2040 controller on each half.
- 3x6 MX switch matrix per half.
- 3 thumb keys per half.
- 1 rotary encoder per half.
- Procyon/MaxTouch trackpad module.
- USB-C-shaped connector between halves, not TRRS.
- Two underside buttons near the inter-half connector. The lower button is
  BOOT/BOOTSEL: hold it while plugging USB to mount `RPI-RP2`.
- Running firmware enumerates on macOS as `Dilemma Max`,
  USB VID/PID `0xA8F8:0x1837`.

Initial bootloader observation on both halves:

```text
UF2 Bootloader v3.0
Model: Raspberry Pi RP2
Board-ID: RPI-RP2
```

This likely meant the board was shipped blank or bootloader-only. No useful
factory firmware backup was available.

The seller's board resembles a "Dilemma Max 3x6" variant. BastardKB's Quentin
has stated that no official Dilemma Max 3x6 exists, so this should be treated
as a clone with custom PCB routing.

## Working Target

QMK base:

```text
bastardkb-qmk
branch: bkb-procyon
target: bastardkb/dilemma/4x6_4_procyon
```

Userspace keymap:

```text
qmk_userspace/keyboards/bastardkb/dilemma/4x6_4_procyon/keymaps/feuerdev
```

Local build command:

```sh
make bastardkb/dilemma/4x6_4_procyon:feuerdev
```

UF2 output:

```text
qmk_userspace/bastardkb_dilemma_4x6_4_procyon_feuerdev.uf2
```

Local QMK setup:

- `qmk config user.qmk_home` points to
  `/Users/jannik/Documents/DEV/feuerdev/bastardkb-qmk`
- `qmk config user.overlay_dir` points to
  `/Users/jannik/Documents/DEV/feuerdev/qmk_userspace`
- `qmk_userspace/Makefile` adds the Homebrew ARM toolchain paths needed for
  local builds.

Important: `qmk.json` should target `4x6_4_procyon:feuerdev` before relying on
GitHub Actions for this board.

## Firmware Overrides

The working hardware overrides live in:

```text
keyboards/bastardkb/dilemma/4x6_4_procyon/keymaps/feuerdev/config.h
```

### USB Master Detection

Upstream uses `USB_VBUS_PIN GP19`. This clone does not route VBUS there, so the
half with USB could misidentify as the slave. The working config uses QMK's USB
detect polling with a long timeout:

```c
#undef USB_VBUS_PIN
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 10000
```

The default timeout was too short during diagnostics. Ten seconds has been
reliable.

### Handedness

Upstream uses `SPLIT_HAND_PIN GP29`. This clone does not appear to provide a
usable handedness signal there. The working config disables pin-based
handedness and declares the USB-connected half as right:

```c
#undef SPLIT_HAND_PIN
#undef SPLIT_HAND_PIN_LOW_IS_LEFT
#define MASTER_RIGHT
```

Normal use expects USB on the right half.

### Matrix

The matrix is asymmetric. The same RP2040 pins are used on both halves, but not
with the same row/column roles.

Working config:

```c
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#undef DIODE_DIRECTION
#define MATRIX_ROW_PINS       { GP15, GP6,  GP12, GP18, GP17 }
#define MATRIX_COL_PINS       { GP10, GP8,  GP7,  GP5,  GP13, GP9 }
#define MATRIX_ROW_PINS_RIGHT { GP15, GP12, GP13, GP17, GP18 }
#define MATRIX_COL_PINS_RIGHT { GP5,  GP6,  GP7,  GP8,  GP9,  GP10 }
#define DIODE_DIRECTION ROW2COL
```

Interpretation:

- `MATRIX_ROW_PINS` / `MATRIX_COL_PINS` apply to the left half.
- `MATRIX_ROW_PINS_RIGHT` / `MATRIX_COL_PINS_RIGHT` apply to the right half.
- Row `0` / `5`, using `GP15`, is a phantom row retained to fit the upstream
  `4x6_4_procyon` matrix shape.
- The real rows are top, middle, bottom, thumb.
- `col[0]` is the outer pinky column on both halves, following BastardKB's
  mirrored layout convention.
- The clone uses `ROW2COL`, opposite of the upstream Procyon target.

Physical row mapping:

```text
Left:
  top    GP6
  middle GP12
  bottom GP18
  thumbs GP17
  cols outer -> inner: GP10, GP8, GP7, GP5, GP13, GP9

Right:
  top    GP12
  middle GP13
  bottom GP17
  thumbs GP18
  cols outer -> inner: GP5, GP6, GP7, GP8, GP9, GP10
```

The working keymap bypasses the upstream `LAYOUT` macro and addresses
`keymaps[][MATRIX_ROWS][MATRIX_COLS]` directly. This exposes all 3 thumb keys
per side, including positions the upstream `LAYOUT` macro does not expose.

### Split Serial

The USB-C inter-half cable carries two crossed data wires:

```text
left/slave GP0 <-> right/master GP1
left/slave GP1 <-> right/master GP0
```

Half-duplex `SOFT_SERIAL_PIN GP1` cannot work on this wiring because each side's
same-named pin is not connected to the other side's same-named pin. Full duplex
does work:

```c
#undef SOFT_SERIAL_PIN
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1
```

The pin swap happens in the cable/PCB routing. Both halves use the same config.

### Rotary Encoders

Both encoders use the same pins:

```c
#undef ENCODER_A_PINS
#undef ENCODER_B_PINS
#define ENCODER_A_PINS { GP14 }
#define ENCODER_B_PINS { GP16 }
```

The current test keymap maps:

- left encoder: volume up/down
- right encoder: page up/down

Encoder support is enabled by the inherited target/keymap build settings. Keep
these overrides if the keymap is moved into a custom target later.

### Trackpad

The Procyon/MaxTouch trackpad works with the upstream I2C pins:

```text
SDA GP2
SCL GP3
```

The upstream motion/interrupt pin is not usable on this clone because upstream
uses `GP12`, which this PCB uses in the keyboard matrix. The working config
undefines the motion pin and lets QMK poll the digitizer:

```c
#undef DIGITIZER_MOTION_PIN
#undef DIGITIZER_MOTION_PIN_ACTIVE_LOW
```

Rules:

```make
POINTING_DEVICE_ENABLE = yes
MAXTOUCH_DEBUG = no
```

Polling is less elegant than interrupt-driven motion reporting, but it works
without identifying whether this clone routes a separate motion pin.

## Current Keymap

The current keymap is intentionally simple and test-focused:

- Totem-inspired alpha order.
- No home-row mods yet.
- No combos yet.
- No Achordion yet.
- No final symbol/navigation/number layers yet.
- Direct matrix addressing instead of the upstream `LAYOUT` macro.

Special bootloader behavior:

- `QK_BOOT` is available on bottom outer pinky positions for flashing.
- `ENT_OR_BOOT` sends `KC_ENT` during normal split use.
- If a half is plugged in alone and the split transport is absent,
  `ENT_OR_BOOT` enters the bootloader instead. This provides a left-solo
  bootloader path despite `MASTER_RIGHT` remapping.

## Flashing

Standard RP2040 UF2 flow:

1. Put the half into bootloader mode.
2. Wait for the `RPI-RP2` volume.
3. Copy the UF2 to the volume.
4. The volume disappears and the half reboots.

Reliable hardware fallback:

```text
Hold lower underside BOOT button while plugging USB.
```

Flash both halves after changes to matrix, split transport, encoder, pointing
device, or QMK version. For normal use, connect USB to the right half.

## Diagnostics History

Useful diagnostics that led to the working config:

- `3x5_3_procyon` was tried first because the board was initially thought to be
  3x5. It is the wrong physical target.
- Upstream `4x6_4_procyon` was closer in shape, but did not work unmodified.
- Forcing the board to master proved USB/HID was healthy and VBUS detection was
  the first blocker.
- Pin probing showed the upstream matrix pins were wrong.
- Pin probing also showed the diode direction was `ROW2COL`.
- Separate probing of each half showed asymmetric matrix wiring.
- Split probing showed the USB-C interconnect is crossed GP0/GP1, requiring
  full-duplex serial.
- Encoder probing identified `GP14` / `GP16` for both encoders.
- Re-enabling the Procyon with upstream I2C pins and no motion pin confirmed the
  trackpad works by polling.

Diagnostic keymaps currently live under:

```text
keyboards/bastardkb/dilemma/4x6_4_procyon/keymaps/pinprobe
keyboards/bastardkb/dilemma/4x6_4_procyon/keymaps/splitprobe
keyboards/bastardkb/dilemma/4x6_4_procyon/keymaps/encoderprobe
```

They are useful historical tools, but not part of the final user layout.

## External References

- BastardKB Dilemma hardware repo:
  https://github.com/Bastardkb/Dilemma
- BastardKB Procyon firmware docs:
  https://docs.bastardkb.com/fw/procyon-compile.html
- BastardKB flashing docs:
  https://docs.bastardkb.com/fw/flashing.html
- Procyon hardware repo:
  https://github.com/george-norton/procyon
- Ghostbuster91 Dilemma 3x6_3 QMK fork, useful as a 3x6 reference but not a
  drop-in target because it is Cirque-based:
  https://github.com/ghostbuster91/qmk_firmware/tree/bkb-master/keyboards/bastardkb/dilemma/3x6_3
- Reddit thread confirming no official Dilemma Max 3x6:
  https://www.reddit.com/r/ErgoMechKeyboards/comments/1s9grl2/

## Remaining Work

- Update `qmk.json` to build `bastardkb/dilemma/4x6_4_procyon:feuerdev` for
  GitHub Actions.
- Decide whether to keep the current keymap-level overrides or create a proper
  custom userspace keyboard target for this clone.
- Port the real Totem layout behavior using the Scylla QMK keymap as the main
  implementation reference.
- Decide final behavior for the extra outer columns and all six thumb clusters.
- Tune pointer features: DPI steps, drag-scroll, sniping, and optional pointer
  layer behavior.
- Decide whether the diagnostic keymaps should stay in-tree or be removed after
  the final target/keymap settles.
