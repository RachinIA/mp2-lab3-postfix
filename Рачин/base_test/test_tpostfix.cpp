#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}
TEST(TPostfix, get_infix)
{
	TPostfix p("a+b*c");
	EXPECT_EQ("a+b*c", p.GetInfix());
}

TEST(TPostfix, ToPostfix)
{
	string tmp = "(a+b)*c";
	TPostfix p(tmp);
	p.ToPostfix();
	tmp = "ab+c*";
	EXPECT_EQ(tmp, p.GetPostfix());
}

TEST(TPostfix, ToPostfix1)
{
	string tmp = "a*b*c";
	TPostfix p(tmp);
	p.ToPostfix();
	tmp = "ab*c*";
	EXPECT_EQ(tmp, p.GetPostfix());
}

TEST(TPostfix, check_calculate)
{
	TPostfix p("(a+b)*c");
	p.ToPostfix();
	p.ArgsInPost(1);
	double* v;
	int N = p.NArgs;
	v = new double[N];
	for (int i = 0; i < N; i++)
	{
		v[i] = i + 1;
	}
	int res;
	res = p.Calculate(v);
	EXPECT_EQ(res, 9);
}

TEST(TPostfix, check_calculate1)
{
	TPostfix p("a-b-c-d");
	p.ToPostfix();
	p.ArgsInPost(1);
	double* v;
	int N = p.NArgs;
	v = new double[N];
	for (int i = 0; i < N; i++)
	{
		v[i] = i + 1;
	}
	int res;
	res = p.Calculate(v);
	EXPECT_EQ(res, -8);
}