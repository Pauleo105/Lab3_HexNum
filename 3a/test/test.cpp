#include <gtest/gtest.h>
#include "../lab3.h"
#include <string.h>

TEST(HexConstructor, DefaultConstructor) {
    Hex::hex a;
    ASSERT_EQ(0, a.getNum());
    ASSERT_EQ(0, strcmp("0", a.getStr()));
    ASSERT_EQ(1, a.getLen());
}

TEST(HexConstructor, InitConstructor) {
    Hex::hex a("abcdef");
    ASSERT_EQ(11259375, a.getNum());
    ASSERT_EQ(0, strcmp("abcdef", a.getStr()));
    ASSERT_EQ(6, a.getLen());
    Hex::hex b("abcdef", 10);
    ASSERT_EQ(11259375, b.getNum());
    ASSERT_EQ(0, strcmp("0000abcdef", b.getStr()));
    ASSERT_EQ(10, b.getLen());
    Hex::hex c(0xbeba);
    ASSERT_EQ(48826, c.getNum());
    ASSERT_EQ(0, strcmp("beba", c.getStr()));
    ASSERT_EQ(4, c.getLen());
}

TEST(HexConstructor, TestException) {
    ASSERT_ANY_THROW(Hex::hex a("ghjkl"));
    ASSERT_ANY_THROW(Hex::hex b("abc", 40));
    ASSERT_ANY_THROW(Hex::hex b("12345", -5));
}

TEST(HexMethods, Setters) {
    Hex::hex a, b;
    a.setCh("baeaea");
    ASSERT_EQ(12249834, a.getNum());
    ASSERT_EQ(0, strcmp("baeaea", a.getStr()));
    ASSERT_EQ(6, a.getLen());
    b.setNu(0xab);
    ASSERT_EQ(171, b.getNum());
    ASSERT_EQ(0, strcmp("ab", b.getStr()));
    ASSERT_EQ(2, b.getLen());
}

TEST(HexMethods, Parametres) {
    Hex::hex a("abc"), b("-bad"), c(0x12a);
    ASSERT_EQ(-241, a.add(b).getNum());
    ASSERT_EQ(2, a.add(b).getLen());
    ASSERT_EQ(3046, a.add(c).getNum());
    ASSERT_EQ(3, a.add(c).getLen());
    ASSERT_EQ(-2691, b.add(c).getNum());
    ASSERT_EQ(3, b.add(c).getLen());
    ASSERT_EQ(2450, a.subtract(c).getNum());
    ASSERT_EQ(3, a.subtract(c).getLen());
    ASSERT_EQ(-3287, b.subtract(c).getNum());
    ASSERT_EQ(3, b.subtract(c).getLen());
    ASSERT_EQ(10, a.rightshift(2).getNum());
    ASSERT_EQ(-3328, b.leftshift(2).getNum());
    ASSERT_EQ(1, a.isgreat(b));
    ASSERT_EQ(-1, b.isgreat(a));
    Hex::hex d("12a");
    ASSERT_EQ(0, c.isgreat(d));
    ASSERT_EQ(1, a.parity());
    ASSERT_EQ(0, b.rightshift(2).parity());
    ASSERT_EQ(1, c.parity());
    ASSERT_EQ(1, d.parity());
}

int main(int argc, char* argv[])
{
::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}