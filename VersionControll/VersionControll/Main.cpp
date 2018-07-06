#include <iostream>


int main(int argc, char* argv[]) {
	std::cout << argv[0];
#ifndef UNIX	
	system("pause");
#endif
}
