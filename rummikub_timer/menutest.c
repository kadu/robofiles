#include <stdio.h>

struct RTmenu {
	int *back;
	char *title;
	char *menu_itens[3];
  int value;
} menu;

int main (int argc, char const *argv[]) {
	menu.back = NULL;
	menu.title = "Welcome";
	menu.menu_itens[0] = "Iniciar";
	menu.menu_itens[1] = "Setup";
	menu.menu_itens[2] = "Volume";
	
	printf("%s", menu.title);
	printf("%s", menu.menu_itens[0]);
	printf("%s", menu.menu_itens[1]);
	printf("%s", menu.menu_itens[2]);
	return 0;
}