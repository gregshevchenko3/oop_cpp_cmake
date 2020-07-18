#ifndef BINARY_HPP
#define BINARY_HPP

#include <iostream>

class Binary
{
    unsigned int m_value;
    size_t m_bits_count;
public:
    Binary();
    Binary(int value);
    Binary(const Binary& other);

    Binary& operator=(const Binary& other);

    Binary& operator<<=(const size_t& right);
    Binary &operator>>=(const size_t& right);

    friend std::ostream& operator<<(std::ostream& lhs, const Binary& rhs);
    friend std::istream& operator>>(std::istream& lhs, Binary& rhs);
private:

};

std::ostream& operator<<(std::ostream& lhs, const Binary& rhs);
std::istream& operator>>(std::istream& lhs, Binary& rhs);
Binary operator<<(Binary& left, const size_t& right);

#endif // BINARY_HPP
