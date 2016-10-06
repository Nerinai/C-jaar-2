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

class phony_string {
public:
	const char * operator <<(const char * phony){
		return phony;
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
	STRING<10> s1("testtext");
	phony_string string;
	REQUIRE(!strcmp(string << s1, s1.c_str()));
}

TEST_CASE ("testing the [] operator", "[string]"){
	
	STRING<10> s1("abcdefg");
	REQUIRE(s1[2] == 'c');
	REQUIRE(failed == false);
	
	char ptr = s1[10];
	REQUIRE(failed == true);
	failed = false;
	
	ptr = s1[6];
	REQUIRE(failed == false);
	REQUIRE(ptr == 'g');
	
	char& ptr2 = s1[9];
	REQUIRE(failed == true);
	failed = false;
	
	ptr2 = s1[0];
	REQUIRE(failed == false);
	REQUIRE(ptr2 == 'a');
	
	s1[3] = 'A';
	REQUIRE(failed == false);
	REQUIRE(s1[3] == 'A');
	REQUIRE(streq(s1, "abcAefg"));
	
}

TEST_CASE ("testing the clear() function", "[string]"){
	
	STRING<5> s1("hallo");
	REQUIRE(s1.length() == 5);
	REQUIRE(streq(s1, "hallo"));
	
	s1.clear();
	REQUIRE(s1.length() == 0);
	REQUIRE(streq(s1, ""));
}

TEST_CASE ("testing c_str() function", "[string]"){
	
	STRING<10> s1("hallo");
	REQUIRE(!strcmp(s1.c_str(), "hallo"));
	
	STRING<10> s2("hallo");
	REQUIRE(!strcmp(s1.c_str(), s2.c_str()));
	
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



// TEST_CASE("Reading characters", "[string]") {
//     STRING<8> s("hoi");
//     REQUIRE(failed == false);
//     REQUIRE(s.length() == 3);

//     char c = s[0];
//     REQUIRE(failed == false);
//     REQUIRE(c == 'h');

//     c = s[2];
//     REQUIRE(failed == false);
//     REQUIRE(c == 'i');

//     c = s[3];
//     REQUIRE(failed == true);

//     failed = false;
// }

// TEST_CASE("Writing characters", "[string]") {
//     STRING<8> s("hoi");
//     REQUIRE(failed == false);

//     char &c1 = s[0];
//     REQUIRE(failed == false);
//     c1 = 'H';
//     REQUIRE(s[0] == 'H');

//     char &c2 = s[2];
//     REQUIRE(failed == false);
//     c2 = 'n';
//     REQUIRE(s[2] == 'n');

//     char &c3 = s[3];
//     REQUIRE(failed == true);

//     failed = false;
// }
