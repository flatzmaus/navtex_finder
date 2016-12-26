PRG            = main
SRC            = main.c system.c appl.c 
OBJ			       =  $(patsubst  %.c,%.o,$(SRC))
LST			       =  $(patsubst  %.c,%.lst,$(SRC))


#MCU_TARGET     = atmega328p
MCU_TARGET     = atmega32
#MCU_TARGET     = atmega8
#MCU_TARGET     = atmega48
#MCU_TARGET     = atmega88
#MCU_TARGET     = atmega168
#MCU_TARGET     = attiny2313
OPTIMIZE       = -Os

DEFS           =
LIBS           =

# You should not have to change anything below here.

CC             = avr-gcc

# Override is only needed by avr-lib build system.

override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS) -Wno-pointer-sign -Wno-long-long 
override LDFLAGS       = -Wl,-Map,$(PRG).map

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

all: $(PRG).elf lst text info

$(PRG).elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

depend:
	$(CC) -MM  $(SRC)>depend.inc

clean:
	del  *.o $(PRG).elf *.eps *.png *.pdf *.bak
	del  *.lst *.map $(EXTRA_CLEAN_FILES)
	del  depend.inc

lst:  $(LST)

%.lst: %.o
	$(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images

text: hex bin srec

hex:  $(PRG).hex
bin:  $(PRG).bin
srec: $(PRG).srec

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@

info: ${TARGET}
	@echo
	@avr-size -A -x --mcu=${MCU} ${TARGET} $(PRG).elf >$(PRG).inf
	@type $(PRG).inf
	@avr-objdump.exe -S $(PRG).elf >$(PRG).dis
	@avr-readelf.exe -a -W $(PRG).elf >>$(PRG).inf


#include dependencies
ifneq ($(wildcard depend.inc),) 
    include depend.inc
endif

