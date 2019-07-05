CC  = /opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j

CFLAGS	= -DGBDK_2_COMPAT

BINS	= main.gb

EMULATOR = sameboy

all:	$(BINS)

%.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o:	%.s
	$(CC) $(CFLAGS) -c -o $@ $<

%.s:	%.c
	$(CC) $(CFLAGS) -S -o $@ $<

%.gb:	%.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o *.lst *.map *.gb

# Link file, and write 0x80 at position 0x143 in header
main.gb:	main.o
	$(CC) $(CFLAGS) -Wl-yp0x143=0x80 -o main.gb main.o

run:	main.gb
	$(EMULATOR) main.gb

tiletest.gb:	tiletest.o
	$(CC) $(CFLAGS) -Wl-yp0x143=0x80 -o tiletest.gb tiletest.o

run-tiletest:	tiletest.gb
	$(EMULATOR) tiletest.gb