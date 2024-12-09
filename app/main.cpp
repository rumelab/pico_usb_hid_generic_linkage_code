#include <bsp/board_api.h>
#include <tusb.h>

int main()
{
    board_init();
    tud_init(BOARD_TUD_RHPORT);
    board_init_after_tusb();
    while (1)
        tud_task();
}

extern "C"
{
    void tud_mount_cb()
    {
        board_led_on();
    }

    void tud_umount_cb()
    {
        board_led_off();
    }

    void tud_hid_set_report_cb(uint8_t p_interface, uint8_t p_report_id, hid_report_type_t p_report_type, const uint8_t *p_buffer, uint16_t p_buffer_size)
    {
        static_cast<void>(p_interface);
        static_cast<void>(p_report_id);
        static_cast<void>(p_report_type);
        static_cast<void>(p_buffer);
        static_cast<void>(p_buffer_size);

        const uint8_t buffer[CFG_TUD_HID_EP_BUFSIZE] = {'R', 'e', 'c', 'e', 'i', 'v', 'e', 'd', '!', '\0'};
        tud_hid_report(0, buffer, CFG_TUD_HID_EP_BUFSIZE); // Report must have the same size as described in the USB report descriptor.
    }

    uint16_t tud_hid_get_report_cb(uint8_t p_interface, uint8_t p_report_id, hid_report_type_t p_report_type, uint8_t *p_buffer, uint16_t p_length)
    {
        static_cast<void>(p_interface);
        static_cast<void>(p_report_id);
        static_cast<void>(p_report_type);
        static_cast<void>(p_buffer);
        static_cast<void>(p_length);

        return 0;
    }
}