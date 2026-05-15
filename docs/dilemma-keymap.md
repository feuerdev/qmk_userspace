# Dilemma Keymap Reference

This documents the current `feuerdev` QMK keymap for the Dilemma Procyon clone.

Source files:

- `keyboards/bastardkb/dilemma/4x6_4_procyon/keymaps/feuerdev/keymap.c`
- `keyboards/bastardkb/dilemma/4x6_4_procyon/keymaps/feuerdev/config.h`
- `keyboards/bastardkb/dilemma/4x6_4_procyon/keymaps/feuerdev/rules.mk`

Build target:

```sh
make bastardkb/dilemma/4x6_4_procyon:feuerdev
```

The generated UF2 is copied to:

```text
qmk_userspace/bastardkb_dilemma_4x6_4_procyon_feuerdev.uf2
```

## Physical Shape

The firmware target is BastardKB's `4x6_4_procyon`, but the actual clone is a
3x6 plus 3-thumb layout on each half. The unused upstream rows/keys are mapped
to `KC_NO`.

In the tables below, keys are shown left half first, then right half. The right
half is written in physical split-keyboard order, from inner index to outer
pinky.

## Base Layer

Base is a Totem-style alpha layout with home-row mods and top-row number holds.

```text
Left                                      Right
Q/1      W/2      F/3      P/4      B/5  J/6      L/7      U/8      Y/9      -/0
SFT(A)   CTL(R)   ALT(S)   GUI(T)   G    M        GUI(N)   ALT(E)   CTL(I)   SFT(O)
:        Z/ß      X        C        D    V/Ü      K        H        ,        .        /        '
                  HYPR     NAV/SPC  TAB  NUM/ENT  SFT/BSPC FUNC/DEL
```

Top-row number holds:

- Tap `Q W F P B J L U Y -` for the letters/symbol.
- Hold the same keys for `1 2 3 4 5 6 7 8 9 0`.
- Hold threshold is `TOP_NUM_TERM = 300 ms`.

Alt character holds:

- Tap `Z` for `Z`; hold it for `Alt+S`, used as `ß` on the Totem/macOS setup.
- Tap `V` for `V`; hold it for `Alt+U`, used as `Ü` / umlaut input on the
  Totem/macOS setup.
- Hold threshold is `ALT_HOLD_TERM = 170 ms`.

Home-row mods:

- `A` = left shift when held.
- `R` = left control when held.
- `S` = left alt when held.
- `T` = left GUI when held.
- `N` = left GUI when held.
- `E` = left alt when held.
- `I` = left control when held.
- `O` = left shift when held.

Thumbs:

- Left outer thumb: Hyper.
- Left middle thumb: Space when tapped, NAV when held.
- Left inner thumb: Tab.
- Right inner thumb: Enter when tapped, NUM when held.
- Right middle thumb: Backspace when tapped, Shift when held.
- Right outer thumb: Delete when tapped, FUNC when held.

Special right inner thumb behavior:

- With both halves connected, it is Enter/NUM.
- If only one half is connected and split transport is absent, pressing it enters
  bootloader. This is mainly for recovering a left-half solo flash situation.

## NAV Layer

Hold left middle thumb, `NAV/SPC`, to access NAV.

```text
Left                                             Right
HYPR-Q   HYPR-W   HYPR-F   HYPR-P   MEH-B       MEH-J    GUI-`    Up       MEH-Y    MEH--
Shift    Ctrl     Alt      GUI      MEH-G       MEH-M    Left     Down     Right    MEH-O
HYPR-;   HYPR-Z   HYPR-X   HYPR-C   HYPR-D MEH-V         MEH-K    MEH-H    SGUI-[   SGUI-]  MEH-/    MEH-'
                           trans    trans trans S-Enter  A-Bspc  A-Del
