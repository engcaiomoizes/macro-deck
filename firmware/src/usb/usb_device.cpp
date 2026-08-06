#include "usb/usb_device.h"

#include "bsp/board_api.h"
#include "tusb.h"

#include "usb/usb_descriptors.h"

namespace usb {
    void UsbDevice::initialize() {
        board_init();
        tusb_init();
    }

    void UsbDevice::update() {
        tud_task();
    }

    bool UsbDevice::mounted() const {
        return tud_mounted();
    }

    bool UsbDevice::sendKeyboardReport(
        uint8_t modifiers,
        const Keycodes& keycodes
    ) {
        if (!tud_hid_ready()) return false;

        return tud_hid_keyboard_report(
            REPORT_ID_KEYBOARD,
            modifiers,
            keycodes.data()
        );
    }

    bool UsbDevice::sendConsumerReport(uint16_t usageCode) {
        if (!tud_hid_ready()) return false;

        return tud_hid_report(
            REPORT_ID_CONSUMER,
            &usageCode,
            sizeof(usageCode)
        );
    }

    bool UsbDevice::releaseKeys() {
        if (!tud_hid_ready()) return false;

        return tud_hid_keyboard_report(
            REPORT_ID_KEYBOARD,
            0,
            nullptr
        );
    }

    bool UsbDevice::releaseConsumerReport() {
        return sendConsumerReport(0);
    }
}

extern "C"
{
    uint16_t tud_hid_get_report_cb(
        uint8_t instance,
        uint8_t reportId,
        hid_report_type_t reportType,
        uint8_t* buffer,
        uint16_t requestLength
    )
    {
        (void) instance;
        (void) reportId;
        (void) reportType;
        (void) buffer;
        (void) requestLength;

        return 0;
    }

    void tud_hid_set_report_cb(
        uint8_t instance,
        uint8_t reportId,
        hid_report_type_t reportType,
        uint8_t const* buffer,
        uint16_t bufferSize
    )
    {
        (void) instance;
        (void) reportId;
        (void) reportType;
        (void) buffer;
        (void) bufferSize;
    }
}