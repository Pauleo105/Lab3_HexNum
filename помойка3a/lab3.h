#ifndef _LAB3_H_
#define _LAB3_H_


namespace prog3 {

    int choise(const char* []);

    class hex {
        private:
            static const int amount = 31;
            const char numbers[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
            int number[4*amount+1];
            int len;
        public:
            hex ();

            hex (const char* chi);

            hex& setNum(const char* num);

            int* getNumBin() const; 
            char* getNumHex() const;

            hex add(hex&);
            int check(hex&);
            hex& rightshift(int);
            hex& leftshift(int);

        friend int giveindex(const char a);
        friend const char givevalue(int a); 
        friend int* chartodir(const char* num, int& lenn, int* mas);
        friend void dirtochar(const int* mas, int len, char* ptr);
        friend int* dirtoadd(int* a, int& len, int* mass);
        friend int* addtodir(int* a, int len, int* mass);
    };

    int translate(int);
    int revtranslate(int );

    int input_m(hex&);
    int output_m(hex&);
    int add_m(hex&); 
    int compare_m(hex&);
    int right_m(hex&);
    int left_m(hex&);

    template <class T>
    int getNum(T &a) {
        std::cin >> a;
        if (!std::cin.good()) return -1;
        return 1;
    }
}

#endif