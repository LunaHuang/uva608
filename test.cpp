#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include "main.cpp"
#if 1
TEST(TestCase1, Solution)
{
    auto Solve = [](std::istream &is) -> std::string {
        std::ostringstream oss;
        solve_uva_problem(is, oss);
        return std::string("\n") + oss.str();
    };
    {
        std::stringstream fake_cin;
        fake_cin << R"(1
ABCD EFGH even
ABCI EFJK up
ABIJ EFGH even
)";

        EXPECT_EQ(
                R"(
K is the counterfeit coin and it is light.
)",
                Solve(fake_cin));
    }
}

TEST(TestCase2, Solution)
{
    auto Solve = [](std::istream &is) -> std::string {
        std::ostringstream oss;
        solve_uva_problem(is, oss);
        return std::string("\n") + oss.str();
    };
    {
        std::stringstream fake_cin;
        fake_cin << R"(1
ABC FGJ down
DC HG down
ABIHG JKEDF up
)";

        EXPECT_EQ(
                R"(
G is the counterfeit coin and it is heavy.
)",
                Solve(fake_cin));
    }
}
#endif
#if 1
TEST(TestCase3, Solution)
{
    auto Solve = [](std::istream &is) -> std::string {
        std::ostringstream oss;
        solve_uva_problem(is, oss);
        return std::string("\n") + oss.str();
    };
    {
        std::stringstream fake_cin;
        fake_cin << R"(15
ABC DEF up
GHI JKL even
EF DA up
AFG JKL down
A J down
A D even
ED FG even 
AB CI up 
A D up 
IL JK even 
A B even 
E L down 
BEF JIL down 
J A even 
CEF BJI even 
AC BD down
AC EF down
A F even
IJK ABC even
C L even
L F up
IJK ABC even
C L even
L F down
ABCDE FGHIJ even
EIL ADJ down
K J even
CBA DEF up
AF BC up
BA CD up
CBA DEF up
A B up
BA CD up
CBA DEF up
B A down
BA CD up
CBA DEF down
AF BC down
BA CD down
CBA DEF down
A B down
BA CD down
CBA DEF down
B A up
BA CD down
)";

        EXPECT_EQ(
                R"(
D is the counterfeit coin and it is light.
J is the counterfeit coin and it is heavy.
A is the counterfeit coin and it is heavy.
E is the counterfeit coin and it is light.
L is the counterfeit coin and it is heavy.
C is the counterfeit coin and it is light.
F is the counterfeit coin and it is light.
F is the counterfeit coin and it is heavy.
L is the counterfeit coin and it is light.
A is the counterfeit coin and it is heavy.
A is the counterfeit coin and it is heavy.
A is the counterfeit coin and it is heavy.
A is the counterfeit coin and it is light.
A is the counterfeit coin and it is light.
A is the counterfeit coin and it is light.
)",
                Solve(fake_cin));
    }
}
#endif
