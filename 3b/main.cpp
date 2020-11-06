#include "lab3.h"

const char* menu[] = {"0. Quit", "1. Input hex", "2. Output", "3. Add", "4. Subtract", "5. Right shift", "6. Left shift", "7. Parity", "8. Compare"};
int (*fptr[])(Hex::hex&) = {nullptr, input_m, output_m, add_m, subtract_m, rightshift_m, leftshift_m, checkparity_m, compare_m};

int main() {
    Hex::hex num;
    int ch;
    while (ch = choise(menu)) {
        if (!fptr[ch](num)) break;
    }
    return 0;
}