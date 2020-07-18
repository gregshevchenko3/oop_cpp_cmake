#include "Binary.hpp"
#include "CBenchmark.hpp"


Binary::Binary() : m_value(0), m_bits_count(0)
{}
Binary::Binary(int value) : m_value(value)
{
    TRACE;
    m_bits_count = sizeof(unsigned int) * 8;
    auto mask  = 1 << (8*sizeof(unsigned int) -1);
    while(!(m_value & mask))
    {
        mask >>=1;
        m_bits_count--;
    }
}
Binary::Binary(const Binary &other) : m_value(other.m_value), m_bits_count(other.m_bits_count)
{}

Binary& Binary::operator=(const Binary &other)
{
    TRACE;
    if(this == &other) return *this;
    m_bits_count = other.m_bits_count;
    m_value = other.m_value;
    return *this;
}


std::ostream &operator<<(std::ostream &lhs, const Binary &rhs)
{
    TRACE;
    if(!rhs.m_bits_count) return lhs << '0';

    auto fmtflags = lhs.flags();
    lhs << std::noboolalpha;

    auto mask = 1 << (8*sizeof(unsigned int)-1);
    while(!(rhs.m_value & mask)) mask >>= 1;
    while(mask) {
        lhs << ((rhs.m_value & mask) != 0);
        mask >>= 1;
    }
    lhs.flags(fmtflags);

    return lhs;
}

std::istream &operator>>(std::istream &lhs, Binary &rhs)
{
    TRACE;
    rhs.m_bits_count = 0;
    bool started = false;
    rhs = Binary();
    while(lhs.peek() == '1' || lhs.peek() == '0' || lhs.peek() == '\r')
    {
        if(!started) // Тригером буде перший введений (найстарший) значащий біт.
        {
            started = lhs.peek() == '1';
            if(!started)
                lhs.get();
        }
        if(started)
        {
            // Здвинути на 1 вліво.
            rhs <<= 1;
            // Записати біт.
            rhs.m_value += lhs.get() - 0x30;
        }
    }
    return lhs;
}

Binary& Binary::operator<<=(const size_t &right)
{
    TRACE;
    m_value <<= right;
    return *this;
}

Binary &Binary::operator>>=(const size_t &right)
{
    TRACE;
    m_value >>= right;
    return *this;
}

