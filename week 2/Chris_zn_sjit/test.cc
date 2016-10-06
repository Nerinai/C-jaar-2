#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <cstring>

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
    #include "string.hh"
#else
    #define STRING string
    #include "string.hpp"
#endif

// Not providing a '==' op.
template<size_t size>
bool streq(String<size> &str, const char *other) {
    return !strcmp(str.c_str(), other);
}

template<size_t size1, size_t size2>
bool streq(String<size1> &str, String<size2> &other) {
    return !strcmp(str.c_str(), other.c_str());
}

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
