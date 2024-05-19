user_dir    := ../user
tools_dir   := ../tools
INCLUDES    := -I../include -I$(user_dir)/include

include $(user_dir)/include.mk
USERLIB     := $(addprefix $(user_dir)/, $(USERLIB))
USERAPPS    := $(addprefix $(user_dir)/, $(USERAPPS))

VGALIB       := port.o

.PRECIOUS: %.b %.b.c
%.x: %.b.c
	$(CC) $(INCLUDES) $(CFLAGS) -c -o $@ $<

%.b.c: %.b
	$(tools_dir)/bintoc -f $< -o $@ -p vga

%.b: %.o $(USERLIB) $(VGALIB)
	$(LD) -o $@ $(LDFLAGS) -T $(user_dir)/user.lds $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

%.o: %.S
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

%.o: $(user_dir)/lib.h

.PHONY: all clean

all: serv.x $(VGALIB)

clean:
	rm -rf *~ *.o *.b.c *.b *.x
