#include "display.h"
#include "ship.h"

#include <iostream>

int main() {
    cout << "entering main func^_^" << endl;

    space evm(0, 0, 0);
	ship::evm_pt = &evm;
    display(evm);
	
	return 0;
}
