#include <iostream>
#include "lab3.h"

const char* menu1[] = {"0. Quit", "1. Input", "2. Output", "3. Add", "4. Compare", "5. Right shift", "6. Left shift"};
int (*fptr[])(prog3::hex&) = {NULL, prog3::input_m, prog3::output_m, prog3::add_m, prog3::compare_m, prog3::right_m, prog3::left_m};

int main() {
    prog3::hex num;
    int ch;
    while (ch = prog3::choise(menu1)) {
        if (!fptr[ch](num)) break;
    }
    return 0;
}

//g++ test3a/googletests.cpp lab3.cpp -o gtests -I$/usr/src/gtest/include -L$/usr/lib -lgtest -lpthread
//./gtests