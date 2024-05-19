#ifndef VGA_H
#define VGA_H

#include <mmu.h>
#include <printk.h>
#include <io.h>

#define IOPORT_OFFSET                               (0x400 - 0x3c0)
#define BEGIN_VGA_IOPORT                            0x30c
#define END_VGA_IOPORT                              0x3df

#define VGA_STD2QEMU(x)                             (x + IOPORT_OFFSET)

// Registers

// External registers
#define MISCELLANEOUS_OUTPUT_READ                   0x3cc
#define MISCELLANEOUS_OUTPUT_WRITE                  0x3c2
#define FEATURE_CONTROL_READ                        0x3ca
#define FEATURE_CONTROL_WRITE_MONO                  0x3ba
#define FEATURE_CONTROL_WRITE_COLOR                 0x3da
#define INPUT_STATUS_0_READ                         0x3c2
#define INPUT_STATUS_1_READ_MONO                    0x3ba
#define INPUT_STATUS_1_READ_COLOR                   0x3da

// Graphic registers
#define GRAPHIC_ADDR                                0x3ce
#define GRAPHIC_DATA                                0x3cf
#define GRAPHIC_SET_RESET                           0x0
#define GRAPHIC_ENABLE_SET_RESET                    (GRAPHIC_SET_RESET + 1)
#define GRAPHIC_COLOR_COMPARE                       (GRAPHIC_ENABLE_SET_RESET + 1)
#define GRAPHIC_DATA_ROTATE                         (GRAPHIC_COLOR_COMPARE + 1)
#define GRAPHIC_READ_MAP_SELECT                     (GRAPHIC_DATA_ROTATE + 1)
#define GRAPHIC_MODE                                (GRAPHIC_READ_MAP_SELECT + 1)
#define GRAPHIC_MISCELLANEOUS_GRAPHIC               (GRAPHIC_MODE + 1)
#define GRAPHIC_COLOR_DONT_CARE                     (GRAPHIC_MISCELLANEOUS_GRAPHIC + 1)
#define GRAPHIC_BIT_MASK                            (GRAPHIC_COLOR_DONT_CARE + 1)

// Sequencer registers
#define SEQUENCER_ADDR                              0x3c4
#define SEQUENCER_DATA                              0x3c5
#define SEQUENCER_RESET                             0x0
#define SEQUENCER_CLOCKING_MODE                     (SEQUENCER_RESET + 1)
#define SEQUENCER_MAP_MASK                          (SEQUENCER_CLOCKING_MODE + 1)
#define SEQUENCER_CHARACTER_MAP                     (SEQUENCER_MAP_MASK + 1)
#define SEQUENCER_MEM_MODE                          (SEQUENCER_CHARACTER_MAP + 1)

// Attribute registers
#define ATTRIBUTE_ADDR                              0x3c0
#define ATTRIBUTE_DATA                              0x3c1
#define ATTRIBUTE_PALETTE_BEGIN                     0x0
#define ATTRIBUTE_PALETTE_END                       (ATTRIBUTE_PALETTE_BEGIN + 0xf)
#define ATTRIBUTE_MODE                              (ATTRIBUTE_PALETTE_END + 1)
#define ATTRIBUTE_OVERSCAN                          (ATTRIBUTE_MODE + 1)
#define ATTRIBUTE_COLOR_PLANE_ENABLE                (ATTRIBUTE_OVERSCAN + 1)
#define ATTRIBUTE_HORIZONTAL_PIXEL_PANNING          (ATTRIBUTE_COLOR_PLANE_ENABLE + 1)
#define ATTRIBUTE_COLOR_SELECT                      (ATTRIBUTE_HORIZONTAL_PIXEL_PANNING + 1)

