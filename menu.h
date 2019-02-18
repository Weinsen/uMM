#ifndef MENU_INC
#define MENU_INC

#include <stdint.h>
#include <stdlib.h>

#define make_item(a, b, c) { .name = a, .ptr = b, .type = c}
#define make_menu_items(NAME) menu_item items ## _ ## NAME[] 
#define make_menu(NAME, VAR) menu_t menu ## _ ## VAR = { .name = NAME, .length = (sizeof(items ## _ ## VAR) / sizeof(menu_item)), .index = 0, .items = items ## _ ## VAR, .parent = NULL }

#if 0
#define make_menu_integer(VAR, MIN, MAX) item_integer menu_integer ## _ ## VAR = { .var = &VAR, .min = MIN, .max = MAX}
#define menu_item_integer(NAME, VAR) { .name = NAME, .ptr = &menu_integer ## _ ## VAR, .type = menu_opt_integer }
#endif

#define make_menu_short(VAR, MIN, MAX) item_short menu_short ## _ ## VAR = { .var = &VAR, .min = MIN, .max = MAX}
#define menu_item_short(NAME, VAR) { .name = NAME, .ptr = &menu_short ## _ ## VAR, .type = menu_opt_short }

#define make_menu_toggle(VAR) item_short menu_short ## _ ## VAR = { .var = &VAR, .min = 0, .max = 1}
#define menu_item_toggle(NAME, VAR) { .name = NAME, .ptr = &menu_short ## _ ## VAR, .type = menu_opt_toggle }

#define menu_item_submenu(NAME, VAR) { .name = NAME, .ptr = &menu ## _ ## VAR, .type = menu_opt_menu }
#define menu_item_action(NAME, PTR) { .name = NAME, .ptr = PTR, .type = menu_opt_action }
#define menu_item_return(NAME) { .name = NAME, .ptr = NULL, .type = menu_opt_cancel }

static void confirm(void);
static void cancel(void);
static void cursor_move(void);
static void cursor_back(void);
static void increase(void);
static void decrease(void);

typedef enum item_type {

	menu_opt_none = 0,
	menu_opt_toggle,
	// menu_opt_list,
	// menu_opt_integer,
	menu_opt_menu,
	menu_opt_action,
	menu_opt_short,
	menu_opt_cancel,
	menu_opt_SIZE

} item_type;

typedef struct item_integer {

	void* 	var;
	int32_t min;
	int32_t max;

} item_integer;

typedef struct item_short {

	void* 	var;
	uint8_t min;
	uint8_t max;

} item_short;

typedef enum menu_mode {

	menu_mode_off,
	menu_mode_menu,
	menu_mode_config

} menu_mode;

typedef struct menu_item menu_item;
struct menu_item {

	char*		name;
	void*		ptr;
	item_type	type;

};

typedef struct menu_t menu_t;
struct menu_t {

	uint8_t		index;
	uint8_t		length;
	char*		name;
	menu_item*	items;
	menu_t*		parent;
	uint32_t	value;	

};

typedef struct menu_controller_t menu_controller_t;
struct menu_controller_t {

	menu_t* 	menu;
	menu_mode 	mode;
	void (*show)();
	void (*confirm)();
	void (*cancel)();
	void (*cursor_back)();
	void (*cursor_move)();
	void (*increase)();
	void (*decrease)();

};

menu_t menu_config;
menu_controller_t menu;

#endif