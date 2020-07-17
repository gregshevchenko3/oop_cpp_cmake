#include "Binary.hpp"
#include "CBenchmark.hpp"


Binary::Binary() : m_value(new unsigned int[1]), m_bits_count(0)
{
    TRACE;
    m_value[0] = 0;
}
Binary::Binary(int value) : m_value(new unsigned int[1])
{
    TRACE;
    m_value[0] = value;
    m_bits_count = sizeof(unsigned int) * 8;
    auto mask  = get_mask();
    while(!(*m_value & mask))
    {
        mask >>=1;
        m_bits_count--;
    }

}
Binary::Binary(const Binary &other)
{
    TRACE;
    m_bits_count = other.m_bits_count;
    copy_m_value(other);
}

Binary::Binary(Binary &&other) : m_value(other.m_value), m_bits_count(other.m_bits_count)
{
    TRACE;
    other.m_value = nullptr;
}

Binary::~Binary()
{
    if(m_value) delete[] m_value;
}

Binary& Binary::operator=(const Binary &other)
{
    TRACE;
    if(this == &other) return *this;
    m_bits_count = other.m_bits_count;
    if(m_value) delete[] m_value;
    copy_m_value(other);
    return *this;
}

Binary &Binary::operator=(Binary &&other)
{
    TRACE;
    if(this == &other) return *this;
    if(m_value) delete[] m_value;
    m_bits_count = other.m_bits_count;
    m_value = other.m_value;
    other.m_value = nullptr;
    return *this;

}

size_t Binary::elements() const
{
    auto elements = m_bits_count / (8*sizeof(unsigned int));
    elements += (m_bits_count % (8*sizeof(unsigned int)))?1:0;
    return (elements)?elements:1;
}

unsigned int Binary::get_mask() const
{
    return 1 << (8*sizeof(unsigned int) -1);
}

void Binary::copy_m_value(const Binary &other)
{
    TRACE;
    auto elements = this->elements();
    if(elements)
    {
        m_value = new unsigned int[elements];
        std::copy(other.m_value, other.m_value + elements, m_value);
    }
    else
    {
        m_value = new unsigned int[1]{0};
    }
}

void Binary::overflow_handler(size_t& elements)
{
    TRACE;
    if(!(m_bits_count % (8*sizeof(unsigned int))) && (m_bits_count / (8*sizeof(unsigned int))))
    {
        auto tmp = new unsigned int[elements + 1];
        std::copy(m_value, m_value + elements, tmp);
        delete[] m_value;
        m_value = tmp;
        m_value[elements] = 0;
        elements++;
    }
}

std::ostream &operator<<(std::ostream &lhs, const Binary &rhs)
{
    TRACE;
    if(!rhs.m_bits_count) return lhs << '0';

    auto fmtflags = lhs.flags();
    lhs << std::noboolalpha;

    unsigned int* tmp = rhs.m_value + rhs.elements() -1;
    auto mask = rhs.get_mask();
    while(!(*tmp & mask)) mask >>= 1;
    do {
        while(mask) {
            lhs << ((*tmp & mask) != 0);
            mask >>= 1;
        }
        mask = rhs.get_mask();
        tmp--;
    } while(tmp >= rhs.m_value);

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
            *rhs.m_value += lhs.get() - 0x30;
        }
    }
    return lhs;
}

Binary& Binary::operator<<=(const size_t &right)
{
    TRACE;
    size_t shift = right % (sizeof(unsigned int) * 8);
    for(size_t j{0}; j < right; j++)
    {
        auto elements = this->elements();
        this->overflow_handler(elements);
        bool c, prev_c = false;
        for(size_t i{0}; i < elements; i++)
        {
            c = m_value[i] & get_mask();
            m_value[i] <<= shift;
            if(prev_c) m_value[i]++;
            prev_c = c;
        }
        m_bits_count++;
    }
    return *this;
}

Binary &Binary::operator>>=(const size_t &right)
{
    TRACE;

}

