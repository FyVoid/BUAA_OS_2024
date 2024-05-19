#include <vga.h>

void sys_vga_write_index_reg(u_char addr, u_char index, u_char value) {
    uint16_t v = (value << 8) + index;
    iowrite16(v, VGA_STD2QEMU(addr));
}

void sys_vga_write_reg(u_char addr, u_char value) {
    iowrite8(value, VGA_STD2QEMU(addr));
}

u_char sys_vga_read_index_reg(u_char addr, u_char index) {
    iowrite8(index, VGA_STD2QEMU(addr));
    return ioread8(VGA_STD2QEMU(addr + 1));    
}

u_char sys_vga_read_reg(u_char addr) {
    return ioread8(VGA_STD2QEMU(addr));
}

void set_display_mode() {
    // Graphic registers
    sys_vga_write_index_reg(GRAPHIC_ADDR, GRAPHIC_SET_RESET, 0x0);
    sys_vga_write_index_reg(GRAPHIC_ADDR, GRAPHIC_ENABLE_SET_RESET, 0b00001111);
    printk("%x\n", sys_vga_read_index_reg(GRAPHIC_ADDR, GRAPHIC_ENABLE_SET_RESET));
    sys_vga_write_index_reg(GRAPHIC_ADDR, GRAPHIC_COLOR_COMPARE, 0x0);
    sys_vga_write_index_reg(GRAPHIC_ADDR, GRAPHIC_DATA_ROTATE, 0x0);
    printk("%x\n", sys_vga_read_index_reg(GRAPHIC_ADDR, GRAPHIC_ENABLE_SET_RESET));
    sys_vga_write_index_reg(GRAPHIC_ADDR, GRAPHIC_READ_MAP_SELECT, 0x0);
    sys_vga_write_index_reg(GRAPHIC_ADDR, GRAPHIC_MODE, 0x01000000);
    sys_vga_write_index_reg(GRAPHIC_ADDR, GRAPHIC_MISCELLANEOUS_GRAPHIC, 0b00000011);
    sys_vga_write_index_reg(GRAPHIC_ADDR, GRAPHIC_COLOR_DONT_CARE, 0x0);
    sys_vga_write_index_reg(GRAPHIC_ADDR, GRAPHIC_BIT_MASK, 0b11111111);

    // Sequencer registers
}

void set_video_memory() {

}

void set_timing_parameters() {

}

void set_color_palette() {

}

void set_cursor_position() {

}

void clear_screen() {
    for (int i = 0; i < 25 * 80; i += 2) {
        iowrite8(' ', 0xb8000 + i);
        iowrite8(' ', 0xb8000 + i);
    }
}

void vga_init() {
    set_display_mode();
    set_video_memory();
    set_timing_parameters();
    set_color_palette();
    set_cursor_position();
    clear_screen();
    printk("vga init complete\n");
}