#include "config/default_profile.h"

#include "tusb.h"

namespace config {
    const Profile& defaultProfile() {
        static const Profile profile(
            Profile::Keymap{
                KeyBinding{HID_KEY_A, 0},
                KeyBinding{HID_KEY_B, 0},
                KeyBinding{HID_KEY_C, 0},
                KeyBinding{HID_KEY_D, 0},
                KeyBinding{HID_KEY_E, 0},
                KeyBinding{HID_KEY_F, 0},
                KeyBinding{HID_KEY_G, 0},
                KeyBinding{HID_KEY_H, 0},
                KeyBinding{HID_KEY_I, 0},
                KeyBinding{HID_KEY_J, 0}
            }
        );

        return profile;
    }
}