# Dilemma Procyon Firmware Notes

Created: 2026-05-13

## Goal

Build a custom QMK firmware for the new AliExpress keyboard, using the existing
Totem layout as the main layout reference and the existing Scylla QMK keymap as
the implementation reference.

No firmware implementation has been started yet.

## Hardware Assumptions

- The sales listing says "Dilemma Max" and "4x6", but the photos and purchase
  context indicate a 3x5 MX split Dilemma variant.
- Procyon is confirmed by text printed on the PCB.
- Two rotary encoders are installed.
- The initially suspected upstream hardware target is:
  `bastardkb/dilemma/3x5_3_procyon`
- This is not the same as the older local target:
  `bastardkb/dilemma/3x5_3`
- Important uncertainty: the upstream Dilemma hardware README lists
  `3x5_3_procyon` as Choc V1 hotswap. Since this board is MX and Procyon, it may
  be a seller-custom/clone variant rather than an exact BastardKB V3 target.

## Upstream References

- BastardKB Dilemma hardware repo:
  https://github.com/Bastardkb/Dilemma
- BastardKB Dilemma V3 firmware docs:
  https://docs.bastardkb.com/fw/procyon-compile.html
- BastardKB flashing docs:
  https://docs.bastardkb.com/fw/flashing.html
- Procyon hardware repo:
  https://github.com/george-norton/procyon
- Procyon QMK/ZMK status:
  https://github.com/george-norton/procyon#software-support

## What the Repos Show

### Local `bastardkb-qmk`

- Current branch: `bkb-master`
- Remote: `https://github.com/bastardkb/bastardkb-qmk`
- The local Dilemma targets are Cirque-based:
  - `bastardkb/dilemma/3x5_2`
  - `bastardkb/dilemma/3x5_3`
  - `bastardkb/dilemma/4x6_4`
- The local `3x5_3` target uses:
  - RP2040
  - `bootloader = rp2040`
  - split soft serial on `GP1`
  - handedness pin `GP29`
  - Cirque Pinnacle over SPI
  - one encoder definition in the JSON, mapped as two encoders by the split
  - RGB matrix with split count `[36, 36]`

This local branch should not be used as-is for the new keyboard if the touchpad
is really Procyon.

### Upstream Dilemma Hardware Repo

The Dilemma hardware README lists these relevant variants:

- `3x5_3`: Dilemma V2, Cirque, MX/Choc, underglow, per-key RGB, rotary encoders.
- `3x5_3_procyon`: Dilemma V3 hotswap, Procyon, Choc V1, underglow, per-key RGB,
  rotary encoders, VIK.
- `4x6_4_procyon`: Dilemma MAX V3 hotswap, Procyon, Choc V1.

The Procyon aspect is confirmed, but the MX switch variant makes the exact
target uncertain.

### BastardKB Procyon Firmware Docs

BastardKB documents Dilemma V3 / Dilemma MAX V3 separately from the older
Dilemma targets. The key points:

- The Procyon Dilemma code is on the `bkb-procyon` branch, not `bkb-master`.
- The example keyboard target is:
  `bastardkb/dilemma/3x5_3_procyon`
- A custom keymap should live in:
  `keyboards/bastardkb/dilemma/3x5_3_procyon/keymaps/<keymap_name>`
- Local build example:
  `qmk compile -c -kb bastardkb/dilemma/3x5_3_procyon -km <keymap_name>`

### Local `qmk_userspace`

- Current branch: `main`
- Remote: `https://github.com/feuerdev/qmk_userspace.git`
- `qmk.json` currently builds only:
  `["bastardkb/scylla", "feuerdev"]`
- Existing Scylla keymap already has QMK equivalents for several Totem ideas:
  - Hands-down-ish alpha layout: `Q W F P B` / `J L U Y -`
  - home row mods
  - combos for escape, copy/cut/paste, symbols, email
  - custom shift keys
  - Achordion
  - swapper helper for window switching

This makes Scylla the best local QMK implementation template.

### Local `zmk-config-totem`

The Totem layout is the desired user-facing behavior reference:

- Layers:
  - `BASE`
  - `NAV`
  - `FUNC`
  - `NUM`
  - `QWERTZ`
  - `GAME`
- Layout traits:
  - 3x5-ish core with extra outer bottom keys and 3 thumb keys per side.
  - hold-tap numbers on the top alpha row.
  - home row mods on `A R S T` and `N E I O`.
  - custom shifted punctuation behavior.
  - many symbol and app shortcut combos.
  - bootloader combo.

The Dilemma `3x5_3_procyon` has 36 physical keys, while the Totem keymap uses
38 positions. The future port needs a deliberate decision for the two keys that
exist on Totem but not on Dilemma.

## Firmware Backup and Restore

### Current plug-in observation

When plugged in, the keyboard exposes only the RP2040 bootloader mass-storage
files: an HTML file pointing to the Raspberry Pi website and a text info file.
That normally means the controller is in BOOTSEL / `RPI-RP2` mode, not running
keyboard firmware.

Observed `INFO_UF2.TXT` contents:

```text
Right:
UF2 Bootloader v3.0
Model: Raspberry Pi RP2
Board-ID: RPI-RP2

Left:
UF2 Bootloader v3.0
Model: Raspberry Pi RP2
Board-ID: RPI-RP2
```

