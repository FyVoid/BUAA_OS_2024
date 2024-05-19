#include "serv.h"

void port_write(u_char port, u_char pa) {
    panic_on(syscall_write_dev(((void*) (port + KSEG1)), pa, 1));
}

u_char port_read(u_char port) {
    u_char ret;
    panic_on(syscall_read_dev(((void*) (port + KSEG1)), &ret, 1));
    return ret;
}

void vga_write_reg(u_char reg, u_char value) {
    port_write(reg, &value);
}

void vga_write_index_reg(u_char addr, u_char data, u_char index, u_char value) {
    port_write(addr, &index);
    port_write(data, &value);
}

u_char vga_read_reg(u_char reg) {
    return port_read(reg);
}

u_char vga_read_index_reg(u_char addr, u_char data, u_char index) {
    port_write(addr, &index);
    return port_read(data);
}