// CRT controller registers
#define CRT_ADDR(s)                                 (0x3b4 + 0x2 * s)
#define CRT_DATA(s)                                 (0x3b5 + 0x2 * s)
#define CRT_HORIZONTAL_TOTAL                        0x0
#define CRT_END_HORIZONTAL_DISPLAY                  (CRT_HORIZONTAL_TOTAL + 1)
#define CRT_START_HORIZONTAL_BLANKING               (CRT_END_HORIZONTAL_DISPLAY + 1)
#define CRT_END_HORIZONTAL_BLANKING                 (CRT_START_HORIZONTAL_BLANKING + 1)
#define CRT_START_HORIZONTAL_RETRACE                (CRT_END_HORIZONTAL_BLANKING + 1)
#define CRT_END_HORIZONTAL_RETRACE                  (CRT_START_HORIZONTAL_RETRACE + 1)
#define CRT_VERTICAL_TOTAL                          (CRT_END_HORIZONTAL_RETRACE + 1)
#define CRT_OVERFLOW                                (CRT_VERTICAL_TOTAL + 1)
#define CRT_PRESET_ROW_SCAN                         (CRT_OVERFLOW + 1)
#define CRT_MAXIMUM_SCAN_LINE                       (CRT_PRESET_ROW_SCAN + 1)
#define CRT_CURSOR_START                            (CRT_MAXIMUM_SCAN_LINE + 1)
#define CRT_CURSOR_END                              (CRT_CURSOR_START + 1)
#define CRT_START_ADDR_HIGH                         (CRT_CURSOR_END + 1)
#define CRT_START_ADDR_LOW                          (CRT_START_ADDR_HIGH + 1)
#define CRT_CURSOR_LOCATION_HIGH                    (CRT_START_ADDR_LOW + 1)
#define CRT_CURSOR_LOCATION_LOW                     (CRT_CURSOR_LOCATION_HIGH + 1)
#define CRT_VERTICAL_RETRACE_START                  (CRT_CURSOR_LOCATION_LOW + 1)
#define CRT_VERTICAL_RETRACE_END                    (CRT_VERTICAL_RETRACE_START + 1)
#define CRT_VERTICAL_DISPLAY_END                    (CRT_VERTICAL_RETRACE_END + 1)
#define CRT_OFFSET                                  (CRT_VERTICAL_DISPLAY_END + 1)
#define CRT_UNDERLINE_LOCATION                      (CRT_OFFSET + 1)
#define CRT_START_VERTICAL_BLANKING                 (CRT_UNDERLINE_LOCATION + 1)
#define CRT_END_VERTICAL_BLANKING                   (CRT_START_VERTICAL_BLANKING + 1)
#define CRT_CRTC_MODE_CONTROL                       (CRT_END_VERTICAL_BLANKING + 1)
#define CRT_LINE_COMPARE                            (CRT_CRTC_MODE_CONTROL + 1)

// Color register
#define DAC_ADDR_WRITE_MODE                         0x3c8
#define DAC_ADDR_READ_MODE                          0x3c7
#define DAC_DATA                                    0x3c9
#define DAC_STATE                                   0x3c7

// Display Buffer
#define VGA_BEGIN_ADDR_128                          0xA0000
#define VGA_END_ADDR_128                            0xBFFFF
#define VGA_BEGIN_ADDR_64                           0xA0000
#define VGA_END_ADDR_64                             0xAFFFF
#define VGA_BEGIN_ADDR_32_1                         0xB0000
#define VGA_END_ADDR_32_1                           0xB7FFF
#define VGA_BEGIN_ADDR_32_2                         0xB8000
#define VGA_END_ADDR_32_2                           0xBFFFF

void sys_vga_write_index_reg(u_char addr, u_char index, u_char value);
void sys_vga_write_reg(u_char addr, u_char value);
u_char sys_vga_read_index_reg(u_char addr, u_char index);
u_char sys_vga_read_reg(u_char addr);
void set_display_mode();
void set_video_memory();
void set_timing_parameters();
void set_color_palette();
void set_cursor_position();
void clear_screen();
void vga_init();

#endif