```

Notable uses:

- `HYPR-*` means Control + Shift + Alt + GUI.
- `MEH-*` means Control + Shift + Alt, without GUI.
- `SGUI-*` means Shift + GUI.
- Right-side arrows are on the right home cluster.
- `SGUI-[` and `SGUI-]` are previous/next tab-style shortcuts on the bottom right.
- Right thumb alternatives provide shifted Enter, alt Backspace, and alt Delete.

## FUNC Layer

Hold right outer thumb, `FUNC/DEL`, to access FUNC.

```text
Left                                      Right
F12      F7       F8       F9       DPI+                    Vol+
F11      F4       F5       F6       DPI-           Prev     Vol-     Next
BOOT     F10      F1       F2       F3                     Play     Stop     Mute              BOOT
```

Pointer controls:

- `DPI+` / `DPI-`: cycle normal pointer DPI.
- Pointer speed is intentionally lower than upstream. The saved default DPI
  index maps to `500 CPI` instead of upstream's `1000 CPI`.
- Runtime DPI steps are `100 CPI` instead of upstream's `200 CPI`.

Media controls:

- Volume up/down.
- Previous/next track.
- Play/pause.
- Stop.
- Mute.

Bootloader:

- FUNC bottom-left outer key enters bootloader.
- FUNC bottom-right outer key also enters bootloader.

## NUM Layer

Hold the right inner thumb, `NUM/ENT`, to access NUM.

```text
Left
         7        8        9
0        4        5        6
0        1        2        3
```

The right half is mostly transparent on NUM.

## QWERTZ Layer

QWERTZ is a toggle layer for a conventional German-ish fallback layout.

Toggle it with the top outside combo:

- From BASE: `Q/1` + `-/0`.
- From QWERTZ: `Q` + `P`.

```text
Left                                      Right
Q        W        E        R        T    Y        U        I        O        P
A        S        D        F        G    H        J        K        L        ;
Shift    Z        X        C        V    B        N        M        ,        .        -        '
                  Ctrl     Space    Tab  Enter    Bspc     Del
```

## Combos

Combo timing:

- Default combo term: `COMBO_TERM_FAST = 24 ms`.
- Slow combos: `COMBO_TERM_SLOW = 40 ms`.
- Toggle combos: `COMBO_TERM_TOGGLE = 50 ms`.
- Boot combo: `COMBO_TERM_BOOT = 60 ms`.

Layer and system combos:

| Chord | Action |
| --- | --- |
| bottom-left outer `:` + bottom-right outer `'` | Bootloader |
| top-left outer + top-right outer | Toggle QWERTZ |
| `A` + `O` home-row mod keys | Caps Word |

Editing combos:

| Chord | Action |
| --- | --- |
| `W/2` + `F/3` | Escape |
| `Q/1` + `W/2` | Control-C |
| `Z/ß` + `X` | GUI-X |
| `X` + `D` | GUI-X |
| `X` + `C` | GUI-C |
| `C` + `D` | GUI-V |

Symbol combos:

| Chord | Output |
| --- | --- |
| `T` + `G` | `#` |
| `F/3` + `P/4` | `$` |
| `L/7` + `U/8` | `[` |
| `U/8` + `Y/9` | `]` |
| `N` + `E` | `(` |
| `E` + `I` | `)` |
| `H` + `,` | `{` |
| `,` + `.` | `}` |
| `S` + `T` | `=` |
| `R` + `S` | `+` |
| `M` + `N` | `@` |
| `P/4` + `T` | `%` |
| `U/8` + `E` | `|` |
| `L/7` + `N` | `~` |
| `N` + `H` | `` ` `` |
| `S` + `C` | `*` |
| `F/3` + `S` | `^` |
| `T` + `D` | `&` |
| `P/4` + `L/7` | `&` |
| `D` + `H` | `` ` `` |
| `F/3` + `U/8` | `*` |
| `,` + `C` | `+` |
| `G` + `M` | Types `jannik@feuer.dev` |

## Shifted Punctuation

The keymap uses a local `custom_shift_keys` helper.

