all: libLcd.a main.elf

CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h 
LDFLAGS 	= -L/opt/ti/msp430_gcc/include -L../lib 
#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c
AR              = msp430-elf-ar

libLcd.a: font-11x16.o spaceships.o lcdutils.o lcddraw.o
	$(AR) crs $@ $^

lcddraw.o: lcddraw.c lcddraw.h lcdutils.h
lcdutils.o: lcdutils.c lcdutils.h
movement.o: movement.h lcddraw.h lcdutils.h assembly.h
buzzer.o: buzzer.h
switches.o: switches.h
assemblyA.o: assemblyA.s assembly.h

install: libLcd.a
	mkdir -p ../h ../lib
	mv $^ ../lib
	cp *.h ../h

clean:
	rm -f libLcd.a *.o *.elf 

main.elf: $(COMMON_OBJECTS) main.o libLcd.a wdt_handler.o movement.o buzzer.o switches.o assemblyA.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lTimer -lp2sw  -lLcd 

load: main.elf
	msp430loader.sh $^
