#include "menu.h"

static void confirm(void)
{
	if(menu.mode == menu_mode_menu) {

		void (*func_call)();
		switch(menu.menu->items[menu.menu->index].type) {

			case menu_opt_menu:	
				(*(menu_t*)(menu.menu->items[menu.menu->index].ptr)).parent = menu.menu;
				menu.menu = menu.menu->items[menu.menu->index].ptr;
				menu.menu->index = 0;
				menu.show();
				break;

			case menu_opt_action:
				func_call = menu.menu->items[menu.menu->index].ptr;
				if (func_call) {
					func_call();
				}
				break;

			case menu_opt_toggle:
				if(*(uint8_t*)((*(item_integer*)(menu.menu->items[menu.menu->index].ptr)).var))
					*(uint8_t*)((*(item_integer*)(menu.menu->items[menu.menu->index].ptr)).var) = 0;
				else
					*(uint8_t*)((*(item_integer*)(menu.menu->items[menu.menu->index].ptr)).var) = 1;
				menu.show();
				break;

			case menu_opt_short:
				menu.mode = menu_mode_config;
				menu_config.parent = menu.menu;
				menu_config.name = menu.menu->items[menu.menu->index].name;
				menu_config.items = menu.menu->items;
				menu_config.index = menu.menu->index;
				menu_config.value = *(uint8_t*)((*(item_integer*)(menu.menu->items[menu.menu->index].ptr)).var);
				menu.menu = &menu_config;
				menu.show();
				break;

			case menu_opt_cancel:
				menu.menu = menu.menu->parent;
				menu.mode = menu_mode_menu;
				menu.show();
				break;

		}

	} else {

		menu.mode = menu_mode_menu;
		menu.menu->parent->value = menu.menu->value;
		menu.menu = menu.menu->parent;
		*(uint8_t*)((*(item_integer*)(menu.menu->items[menu.menu->index].ptr)).var) = menu.menu->value;
		menu.show();

	}

}

static void cancel(void)
{
}

static void cursor_move(void)
{
	if((menu.mode == menu_mode_menu) && (menu.menu->index < menu.menu->length - 1)) {
		menu.menu->index++;
		menu.show();
	} 
}

static void cursor_back(void)
{
	if((menu.mode == menu_mode_menu) && (menu.menu->index > 0)) {
		menu.menu->index--;
		menu.show();
	} 
}

static void increase(void)
{
	if(menu.mode == menu_mode_config) {
		switch(menu.menu->items[menu.menu->index].type) {
			case menu_opt_short:
				if(((*(item_short*)(menu.menu->items[menu.menu->index].ptr)).min) > menu.menu->value) {
					menu.menu->value = (uint8_t)(*(item_short*)(menu.menu->items[menu.menu->index].ptr)).min;
				} else if ((uint8_t)((*(item_short*)(menu.menu->items[menu.menu->index].ptr)).max) > menu.menu->value) {
					menu.menu->value++;
				} else if ((uint8_t)((*(item_short*)(menu.menu->items[menu.menu->index].ptr)).max) < menu.menu->value) {
					menu.menu->value = (uint8_t)(*(item_short*)(menu.menu->items[menu.menu->index].ptr)).max;
				}
				break;
		}
		menu.show();	
	}
}

static void decrease(void)
{
	if(menu.mode == menu_mode_config) {
		switch(menu.menu->items[menu.menu->index].type) {
			case menu_opt_short:
				if(((*(item_short*)(menu.menu->items[menu.menu->index].ptr)).max) < menu.menu->value) {
					menu.menu->value = (uint8_t)(*(item_short*)(menu.menu->items[menu.menu->index].ptr)).max;
				} else if ((uint8_t)((*(item_short*)(menu.menu->items[menu.menu->index].ptr)).min) < menu.menu->value) {
					menu.menu->value--;
				} else if ((uint8_t)((*(item_short*)(menu.menu->items[menu.menu->index].ptr)).min) > menu.menu->value) {
					menu.menu->value = (uint8_t)(*(item_short*)(menu.menu->items[menu.menu->index].ptr)).min;
				}
				break;
		}
		menu.show();	
	}
}

menu_t menu_config = {
	.name = NULL,
	.items = NULL,
	.parent = NULL,
	.length = 1,
	.index = 0,
	.value = 0
};

menu_controller_t menu = {
	.menu 			= NULL,
	.show			= NULL,
	.mode			= menu_mode_menu,
	.confirm 		= confirm,
	.cancel 		= cancel,
	.cursor_move 	= cursor_move,
	.cursor_back 	= cursor_back,
	.increase 		= increase,
	.decrease 		= decrease
};