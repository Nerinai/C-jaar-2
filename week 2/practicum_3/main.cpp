#define CATCH_CONFIG_MAIN
#include <catch_with_main.hpp>
#include <iostream>
#include <cstring>
#include <sstream>

bool failed = false;

#define STRING_PANIC_FUN [](){ failed = true; }

#ifdef STRING_PROVIDER_CHRIS
    #include "string.hh"
    #define STRING String
#elif defined(STRING_PROVIDER_JAN)
    #define STRING BestStringClass4Leven
    #include "stringsxxx.hh"
#elif defined(STRING_PROVIDER_DAVID)
    #define STRING string_template
    #include "string_template.hpp"
#else
    #define STRING string
    #include "string.hpp"
#endif

// Not providing a '==' op.
template<size_t size>
bool streq(const STRING<size> &str, const char *other) {
    return !strcmp(str.c_str(), other);
}

template<size_t size1, size_t size2>
bool streq(const STRING<size1> &str, const STRING<size2> &other) {
    return !strcmp(str.c_str(), other.c_str());
}

template <size_t size>
class string_phony
{
	size_t index = 0;
	char string[size +1] = { };
public:

string_phony() = default;

string_phony& operator += (const char * str){
	const char * base_addr = str;
	size_t ind = 0;
	while ((*str != '\0') && (index + ind < size)){
		ind++;
		str++;
	}
	
	str = base_addr;
	
	for(size_t i = ind; i > 0; i--){
			string[index] = * str;
			index++;
			str++;
	}
	string[index] = '\0';
	return *this;
	}
	
	char * c_str(){
		return string;
	}

	const char * c_str() const {
		return string;
	}

	string_phony & operator << (const char * str){
		return *this += str;
	}

};

TEST_CASE("Creating empty strings", "[string]") {
    STRING<8> s;
    REQUIRE(s.length() == 0);
    REQUIRE(streq(s, ""));
}

TEST_CASE("Constructing strings from char*", "[string]") {
    // Basic construction.
    STRING<8> s1("hoi");
    REQUIRE(failed == false);
    REQUIRE(s1.length() == 3);
    REQUIRE(streq(s1, "hoi"));

    // Construction with truncation.
    STRING<2> s2("hoi");
    REQUIRE(failed == false);
    REQUIRE(s2.length() == 2);
    REQUIRE(streq(s2, "ho"));
}

TEST_CASE("Constructing strings from chars", "[string]") {
    // Basic construction.
    STRING<8> s1('@');
    REQUIRE(failed == false);
    REQUIRE(s1.length() == 1);
    REQUIRE(streq(s1, "@"));

    // Construction with truncation.
    STRING<0> s2('@');
    REQUIRE(failed == false);
    REQUIRE(s2.length() == 0);
    REQUIRE(streq(s2, ""));
}

TEST_CASE("Constructing strings from other strings", "[string]") {
    STRING<8> s1("hoi");

    // Basic copy construction.
    STRING<3> s2(s1);
    REQUIRE(failed == false);
    REQUIRE(s2.length() == 3);
    REQUIRE(streq(s2, "hoi"));

    // Check if the contents were properly copied.
    // Use c_str() because testing the [] operator is not our
    // responsibility.
    s2.c_str()[1] = 'a';
    REQUIRE(streq(s1, "hoi"));

    // Copy construction with truncation.
    STRING<2> s3(s1);
    REQUIRE(failed == false);
    REQUIRE(s3.length() == 2);
    REQUIRE(streq(s3, "ho"));
}

TEST_CASE("Assigning shit", "[string]") {
    // Assigning to empty strings.
    STRING<8> s1;
    s1 = '@';
    REQUIRE(s1.length() == 1);
    REQUIRE(streq(s1, "@"));

    STRING<8> s2;
    s2 = "hooi";
    REQUIRE(s2.length() == 4);
    REQUIRE(streq(s2, "hooi"));

    STRING<8> s3;
    s3 = STRING<8>("hooi");
    REQUIRE(s3.length() == 4);
    REQUIRE(streq(s3, "hooi"));

    // Assigning to non-empty strings.
    s2 = STRING<10>("hoi");
    REQUIRE(s2.length() == 3);
    REQUIRE(streq(s2, "hoi"));

    s2 = "oi";
    REQUIRE(s2.length() == 2);
    REQUIRE(streq(s2, "oi"));

    s2 = '@';
    REQUIRE(s2.length() == 1);
    REQUIRE(streq(s2, "@"));

    // Assigning with truncation.
    s2 = STRING<10>("123456789");
    REQUIRE(s2.length() == 8);
    REQUIRE(streq(s2, "12345678"));

    s2 = "987654321";
    REQUIRE(s2.length() == 8);
    REQUIRE(streq(s2, "98765432"));

    STRING<0> s4;
    s4 = '@';
    REQUIRE(s4.length() == 0);
    REQUIRE(streq(s4, ""));
}

TEST_CASE("testing the << operator", "[string]"){
	// streaming string into other string
	STRING<10> s1("testtext");
	string_phony<10> s2;
	s2 << s1;
	REQUIRE(!strcmp(s1.c_str(),s2.c_str()));
	//hwlib::cout << s1 << hwlib::endl;
	//std::cout << s1 << std::endl;
}

