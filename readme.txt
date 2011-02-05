---------------------------------------------------------------------------------
This is based upon the FreeRTOS demo, stripped down and improved by Zizzle - mattpratt.au@gmail.com
---------------------------------------------------------------------------------
sadasdsada
The Wifi Board arrived. Now I try to port the SPI driver from the examples to FreeRTOS.


Need to add following things:
	-clock
	-email client
	-rss reader
	-unpn client which can stream mp3 files for a alarm clock
	-interface to my 16x16 LED matrix
	-interface to my 4x4 LED cube
	-use build in microphone for FFT-->Music visualisation on the LEDs (start with Vu-meter)
	-temperature sensor interface both on board and external (i2c)ds18xxx chip
		




flashing: 
-Configure the RX USB port for "USB Device" (aka "FUNCT") - on/off/off/on for SW6.
-Configure the MCU MODE (SW5) for off/on/on/on (USB boot mode)
-Jumper the "J-LINK DISABLE" (JP13).
-You can power the RDK either via the RX USB port (like I do) or via the wall wart.  If you use the wall wart, you may need to power cycle the board for each download to ensure the device is re-discovered.
-Plug in the USB cable.  Your /var/log/messages should show a USB device of 045b:0025
-Run "rxusb -v your_program.elf"  (rxusb is one of my flash tools).  You'll either need to be root to do this, or use udev to make 045b:0025 world-writable.  Of course, you could make rxusb setuid-root too.
-Turn SW5.2 OFF (the MCU mode now matches "RUN") and press RESET (SW4).  Your program should be running now!


//////////////////////////////////////////////////////////////////////////////////
This is a stripped down version of FreeRTOS 6.1.0 that runs on the Renesas
YRDKRX62N demo board.

I have removed Windows specific build artifacts and a heap of uneeded code for
other ports/board to make it easier to grep the code and get relevent results.

It includes makefiles to build under Linux, and an LCD display driver.

The standard FreeRTOS demos are built by default.

Get the original source package at http://www.freertos.org

Zizzle - mattpratt.au@gmail.com
