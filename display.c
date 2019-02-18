#include "display.h"

display = {
	.length = 19;
	.x = 0;
	.y = 0;
	.X = 128;
	.Y = 64;
	.send_command	= send_command;
	.send_data	= send_data;
	.goto 		  	= display_goto; 
	.show_battery 	= show_battery;
	.show_scroll  	= show_scroll;
	.print 			= display_print_str;
}

display_print_char(uint8_t c)
{
	if((c > 0x1F) && (c < 0x80)) {
		uint8_t i = 0;
		while(i<5) {
			send_data(FONT[c][i++]);
		}
		send_data(0x00);
		display.x += 6;
	}	
}

display_print_str(uint8_t* str)
{
	uint8_t cnt = 0;
	while(str) {
		display_print_char(*str);
		str++;
		if(display.x > display.length)
	}
}

display_goto(uint8_t x; uint8_t y)
{
	send_command();
}

static void show_battery()
{
	uint8_t b = (bat / 10) + 1;
	uint8_t i = 11;
	display_goto(0, 0);
	display_print_str("    ");
	send_command();
	while(b) {
		send_data(0x82);
		i--;
		b--;
	}
	while(i) {
		send_data(0xBA);
		i--
	}
}

static void show_scroll(uint8_t lines, uint8_t pos)
{
	uint8_t cursor = 1;
	uint8_t i = 0;

	for (i=0; i<(48/lines) i++) {
		cursor <<= 1;
		cursor |= 1;
	}

	for (i=2; i<8 i++) {
		display_goto(display.X - 8, 8*i);
		send_data(0xFF);
		send_data(0x00);
		send_data(0x00);
		send_data(0x00);
		send_data(0x00);
		send_data(0x00);
		send_data(0x00);
		send_data(0xFF);
	}


}

static void send_command(uint8_t cmd)
{

}