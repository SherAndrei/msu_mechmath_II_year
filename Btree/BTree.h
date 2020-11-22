#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//
// Forward declrations:
//
template<class TKey, class TPayload>
class Node;

//
// Constants:
//
const int INVALID_INDEX      = -1;
const int MAX_NODE_ELEMS     = 200;
const int MAX_ARRAY_IN_BYTES = 800;

template<class TKey, class TPayload>
class Element
{
public:
    using TNode = Node<TKey, TPayload>;

public:
    Element() : m_subtree{ nullptr }
    {}

    Element(const TKey& key, const TPayload& payload)
        : m_subtree{ nullptr }
        , m_key    { key     }
        , m_payload{ payload }
    {}

public:
    /*inline*/ static Element createFailuredElem()
    {
        Element fe;
        fe.invalidate();
        return fe;
    }

// Operators:
public:
    bool operator == (const Element& other) const { return m_key == other.m_key; }
    bool operator >= (const Element& other) const { return m_key >= other.m_key; }
    bool operator <= (const Element& other) const { return m_key <= other.m_key; }
    bool operator >  (const Element& other) const { return m_key >  other.m_key; }
    bool operator <  (const Element& other) const { return m_key <  other.m_key; }

    Element& operator = (const Element& other)
    {
        // TODO: through setters
        m_key      = other.m_key;
        m_payload  = other.m_payload;
        m_subtree  = other.m_subtree;

        return *this;
    }

    bool isValid() const { return INVALID_INDEX != (int)((int*)subtree()); }
    void invalidate()    { setSubtree( (TNode*)INVALID_INDEX );            }

    void print() const;

// Getters + Setters:
public:
    TKey&           key()           { return m_key;     }
    const TKey&     key()     const { return m_key;     }
    
    TPayload&       payload()       { return m_payload; }
    const TPayload& payload() const { return m_payload; }

// Getters only:
    TNode*     subtree() const { return m_subtree; }

// Setters:
public:
    void setSubtree(TNode* newSubtree)
    {
        m_subtree = newSubtree;
    }

    Element<TKey,TPayload>& setByDefault()
    {
        return set(TKey{}, TPayload{});
    }

    Element<TKey,TPayload>& set(const Element& otherElem)
    {
        return set( otherElem.key(), otherElem.payload() );
    }
    Element<TKey,TPayload>& set(const TKey& newKey, const TPayload& newPayload)
    {
        m_key     = newKey;
        m_payload = newPayload;
        return *this;
    }

// Fields:
private:
    TKey     m_key;
    TPayload m_payload;
    TNode*    m_subtree;
};

// for ADL
template <class TKey, class TPayload>
void Element<TKey, TPayload>::print() const
{
    cout << "key = "     << m_key     << ";  "
         << "payload = " << m_payload << ";  "
         << "sub = " << ' ';
    if (subtree() && isValid())
        subtree()->print();
}


//===============================================================


template <class TElemKey,class TElemPayload>
class RootLinker
{
public:
    using TNode = Node <TElemKey, TElemPayload>;

// Constructors
public:
    RootLinker() : m_root{ nullptr }
    {}

   ~RootLinker()
    {
        // �� ������ :)
        if (root())
        {
            int count = root()->deleteAllSubtrees();
            //~ cout << endl << "~RootLinker(): count = " << count << endl;
            delete m_root;
        }
    }

// Methods:
public:
    TNode* root() const { return m_root; }
    void   setRoot(TNode* oldRoot, TNode* newRoot)
    {
        // root ������ ���� ������ ��� �� �����, �.�. � ����� ���� ������ ���� �� ���� �� ������.
        if (oldRoot != root())
            throw "Wrong old root in RootLinker::setRoot()";
        else
            m_root = newRoot;
    }

    TNode* createRoot()
    {
        if (root())
            return root();

        TNode* newRoot = new TNode(*this);
        setRoot(nullptr, newRoot);

        return root();
    }

protected:
    TNode* m_root;
};


template <class TKey, class TPayload>
class Node
{
public:
    using TElem       = Element    <TKey, TPayload>;
    using TRootLinker = RootLinker <TKey, TPayload>;

    const std::string Print_ElemMarginString = "  ";
    const std::string Print_NodeMarginString = "    ";

// Constructors:
public:
    //~ static int s_instanceCounter;

