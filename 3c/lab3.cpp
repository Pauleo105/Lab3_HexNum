#include "lab3.h"
#include <iostream>
#include <string.h>
#include <math.h>

namespace Hex {
    hex::hex(const char* mas) {
        const char* mas1;
        len = strlen(mas);
        sign = 0, mas1 = mas, type = 0;
        if (mas[0] == '-') {
            len--;
            mas1 = mas + 1;
            sign++;
        }
        if (len > 31) throw std::runtime_error("Overflow!");
        mas1 = leadzero(mas1, len);
        for (int i = len - 1; i >= 0; i--) {
            if (charcheck(mas1[i])) throw std::runtime_error("Invalid input!");
            letters[len-1 - i] = (mas1[i] - 'a' + 10 < 0) ? (mas1[i]-'0') : (mas1[i] - 'a' + 10);
        }
    }

    hex::hex(const char* mas, int dig) {
        if (dig <= 0 || dig > 31) throw std::runtime_error("The amount of digits is [1,31]");
        const char* mas1;
        len = strlen(mas), type = 0;
        sign = 0, mas1 = mas;
        if (mas[0] == '-') {
            len--;
            mas1 = mas + 1;
            sign++;
        }
        if (len > 31) throw std::runtime_error("Overflow!");
        mas1 = leadzero(mas1, len);
        if (dig < len) throw std::runtime_error("Overflow!");
        for (int i = len - 1; i >= 0; i--) {
            if (charcheck(mas1[i])) throw std::runtime_error("Invalid input!");
            letters[len-1 - i] = (mas1[i] - 'a' + 10 < 0) ? (mas1[i]-'0') : (mas1[i] - 'a' + 10);
        }
        for (int j = len; j < dig; j++) {
            letters[j] = '0'-'0';
        }
        len = dig;
    }

    hex::hex(int num) {
        type = 0, len = 0, sign = (num > 0) ? 0:1;
        num = abs(num);
        do {
            letters[len] = char(num%16);
            num /= 16;
            len++;
        } while (num != 0 && len <= 31);
        if (len == 31 && num/16 > 0) throw std::runtime_error("Overflow!");
    }

    hex& hex::setCh(const char* a) {
        hex b(a);
        (*this) = b;
        return *this;
    }

    hex& hex::setNu(int n) {
        hex a(n);
        (*this) = a;
        return *this;
    }

    int hex::getNum() const{
        int res = 0;
        for (int i = 0; i < (*this).len; i++) res += pow(16,i)*int(letters[i]);
        return (*this).sign ? res*(-1):res;
    }

    const char* hex::getStr() const {
        char c[32];
        int k = 0;
        if ((*this).sign) c[k] = '-', k++;
        for (int i = (*this).len - 1; i>= 0; i--) {
            char p = (int((*this).letters[i]) >= 0 && int((*this).letters[i]) <= 9) ? ((*this).letters[i] + '0'):((*this).letters[i]-10+'a');
            c[k] = p, k++;
        }
        char* temp = new char[k];
        for (int j = 0; j < k; j++) temp[j] = c[j];
        return temp;
    }   

    hex hex::excode(int n, bool c) const{
        hex res = (*this);
        if (n > 31 || n <= 0 || ((*this).len > n && !c)) throw std::runtime_error("Invalid amount of digits!");
        if (!(*this).sign) {
            if ((*this).len <= n) {
                for (int j = (*this).len; j < n; j++) res.letters[j] = '0'-'0';
            }
        }
        else {
            int check = 1;
            for (int i = 0; i < (*this).len; i++) {
                if (check && int((*this).letters[i]) == 0) res.letters[i] = '0'-'0';
                else if (check && int((*this).letters[i]) != 0) res.letters[i] = char(16)-(*this).letters[i], check--; // Difference in 16 symbols
                else res.letters[i] = char(15)-(*this).letters[i]; // Difference in 15 symbols
            }
            if ((*this).len < n) {
                for (int j = (*this).len; j < n; j++) !(*this).type ? (res.letters[j] = char(15)):(res.letters[j] = '0'-'0');
            }
        }
        res.type = 1 - res.type;
        res.len = n;
        return res;
    }

