/*
 * hello.cc
 *
 *  Created on: Nov 14, 2011
 *      Author: lauril
 */



#include <iostream>

extern "C" void hello() {
    std::cout << "hello" << '\n';
}
