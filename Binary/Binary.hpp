#ifndef BINARY_HPP
#define BINARY_HPP

#include <iostream>

/**
 * @brief The Binary class
 * Теоретично представляє собою std::numeric_limits<size_t>::max()-бітне двійкове число.
 *
 */
class Binary
{
    unsigned int* m_value;
    size_t m_bits_count;
public:
    Binary();
    Binary(int value);
    Binary(const Binary& other);
    Binary(Binary&& other);
    ~Binary();

    Binary& operator=(const Binary& other);
    Binary& operator=(Binary&& other);

    Binary& operator<<=(const size_t& right);
    Binary &operator>>=(const size_t& right);

    friend std::ostream& operator<<(std::ostream& lhs, const Binary& rhs);
    friend std::istream& operator>>(std::istream& lhs, Binary& rhs);
private:
    inline size_t elements() const;
    inline unsigned int get_mask() const;
    void copy_m_value(const Binary& other);
    void overflow_handler(size_t& elements);

};

std::ostream& operator<<(std::ostream& lhs, const Binary& rhs);
std::istream& operator>>(std::istream& lhs, Binary& rhs);
Binary operator<<(Binary& left, const size_t& right);

#endif // BINARY_HPP