    Node() = delete;
    Node(TRootLinker& rootLinker)
        : m_root(rootLinker)
    {
        //~ cout << "Node::.ctor: s_instanceCounter = " << ++s_instanceCounter << endl;

        //int holderSize = MAX_NODE_ELEMS *sizeof(TElem) <= MAX_ARRAY_IN_BYTES
        //    ? MAX_NODE_ELEMS
        //    : MAX_ARRAY_IN_BYTES /sizeof(TElem);

        //// ������� �����/����?
        ////if (holderSize < 3)
        //    holderSize = 3;
        
        int holderSize = 4;
        m_holder.resize(holderSize);

        setElemCount(0);
        setParent(nullptr);

        insertSubtreeToZeroPos(nullptr);
    }

    ~Node()
    {
        //~cout << "Node::.dtor: s_instanceCounter = " << s_instanceCounter-- << endl;
    }

// Operators:
public:
    TElem& operator [] (int i) { return m_holder[i]; }

// Getters:
public:
    int elemCount() const { return m_elemCount; }

// Methods:
public:
    TElem& search(const TElem& desiredElem, Node*& lastVisitedNodePtr)
    {
        Node* current = this;

        if (!keyCount())
            current = nullptr;

        while (current)
        {
            lastVisitedNodePtr = current;

            if (current->elemCount() > 1 && desiredElem < current->m_holder[1])
                current = current->m_holder[0].subtree();
            else
            if (desiredElem > current->m_holder[current->elemCount()-1])
                current = current->m_holder[current->elemCount()-1].subtree();
            else
            {// �������� ����� �� ������

                int firstPos = 1;
                int lastPos  = current->lastElemPos();

                while (lastPos-firstPos > 1)
                {
                    int midPos = firstPos +(lastPos-firstPos)/2;
                    if (desiredElem >= current->m_holder[midPos])
                        firstPos = midPos;
                    else
                        lastPos = midPos;
                }

                if (current->m_holder[firstPos] == desiredElem)
                    return current->m_holder[firstPos];

                if (current->m_holder[lastPos]==desiredElem)
                    return current->m_holder[lastPos];
                else
                if (current->m_holder[lastPos]>desiredElem)
                    current = current->m_holder[firstPos].subtree();
                else
                    current = current->m_holder[lastPos].subtree();
            }
        }

        return FailuredElem;
    }

    bool treeInsert(const TElem& elem)
    {
        Node* lastVisitedNode = this;

        // ������� ��� � ������?
        TElem& found = search(elem, lastVisitedNode);
        bool is_valid = found.isValid();
        if (is_valid)
            return false;

        if (lastVisitedNode->insertToHolder(elem))
            return true;

        return lastVisitedNode->splitInsert(elem);
    }

    bool deleteElem(TElem& targetElem)
    {
        // ����� 1� ���� � targetElem.key
        Node* node = nullptr;
        TElem& found = search(targetElem, node);
        if (!found.isValid())
            return false;

        if (node->isLeaf() && node->keyCount() > node->minimumKeys())
            return node->deleteFromHolder(targetElem);
        else
        if (node->isLeaf())
        {
            node->deleteFromHolder(targetElem);

            // ��� ����� ������ �������� this ����� ����� �������.
            while (node)
            {
                if (node == node->findRoot() && node->isLeaf())
                    break;

                // �� ������, ���� root �������:
                if (node == node->findRoot() && !node->isLeaf())
                    throw "Node should not be root in deleteElement loop.";

                int thisParentIndex = INVALID_INDEX;

                // �������� ������� ����� ��� ��������:
                Node* rightNode = node->rightSibling(thisParentIndex);
                if (rightNode && rightNode->keyCount() > rightNode->minimumKeys())
                    node = node->rotateFromRight(thisParentIndex);
                else
                {
                    // �������� ������ ����� ��� ��������:
                    Node* leftNode = node->leftSibling(thisParentIndex);
                    if (leftNode && leftNode->keyCount() > leftNode->minimumKeys())
                        node = node->rotateFromLeft(thisParentIndex);
                    else
                    if (rightNode)
                        node = node->mergeRight(thisParentIndex);
                    else
                    if (leftNode)
                        node = node->mergeLeft(thisParentIndex);
                }
            }
        }
        else
        {
            TElem& smallestInSubtree = found.subtree()->smallestKeyInSubtree();
            found.set(smallestInSubtree);
            found.subtree()->deleteElem(smallestInSubtree);
        }

        return true;
    }

