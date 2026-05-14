# QMK Userspace

This is the QMK Userspace for the Bastard Keyboards keymaps - feuerdev version.

You can read how to compile your own keymap on the official docs here: [https://docs.bastardkb.com/fw/compile-firmware.html](https://docs.bastardkb.com/fw/compile-firmware.html).

## Local builds

This userspace is configured to build against the local BastardKB QMK checkout
at `/Users/jannik/Documents/DEV/feuerdev/bastardkb-qmk`.

For the Dilemma Procyon clone keymap:

```sh
make bastardkb/dilemma/4x6_4_procyon:feuerdev
```

The generated UF2 is copied to the userspace root as:

```text
bastardkb_dilemma_4x6_4_procyon_feuerdev.uf2
```
