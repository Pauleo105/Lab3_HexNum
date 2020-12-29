#include <gtest/gtest.h>
#include "../lab3.h"
#include <math.h>

TEST(HexNum, DefaultConstructor){
prog3::hex a1;
ASSERT_EQ(0, a1.getNumBin()[0]);
ASSERT_EQ(0, a1.getNumBin()[1]);
ASSERT_EQ(0, a1.getNumBin()[2]);
ASSERT_EQ(0, a1.getNumBin()[3]);
ASSERT_EQ(0, a1.getNumBin()[4]);
}

// TEST(HexNum1, InitConstructor) {
//     const char aa2[7] = "ABC123";
//     prog3::hex a2(aa2);
//     prog3::hex a3("34567");
//     ASSERT_EQ(aa2, a2.getNumHex());
//     ASSERT_EQ("34567", a3.getNumHex());
// }

TEST(HexInit, TestException)
{
    ASSERT_ANY_THROW(prog3::hex("JKO"));
    ASSERT_ANY_THROW(prog3::hex("!!!!!!#$%"));
    ASSERT_ANY_THROW(prog3::hex("a123R"));
}

TEST(HexMethods, Setters)
{
    prog3::hex a;
    prog3::hex b("32A");
    prog3::hex c("032");
    prog3::hex d("2A0");
    // ASSERT_EQ(b, a.add(b));
    ASSERT_EQ(-1, a.check(b));
    //ASSERT_EQ(1, b.check(a));
    //ASSERT_EQ(c, b.rightshift(1));
}

int main(int argc, char* argv[])
{
::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}