Likely explanations:

- The controller is blank or does not contain valid firmware.
- The controller was intentionally shipped in bootloader mode.
- A BOOT/BOOTSEL or reset/update control is stuck or held.
- Less likely: the wrong half or a disconnected/failed split setup is masking
  the expected keyboard behavior.

If this is the only USB behavior on both halves, there may be no shipped
QMK/Vial firmware to back up or restore.

### Can the current firmware be extracted?

If firmware is present, probably yes at the RP2040 flash level, but not as
useful source code. If the board is blank, extraction will only produce an empty
or bootloader-only flash image.

For RP2040 boards, `picotool save` can save the installed program or the full
flash while the board is in BOOTSEL / `RPI-RP2` mode. This can produce a `.uf2`
or `.bin` backup. That backup is a binary image, not the original QMK source,
keymap C code, or Vial/VIA JSON.

Useful commands once `picotool` is installed:

```sh
picotool info
picotool save current-firmware.uf2 -t uf2
picotool save -a current-full-flash.uf2 -t uf2
```

Current local state: `picotool` is not installed on this machine.

### Can the current firmware be restored later?

Yes, if a valid backup was created before flashing.

Restore options:

- Put the keyboard half into RP2040 bootloader mode.
- Copy the saved `.uf2` to the `RPI-RP2` drive, or use `picotool load`.
- Repeat for the other half if both halves were backed up/flashed.

Important caveats:

- A binary backup restores firmware bytes, not source.
- Dynamic Vial/VIA settings may live in EEPROM/flash storage. A full-flash
  backup is safer than program-only if the goal is a practical rollback.
- If the AliExpress firmware is not built from public BastardKB sources, the
  backup is the only exact way back to that shipped image.
- If the board was shipped blank, there is no current keyboard firmware to
  revert to. The fallback becomes a known-good firmware built from source.
- Vial can usually export/save the dynamic keymap configuration, but that is not
  a firmware backup.

## Flashing Process

The board is RP2040-based if it follows the BastardKB Dilemma V3 design.

High-level process:

1. Build or obtain a `.uf2` firmware image for the exact board target.
2. Put one keyboard half into bootloader mode.
3. Wait for the `RPI-RP2` USB drive to appear.
4. Copy the `.uf2` file onto that drive, or use `qmk flash`.
5. The drive disappears and the keyboard reboots.
6. Flash the other half too if the QMK version, RGB behavior, encoder behavior,
   split behavior, or pointing-device behavior changed.

Bootloader entry methods documented by BastardKB:

- `QK_BOOT` keycode, if the current keymap exposes it.
- Bootmagic, by holding the configured bootmagic key while plugging in USB.
- Double-tap the keyboard's reset/update button within 500 ms.
- Hardware fallback: hold the BOOT/BOOTSEL button while plugging in USB.

For the Dilemma family, BastardKB notes that the default firmware expects USB on
the right side during normal use.

## First Safe Steps When the Keyboard Arrives

1. Plug in each half separately without flashing anything.
2. Record whether each half appears as a keyboard or as the `RPI-RP2`
   bootloader drive.
3. If a half appears as a keyboard, try Vial and VIA, then export/save any
   dynamic layout configuration.
4. If a half appears only as `RPI-RP2`, inspect the text info file and save its
   contents in these notes.
5. Install `picotool`.
6. If `picotool info` can see a program image, save program-only and full-flash
   backups for each half before flashing.
7. If both halves are blank or bootloader-only, build and flash a known-good
   firmware for the exact hardware target.

## Open Questions

- Is the PCB electrically compatible with BastardKB `3x5_3_procyon`, despite
  being MX rather than the upstream-documented Choc V1 hotswap variant?
- Is the firmware Vial, VIA, or a custom fork?
- Was the keyboard shipped blank, or is a boot/reset control causing it to enter
  bootloader mode every time?
- Does each half expose the expected reset/update/boot hardware access without
  disassembly?
- Does the AliExpress board use unmodified BastardKB V3 PCBs, or a clone with
  pin/layout changes?
- Does the right encoder/left encoder match the BastardKB defaults, or did the
  seller customize the encoder map?

## Future Implementation Direction

Initial scaffold setup:

- `qmk_userspace` now has a `dilemma-procyon` branch.
- `bastardkb-qmk` has the `bkb-procyon` branch fetched locally.
- The upstream BastardKB Procyon `vendor` keymap has been copied into:
  `keyboards/bastardkb/dilemma/3x5_3_procyon/keymaps/vendor`
- A `feuerdev` keymap scaffold has been copied from that vendor keymap:
  `keyboards/bastardkb/dilemma/3x5_3_procyon/keymaps/feuerdev`
- `qmk.json` now builds:
  `["bastardkb/dilemma/3x5_3_procyon", "feuerdev"]`
- The GitHub Actions workflow now targets BastardKB QMK `bkb-procyon`.

Still to do:

- Port the Totem layout behavior using the existing Scylla QMK code where
  possible.
- Decide how to handle the Totem-only extra keys before writing the keymap.
- Keep a `QK_BOOT` path and a physical bootloader fallback available in early
  builds.
