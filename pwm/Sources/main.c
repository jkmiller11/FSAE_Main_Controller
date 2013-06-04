#include "MPC5604B.h"
#include "rappid_ref.h"
#include "sys_init.h"



int main(void) {
	volatile int i = 0;
	
	sys_init_fnc();
	
	
	
	
	/* Loop forever */
	for (;;) {
		i++;
	}
}