TEST_CASE ("testing the [] operator", "[string]"){
	
	//looking up a character
	STRING<10> s1("abcdefg");
	REQUIRE(s1[2] == 'c');
	REQUIRE(failed == false);
	
	//requiesting a character out of scope
	char ptr = s1[10];
	REQUIRE(failed == true);
	failed = false;
	
	//character request
	ptr = s1[6];
	REQUIRE(failed == false);
	REQUIRE(ptr == 'g');
	
	//failed request to another string
	char& ptr2 = s1[9];
	REQUIRE(failed == true);
	failed = false;
	
	//character request to another string
	ptr2 = s1[0];
	REQUIRE(failed == false);
	REQUIRE(ptr2 == 'a');
	
	//Replacing a character within the sting
	s1[3] = 'A';
	REQUIRE(failed == false);
	REQUIRE(s1[3] == 'A');
	REQUIRE(streq(s1, "abcAefg"));
	
}

TEST_CASE ("testing the clear() function", "[string]"){
	//initialize sting and test its contents
	STRING<5> s1("hallo");
	REQUIRE(s1.length() == 5);
	REQUIRE(streq(s1, "hallo"));
	
	//clearing the string
	s1.clear();
	REQUIRE(s1.length() == 0);
	REQUIRE(streq(s1, ""));
}

TEST_CASE ("testing c_str() function", "[string]"){
	
	//literal string return
	STRING<10> s1("hallo");
	REQUIRE(!strcmp(s1.c_str(), "hallo"));
	
	//comparing the pointers
	STRING<10> s2("hallo");
	REQUIRE(!strcmp(s1.c_str(), s2.c_str()));
	
	//comparing the output
	STRING<10> s3(s2);
	char * ptr1 = s2.c_str();
	const char * ptr2 = s3.c_str();
	REQUIRE (ptr1 != ptr2);
}

TEST_CASE ("testing length() function", "[string]") {

	//default string is lenght 0
	STRING<10> s1;
	REQUIRE(s1.length() == 0);
	
	//increasing the length
	s1 = "testtext";
	REQUIRE(s1.length() == 8);
	
	//decreasing the length
	s1 = "testte";
	REQUIRE(s1.length() == 6);
	
	//length does not count droped characters
	s1 = "12characters";
	REQUIRE(s1.length() == 10);
}

//jan
TEST_CASE("Test += operators for empty string with const char *", "[string]") {
    STRING<8> s;
    s += "vier";
    REQUIRE(s.length() == 4);
    REQUIRE(streq(s, "vier"));
    REQUIRE(failed == false);

    STRING<2> s2;
    s2 += "vier";
    REQUIRE(s2.length() == 2);
    REQUIRE(streq(s2, "vi"));
    REQUIRE(failed == false);
}

 TEST_CASE("Test += operators for already filled string with const char *", "[string]") {
    STRING<8> s("vier");
    s += "honderdduizend";
    REQUIRE(s.length() == 8);
    REQUIRE(streq(s, "vierhond"));
    REQUIRE(failed == false);

    STRING<4> s2("een");
    s2 += "x";
    REQUIRE(s2.length() == 4);
    REQUIRE(streq(s2, "eenx"));
    REQUIRE(failed == false);
}

TEST_CASE("Test += operators for empty string with char", "[string]") {
    STRING<1> s;
    s += 'X';
    REQUIRE(s.length() == 1);
    REQUIRE(streq(s, "X"));
    REQUIRE(failed == false);

    STRING<0> s2;
    s2 += 'X';
    REQUIRE(s2.length() == 0);
    REQUIRE(streq(s2, ""));
    REQUIRE(failed == false);

}

TEST_CASE("Test += operators for filled string with char", "[string]") {
    STRING<2> s3;
    s3 += 'X';
    s3 += 'Y';
    s3 += 'Z';
    REQUIRE(s3.length() == 2);
    REQUIRE(streq(s3, "XY"));
    REQUIRE(failed == false);
}

TEST_CASE("Test += operators for empty and non emptey strings with other strings", "[string]") {
    STRING<8> s("vier");
    STRING<4> s2;
    s2 += s;
    REQUIRE(s2.length() == 4);
    REQUIRE(streq(s2, "vier"));
    REQUIRE(failed == false);
    s += s2;
    REQUIRE(s.length() == 8);
    REQUIRE(streq(s, "viervier"));
    REQUIRE(failed == false);

    STRING<6> s3;
    s3 += s;
    REQUIRE(s3.length() == 6);
    REQUIRE(streq(s3, "viervi"));
    REQUIRE(failed == false);
}

TEST_CASE("If you pass this you won't get a cookie (no seriously this test is checking if you return your *this pointer properly", "[string]") {
	STRING<4> s;
	STRING<1> s2("X");
	((s += 'x') += s2) += "LOL";
	REQUIRE(s.length() == 4);
	REQUIRE(streq(s, "xXLO"));
	REQUIRE(failed == false);
}