    // ������� -- ���������� �������� ���.
    int deleteAllSubtrees()
    {
        int deletedNodesNum = 0;

        for (int i = 0; i < elemCount(); i++)
        {
            Node* subtree = m_holder[i].subtree();
            if (!subtree)
                continue;

            if (subtree->isLeaf())
            {
                delete subtree;
                ++deletedNodesNum;
            }
            else
                deletedNodesNum += subtree->deleteAllSubtrees();
        }

        return deletedNodesNum;
    }

    Node* findRoot()
    {
        Node* current = this;
        while (current->parent())
            current = current->parent();

        return current;
    }

    int treeHeight(int& currentHeight) const;
    int calcFullPrintWidth(int& fullWidth) const;
    void printFamily(int& start) const;
    void printElementKeys() const;
    void print();

    std::vector<Node*> getChildren() const
    {
        std::vector<Node*> children;
        for (int i = 0; i < elemCount(); ++i)
            if (m_holder[i].subtree())
                children.push_back(m_holder[i].subtree());

        return children;
    }

    Node* findLeftLeaf()
    {
        if (isLeaf()) 
            return this;

        return m_holder[0].subtree()->findLeftLeaf();
    }

    Node* findLeftLeaf(int& level)
    {
        if (isLeaf()) return this;

        ++level;
        return m_holder[0].subtree()->findLeftLeaf(level);
    }

protected:
    bool isLeaf()  const { return m_holder[0].subtree() == nullptr; }
    bool isFull()  const { return elemCount() == m_holder.size()-1; }

    // ��������� �� ������� ������� (��� split)?
    bool isFullX() const { return elemCount() >= m_holder.size()-1; }

    // ������� � ������/������ ���������.
    // �������: true -- ������
    bool insertToHolder(const TElem& elem)
    {
        if (isFullX())
            return false;

        int i = elemCount();
        while (i > 0 && m_holder[i-1] > elem)
        {
            m_holder[i] = m_holder[i-1];
            --i;
        }

        if (elem.subtree())
            elem.subtree()->setParent(this);

        m_holder[i] = elem;
        ++m_elemCount;

        return true;
    }

    // ������� ����� ������� �������. ��������� ������ ������ �� splitInsert.
    // ������� true -- ��������.
    bool insertToHolderForSplit(const TElem& elem)
    {
        if (elemCount() >= m_holder.size())
            // The Big error!
            return false;

        int i = elemCount();
        while (i > 0 && m_holder[i-1] > elem)
        {
            m_holder[i] = m_holder[i-1];
            --i;
        }

        if (elem.subtree())
            elem.subtree()->setParent( this );

        m_holder[i] = elem;
        ++m_elemCount;

        return true;
    }

    bool splitInsert(const TElem& elem)
    {
        if (!isFull())
            // splitInstert ����� ���� ������ ������, ���� ���� ���������
            throw "Bad count of elements in splitInsert.";

        insertToHolderForSplit(elem);

        int splitPoint = elemCount() /2;
        if (splitPoint*2 < elemCount())
            ++splitPoint;

        // ����� ���� ���� ����� ��������.
        Node* newNode = new Node( root() );

        TElem upwardElem = m_holder[splitPoint];
        newNode->insertSubtreeToZeroPos( upwardElem.subtree() );

        // ��������� � �������� ����� ����:
        upwardElem.setSubtree( newNode );

        for (int i = 1; i < elemCount() -splitPoint; ++i)
            newNode->insertToHolder( m_holder[splitPoint+i] );

        newNode->setElemCount( elemCount()-splitPoint );
        setElemCount( splitPoint );
        newNode->setParent( parent() );

        // ������� ����� ���� � ��������, �������� � ����������:
        if (parent() && parent()->insertToHolder(upwardElem))
            return true;
        else
        if (parent() && parent()->splitInsert(upwardElem))
            return true;
        else
        // ��� ��� root?
        if (!parent())
        {
            Node* newRoot = new Node( root() );
            newRoot->insertSubtreeToZeroPos(this);

            this   ->setParent( newRoot );
            newNode->setParent( newRoot );

            newRoot->insertToHolder(upwardElem);
            setRootOfRoot(newRoot);

            newRoot->setParent(nullptr, false); // ??? deleteIfNullptr ?= false
        }

        return true;
    }

