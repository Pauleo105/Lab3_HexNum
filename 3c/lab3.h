#ifndef _LAB3_H_
#define _LAB3_H_
#include <iostream>

namespace Hex {

    class hex {
        private:
            char* letters;
            int sign; // 0 - +, 1 - -
            int len;
        public:
            hex(): sign(0), len(1), letters(new char[1]){letters[0] = '0'-'0';};//
            hex(const char*);//
            hex(int);//
            ~hex(){delete [] letters;}//destructor
            hex(const hex&);//copying constrictor
            hex(hex && b): sign(b.sign), len(b.len), letters(b.letters) {b.letters = nullptr;}//constructor of displacement

            hex& setCh(const char*);
            hex& setNu(int);
            int getNum() const;
            const char* getStr() const;
            int getLen() const {return len;}
            hex excode() const; //done
            hex& expanse(int); //done
            int isgreat(const hex&) const;//fixed
            bool parity() const {return (int((*this).letters[0])&1) ? false : true;}; //fixed
            hex& leadzero1(); //fixed
            hex& operator <<=(const int&);//fixed
            hex& operator >>=(const int&);//fixed
            hex& operator =(hex &&);//displacement assigment operator
            hex& operator =(const hex&); //assignment operator

        friend const hex operator +(const hex&, const hex&); //displaced from public
        friend const hex operator -(const hex&, const hex&); //displaced from public
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