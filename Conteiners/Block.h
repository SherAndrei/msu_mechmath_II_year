#pragma once

enum class ErrorCode
{
    NoError = 0,
    NoElem = 1,
};

template<class TData>
struct ResultT
{
    TData     data;
    ErrorCode resultCode;

    explicit ResultT(ErrorCode code) : data(TData{}), resultCode(code)
    {}

    ResultT(const TData& d, ErrorCode code) : data(d), resultCode(code)
    {}
};


template<class T>
class Block
{
public:
    enum { BlockSize = 1024 };

public:
    bool isEmpty() const
    {
        return m_length == 0;
    }

    bool isIndexValid(int index) const
    {
        return (index >= 0 && index < m_length);
    }

    bool isFull() const
    {
        return length() == BlockSize;
    }

    int length() const
    {
        return m_length;
    }

    T& firstElem()
    {
        try
        {
            return at(0);
        } catch(...) {
            return m_elems[0];
        }
        // if (length()) return at(0);
        // return m_elems[0];
    }

    T& endElem()                                                                ///// last наверное
    {
        try
        {
            return at(length() -1);
        } catch(...) {
            return m_elems[0];
        }
        // if (length()) return at(length() -1);
        // return m_elems[0];
    }

    // Возращает ссылку на элемент в позиции index.
    T& at(int index)
    {
        if (!isIndexValid(index)) throw std::out_of_range("Index is out of range");
        return m_elems[index];
    }

    // Добавляет элемент в конец блока.
    // Возвращает индекс вставленного элемента относительно блока.
    int addElem(const T& elem)
    {
        if (isFull()) throw std::logic_error("Can't add the elem. The Block is full");
        at(m_length++) = elem; //m_elems[m_length++] = elem;
        return m_length -1;                                                               ////// почему уменьшаем длину? abcde = len() = 5
    }

    // Смещает все элементы влево на одну позицию, начиная с index+1.
    // Возвращает вымещенный элемент.
    // Изменяет количество элементов.
    T removeElem(int index)
    {
        T shiftedElem = leftShift(index);
        --m_length;
        return shiftedElem;
    }

    // Смещает все элементы влево к позиции toIndex, начиная с toIndex+1.
    // Возвращает вымещенный элемент.
    // НЕ изменяет количество элементов.
    T leftShift(int toIndex =0)                                                         ///////// как это?
    {                                                                                   ///////// то есть мы подаем элемент, который сразу же станет 0?
        T shifted = at(toIndex);                                                        ///////// если да, то почему не написать везде 0
        for (int i = toIndex; i < length(); ++i)
            m_elems[i] = m_elems[i +1];

        return shifted;
    }

    // Смещает все элементы влево к позиции toIndex, начиная с toIndex+1
    //   и добавляет/устанавливает элемент additiveElem последним.
    // Возвращает вымещенный элемент.
    // Изменяет количество элементов.
    T leftShiftAndAddElem(int& toIndex, const T& additiveElem, bool setToIndexAsBegin =true) //////////получаем ссылку на toIndex?
    {
        T shifted = leftShift(toIndex);
        endElem() = additiveElem;
        if (setToIndexAsBegin) toIndex = 0;                                                  ///////////тоже не совсем понимаю, если мы ставим сначала true, то когда false?
        return shifted;
    }

    // Смещает все элементы вправо, начиная с позиции fromIndex.
    // Возвращает вымещенный(последний по длине(!) блока) элемент.
    // НЕ изменяет количество элементов.
    T rightShift(int fromIndex)
    {
        // забираем существенный(т.е. реально последний) элемент: q -> [xet.]
        T shifted = endElem();

        // по идее, должно быть так: "for (int i = length() -1; i > fromIndex; --i)", но из-за "существенного" элемента, сдвигаем весь блок
        for (int i = BlockSize -1; i > fromIndex; --i)
            m_elems[i] = m_elems[i -1];

        return shifted;
    }

    // Смещает все элементы вправо, начиная с позиции fromIndex.
    // Возвращает вымещенный элемент.
    // Изменяет количество элементов: увеличивает на 1, но не более общего размера блока.
    T rightShiftWithInsert(int& fromIndex, const T& elem, bool setFromIndexAsBegin =true) //////////получаем ссылку на fromIndex?
    {
        T shifted = rightShift(fromIndex);

        // увеличиваем на 1, но не более размера блока:
        m_length += (m_length+1 < BlockSize) ? 1 : 0;

        at(fromIndex) = elem;

        if (setFromIndexAsBegin) fromIndex = 0;

        return shifted;
    }

    Block<T>* nextBlock() const
    {
        return m_nextBlock;
    }

    // Устанавливает указатель на следующий блок и возвращает его.
    Block<T>* setNextBlock(Block<T>* nextBlock)
    {
        if (nextBlock == this) throw std::logic_error("The looped blocks are prohibited");
        return (m_nextBlock = nextBlock);
    }

public:
    Block<T>& operator = (const Block<T>& other)
    {
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