    // ������� ���� �� ������� �� ����� ���������.
    bool deleteFromHolder(TElem& targetElem)
    {
        int targetPos = -1;
        int firstPos  = 1;
        int lastPos   = lastElemPos();

        // ������ �������� �����:
        while (lastPos -firstPos > 1)
        {
            int mid = firstPos +(lastPos -firstPos) /2;
            if (targetElem >= m_holder[mid])
                firstPos = mid;
            else
                lastPos = mid;
        }

        if (m_holder[firstPos] == targetElem)
            targetPos = firstPos;
        else
        if (m_holder[lastPos] == targetElem)
            targetPos = lastPos;
        else
            return false;

        // ���� ���� ���������, �� ������� ��� ������������.
        //if (m_holder[i].subtree())
        //    delete m_holder[i].subtree();

        // �� ����� ������ �������� ������ � ������� targetPos.
        for (int i = targetPos; i < elemCount(); ++i)
            m_holder[i] = m_holder[i+1];

        --m_elemCount;

        return true;
    }

    // ������� ������� �� ������� �� �������.
    bool deleteFromHolder(int targetPos)
    {
        if (targetPos < 0 || targetPos >= elemCount()) // ??? check for isElemPosValid(): ">= m_elemCount"
            return false;

        // ���� ���� ���������, �� ������� ��� ������������.
        //if (m_holder[i].subtree())
        //    delete m_holder[i].subtree();

        // �� ����� ������ �������� ������ � ������� targetPos.
        for (int i = targetPos; i < elemCount(); ++i)
            m_holder[i] = m_holder[i+1];

        --m_elemCount;

        return true;
    }

    // ������� � ������� ������� �������.
    void insertSubtreeToZeroPos(Node* subtree)
    {
        m_holder[0].setSubtree(subtree);
        m_holder[0].setByDefault();

        setElemCount(1);

        if (subtree)
            subtree->setParent(this);
    }

    int lastElemPos() const { return elemCount()-1; }
    int keyCount()    const { return elemCount()-1; }

    TElem&       largestKey()        { return m_holder[lastElemPos()]; }
    TElem&       smallestKey()       { return m_holder[1];             }
    const TElem& smallestKey() const { return m_holder[1];             }

    // ���������� ����� ��������� ������� ������� � ���� � ������.
    TElem& smallestKeyInSubtree()
    {
        return isLeaf()
            ? m_holder[1]
            : m_holder[0].subtree()->smallestKeyInSubtree();
    }

    // ���������� ������ �������� (�������) � parent-�, ���� �� ��������� �� ��� ����.
    int subtreeIndexInParent() const
    {
        if (!parent())
            return INVALID_INDEX;

        int firstPos = 0;
        int lastPos  = parent()->lastElemPos();

        while (lastPos -firstPos > 1)
        {
            int midPos = firstPos +(lastPos-firstPos)/2;
            const TElem& smallest = smallestKey();
            if (smallest >= parent()->m_holder[midPos])
                firstPos = midPos;
            else
                lastPos = midPos;
        }

        if (parent()->m_holder[firstPos].subtree() == this)
            return firstPos;
        else
        if (parent()->m_holder[lastPos].subtree() == this)
            return lastPos;
        else
            throw "This node has not index in the parent().";
    }

// Siblings:
public:
    Node* leftSibling (int& thisParentIndex)
    {
        // ������� ���� ������ � parent()
        thisParentIndex = subtreeIndexInParent();
        if (thisParentIndex == INVALID_INDEX)
            return nullptr;

        if (thisParentIndex == 0)
            // ������ ����� ���:
            return nullptr;

        // ������� ����� ���� �� nullptr:
        return parent()->m_holder[thisParentIndex-1].subtree();
    }

