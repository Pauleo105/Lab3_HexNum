#include "../3c/lab3.h"
#include <iostream>

const int N = 10;

void output(Hex::hex* m) {
    for (int i = 0; i < N; i++) {
        std::cout << m[i] << std::endl;
    } 
}

void minmax(Hex::hex* m, Hex::hex& min, Hex::hex& max) {
    Hex::hex mi, ma;
    bool check = false;
    for (int i = 0; i < N; i++) {
        if (m[i].parity()) {
            mi = m[i], ma = m[i];
            check = true;
            break;
        }
    }
    if (!check) {
        std::cout << "There are no even numbers" << std::endl;
        return;
    }
    for (int i = 0; i < N; i++) {
        if (m[i].parity()) {
            if ((mi).isgreat(m[i]) > 0)  mi = m[i];
            if ((ma).isgreat(m[i]) < 0) ma = m[i];
        }
        else continue;
    }
    min = mi, max = ma;
}

void outminmax (Hex::hex& min, Hex::hex& max) {
    std::cout << "Minimal even: " << min << std::endl << "Maximum even: " << max << std::endl;
    Hex::hex sum = min + max;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Right shift: " << (sum >>= 1) << std::endl;
    sum = min + max;
    std::cout << "Left shift: " << (sum <<= 1) << std::endl;
}

int main () {
    try {
        Hex::hex mas[N] = {"abc", "2134aa", "459ff", "-123456", "eeea", "baaaae", "1234", "ddaea", "1233218", "ffff0"}, min, max;
        output(mas);
        minmax(mas, min, max);
        outminmax(min, max);
        return 0;
    }
    catch (std::exception& e) {
        std::cout << "Error! " << e.what() << std::endl;
        return 1;
    }
}