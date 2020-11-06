#include <iostream>
#include <string.h>
#include "lab3.h"
#include <cmath>

namespace prog3 {
    int compare_m(hex& menu) {
        char *cin1 = new char;
        hex b;
        std::cout << "Please enter number: ";
        std::cin >> cin1;
        if (std::cin.good()) {
            b.setNum(cin1);
        }
        else throw std::runtime_error("Invalid input!");

        if (menu.check(b) > 0) {
            std::cout << menu.getNumHex() << " is bigger than " << b.getNumHex() << std::endl;
        }
        else if (menu.check(b) < 0) {
            std::cout << b.getNumHex() << " is bigger than " << menu.getNumHex() << std::endl;
        }
        else std::cout << "They're equal" << std::endl;
        delete cin1;
        return 1;
    }
    int add_m(hex& menu) {
        char *cin1 = new char;
        hex b;
        std::cout << "Please enter number: ";
        std::cin >> cin1;
        if (std::cin.good()) {
            b.setNum(cin1);
        }
        else throw std::runtime_error("Invalid input!");
        prog3::hex rt = menu.add(b);
        std::cout << "Hex answer: " << rt.getNumHex() << std::endl;
        int len = strlen(rt.getNumHex());
        if (rt.getNumHex()[0] == '-') len--;
        std::cout << "Direct binary: ";
        int* dir = rt.getNumBin();
        for (int i = 0; i < 4*len +1; i++) {
            std::cout << dir[i];
        }
        std::cout << std::endl;
        delete cin1;
        return 1;
    }
    int output_m(hex& menu) {
        const char* hex = menu.getNumHex();
        int len = strlen(hex);
        if (hex[0] == '-') len--;
        std::cout << "Hex: " << hex << std::endl << "Direct binary: ";
        int* dir = menu.getNumBin();
        for (int i = 0; i < 4*len +1; i++) {
            std::cout << dir[i];
        }
        std::cout << std::endl;
        return 1;
    }
    int input_m(hex& menu) {
        char* pin = new char;
        std::cout << "Please enter hex: ";
        std::cin >> pin;
        if (strlen(pin) > 31) throw std::runtime_error("Memory overflow!");
        if (std::cin.good()) {
            menu.setNum(pin);
            return 1;
        }
        else throw std::runtime_error("Invalid input!");
    }

    int right_m(hex& menu) {
        menu.rightshift(1);
        output_m(menu);
        return 1;
    }

    int left_m (hex& menu) {
        menu.leftshift(1);
        output_m(menu);
        return 1;
    }

    int choise(const char* menu1[]) {
        int check;
        const char* pr = "";
        do{
            std::cout << pr << std::endl;
            pr = "You made a mistake! Try again!";
            for (int i = 0; i < 7; i++) std::cout << menu1[i] << '\n';
            std::cout << "Make your choise: ";
            if (getNum(check) < 0) throw std::runtime_error("Invalid input!");
        } while(check < 0 || check > 6);
        return check;
    }

    int giveindex(const char a) {
        hex b;
        for (int i = 0; i < 16; i++) {
            if (a == b.numbers[i]) return i;
        }
        throw std::runtime_error("Wrong input!"); 
    }

    const char givevalue(int a) {
        hex b;
        return b.numbers[a];
    } 

    int* dirtoadd(int* a, int& len, int* mass) {
        hex b;
        //int mass[b.amount*4+1];
        if (a[0] == 0) {
            for (int i = 0; i < 4*len + 1; i++) {
                mass[i] = a[i];
            }
            return mass;
        }
        mass[0] = 1;
        for (int i = 1; i < 4*len + 1; i++) {
            mass[i] = 1- a[i];
        }
        int i = 4*len + 1;                                   // direct into reverse
        while (i > 0) {
            if (mass[i] + 1 == 2) {
                mass[i] = 0;
                i--;
            }
            else {
                mass[i] = 1;
                return mass;
            }
        }
        if (len < b.amount) {
            for (int k = 0; k < 4*len + 1; k++) {
                mass[4*len+4 - k] = mass[4*len - k];
            }
            for (int z = 1; z < 4; z++) {
                mass[z] = 0;
            }
            mass[4] = 1;
            len += 1;
            return mass;
        }
        else throw std::runtime_error("Overflow!");
    }

    int* addtodir(int* a, int len, int* mass) {
        hex b;
        int i = 4*len + 1;
        for (int j = 0; j < i; j++) {
            mass[j] = a[j];
        }
        if (a[0] == 0) return mass;
        while (i > 0) {
            if (mass[i] - 1 == 0) break;
            else {
                mass[i] = 1;
                i--;
            }
        }
        if (i == 0) throw std::runtime_error("Overflow in addcode!");
        for (int j = 1; j<4*len + 1; j++) {
            mass[j] = 1 - mass[j];
        }
        return mass;
    }

    int translate(int a) {                  // 1hex into 4bin
        int res = 0, a1 = a;
        for (int i = 3; i >= 0; i--) {
            res = res + pow(10,(3-i))*(a1%2);
            a1 = a1/2;
        }
        return res;
    }

    int revtranslate(int a) {               // 4bin into 1hex
        int sum = 0, a1 = a;
        for (int i =0; i < 4; i++) {
            sum += (a1%10)*pow(2,i);
            a1 /= 10;
        }
        return sum;
    }

    int* chartodir(const char* num, int& lenn, int* mass) {
        hex a;
        int len = strlen(num), len1 = len, i = 0, j =1, b=1, letter;
        if (num[0] == '-') mass[0] = 1, i = 1, len1--;
        else mass[0] = 0;  
        if (len1 < 0 || len1 > 31) throw std::runtime_error("Invalid amount of numbers!");
        for (i; i < len; i++) {
            letter = translate(giveindex(num[i]));
            for (j = 0; j < 4; j++) {
                mass[b*4- j] = letter%10;
                letter /= 10;
            }
            b++;
        }
        lenn = len1;
        return mass;
    }

