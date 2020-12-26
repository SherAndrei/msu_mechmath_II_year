#pragma once

enum class ErrorCode {
    NoError = 0,
    NoElem = 1,
};

template<class TData>
struct ResultT {
    TData     data;
    ErrorCode resultCode;

    explicit ResultT(ErrorCode code) : data(TData{}), resultCode(code) {}

    ResultT(const TData& d, ErrorCode code) : data(d), resultCode(code) {}
};


template<class T>
class Block {
 public:
    enum { BlockSize = 1024 };

 public:
    bool isEmpty() const {
        return m_length == 0;
    }

    bool isIndexValid(int index) const {
        return (index >= 0 && index < m_length);
    }

    bool isFull() const {
        return length() == BlockSize;
    }

    int length() const {
        return m_length;
    }

    T& firstElem() {
        try {
            return at(0);
        } catch(...) {
            return m_elems[0];
        }
    }

    T& endElem() {
        try {
            return at(length() -1);
        } catch(...) {
            return m_elems[0];
        }
    }

    T& at(int index) {
        if (!isIndexValid(index)) throw std::out_of_range("Index is out of range");
        return m_elems[index];
    }

    int addElem(const T& elem) {
        if (isFull()) throw std::logic_error("Can't add the elem. The Block is full");
        at(m_length++) = elem;
        return m_length -1;
    }

    T removeElem(int index) {
        T shiftedElem = leftShift(index);
        --m_length;
        return shiftedElem;
    }

    T leftShift(int toIndex = 0) {
        T shifted = at(toIndex);
        for (int i = toIndex; i < length(); ++i)
            m_elems[i] = m_elems[i +1];

        return shifted;
    }

    T leftShiftAndAddElem(int& toIndex, const T& additiveElem,
                          bool setToIndexAsBegin = true) {
        T shifted = leftShift(toIndex);
        endElem() = additiveElem;
        if (setToIndexAsBegin) toIndex = 0;
        return shifted;
    }

    T rightShift(int fromIndex) {
        T shifted = endElem();
        for (int i = BlockSize -1; i > fromIndex; --i)
            m_elems[i] = m_elems[i -1];

        return shifted;
    }

    T rightShiftWithInsert(int& fromIndex, const T& elem,
                           bool setFromIndexAsBegin = true) {
        T shifted = rightShift(fromIndex);

        m_length += (m_length+1 < BlockSize) ? 1 : 0;

        at(fromIndex) = elem;

        if (setFromIndexAsBegin) fromIndex = 0;

        return shifted;
    }

    Block<T>* nextBlock() const {
        return m_nextBlock;
    }

    Block<T>* setNextBlock(Block<T>* nextBlock) {
        if (nextBlock == this) throw std::logic_error("The looped blocks are prohibited");
        return (m_nextBlock = nextBlock);
    }

 public:
    Block<T>& operator = (const Block<T>& other) {
        m_nextBlock = other.nextBlock;
        m_length    = other.m_length;

        for (int i=0; i < BlockSize; ++i)
            m_elems[i] = other.m_elems[i];
    }

// Friends:
    template<class Type> friend class BlockArray;

 protected:
    Block<T>* m_nextBlock = nullptr;
    int       m_length    = 0;
    T         m_elems[BlockSize];
};
