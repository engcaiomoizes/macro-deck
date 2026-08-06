#include "tusb.h"

#include "usb/usb_descriptors.h"

enum
{
    ITF_NUM_HID,
    ITF_NUM_TOTAL
};

#define CONFIG_TOTAL_LEN TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN

#define EPNUM_HID 0x81

static uint8_t const hid_report_descriptor[] =
{
    TUD_HID_REPORT_DESC_KEYBOARD(
        HID_REPORT_ID(REPORT_ID_KEYBOARD)
    ),

    TUD_HID_REPORT_DESC_CONSUMER(
        HID_REPORT_ID(REPORT_ID_CONSUMER)
    )
};

uint8_t const* tud_hid_descriptor_report_cb(
    uint8_t instance
)
{
    (void) instance;

    return hid_report_descriptor;
}

tusb_desc_device_t const device_descriptor =
{
    .bLength = sizeof(tusb_desc_device_t),
    .bDescriptorType = TUSB_DESC_DEVICE,
    .bcdUSB = 0x0200,

    .bDeviceClass = 0x00,
    .bDeviceSubClass = 0x00,
    .bDeviceProtocol = 0x00,

    .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,

    // Valores provisórios para desenvolvimento.
    .idVendor = 0xCafe,
    .idProduct = 0x4001,

    .bcdDevice = 0x0100,

    .iManufacturer = 0x01,
    .iProduct = 0x02,
    .iSerialNumber = 0x03,

    .bNumConfigurations = 0x01
};

uint8_t const* tud_descriptor_device_cb(void)
{
    return (uint8_t const*) &device_descriptor;
}

uint8_t const configuration_descriptor[] =
{
    TUD_CONFIG_DESCRIPTOR(
        1,
        ITF_NUM_TOTAL,
        0,
        CONFIG_TOTAL_LEN,
        TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP,
        100
    ),

    TUD_HID_DESCRIPTOR(
        ITF_NUM_HID,
        4,
        HID_ITF_PROTOCOL_KEYBOARD,
        sizeof(hid_report_descriptor),
        EPNUM_HID,
        CFG_TUD_HID_EP_BUFSIZE,
        10
    )
};

uint8_t const* tud_descriptor_configuration_cb(
    uint8_t index
)
{
    (void) index;

    return configuration_descriptor;
}

static char const* string_descriptors[] =
{
    (const char[]) { 0x09, 0x04 },
    "Caio Moizes",
    "Macro Deck",
    "000001",
    "Macro Deck Keyboard"
};

static uint16_t string_descriptor_buffer[32];

uint16_t const* tud_descriptor_string_cb(
    uint8_t index,
    uint16_t langid
)
{
    (void) langid;

    uint8_t character_count;

    if (index == 0)
    {
        string_descriptor_buffer[1] = 0x0409;
        character_count = 1;
    }
    else
    {
        if (index >=
            sizeof(string_descriptors) /
                sizeof(string_descriptors[0]))
        {
            return NULL;
        }

        const char* text = string_descriptors[index];

        character_count = 0;

        while (
            text[character_count] != '\0' &&
            character_count < 31
        )
        {
            string_descriptor_buffer[
                1 + character_count
            ] = text[character_count];

            ++character_count;
        }
    }

    string_descriptor_buffer[0] =
        (uint16_t) (
            (TUSB_DESC_STRING << 8) |
            (2 * character_count + 2)
        );

    return string_descriptor_buffer;
}