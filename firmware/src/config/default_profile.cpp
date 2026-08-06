#include "config/default_profile.h"

#include "actions/action.h"
#include "tusb.h"

namespace config {
    const Profile& defaultProfile() {
        static const Profile profile(
            Profile::ActionMap{
                actions::Action::keyboard(HID_KEY_A),
                actions::Action::keyboard(HID_KEY_B),
                actions::Action::keyboard(HID_KEY_C),
                actions::Action::keyboard(HID_KEY_D),
                actions::Action::keyboard(HID_KEY_E),
                actions::Action::keyboard(HID_KEY_F),

                actions::Action::consumer(HID_USAGE_CONSUMER_VOLUME_INCREMENT),
                actions::Action::consumer(HID_USAGE_CONSUMER_VOLUME_DECREMENT),
                actions::Action::consumer(HID_USAGE_CONSUMER_MUTE),
                actions::Action::consumer(HID_USAGE_CONSUMER_PLAY_PAUSE)
            }
        );

        return profile;
    }
}