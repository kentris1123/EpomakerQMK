#pragma once

// Match the mod-tap timing used by the Planck ZMK keymap.
#define TAPPING_TERM 140

// ZMK's default &mt behavior used by the Planck keymap is hold-preferred:
// pressing another key while a mod-tap is held resolves it as a modifier.
#define HOLD_ON_OTHER_KEY_PRESS

// The Planck ZMK keymap does not enable quick-tap. Disable QMK's default
// tap-repeat window so a second held press can resolve to the modifier.
#define QUICK_TAP_TERM 0

// Geonix reserves layers 0/1 for its persisted Mac/Windows mode and supports
// five Vial layers in total.
#define DYNAMIC_KEYMAP_LAYER_COUNT 5