    Node* rightSibling(int& thisParentIndex)
    {
        // ������� ���� ������ � parent()
        thisParentIndex = subtreeIndexInParent();
        if (thisParentIndex == INVALID_INDEX)
            return nullptr;

        if (thisParentIndex >= parent()->elemCount()-1)
            // ������� ����� ���:
            return nullptr;

        // ������� ����� ���� �� nullptr:
        return parent()->m_holder[thisParentIndex+1].subtree();
    }

// Rotates:
public:
    Node* rotateFromLeft (int thisParentIndex)
    {
        Node& parentRef = *parent();

        // ����� ������� ��� ���������� � ����:
        TElem underflowFiller = parentRef[thisParentIndex];

        // ������� ������� �����:
        Node& leftSibling = *parentRef[thisParentIndex-1].subtree();

        Node& self = *this;
        underflowFiller.setSubtree( self[0].subtree() );

        self[0].setSubtree( leftSibling[leftSibling.lastElemPos()].subtree() );

        if (self[0].subtree())
            self[0].subtree()->setParent( this );

        // ��������� ������� (��):
        parentRef[thisParentIndex] = leftSibling[leftSibling.lastElemPos()];

        // ��������������� ��� ���������:
        self[thisParentIndex].setSubtree( this );

        insertToHolder(underflowFiller);
        leftSibling.deleteFromHolder(leftSibling.lastElemPos());

        // ��� ���� parent ��� �������� ���� ���������� ���������:
        return nullptr;
    }

    Node* rotateFromRight(int thisParentIndex)
    {
        Node& parentRef = *parent();

        // ����� ������� ��� ���������� � ����:
        TElem underflowFiller = parentRef[thisParentIndex+1];

        // ������� ������� ������:
        Node& rightSibling = *( parentRef[thisParentIndex+1].subtree() );
        underflowFiller.setSubtree(rightSibling[0].subtree());

        // ��������� ������� (��):
        parentRef[thisParentIndex+1] = rightSibling[1];

        // ��������������� ��� ���������:
        parentRef[thisParentIndex+1].setSubtree(&rightSibling);

        insertToHolder(underflowFiller);
        rightSibling.deleteFromHolder(0);

        rightSibling[0].setByDefault();

        // ��� ���� parent ��� �������� ���� ���������� ���������
        return nullptr;
    }

// Merging:
public:
    // �������� �� � ������ � ����� �� ���� � ��������, � ����� ������� ����.
    // ������� -- ����� �� ��������.
    Node* mergeLeft(int thisParentIndex)
    {
        Node& parentRef = *parent();
        TElem parentElem = parentRef[thisParentIndex];

        parentElem.setSubtree( (*this)[0].subtree() );

        Node& leftSibling = *( parentRef[thisParentIndex-1].subtree() );

        leftSibling.insertToHolder (parentElem);
        for (int i = 1; i < elemCount(); ++i)
            leftSibling.insertToHolder(m_holder[i]);

        parentRef.deleteFromHolder(thisParentIndex);

        // �������� paretn ����� ��������� ����� ����:
        Node* savedParentNodePtr = parent();

        if (parent() == findRoot() && !parent()->keyCount())
        {
            setRootOfRoot( &leftSibling );
            setParent(nullptr);

            leftSibling.setParent(nullptr);

            delete this;
            return nullptr;
        }
        else
        if (parent() == findRoot() && parent()->keyCount())
        {
            delete this;
            return nullptr;
        }

        delete this;

        if (savedParentNodePtr->keyCount() >= savedParentNodePtr->minimumKeys())
            // �������� ������ �� �����:
            return nullptr;

        return savedParentNodePtr;
    }

    // �������� �� �� �������, � ����� ������� ���.
    // ������� ��������.
    Node* mergeRight(int thisParentIndex)
    {
        Node& parentRef = *parent();
        TElem parentElem = parentRef[thisParentIndex+1];

        Node& rightSibling = *( parentRef[thisParentIndex+1].subtree() );

        parentElem.setSubtree( rightSibling[0].subtree() );
        insertToHolder (parentElem);

        for (int i = 1; i < rightSibling.elemCount(); ++i)
            insertToHolder( rightSibling[i] );

        parentRef.deleteFromHolder( thisParentIndex+1 );

        delete &rightSibling;

        if (parent() == findRoot() && !parent()->keyCount())
        {
            setRootOfRoot( this );
            return /*nullptr*/ setParent(nullptr);
        }
        else
        if (parent() == findRoot() && parent()->keyCount())
            return nullptr;

        if (parent() && parent()->keyCount() >= parent()->minimumKeys())
            // �������� ������ �� �����:
            return nullptr;

        return parent();
    }

