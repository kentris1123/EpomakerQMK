# Kentris Geonix Rev.2.5 1U keymap

This keymap ports the Kentris Planck layout used on the Thock.co Conundrum to
the split-1U Geonix Rev.2.5 (`geonix41`). It preserves the Default, Lower, and
Raise layouts, the 140 ms mod-tap timing, and the Raise-layer Alt-Tab behavior.

The Planck ZMK mod-tap behavior is reproduced with these QMK settings:

| Planck ZMK behavior | Geonix QMK equivalent |
| --- | --- |
| `tapping-term-ms = <140>` | `TAPPING_TERM 140` |
| `flavor = "hold-preferred"` | `HOLD_ON_OTHER_KEY_PRESS` |
| Quick Tap not enabled | `QUICK_TAP_TERM 0` |

These settings apply to the four outer Control/Shift mod-tap keys. The
Corne-ish Zen's home-row-mod-specific 200 ms balanced behavior and 150 ms
prior-idle filter are intentionally not applied to this Planck layout.

The Geonix firmware reserves layers 0 and 1 for its persisted Mac/Windows mode,
so both contain the same Kentris base layout. Lower and Raise use layers 2 and
3. Holding Lower and either Raise activates layer 4, following the Corne-ish Zen
tri-layer pattern and exposing the Geonix wireless controls:

| Key | Connection |
| --- | --- |
| Top-row 1 | USB |
| Top-row 2 | Bluetooth 1 |
| Top-row 3 | Bluetooth 2 |
| Top-row 4 | Bluetooth 3 |
| Top-row 5 | 2.4 GHz receiver |

Build with:

    make chosfox/geonix_rev25/geonix41:kentris

After flashing this keymap for the first time, reset the keyboard's EEPROM from
Vial so that an existing dynamic keymap does not override these compiled
defaults. This also clears any previous Vial remapping.

To enter the bootloader, hold the top-left two keys while connecting USB. A
`NO_NAME` drive appears; copy the generated `.bin` file onto it.