    hex hex::add(const hex& a) const {
        int len = (*this).len >= a.len ? (this->len):(a.len);
        char temp = '0'-'0';
        hex a1 = a.excode(len), b1 = (*this).excode(len), c1;
        a1.letters[len] = char(a1.sign);
        b1.letters[len] = char(b1.sign);
        for (int i = 0; i <= len; i++) {
            if (a1.letters[i] + b1.letters[i] + temp >= char(16)) {
                c1.letters[i] = a1.letters[i] + b1.letters[i] + temp - char(16);
                temp='1'-'0';
            }
            else {
                c1.letters[i] = a1.letters[i] + b1.letters[i] + temp;
                temp='0'-'0';
            }
        }
        c1.len = len, c1.sign = int(c1.letters[len])%2;
        if ((a1.sign && b1.sign && int(c1.letters[len]) == 2) || (!a1.sign && !b1.sign && int(c1.letters[len]) == 1)) throw std::runtime_error("Overflow!");
        c1 = c1.excode(c1.len);
        c1.leadzero1();
        return c1;
    }

    hex hex::subtract(const hex& a) const{
        hex a1 = a;
        a1.sign = 1 - a1.sign;
        return this->add(a1);
    }

    hex& hex::rightshift(int n){
        for (int i = 0; i < (*this).len - n; i++) (*this).letters[i] = (*this).letters[i+n];
        for (int i = (*this).len - n; i < (*this).len; i++) (*this).letters[i] = '0'-'0';
        return (*this);
    }

    hex& hex::leftshift(int n){
        for (int i = (*this).len - 1; i >= 0; i--) (*this).letters[i+n] = (*this).letters[i];
        for (int i = 0; i < n; i++) (*this).letters[i] = '0'-'0';
        return (*this);
    }

    int hex::isgreat(const hex& c) const {
        hex a = *this, b = c;            
        if (a.sign < b.sign) return 1;
        else if (a.sign > b.sign) return -1;
        else {
            int temp;
            temp = a.sign, a.sign = 0, b.sign = 0;
            a.len >= b.len ? (b.excode(a.len)):(a.excode(b.len));
            for (int i = 0; i < a.len; i++) {
                if ((int(a.letters[i]) > int(b.letters[i])) && !temp) return 1;
                else if ((int(a.letters[i]) < int(b.letters[i])) && !temp) return -1;
                else if ((int(a.letters[i]) > int(b.letters[i])) && temp) return -1;
                else if ((int(a.letters[i]) < int(b.letters[i])) && temp) return 1;
            }
            return 0;
        }
    }

    void hex::leadzero1() {
        int i = this->len - 1;
        while (i >= 0) {
            if (this->letters[i] == '0'-'0') i--;
            else break;
        }
        this->len = i+1;
    }
    
    std::ostream& operator <<(std::ostream& c, const hex& a) { //output operator overloading
        if (a.sign) c<<'-';
        for (int i = a.len - 1; i>= 0; i--) {
            char p = (int(a.letters[i]) >= 0 && int(a.letters[i]) <= 9) ? (a.letters[i] + '0'):(a.letters[i]-10+'a');
            c << p;
        }
        return c;
    }

    std::istream& operator >>(std::istream& c, hex& a) { //input operator overloading
        const char* pr = "";
        char* ptr;
        do {
            std::cout << pr;
            pr = "Maximum 31 digits!!!\n";
            c >> ptr;
        } while (strlen(ptr) > 31);
        a.setCh(ptr);
        return c;
    }

    hex& hex::operator <<=(const int& n) {
        (*this).leftshift(n);
        return *this;
    }

    hex& hex::operator >>=(const int& n) {
        (*this).rightshift(n);
        return *this;
    }
}

