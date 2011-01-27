---------------------------------------------------------------------------------
This is based upon the FreeRTOS demo, stripped down and improved by Zizzle - mattpratt.au@gmail.com
---------------------------------------------------------------------------------

I hope that my wifi board arrives soon.


Need to add following things:
	-clock
	-email client
	-rss reader
	-unpn client which can stream mp3 files as alarm clock
	-interface to my 16x16 LED matrix
	-interface to my 4x4 LED cube
	-use build in microphone for FFT-->Music visualisation on the LEDs (start with Vu-meter)
		

//////////////////////////////////////////////////////////////////////////////////
This is a stripped down version of FreeRTOS 6.1.0 that runs on the Renesas
YRDKRX62N demo board.

I have removed Windows specific build artifacts and a heap of uneeded code for
other ports/board to make it easier to grep the code and get relevent results.

It includes makefiles to build under Linux, and an LCD display driver.

The standard FreeRTOS demos are built by default.

Get the original source package at http://www.freertos.org

Zizzle - mattpratt.au@gmail.com
