#include <time.h>
#include <stdint.h>

static void int_20();
extern void timer_handler();
extern void keyboard_handler();

void irqDispatcher(uint64_t irq) {
	switch (irq) {
		case 0:
			int_20();
			break;
		case 8:
			int_21();
			break;
		
	}
	return;
}



void int_20() {   //TIMER TICK
	timer_handler();
}

void int_21() {  // TECLADO
	keyboard_handler();
	
}



