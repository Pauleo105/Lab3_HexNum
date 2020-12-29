#include "lab3.h"
#include <iostream>
#include <string.h>
#include <math.h>

namespace Hex {
    hex::hex(const char* mas) {
        const char* mas1;
        len = strlen(mas);
        sign = 0,
        mas1 = leadzero(mas, len);;
        if (mas[0] == '-') {
            len--;
            mas1 = mas + 1;
            sign++;
        }
        mas1 = leadzero(mas1, len);
        letters = new char[len+1];
        for (int i = len - 1; i >= 0; i--) {
            if (charcheck(mas1[i])) throw std::runtime_error("Invalid input!");
            letters[len-1 - i] = (mas1[i] - 'a' + 10 < 0) ? (mas1[i]-'0') : (mas1[i] - 'a' + 10);
        }
    }

    hex::hex(int num) {
        len = 7, sign = (num > 0) ? 0:1;
        int num1 = abs(num);
        char nmas[7];
        for (int j= 0; j < 7; j++) {
            nmas[6-j] = '0' + char(num%16);
            num /= 16;
        }
        const char* mas = nmas;
        mas = leadzero(mas, len);
        letters = new char[len+1];
        for (int k = 0; k < len; k++) letters[k] = mas[len - k - 1] - '0';
    }

