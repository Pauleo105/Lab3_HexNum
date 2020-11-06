#ifndef _LAB3_H_
#define _LAB3_H_
#include <iostream>

namespace Hex {

    class hex {
        private:
            static const int SZ = 31;
            char* letters;
            int sign; // 0 - +, 1 - -
            int type; // 0 - прямой, 1 - дополнительный
            int len;
        public:
            hex(): sign(0), len(1), letters(new char[1]), type(0) {letters[0] = '0'-'0';};//
            hex(const char*);//
            hex(const char*, int);//
            hex(int);//
            ~hex(){delete [] letters;}//destructor
            hex(const hex&);//copying constrictor
            hex(hex && b): sign(b.sign), len(b.len), type(b.type), letters(b.letters) {b.letters = nullptr;}//constructor of displacement

            hex& setCh(const char*);//
            hex& setNu(int);//
            int getNum() const;//
            const char* getStr() const;//
            int getLen() const {return len;}
            hex excode(int n, bool c = false) const;//
            hex add(const hex&) const;//
            hex subtract(const hex&) const;//
            hex& rightshift(int);//
            hex& leftshift(int);//
            int isgreat(const hex&) const;//
            bool parity() const {return ((*this).letters[0]%2 == 0) ? true : false;};//
            void leadzero1();//

            hex& operator =(hex &&);//displacement assigment operator
            hex& operator =(const hex&); //assignment operator
            const hex operator +(const hex& b) {return (*this).add(b);}
            const hex operator -(const hex& b) {return (*this).subtract(b);}
            hex& operator <<=(const int&);
            hex& operator >>=(const int&);


        friend std::ostream& operator <<(std::ostream&, const hex&);
        friend std::istream& operator >>(std::istream&, hex&);
    };
}


int input_m(Hex::hex& a);
int output_m(Hex::hex& a);
int add_m(Hex::hex& a);
int subtract_m(Hex::hex& a);
int rightshift_m(Hex::hex& a);
int leftshift_m(Hex::hex& a);
int checkparity_m(Hex::hex& a);
int compare_m(Hex::hex& a);

int charcheck(char);
const char* leadzero(const char* &, int&);
int choise(const char* menu[]);

template <class T>
    int getNum(T &a) {
        std::cin >> a;
        if (!std::cin.good()) return -1;
        return 1;
    }

#endif