    void dirtochar(const int* mas, int len, char*& ptr) {
        int b = 0;
        if (mas[0] == 1)  {
            b = 1;
            ptr[0] = '-';
        }
        for (int i = 0; i < len; i++) {
            int summ = 0;
            for (int j = (4*i + 1); j < 4*i + 5; j++) {
                summ += mas[j]*pow(10,(4*i + 4 - j));  
            }
            ptr[b] = givevalue(revtranslate(summ));
            b++;
        }
    }

    hex::hex() {
        for (int i = 0; i < 5; i++) {
            number[i] = 0;
        }
        len = 1;
    }

    hex::hex (const char* chi) {
        int mas[amount*4+1], b =0;
        len = strlen(chi);
        if (chi[0] == '-') {
            len--;
            b = 1;
        }
        chartodir(chi, len, mas);
        for (int i = 0; i < len*4+1; i++) {
            number[i] = mas[i];
        }
    }

    hex& hex::setNum(const char* a) {
        int mas[amount*4+1];
        chartodir(a, len, mas);
        for (int i = 0; i < len*4+1; i++) {
            number[i] = mas[i];
        }
        return *this;
    }

    char* hex::getNumHex() const{
        char* ptr = new char;
        dirtochar(number, len, ptr);
        return ptr;
    }

    int* hex::getNumBin() const {
        int* mass = new int[len*4+1];
        for (int i = 0; i < len*4+1; i++) {
            mass[i] = (*this).number[i];
        }
        return mass;
    }

    hex hex::add(hex& b){
        int one[4*b.amount+1], two[4*b.amount+1], res[4*b.amount+1], maxx;
        hex resu;
        if ((*this).len > b.len) {
            int diff = (*this).len - b.len;
            b.len = (*this).len;
            b.rightshift(diff);
        }
        else if ((*this).len < b.len) {
            int diff = b.len - (*this).len;
            (*this).len = b.len;
            (*this).rightshift(diff);
        }
        dirtoadd((*this).number, (*this).len, one);
        dirtoadd(b.number, b.len, two);
        maxx = b.len;
        int temp = 0;
        if (one[0] == 0 && two[0] == 0) {
            for (int i = 4*maxx; i >= 0; i--) {
                res[i] = 0;
                res[i] = one[i] + two[i] + temp;
                temp = 0;
                if (res[i] == 2) {
                    res[i] = 0;
                    temp = 1;
                }
                else if (res[i] == 3) {
                    res[i] = 1;
                    temp = 1;
                }
            }
            if (res[0] == 0) {
                resu.len = maxx;
                for (int i = 0; i < 4*resu.len+1; i++) resu.number[i] = res[i];
            }
            else if (res[0] == 1) throw std::runtime_error("Overflow!");
        }
        else if (one[0] == 1 && two[0] == 1) {
            for (int i = maxx*4; i >= 0; i--) {
                res[i] = one[i] + two[i] + temp;
                temp = 0;
                if (res[i] == 2) {
                    res[i] = 0;
                    temp = 1;
                }
                else if (res[i] == 3) {
                    res[i] = 1;
                    temp = 1;
                }
            }
            if (res[0] == 1) {
                addtodir(res, maxx, resu.number);
                resu.len = maxx;
                for (int i = 0; i < resu.len; i++) resu.number[i] = res[i];
            }
            else if (res[0] == 0) throw std::runtime_error("Overflow!");
        }
        else {
            for (int i = 4*maxx; i >= 0; i--) {
                res[i] = one[i] + two[i] + temp;
                temp = 0;
                if (res[i] == 2) {
                    res[i] = 0;
                    temp = 1;
                }
                else if (res[i] == 3) {
                    res[i] = 1;
                    temp = 1;
                }
            }
            res[maxx-1] += temp;
            int res1[4*b.amount+1];
            addtodir(res, maxx, res1);
            resu.len = maxx;
            for (int i = 0; i < 4*resu.len+1; i++) resu.number[i] = res1[i];
        }
        return resu;
    }

    int hex::check(hex& b){
        int maxx;
        if ((*this).len > b.len) {
            int diff = (*this).len - b.len;
            b.len = (*this).len;
            b.rightshift(diff);
        }
        else if ((*this).len < b.len) {
            int diff = b.len - (*this).len;
            (*this).len = b.len;
            (*this).rightshift(diff);
        }
        maxx = b.len;
        if ((*this).number[0] < b.number[0]) return 1;
        else if ((*this).number[0] > b.number[0]) return -1;
        for (int i = 1; i < 4*maxx+1; i++) {
            if ((*this).number[i] > b.number[i]) return 1;
            else if ((*this).number[i] < b.number[i]) return -1;
            else continue;
        }
        return 0;
    }

    hex& hex::rightshift(int shift) {
        for (int i = 0; i < 4*(*this).len; i++) {
            if (4*(*this).len - 4*shift - i > 0) (*this).number[4*(*this).len-i] = (*this).number[4*(*this).len - 4*shift - i];
            else  (*this).number[4*(*this).len-i] = 0;
        }
        return *this;
    }

    hex& hex::leftshift(int shift) {
        for (int i = 1; i <= 4*(*this).len; i++) {
            if ((4*shift + i) > 4*(*this).len) (*this).number[i] = 0;
            else (*this).number[i] = (*this).number[(4*shift + i)];
        }
        return *this;
    }
}