/**
 * \file
 * \brief     Constant-size string class.
 * \copyright Copyright (c) 2016, Chris Smeele
 */
#pragma once

#include <cstdlib>

#ifndef STRING_PANIC_FUN
#define STRING_PANIC_FUN [](){ for(;;); }
#endif

template<size_t capacity>
class String {
    // static_assert(capacity > 0, "String size must be a non-zero positive integer.");

    size_t _length = 0;
    char _str[capacity+1] = { };

public:
    void clear() {
        _str[0] = '\0';
        _length = 0;
    }

    // size_t size()   const { return capacity; }
    size_t length() const { return _length; }

    const char *c_str() const { return _str; }
          char *c_str()       { return _str; }

    // Easy-mode support for both indexing and std::cout()-ing.
    // Too bad the assignment wants us to do checking...
    //operator char*() { return str; }

    // Index operators {{{

    char operator[](size_t i) const {
        if (i > _length) {
            STRING_PANIC_FUN();
            return '\0';
        }
        return _str[i];
    }

    char &operator[](size_t i) {
        // Don't allow getting a non-const ref to the null byte or beyond.
        if (i >= _length) {
            STRING_PANIC_FUN();
            static char n = '\0';
            return n;
        }
        return _str[i];
    }

    // }}}
    // Append operators {{{

    String &operator+=(const char *other) {
        size_t i;
        for (i = 0; _length + i < capacity && other[i]; i++)
            _str[_length + i] = other[i];
        _str[_length + i] = '\0';
        _length += i;
        return *this;
    }

    String &operator+=(char other) {
        char buf[2] = { other, '\0' };
        return *this += buf;
    }

    template<size_t otherSize>
    String &operator+=(const String<otherSize> &other) {
        return *this += other.c_str();
    }

    // }}}
    // Assignment operators {{{

    String &operator=(const char *other) {
        this->clear();
        return *this += other;
    }

    String &operator=(char other) {
        this->clear();
        return *this += other;
    }

    template<size_t otherSize>
    String &operator=(const String<otherSize> &other) {
        this->clear();
        return *this += other;
    }

    // }}}
    // Constructors {{{

    String(const char *other) {
        *this = other;
    }

    String(char other) {
        *this = other;
    }

    template<size_t otherSize>
    String(const String<otherSize> &other) {
        *this = other;
    }

    String() = default;

    // }}}

    virtual ~String() = default;
};

template<class Printer, size_t stringSize>
Printer &operator<<(Printer &p, const String<stringSize> &str) {
    return p << str.c_str();
}
