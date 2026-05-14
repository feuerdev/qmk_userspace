# QMK Userspace Notes

This repo is the personal QMK userspace fork. Put custom keymaps, userspace
keyboard overrides, build-target config, and local documentation here. Avoid
editing `../bastardkb-qmk` unless QMK core or upstream keyboard definitions
really need to change.

## Repos And Branches

- This repo: `qmk_userspace`, remote `origin =
  https://github.com/feuerdev/qmk_userspace.git`.
- Current Dilemma work branch: `dilemma-procyon`.
- QMK engine repo: `../bastardkb-qmk`, branch `bkb-procyon`.
- Totem reference repo: `../zmk-config-totem`.

Relationship:

- `../bastardkb-qmk` provides QMK itself, BastardKB keyboard targets, Procyon
  support, and the build system.
- This repo overlays keymaps and userspace files on top of that QMK checkout.
- `../zmk-config-totem` is only a layout/behavior reference for the future
  Totem-to-Dilemma port.

## Local Build Workflow

Expected QMK config:

```sh
qmk config user.qmk_home=/Users/jannik/Documents/DEV/feuerdev/bastardkb-qmk
qmk config user.overlay_dir=/Users/jannik/Documents/DEV/feuerdev/qmk_userspace
```

Use `make` from this repo instead of plain `qmk compile`; the local Makefile
adds Homebrew ARM toolchain paths needed on this machine.

Build the current Dilemma clone firmware:

```sh
make bastardkb/dilemma/4x6_4_procyon:feuerdev
```

The UF2 is copied to the userspace root:

```text
bastardkb_dilemma_4x6_4_procyon_feuerdev.uf2
```

Firmware artifacts are ignored by `.gitignore`; do not commit `.uf2`, `.bin`,
or `.hex` files.

## GitHub Actions

`qmk.json` controls what GitHub Actions builds. It should point at the working
Dilemma clone target:

```json
["bastardkb/dilemma/4x6_4_procyon", "feuerdev"]
```

If the build target changes locally, update `qmk.json` before pushing.

## Dilemma Clone Source Of Truth

Main notes:

```text
docs/dilemma-procyon-notes.md
```

Working keymap:

```text
keyboards/bastardkb/dilemma/4x6_4_procyon/keymaps/feuerdev
```

Diagnostic keymaps kept for future hardware debugging:

```text
keyboards/bastardkb/dilemma/4x6_4_procyon/keymaps/pinprobe
keyboards/bastardkb/dilemma/4x6_4_procyon/keymaps/splitprobe
keyboards/bastardkb/dilemma/4x6_4_procyon/keymaps/encoderprobe
```

## Dilemma Clone Pitfalls

The AliExpress board is not an official BastardKB target. Treat upstream
pinouts as hints, not truth.

Known working facts:

- Physical layout is 3x6 plus 3 thumbs per half, not 3x5 and not official
  4x6_4.
- Base target is still `bastardkb/dilemma/4x6_4_procyon`, with keymap-level
  hardware overrides.
- USB should normally be connected to the right half.
- `USB_VBUS_PIN GP19` does not work on this PCB. Use `SPLIT_USB_DETECT` with
  `SPLIT_USB_TIMEOUT 10000`.
- `SPLIT_HAND_PIN GP29` is not usable. The working config uses `MASTER_RIGHT`.
- Matrix wiring is asymmetric between halves; use the per-side row/col pins in
  the `feuerdev/config.h`.
- Diode direction is `ROW2COL`, opposite of upstream Procyon.
- The USB-C interconnect carries crossed `GP0`/`GP1` data wires. Half-duplex
  `SOFT_SERIAL_PIN GP1` does not work. Use full-duplex serial:
  `SERIAL_USART_TX_PIN GP0`, `SERIAL_USART_RX_PIN GP1`.
- Both encoders use `GP14` and `GP16`.
- The Procyon/MaxTouch trackpad works on upstream I2C pins `GP2`/`GP3`, but the
  upstream motion pin conflicts with the matrix. Leave `DIGITIZER_MOTION_PIN`
  undefined so QMK polls the digitizer.
- The upstream `LAYOUT` macro does not expose this clone's exact thumb layout.
  The current keymap directly addresses `keymaps[][MATRIX_ROWS][MATRIX_COLS]`.

## Flashing

Standard RP2040 flow:

1. Put one half into bootloader mode.
2. Wait for the `RPI-RP2` volume.
3. Copy the generated UF2 to the volume.
4. The volume disappears and the half reboots.
5. Flash both halves after matrix, split, encoder, pointing-device, or QMK
   version changes.

Reliable hardware fallback:

```text
Hold the lower underside BOOT/BOOTSEL button while plugging in USB.
```

## Repo Hygiene

- Commit and push userspace changes from this repo.
- Do not commit generated firmware files.
- Do not commit `session.txt`.
- Do not push from `../bastardkb-qmk` unless intentionally maintaining a QMK
  fork.
- Dirty `../bastardkb-qmk` submodule markers like `? lib/chibios` usually mean
  untracked files inside QMK submodules, not userspace changes.
- Keep unrelated keyboard folders unless there is a clear reason to remove
  them. `qmk.json` determines what actually builds.