    hex::hex(const hex& a): sign(a.sign), len(a.len){
        letters = new char[len+1];                   
        for (int i = 0; i < len; i++) letters[i] = a.letters[i];
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

    hex hex::excode() const{
        hex res = (*this);
        if (!(*this).sign) {
            return res;
        }
        else {
            int check = 1;
            for (int i = 0; i < (*this).len; i++) {
                if (check && int((*this).letters[i]) == 0) res.letters[i] = '0'-'0';
                else if (check && int((*this).letters[i]) != 0) res.letters[i] = char(16)-(*this).letters[i], check--; // Difference in 16 symbols
                else res.letters[i] = char(15)-(*this).letters[i]; // Difference in 15 symbols
            }
        }
        return res;
    }

    hex& hex::expanse(int n) {
        if (n > 31 || n <= 0 || ((*this).len > n)) throw std::runtime_error("Invalid amount of digits!");
        hex b = *this;
        delete [] b.letters;
        b.letters = new char[n+1];
        b.len = n+1;
        for (int i = len; i < n; i++) b.letters[i] = char(0);
        for (int i = 0; i < len; i++) b.letters[i] = this->letters[i];
        *this = b;
        return (*this);
    }

    int hex::isgreat(const hex& c) const {
        hex a = *this, b = c;            
        if (a.sign < b.sign) return 1;
        else if (a.sign > b.sign) return -1;
        else {
            int temp;
            temp = a.sign, a.sign = 0, b.sign = 0;
            a.len >= b.len ? (b.expanse(a.len), a.expanse(a.len)):(a.expanse(b.len), b.expanse(b.len));
            for (int i = a.len; i != 0; i--) {
                if ((int(a.letters[i]) > int(b.letters[i])) && !temp) return 1;
                else if ((int(a.letters[i]) < int(b.letters[i])) && !temp) return -1;
                else if ((int(a.letters[i]) > int(b.letters[i])) && temp) return -1;
                else if ((int(a.letters[i]) < int(b.letters[i])) && temp) return 1;
            }
            return 0;
        }
    }

    hex& hex::leadzero1() {
        int i = this->len - 1;
        while (i >= 0) {
            if (this->letters[i] == '0'-'0') i--;
            else break;
        }
        char* temp = new char[i+2];
        for (int j = 0; j <= i; j++) temp[j] = letters[j];
        delete [] letters;
        letters = temp;
        this->len = i+1;
        return *this;
    }

    hex& hex::operator =(hex && b) {
        int len1 = len;
        len = b.len;
        b.len = len1;
        int sign1 = sign;
        sign = b.sign;
        b.sign = sign1;
        char* letters1 = letters;
        letters = b.letters;
        b.letters = letters1;
        return *this;
    }

    hex& hex::operator =(const hex& b) {
        if (this != &b) {
            delete [] letters;
            letters = nullptr;
            this->len = b.len;
            this->sign = b.sign;
            if(len) {
                letters = new char[len];
                for (int i = 0; i < len; i++) letters[i] = b.letters[i];
            }
        }
        return *this;
    };
    
    std::ostream& operator <<(std::ostream& c, const hex& a) { //output operator overloading
        if (a.sign) c<<'-';
        for (int i = a.len - 1; i>= 0; i--) {
            char p = (int(a.letters[i]) >= 0 && int(a.letters[i]) <= 9) ? (a.letters[i] + '0'):(a.letters[i]-10+'a');
            c << p;
        }
        return c;
    }

    std::istream& operator >>(std::istream& c, hex& a) { //input operator overloading
        char* ptr;
        c >> ptr;
        a.setCh(ptr);
        return c;
    }

    const hex operator +(const hex& a, const hex& b) {
        int len = a.len >= b.len ? (a.len):(b.len);
        char temp = '0'-'0';
        hex a1, b1, c1;
        a1 = b, b1 = a;
        a1.expanse(len), b1.expanse(len);
        a1 = a1.excode(),b1 = b1.excode();
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
        c1.len = len, c1.sign = int(c1.letters[len])&1;
        if ((a1.sign && b1.sign && int(c1.letters[len]) == 2) || (!a1.sign && !b1.sign && int(c1.letters[len]) == 1)) throw std::runtime_error("Overflow!");
        c1 = c1.excode();
        c1.leadzero1();
        return c1;
    }

    const hex operator -(const hex& a, const hex& b) {
        hex b1 = b;
        b1.sign = 1 - b1.sign;
        return a + b1;
    }

    hex& hex::operator <<=(const int& n) {
        for (int i = (*this).len - 1; i >= 0; i--) (*this).letters[i+n] = (*this).letters[i];
        for (int i = 0; i < n; i++) (*this).letters[i] = '0'-'0';
        return *this;
    }

    hex& hex::operator >>=(const int& n) {
        for (int i = 0; i < (*this).len - n; i++) (*this).letters[i] = (*this).letters[i+n];
        for (int i = (*this).len - n; i < (*this).len; i++) (*this).letters[i] = '0'-'0';
        (*this).leadzero1();
        return *this;
    }
}

int charcheck(char a) { //checking the correctness of input
        int a1 = int(a - '0');
        int b1 = int(a - 'a' + 10); //добавить проверку верхнего и нижнего регистра
        return ((a1 >= 0 && a1 <= 9) || (b1 >= 10 && b1 <= 15)) ? 0 : 1;
    }

const char* leadzero(const char*& str, int& len) { //deleting leading zeros in string
    const char* str1 = str;
    int len1 = len;
    for (int i = 0; i < len - 1; i++) {
        if (str[i] == '0' || str[i] == '\n') {
            len1--;
            str1 = str + i + 1;
        }
        else break;
    }
    len = len1;
    return str1;
}

    int input_m(Hex::hex& a) {
        char* str;
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
        char* str;
        Hex::hex b;
        std::cout << "Enter the hex you want to add to " << a << std::endl;
        std::cout << "---> ";
        std::cin >> str;
        try {
            b.setCh(str);
            std::cout << "Result: " << (a+b) << std::endl;
        } catch (std::runtime_error err) {
            std::cout << err.what() << "\nPlease, try again!" << std::endl;
        }
        return 1;
    }

    int subtract_m(Hex::hex& a) {
        char* str;
        Hex::hex b;
        std::cout << "Enter the hex you want to subtract from " << a << std::endl;
        std::cout << "---> ";
        std::cin >> str;
        try {
            b.setCh(str);
            std::cout << "Result: " << (a-b) << std::endl;
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
            std::cout << (a >>= n);
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
            std::cout << (a <<= n);
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