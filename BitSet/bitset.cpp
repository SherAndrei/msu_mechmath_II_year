#include "bitset.h"
#include <string>
#include <algorithm>
#include <stdexcept>

BitSet::BitSet()
    : _size(0)
    , _capacity(0)
    , _bits(nullptr)
    , _bit() {}

BitSet::BitSet(size_t max_size)
    : _size(max_size)
    , _capacity(max_size / 32 + ((max_size & 31) != 0))
    , _bits(new uint32_t[_capacity])
    , _bit() {}

BitSet::~BitSet() {
    delete [] _bits;
}

BitSet::BitSet(const BitSet& another)
    : _size(another._size)
    , _capacity(another._capacity)
    , _bits(nullptr)
    , _bit(another._bit) {
    if (another._bits != nullptr) {
        this->_bits     = new uint32_t[_capacity];
        std::copy(another._bits, another._bits + another._capacity,
                  this->_bits);
    }
}

BitSet& BitSet::operator =   (const BitSet& other) {
    if (*this != other) {
        if (this->_capacity != other._capacity) {
            this->_bits = new uint32_t[other._capacity];
            delete [] this->_bits;
            this->_capacity     = other._capacity;
        }
        this->_size = other._size;
        if (other._bits)
            std::copy(other._bits, other._bits + other._capacity, this->_bits);
    }
    return *this;
}

// throws exception if not equal
static bool cmp_sz(size_t lhs, size_t rhs, const std::string& hint = {}) {
    if (lhs != rhs)
        throw std::invalid_argument("Different sizes: " + hint);
    return true;
}
BitSet BitSet::operator &   (const BitSet& other) const {
    cmp_sz(this->_size, other._size, "operator &");
    BitSet result(this->_size);

    for (size_t i = 0u; i < this->_capacity; i++)
        result._bits[i] = this->_bits[i] & other._bits[i];
    return result;
}

BitSet BitSet::operator |   (const BitSet& other) const {
    cmp_sz(this->_size, other._size, "operator |");
    BitSet result(this->_size);

    for (size_t i = 0u; i < this->_capacity; i++)
        result._bits[i] = this->_bits[i] | other._bits[i];
    return result;
}

BitSet BitSet::operator ^   (const BitSet& other) const {
    cmp_sz(this->_size, other._size, "operator ^");
    BitSet result(this->_size);

    for (size_t i = 0; i < this->_capacity; i++)
        result._bits[i] = this->_bits[i] ^ other._bits[i];
    return result;
}
BitSet BitSet::operator <<  (const size_t amount) const {
    if (amount == 0)
        return *this;

    BitSet result(this->_size);
    for (size_t i = amount, j = 0u; i < this->_size; j++, i++) {
        result[i] = (*this)[j];
    }
    return result;
}
BitSet BitSet::operator >>  (const std::size_t amount) const {
    if (amount == 0)
        return *this;

    BitSet result(this->_size);
    for (size_t i = _size - amount, j = _size; i >= 1u; j--, i--) {
        result[i - 1] = (*this)[j - 1];
    }
    return result;
}
BitSet BitSet::operator~() const {
    BitSet result(this->_size);

    for (size_t i = 0u; i < this->_capacity; i++)
        result._bits[i] = ~this->_bits[i];
    return result;
}
BitSet& BitSet::operator &=  (const BitSet& other) {
    cmp_sz(this->_size, other._size, "operator &=");

    for (size_t i = 0u; i < this->_capacity; i++)
        this->_bits[i] &= other._bits[i];
    return *this;
}
BitSet& BitSet::operator |=  (const BitSet& other) {
    cmp_sz(this->_size, other._size, "operator |=");

    for (size_t i = 0u; i < this->_capacity; i++)
        this->_bits[i] |= other._bits[i];
    return *this;
}
BitSet& BitSet::operator ^=  (const BitSet& other) {
    cmp_sz(this->_size, other._size, "operator ^=");

    for (size_t i = 0u; i < this->_capacity; i++)
        this->_bits[i] ^= other._bits[i];
    return *this;
}

