#include <sort.hpp>
#include <catch.hpp>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

SCENARIO("8mb", "[8mb]")
{
  Sort other("8mb", "out_8", 1);
  bool x = true;
  std::ifstream f1("out_8"), f2("out8");
  man m1, m2;
  while(!f2.eof() && !f1.eof())
  {
    if((f1>>st1)&&(f2>>st2))
    {
      if(m1.name!=m2.name)
      {
        x=false;
        break;
      }
    }
    else break;
  }
  f1.close();
  f2.close();
  REQUIRE(x);
}

SCENARIO("15mb", "[15mb]")
{
  Sort other("15mb", "out_15", 4);
  bool x = true;
  std::ifstream f1("out_15"), f2("out15");
  man m1, m2;
  while(!f2.eof() && !f1.eof())
  {
    if((f1>>st1)&&(f2>>st2))
    {
      if(m1.name!=m2.name)
      {
        x=false;
        break;
      }
    }
    else break;
  }
  f1.close();
  f2.close();
  REQUIRE(x);
}

SCENARIO("32mb", "[32mb]")
{
  Sort other("32mb", "out_32", 17);
  bool x = true;
  std::ifstream f1("out_32"), f2("out32");
  man m1, m2;
  while(!f2.eof() && !f1.eof())
  {
    if((f1>>st1)&&(f2>>st2))
    {
      if(m1.name!=m2.name)
      {
        x=false;
        break;
      }
    }
    else break;
  }
  f1.close();
  f2.close();
  REQUIRE(x);
}