| Base key | With Shift |
| --- | --- |
| `,` | `!` |
| `.` | `?` |
| `/` | `\` |
| `:` | `;` |
| `(` | `<` |
| `)` | `>` |

## Encoders

Both halves have one encoder.

Current behavior:

- Encoder index `0`: volume up/down.
- Encoder index `1`: page down/page up.

The physical left/right assignment depends on how QMK enumerates the split
encoders after both halves are flashed.

## Trackpad

The trackpad is the Procyon / MaxTouch module.

Enabled in `rules.mk`:

```make
POINTING_DEVICE_ENABLE = yes
MAXTOUCH_DEBUG = no
```

Wiring/config:

- I2C is inherited from upstream: GP2 SDA, GP3 SCL.
- `DIGITIZER_MOTION_PIN` is undefined because the clone uses upstream's motion
  pin as a matrix row.
- Without a motion interrupt pin, the digitizer uses polling.

Runtime controls are on the FUNC layer:

- normal DPI up/down

The normal pointer DPI range is lowered in `config.h`:

```c
#define DILEMMA_MINIMUM_DEFAULT_DPI 200
#define DILEMMA_DEFAULT_DPI_CONFIG_STEP 100
```

Upstream maps default index `3` to `1000 CPI`; this keymap maps it to
`500 CPI`.

Touch sensitivity is also reduced compared to upstream:

```c
#define MXT_TOUCH_THRESHOLD 20
#define MXT_TOUCH_HYST 5
```

The Procyon default threshold is `20`; this keymap keeps that threshold. Touch
hysteresis is lowered from the Procyon default `10` to `5`, so releases are less
sticky.

Two-finger scroll is slowed down and reversed in firmware:

```c
#define DIGITIZER_SCROLL_DIVISOR 50
#define DILEMMA_REVERSE_DIGITIZER_SCROLL
```

Upstream defaults the scroll divisor to `10`; larger values make wheel reports
smaller. The keymap-level `pointing_device_task_user()` hook reverses horizontal
and vertical scroll reports, while leaving cursor movement unchanged.

## Tap-Hold Configuration

The keymap uses QMK's core tap-hold options to approximate the Totem ZMK home-row
mod behavior.

```c
#define TAPPING_TERM 250
#define PERMISSIVE_HOLD
#define FLOW_TAP_TERM 150
#define CHORDAL_HOLD
#define SPECULATIVE_HOLD
```

Meaning:

- `TAPPING_TERM 250`: generous hold-tap window.
- `PERMISSIVE_HOLD`: nested cross-hand chords can resolve as holds quickly.
- `FLOW_TAP_TERM 150`: fast typing resolves mod-taps as taps more eagerly.
- `CHORDAL_HOLD`: same-hand rolls tend to stay taps, opposite-hand chords can
  become holds.
- `SPECULATIVE_HOLD`: modifiers are applied early while QMK is still deciding,
  which helps modifier plus mouse/trackpad use.

Handedness for Chordal Hold:

- Rows in the left half are treated as left hand.
- Rows in the right half are treated as right hand.
- Thumb rows are treated as wildcard hand (`'*'`), so thumb hold-taps can chord
  with either hand. This keeps the right middle thumb, Backspace when tapped and
  Shift when held, from being forced into a same-hand tap decision when followed
  by a right-hand key.

## Split And Hardware Config

USB/master behavior:

```c
#undef USB_VBUS_PIN
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 10000
#undef SPLIT_HAND_PIN
#undef SPLIT_HAND_PIN_LOW_IS_LEFT
#define MASTER_RIGHT
```

This clone does not match upstream's USB VBUS and handedness pins. The right
half is the intended USB/master side.

Matrix:

- The clone matrix is asymmetric between halves.
- Both halves are `ROW2COL`.
- There is one phantom row per half to fit upstream's 5-row layout shape.

Split transport:

```c
#undef SOFT_SERIAL_PIN
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1
```

The inter-half USB-C cable carries crossed GP0/GP1 serial lines.

Encoder pins:

```c
#undef ENCODER_A_PINS
#undef ENCODER_B_PINS
#define ENCODER_A_PINS { GP14 }
#define ENCODER_B_PINS { GP16 }
```

## Enabled QMK Features

From `rules.mk`:

```make
POINTING_DEVICE_ENABLE = yes
CAPS_WORD_ENABLE = yes
COMBO_ENABLE = yes
SRC += features/custom_shift_keys.c
MAXTOUCH_DEBUG = no
```

From `config.h`:

```c
#define DYNAMIC_KEYMAP_LAYER_COUNT 5
#define COMBO_TERM 50
#define COMBO_TERM_PER_COMBO
#define DILEMMA_MINIMUM_DEFAULT_DPI 200
#define DILEMMA_DEFAULT_DPI_CONFIG_STEP 100
#define MXT_TOUCH_THRESHOLD 20
#define MXT_TOUCH_HYST 5
#define DIGITIZER_SCROLL_DIVISOR 50
#define DILEMMA_REVERSE_DIGITIZER_SCROLL
```
