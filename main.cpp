
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <iostream>
#include <string>
#include "catch.hpp"
using std::string;
using std::size_t;

unsigned int calculator(string words) {
    if(words=="")  {
        return 0;
    }   else    {
        int i = 0;
        int sum = 0;
        if(words[i]=='-')
            {throw std::runtime_error("negatives not allowed");}
        while(isdigit(words[i]))
        {
            char dig = words[i];
            sum = sum*10 + (int)(dig - '0');
            i++;
        }
        if(sum>1000)
            sum=0;
        if(words[i]=='-')
            {throw std::runtime_error("negatives not allowed");}
        if(words[i] == ',' || words[i]== '\n')  {
            return sum + calculator(words.substr(i+1,words.size()));
        }

        return sum;
    }


}

TEST_CASE("Test Case: Empty String ('')returns 0") {
    REQUIRE(calculator("")==0);
}

TEST_CASE("Single number returns value")
{
    //REQUIRE(calculator("1") == 1);
    REQUIRE(calculator("45") == 45);
    REQUIRE(calculator("678") == 678);
}
TEST_CASE("Numbers seperated by commas return sum") {
    REQUIRE(calculator("1,1")==2);
    REQUIRE(calculator("7,3,6")==16);
    REQUIRE(calculator("108,56")==164);

    REQUIRE(calculator("108,56,215,512,314")==(164+215 + 512 + 314));
}
TEST_CASE("Numbers seperated by newlines return sum") {
    REQUIRE(calculator("1\n1")==2);
    REQUIRE(calculator("7\n3\n6")==16);
    REQUIRE(calculator("108\n56")==164);

    REQUIRE(calculator("108\n56,215\n512,314")==(164+215 + 512 + 314));
}
TEST_CASE("Numbers>1000 are ignored") {
    REQUIRE(calculator("2,1001")==2);
    REQUIRE(calculator("10001,1001")==0);
    REQUIRE(calculator("10001,1001,10001,1001,10001,1001,10001,1001")==0);
}
