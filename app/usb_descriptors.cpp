#include <bsp/board_api.h>
#include <tusb.h>
#include <cstdlib>

enum StringDescriptorIndex : uint8_t
{
    LANGUAGE = 0x00,
    MANUFACTURER = 0x01,
    PRODUCT = 0x02,
    SERIAL_NUMBER = 0x03
};

static const char *string_descriptor_array[] = {
    (const char[]){0x09, 0x04},          // English language.
    "RumeLab",                           // Manufacturer.
    "RumeLab Generic HID Linkage Study", // Product
    NULL                                 // Serial Number.
};

static const tusb_desc_device_t device_descriptor = {
    .bLength = sizeof(tusb_desc_device_t),
    .bDescriptorType = TUSB_DESC_DEVICE,
    .bcdUSB = 0x0200,
    .bDeviceClass = 0x00,
    .bDeviceSubClass = 0x00,
    .bDeviceProtocol = 0x00,
    .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,

    .idVendor = CFG_TUD_ID_VENDOR,
    .idProduct = CFG_TUD_ID_PRODUCT,
    .bcdDevice = 0x0100,

    .iManufacturer = StringDescriptorIndex::MANUFACTURER,
    .iProduct = StringDescriptorIndex::PRODUCT,
    .iSerialNumber = StringDescriptorIndex::SERIAL_NUMBER,

    .bNumConfigurations = 0x01};

static const uint8_t report_descriptor[] = {
    TUD_HID_REPORT_DESC_GENERIC_INOUT(CFG_TUD_HID_EP_BUFSIZE)};

static const uint8_t configuration_descriptor[] = {
    TUD_CONFIG_DESCRIPTOR(1, 1, 0, (TUD_CONFIG_DESC_LEN + TUD_HID_INOUT_DESC_LEN), 0x00, 100),
    TUD_HID_INOUT_DESCRIPTOR(0, 0, HID_ITF_PROTOCOL_NONE, sizeof(report_descriptor), 0x01, 0x81, CFG_TUD_HID_EP_BUFSIZE, 10)};

extern "C"
{
    const uint8_t *tud_descriptor_device_cb()
    {
        return reinterpret_cast<const uint8_t *>(&device_descriptor);
    }

    const uint8_t *tud_hid_descriptor_report_cb(uint8_t p_interface)
    {
        static_cast<void>(p_interface);
        return report_descriptor;
    }

    const uint8_t *tud_descriptor_configuration_cb(uint8_t p_index)
    {
        static_cast<void>(p_index);
        return configuration_descriptor;
    }

    const uint16_t *tud_descriptor_string_cb(uint8_t p_index, uint16_t p_language)
    {
        static_cast<void>(p_language);

        constexpr const uint8_t string_descriptor_length = 64;
        static uint16_t string_descriptor[string_descriptor_length] = {0}; // Follows the maximum length of string in string descriptor array.
        uint16_t count;

        switch (p_index)
        {
        case StringDescriptorIndex::LANGUAGE:
            memcpy(&string_descriptor[1], string_descriptor_array[0], 2);
            count = 1;
            break;

        case StringDescriptorIndex::SERIAL_NUMBER:
            count = board_usb_get_serial(&string_descriptor[1], 34);
            break;

        default:
            constexpr const size_t string_descriptor_array_length = sizeof(string_descriptor_array) / sizeof(string_descriptor_array[0]);
            if (p_index >= string_descriptor_array_length)
                return NULL;

            const char *string = string_descriptor_array[p_index];
            count = strlen(string);
            if (count > (string_descriptor_length - 1))
                count = string_descriptor_length - 1;

            for (size_t i = 0; i < count; ++i)
                string_descriptor[i + 1] = string[i];

            break;
        }

        string_descriptor[0] = (uint16_t)(TUSB_DESC_STRING << 8) | (2 * count + 2);
        return string_descriptor;
    }
}
