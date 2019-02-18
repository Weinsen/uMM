#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"

void test_func1(void);
void test_func2(void);

void print_menu_t(void);

uint8_t test_var = 00;
uint8_t toggle1 = 0;
uint8_t toggle2 = 0;

make_menu_short(test_var, 20, 50);
make_menu_toggle(toggle1);
make_menu_toggle(toggle2);

make_menu_items(menu_3) = {
	menu_item_return("Exit")
};
make_menu("Menu 3", menu_3);

make_menu_items(menu_2) = {
	menu_item_action("Acao", test_func1),
	menu_item_short("Test_Var", test_var),
	menu_item_submenu("Menu 3", menu_3),
	menu_item_return("Exit")
};
make_menu("Menu 2", menu_2);

make_menu_items(menu_1) = {
	menu_item_toggle("Toggle 1: ", toggle1),
	menu_item_toggle("Toggle 2: ", toggle2),
	menu_item_submenu("Menu 2", menu_2),
	menu_item_return("Exit")
};
make_menu("Menu 1", menu_1);

int main(int argc, char **argv)
{

	uint8_t c = 0;

	menu.menu = &menu_menu_1;
	menu.menu->parent = &menu_menu_1;
	menu.show = print_menu_t;

	

	while(c != 'e') {

		// system("clear");

		// c = 0;
		// while (!c) {
		// 	c = getchar();
		// }

		c = rand() % 3;
		switch(c) {
			case 0:
				c = '-';
				break;

			case 1:
				c = ' ';
				break;

			case 2:
				c = '+';
				break;
		}		

		switch(c) {
			case '+':
				menu.cursor_move();
				menu.increase();
				break;

			case '-':
				menu.cursor_back();
				menu.decrease();
				break;

			case ' ':
				menu.confirm();
				break;
		}

		sleep(1);

	}
	
	return 0;
}

void print_menu(menu_t *menu_ptr)
{
	uint8_t i = 0;

	system("clear");

	if(menu_ptr->name)
		printf("\n-----------\n%s - %d\n\n", menu_ptr->name, menu_ptr->length);

	if(menu.mode == menu_mode_menu) {
		for(i=0; i<menu_ptr->length; i++) {
			if(i == menu_ptr->index) {
				printf(">");
			} else {
				printf("%d", i);		
			}
			printf(" - %s ", menu_ptr->items[i].name);	
			if(menu_ptr->items[i].type == menu_opt_toggle) {
				printf("%d", *(uint8_t*)((*(item_integer*)(menu_ptr->items[i].ptr)).var));
			}
			printf("\n");
		}	
	} else {
		printf("%d", menu.menu->value);
	}
	fflush(stdout);
}

void print_menu_t(void)
{
	print_menu(menu.menu);	
}

void test_func1(void)
{
	printf("ok 1\n");
}

void test_func2(void)
{
	printf("ok 2\n");
}