    // ���������� ���������� ����-�������.
    int minimumKeys() const
    {
        // ������� ������� �� ���� (����� ��� ����������).
        int size = m_holder.size();

        // ��������� � ������� �������:
        int ceiling_func = (size-1) /2;

        if (ceiling_func*2 < size-1)
            ++ceiling_func;

        return ceiling_func-1;
    }


// Convience's methods:
protected:


// Getters:
protected:
    Node*        parent() const { return m_parent;     }
    TRootLinker& root()         { return m_root;       }
    Node*        rootOfRoot()   { return root().root(); }

// Setters:
protected:
    Node* setParent(Node* newParent, bool deleteIfNullptr =true)
    {
        if (newParent == parent()) return parent();

        if (nullptr == newParent && deleteIfNullptr)
             delete m_parent;

        return (m_parent = newParent);
    }

    void setRootOfRoot(Node* newRoot)
    {
        RootLinker<TKey,TPayload>& r = root();
        r.setRoot( r.root(), newRoot );
    }

    void setElemCount(int newElemCount)
    {
        m_elemCount = newElemCount;
    }

// Fields:
protected:
    std::vector<TElem> m_holder;

    // ���-�� ��������� � ������� + ������� ������� (������ ��� ���������, ��� Elem).
    int m_elemCount;

    Node* m_parent;

    // ������� ��� �������� ������� ������ � �.�.
    static TElem FailuredElem;

    // �������� ��� ��������� ��������. �����, ����� �� �������� ��� � �������� �������� �����.
    TRootLinker& m_root;
};


// ������� ��� �������� ������� ������ � �.�.
template <class TKey, class TPayload>
Element <TKey, TPayload>    Node <TKey, TPayload>::FailuredElem = Element<TKey, TPayload>::createFailuredElem();

//template <class TKey, class TPayload>
//int Node<TKey, TPayload>::s_instanceCounter = 0;


template <class TKey, class TPayload>
void Node<TKey,TPayload>::print()
{
    if (this == rootOfRoot())
        cout << "__root__" << endl;
    else
        cout << endl;

    //cout << endl << "this = " << this << endl;
    cout << "parent is = " << parent() << " elems = " << elemCount() << endl;

    int i = 0;
    for (i = 0; i < elemCount(); ++i)
        m_holder[i].print();

    cout << endl;
}


//
// ����� -- ��� ������� �������.
//
template <class TKey, class TPayload>
int Node<TKey, TPayload>::treeHeight(int& currentHeight) const
{
    static int s_calledCounter = 0;
    cout << endl << "treeHeight::s_calledCounter = " << ++s_calledCounter << endl;

    ++currentHeight;

    if (isLeaf())
        return currentHeight;
    else
        return m_holder[0].subtree()->treeHeight(currentHeight);
}

template <class TKey, class TPayload>
int Node<TKey, TPayload>::calcFullPrintWidth(int& width) const
{
    if (!isLeaf() && elemCount() > 0)
    {
        for (int i = 0; i < elemCount(); ++i)
            if (m_holder[i].subtree())
                m_holder[i].subtree()->calcFullPrintWidth(width);

        return width;
    }

    int thisWidth = 0;

    for (int i = 0; i < elemCount(); ++i)
    {
        const TElem& elem = m_holder[i];
        string s = elem.key();
        thisWidth += s.length() + Print_ElemMarginString.length();
    }

    width += thisWidth + Print_NodeMarginString.length();

    return width;
}

template <class TKey, class TPayload>
void Node<TKey, TPayload>::printFamily(int& level) const
{
    static int printFamily_counter = 0;
    cout << "{" << ++printFamily_counter << "}";
    cout << "~" << level << "~";

    if (!parent())
        return;

    std::vector<Node*> siblings = parent()->getChildren();
    
    int i;
    for (i = 0; i < siblings.size(); ++i)
    {
        Node* sibl = siblings[i];

        sibl->printElementKeys();
    }

    cout << "<" << siblings.size() << ">";

    cout << endl;
    parent()->printFamily(++level);
}

template <class TKey, class TPayload>
void Node<TKey, TPayload>::printElementKeys() const
{
    cout << "[";
    for (int i = 0; i < m_holder.size(); ++i)
    {
        const TElem& elem = m_holder[i];
        cout << elem.key();
        if (i < m_holder.size() -1)
            cout << Print_ElemMarginString;
    }
    cout << "]";

    cout << Print_NodeMarginString;
}

