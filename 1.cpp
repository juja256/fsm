#include <iostream>
#include <cstring>
#include "fsm.h"

int main() {
std::string s = "??2.pfx";
fsmFileMask a(s);
std::cout << a.recognize("112.pfx");
return 0;
}
