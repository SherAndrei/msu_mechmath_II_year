#pragma once
#include <cstdint>
#include <iostream>

class BitSet {
 public:
    BitSet();
    explicit BitSet(std::size_t max_size);
    ~BitSet();
    BitSet(const BitSet& another);

 public:
    BitSet  operator& (const BitSet& other) const;
    BitSet  operator| (const BitSet& other) const;
    BitSet  operator^ (const BitSet& other) const;
    BitSet  operator<<(const std::size_t amount) const;
    BitSet  operator>>(const std::size_t amount) const;
    BitSet  operator~ () const;

 public:
    BitSet& operator =   (const BitSet& other);
    BitSet& operator &=  (const BitSet& other);
    BitSet& operator |=  (const BitSet& other);
    BitSet& operator ^=  (const BitSet& other);
    BitSet& operator <<= (const std::size_t amount);
    BitSet& operator >>= (const std::size_t amount);

 public:
    bool operator == (const BitSet& other) const;
    bool operator != (const BitSet& other) const;
    bool operator <  (const BitSet& other) const;
    bool operator <= (const BitSet& other) const;
    bool operator >  (const BitSet& other) const;
    bool operator >= (const BitSet& other) const;

 public:
    BitSet& set();
    BitSet& reset();

  // Getters
 public:
    size_t size() const;
    size_t capacity() const;

  // to access a specific bit
 public:
    class Bit {
     public:
         Bit() = default;
        ~Bit() = default;
        Bit(const Bit& other) = default;
        Bit(uint32_t* number, size_t idx);
        Bit& operator=(bool b);
        Bit& operator=(const Bit& other);
        operator bool() const;
        Bit& flip();

     private:
        size_t    _idx   = 0;
        uint32_t* _p_num = nullptr;
    };

 public:
    Bit& operator[](size_t idx);
    bool operator[](size_t idx) const;

 private:
    std::size_t    _size;
    std::size_t    _capacity;
    std::uint32_t* _bits;
    Bit            _bit;
};

std::istream& operator >> (std::istream& is, BitSet& bs);
std::ostream& operator << (std::ostream& os, const BitSet& bs);
