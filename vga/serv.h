#ifndef VGA_SERV_H
#define VGA_SERV_H

#include <vga.h>
#include <lib.h>

void port_write(u_char, u_char);
u_char port_read(u_char);

void vga_write_reg(u_char reg, u_char value);
void vga_write_index_reg(u_char addr, u_char data, u_char index, u_char value);
u_char vga_read_reg(u_char reg);
u_char vga_read_index_reg(u_char addr, u_char data, u_char index);

#endif