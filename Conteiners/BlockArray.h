#pragma once
#include <iostream>
#include <string>
#include "Block.h"

template<class T>
class BlockArray
{
// // Forward declarations:
// public:
//     class ForwardIterator;
//
public:
    enum { InvalidIndex = -1 };

public:
    BlockArray()
        : m_length(0)
        , m_blockCount(0)
        , m_head(nullptr)
        , m_tail(nullptr)
    {
//        using namespace std;
//        cout << endl << "BlockArray<T> has been created" << endl;
    }

    ~BlockArray()
    {
        using namespace std;
//        cout << endl << "~BlockArray<T> has been called" << endl;

        Block<T>* block = headBlock();
        if (!headBlock()) return;

        while (Block<T>* next = block->nextBlock())
        {
            delete block;
            block = next;
        }
        delete m_head->m_nextBlock;
        delete m_head;

    }

public:
    bool isEmpty() const
    {
        return 0 == length();
    }

    int length() const                          /////����� �������? m_lenght ��� ������� � ����� ���������� ��� ��, � ������ ������
    {
        return m_length;
    }

    bool isIndexValid(int index) const
    {
        return (index >= 0 && index < length());
    }

public:
    // ���������� ������ �� ������� � ������� elemIndex.
    const T& at(int elemIndex) const
    {
        if (!isIndexValid(elemIndex))
            throw std::out_of_range("Index is out of range");
        return getBlockByElemIndex(elemIndex)->at(blockOffsetIndex(elemIndex));
    }

    T& at(int elemIndex)
    {
        if (!isIndexValid(elemIndex))
            throw std::out_of_range("Index is out of range");
        return getBlockByElemIndex(elemIndex)->at(blockOffsetIndex(elemIndex));
    }

    // ��������� ������� � ����� �������
    int add(const T& elem)
    {
        return insert(elem, length());
    }

    // ��������� ������� elem � ������� elemIndex
    int insert(const T& elem, int elemIndex)
    {
        if (!length())
        {
            appendBlock()->addElem(elem);
            return ++m_length;
        }

        // ������� ���� ������ ��������?
        if (length() == elemIndex)
        {
            Block<T>* newBlock = tailBlock();
            // [abcd]  [efgh]   [ijk.]
            // ������� ��������� ������� � ����� ���������� �����?
            if (0 == length() % Block<T>::BlockSize)
                // ������� ����:
                newBlock = appendBlock();

            // ������� ������� � ����:
            newBlock->addElem(elem);
            return ++m_length;
        }

        if (!isIndexValid(elemIndex)) throw std::out_of_range("Index is out of range"); //return InvalidIndex;

        Block<T>* block = getBlockByElemIndex(elemIndex);
        if (!block) throw std::out_of_range("Index is out of range"); //return InvalidIndex;

        // ��������� �������� ������ �����:
        int blockElemIdx = blockOffsetIndex(elemIndex);

        // ���� ��������� ���� �������� ���������, �� ���������� �������� ���� ����� ������ �������:
        if (tailBlock() && tailBlock()->isFull())
            appendBlock();

        T shiftedElem = elem;
        do    shiftedElem = block->rightShiftWithInsert(blockElemIdx, shiftedElem);
        while (block = block->nextBlock());

        // ���������� ��������� ������ � ���������� �����:
        tailBlock()->m_length++;

        // ����������� ����� ������ �������:
        ++m_length;

        return elemIndex;
    }