BitSet& BitSet::operator <<= (const std::size_t amount) {
    return *this = (*this << amount);
}
BitSet& BitSet::operator >>= (const std::size_t amount) {
    return *this = (*this >> amount);
}

bool BitSet::operator == (const BitSet& other) const {
    cmp_sz(this->_size, other._size, "operator ==");
    for (size_t i = 0u; i < other._size; i++) {
        if ((*this)[i] ^ other[i]) return false;
    }
    return true;
}
bool BitSet::operator != (const BitSet& other) const {
    cmp_sz(this->_size, other._size, "operator !=");
    return !(*this == other);
}
bool BitSet::operator <  (const BitSet& other) const {
    cmp_sz(this->_size, other._size, "operator <");
    for (size_t i = other._size; i >= 1u; i--) {
        if ((*this)[i - 1] ^ other[i - 1]) return other[i - 1];
    }
    return false;
}
bool BitSet::operator <= (const BitSet& other) const {
    cmp_sz(this->_size, other._size, "operator <=");
    return !(*this > other);
}
bool BitSet::operator >  (const BitSet& other) const {
    cmp_sz(this->_size, other._size, "operator >");
    for (size_t i = other._size; i >= 1u; i--) {
        if ((*this)[i - 1] ^ other[i - 1]) return (*this)[i - 1];
    }
    return false;
}
bool BitSet::operator >= (const BitSet& other) const {
    cmp_sz(this->_size, other._size, "operator >=");
    return !(*this < other);
}

BitSet& BitSet::set() {
    for (size_t i = 0u; i < _size; i++) {
        (*this)[i] = 1;
    }
    return *this;
}
BitSet& BitSet::reset() {
    for (size_t i = 0u; i < _size; i++) {
        (*this)[i] = 0;
    }
    return *this;
}

size_t BitSet::size() const {
    return _size;
}
size_t BitSet::capacity() const {
    return _capacity;
}
BitSet::Bit::Bit(uint32_t* p_number, size_t idx)
    : _idx(idx)
    , _p_num(p_number) {}
BitSet::Bit& BitSet::Bit::operator=(bool b) {
    if (b)
        (*_p_num) |=  (1u << _idx);
    else
        (*_p_num) &= ~(1u << _idx);

    return *this;
}
BitSet::Bit& BitSet::Bit::operator=(const Bit& other) {
    this->_p_num = other._p_num;
    this->_idx   = other._idx;
    return *this;
}
BitSet::Bit::operator bool() const {
    return (*_p_num) & (1u << _idx);
}
BitSet::Bit& BitSet::Bit::flip() {
    (*_p_num) ^= 1u << _idx;
    return *this;
}

BitSet::Bit& BitSet::operator[](size_t idx) {
    if (idx > _size)
        throw std::invalid_argument("operator []");

    _bit = Bit(&(_bits[idx / 32]), idx & 31);
    return _bit;
}
bool BitSet::operator[](size_t idx) const {
    if (idx > _size)
        throw std::invalid_argument("operator []");

    return Bit(&(_bits[idx / 32]), idx & 31);
}

#include <iostream>
std::istream& operator >> (std::istream& is, BitSet& bs) {
    std::string bit_str;
    std::getline(is, bit_str);
    size_t bit_sz = bit_str.size();

    for (size_t i = 0u; i < bit_sz; i++) {
        if ((bit_str[i] == '0' || bit_str[i] == '1') && i < bs.size()) {
            bs[i] = (bit_str[bit_sz - i - 1] == '1');
        } else {
            throw std::invalid_argument("istream operator >>: " + bit_str);
        }
    }
    return is;
}
std::ostream& operator << (std::ostream& os, const BitSet& bs) {
    for (size_t i = bs.size(); i >= 1u; i--) {
        os << bs[i - 1];
    }
    return os;
}