int charcheck(char a) { //checking the correctness of input
        int a1 = int(a - '0');
        int b1 = int(a - 'a' + 10);
        return ((a1 >= 0 && a1 <= 9) || (b1 >= 10 && b1 <= 15)) ? 0 : 1;
    }

const char* leadzero(const char*& str, int& len) { //deleting leading zeros in string
    const char* str1 = str;
    int len1 = len;
    for (int i = 0; i < len - 1; i++) {
        if (str[i] == '0') {
            len1--;
            str1 = str + i + 1;
        }
        else break;
    }
    len = len1;
    return str1;
}

int choise(const char* menu1[]) {
    int check;
    const char* pr = "";
    do{
        std::cout << pr << std::endl;
        pr = "You made a mistake! Try again!";
        for (int i = 0; i < 9; i++) std::cout << menu1[i] << '\n';
        std::cout << "Make your choise: ";
        if (getNum(check) < 0) continue;
    } while(check < 0 || check > 8);
    return check;
}

    int input_m(Hex::hex& a) {
        char str[31];
        std::cout << "Enter hex: ";
        std::cin >> str;
        try {
            a.setCh(str);
        } catch (std::runtime_error err) {
            std::cout << err.what() << "\nPlease, try again!" << std::endl;
        }
        return 1;
    }

    int output_m(Hex::hex& a) {
        std::cout << "Your hex is " << a << std::endl;
        return 1;
    }

    int add_m(Hex::hex& a) {
        char str[31];
        Hex::hex b;
        std::cout << "Enter the hex you want to add to " << a << std::endl;
        std::cout << "---> ";
        std::cin >> str;
        try {
            b.setCh(str);
            Hex::hex c = a.add(b);
            std::cout << "Result: " << c << std::endl;
        } catch (std::runtime_error err) {
            std::cout << err.what() << "\nPlease, try again!" << std::endl;
        }
        return 1;
    }

    int subtract_m(Hex::hex& a) {
        char str[31];
        Hex::hex b;
        std::cout << "Enter the hex you want to subtract from " << a << std::endl;
        std::cout << "---> ";
        std::cin >> str;
        try {
            b.setCh(str);
            Hex::hex c = a.subtract(b);
            std::cout << "Result: " << c << std::endl;
        } catch (std::runtime_error err) {
            std::cout << err.what() << "\nPlease, try again!" << std::endl;
        }
        return 1;
    }

    int rightshift_m(Hex::hex& a) {
        int n;
        std::cout << "Enter how big will be right shift: ";
        try {
            if (getNum(n) < 0) throw std::runtime_error("Invalid input!");
            std::cout << a.rightshift(n);
        } catch (std::runtime_error err) {
            std::cout << err.what() << "\nPlease, try again!" << std::endl;
        }
        return 1;
    }

    int leftshift_m(Hex::hex& a) {
        int n;
        std::cout << "Enter how big will be left shift: ";
        try {
            if (getNum(n) < 0) throw std::runtime_error("Invalid input!");
            std::cout << a.leftshift(n);
        } catch (std::runtime_error err) {
            std::cout << err.what() << "\nPlease, try again!" << std::endl;
        }
        return 1;
    }

    int checkparity_m(Hex::hex& a) {
        std::cout << "The number is " << ((a.parity()) ? ("even") : ("odd")) << std::endl;
        return 1;
    }

    int compare_m(Hex::hex& a) {
        char str[31];
        std::cout << "Enter the hex to compare with " << a <<std::endl;
        std::cout << "---> ";
        std::cin >> str;
        try {
            Hex::hex b(str);
            int temp = a.isgreat(b);
            if (temp == 1) std::cout << a << " is bigger than " << b<<std::endl;
            else if (temp == -1) std::cout << b << " is bigger than " << a<<std::endl;
            else std::cout << a << " and " << b << "are equal"<<std::endl;
        } catch (std::runtime_error err) {
            std::cout << err.what() << "\nPlease, try again!" << std::endl;
        }
        return 1;
    }