    // ������� ������� �� �������.
    T remove(int elemIndex)
    {
        if (!isIndexValid(elemIndex)) throw std::out_of_range("Index is out of range");

        Block<T>* block = getBlockByElemIndex(elemIndex);
        if (block == nullptr) throw std::out_of_range("Index is out of range");

        int blockElemIdx = blockOffsetIndex(elemIndex);

        // ������ ����� �������� ��������:
        T removedElem = block->at(blockElemIdx);

        // ��������� ��������� �� �������� ����:
        Block<T>* nextBlock = nullptr;

        do
        {
            if (nextBlock = block->nextBlock())
                block->leftShiftAndAddElem(blockElemIdx, nextBlock->firstElem());
            else
                block->removeElem(blockElemIdx);

        } while (block = block->nextBlock());

        // ���� ��������� ���� �������� ���� ���� �������, �� ����� ������� �� ������ ������ ���� ����:
        if (tailBlock()->length() == 0)
            removeBlock(tailBlock());

        // ��������� ����� ����� �������:
        --m_length;

        return removedElem;                         //////// ����� ��� ����������
    }

public:
    BlockArray<T>& operator = (const BlockArray<T>& other)
    {
        for (int i = 0; i < other.length(); ++i)
            add(other.at(i));

        return *this;
    }

public:
    // void print(const std::string& suffix, const std::string& prefix ="", bool printSuffixAtLastElem =false, std::ostream& stream =std::cout, int from =0, int to =-1) //////////???
    // array.print(", ")
    // [.....], [.....], []
    // �������� � std::iostream ��� �������� �������, �������� �� delimeter
    void print(const std::string& delimeter, std::ostream& stream =std::cout, int from =0, int to =-1) //////////???
    {
        if (!length())                    return;
        if (from < 0 || from >= length()) return;
        if (to > length())                return;

        if (to <  0) to += length();
        if (to <= 0) return;                                    ///??

        for (int i = from; i <= to; ++i)
        {
            // if (i % (Block<T>::BlockSize) == 0 && i != 0)
            //     stream << "\n";
            // stream << "[" << i <<"] " << at(i) << (i == to ? "\n" : delimeter);
            stream << at(i) << (i == to ? "" : delimeter);
        }

    }

    friend std::ostream& operator << (std::ostream& out, const BlockArray<T>& blockArray) //////////???
    {
        int count = 0;
        if (!blockArray.length()) return out;

        for (int i = 0; i < blockArray.length(); ++i)
        {
            if (i % (Block<T>::BlockSize) == 0 && i != 0)
                 out << "\n";
            out << "[" << i <<"] " << blockArray.at(i) << (i == blockArray.length()-1 ? "" : ", ");
        }

        return out;
    }

protected:
    Block<T>* getBlockByElemIndex(int elemIndex) const
    {
        if (isEmpty())
            return nullptr;
        if (!isIndexValid(elemIndex))
            return nullptr;

        int blockNum = getBlockNumByElemIndex(elemIndex);

        Block<T>* block = m_head;
        while (blockNum-- > 0)
            block = block->nextBlock();

        return block;
    }

    int getBlockNumByElemIndex(int elemIndex) const
    {
        if (!isIndexValid(elemIndex))
            return InvalidIndex;

        return elemIndex / Block<T>::BlockSize;
    }

    int blockCount() const
    {
        return m_blockCount;
    }

    Block<T>* headBlock() const
    {
        return m_head;
    }

    Block<T>* tailBlock() const
    {
        return m_tail;
    }

    // ��������� �������� ������ �����, � ������� ��������� ������� � ������� elemIndex.
    // checkRange -- ����� �� ������ �������� ���������.
    int blockOffsetIndex(int elemIndex) const
    {
        return elemIndex % Block<T>::BlockSize;
    }

    Block<T>* appendBlock()
    {
        Block<T>* newBlock = new Block<T>();

        if (!m_head)
            m_tail = m_head = newBlock;
        else
        {
            m_tail->setNextBlock(newBlock);
            m_tail = m_tail->nextBlock();
        }

        ++m_blockCount;
        return m_tail;
    }

    bool removeBlock(Block<T>* block)                           ///////////�� ������� ����� ������� ������ ���������, ���� ������ ����� ���� ������� ���-�� ���������
    {
        if (!block) return false;

        Block<T>* b = headBlock();

        while (b && b->nextBlock() != block)
            b = b->nextBlock();

        if (!b) return false;

        b->setNextBlock(block->nextBlock());
        delete block;

        return true;
    }



protected:
    int       m_length     = 0;
    int       m_blockCount = 0;
    Block<T>* m_head       = nullptr;
    Block<T>* m_tail       = nullptr;
};
