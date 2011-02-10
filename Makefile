all : freertos.elf

PATH := /usr/share/gnurx_v10.03_elf-1/bin:/usr/share/gnurx_v10.03_elf-1/rx-elf/bin:$(PATH)

CFLAGS = \
	-I telnetd \
	-I ethernet \
	-I board_hw \
	-I board_hw/wifi_driver \
	-I ethernet/FreeTCPIP \
	-I ethernet/FreeTCPIP/net \
	-I FreeRTOS/include \
	-I FreeRTOS/portable/GCC/RX600 \
	-I FreeRTOS \
	-I ethernet/FreeTCPIP/sys \
	-std=c99 \
	$(END)


CFILES_ENET = \
	board_hw/temp_board.c \
	board_hw/net.c \
	board_hw/i2c.c \
	board_hw/accelerometer.c \
	board_hw/wifi_driver/network_config.c \
	board_hw/wifi_driver/process_data.c \
	board_hw/wifi_driver/rs22_spi_bus.c \
	board_hw/wifi_driver/rs22_spi_pine.c \
	board_hw/wifi_driver/rs22_ssp_hcd.c \
	board_hw/wifi_driver/rsi_spi.c \
	board_hw/wifi_driver/rsi_util.c \
	board_hw/spi_driver.c \
	ethernet/memb.c \
	telnetd/telnetd.c \
	telnetd/shell.c \
	ethernet/ip_apps.c \
	FreeRTOS/BlockQ.c \
	FreeRTOS/GenQTest.c \
	FreeRTOS/IntQueue.c \
	FreeRTOS/PollQ.c \
	FreeRTOS/QPeek.c \
	FreeRTOS/blocktim.c \
	FreeRTOS/death.c \
	FreeRTOS/flop.c \
	FreeRTOS/integer.c \
	FreeRTOS/recmutex.c \
	FreeRTOS/semtest.c \
	board_hw/start.asm \
	ethernet/FreeTCPIP/psock.c \
	ethernet/FreeTCPIP/timer.c \
	ethernet/FreeTCPIP/uip.c \
	ethernet/FreeTCPIP/uip_arp.c \
	board_hw/hwinit.c \
	inthandler.c \
	HighFrequencyTimerTest.c \
	IntQueueTimer.c \
	board_hw/hwsetup.c \
	main.c \
	uIP_Task.c \
	board_hw/vects.c \
	ethernet/EMAC.c \
	ethernet/phy.c \
	board_hw/lcd.c \
	board_hw/font_x5x7.c \
	FreeRTOS/list.c \
	FreeRTOS/portable/GCC/RX600/port.c \
	FreeRTOS/portable/MemMang/heap_2.c \
	FreeRTOS/queue.c \
	FreeRTOS/tasks.c \
	$(END)

CFILES = \
	start.asm \
	board_hw/vects.c \
	FreeRTOS/list.c \
	FreeRTOS/queue.c \
	FreeRTOS/tasks.c \
	FreeRTOS/portable/MemMang/heap_2.c \
	FreeRTOS/portable/GCC/RX600/port.c \
	hwinit.c \
	inthandler.c \
	hwsetup.c \
	$(END)st

OFILES := $(addsuffix .o,$(basename $(CFILES_ENET)))

freertos.elf : $(OFILES)
	rx-elf-gcc -nostartfiles $(OFILES) -o freertos.elf -T main.gsi
	rx-elf-size freertos.elf

%.o : %.c
	rx-elf-gcc -c $(CFLAGS) -Os $< -o $@

%.o : %.S
	rx-elf-gcc -x assembler-with-cpp -c $(CFLAGS) -O2 $< -o $@

%.o : %.asm
	rx-elf-gcc -x assembler-with-cpp -c $(CFLAGS) -O2 $< -o $@

flash : freertos.elf
	sudo ../flash-tools/rxusb -v freertos.elf

clean :
	rm -f $(OFILES) freertos.elf
