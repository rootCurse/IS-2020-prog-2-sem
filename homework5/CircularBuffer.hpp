#ifndef CH_H
#define CH_H
#include <iostream>
template<typename CBtype>
class CircularBuffer;

template<typename valType>
struct CBiterator
{
    using difference_type = std::ptrdiff_t;
    using value_type = valType;
    using pointer = valType*;
    using reference = valType&;
    using iterator_category = std::random_access_iterator_tag;
    template<typename CBtype>
    friend class CircularBuffer;
    valType* point;
    CBiterator(valType* point) :point(point) {}

    CBiterator(const CBiterator& it) :point(it.point) {}

    bool operator !=(CBiterator const& second) { return point != second.point; }

    bool operator ==(CBiterator const& second) { return point == second.point; }

    int operator-(CBiterator other) const 
    { 
        valType* temp = other.point;
        return *point - *temp;
    }

    typename CBiterator::reference operator*() const { return *point; }

    CBiterator& operator++()
    {
        ++point;

        return *this;
    }

    CBiterator& operator--()
    {
        --point;
        return *this;
    }
};



template<typename CBtype>
class CircularBuffer
{
private:
    CBtype* buffer;
    int capacity;
    int size;
    bool flagT, flagH;
public:
    typedef CBiterator<CBtype> iterator;
    typedef CBiterator<const CBtype> const_iterator;

    CircularBuffer(int cap)
    {
        buffer = new CBtype[cap];
        capacity = cap;
        size = 0;
        flagH = flagT = false;
    }

    bool isFull()
    {
        return size == capacity;
    }

    const_iterator begin() const
    {
        return const_iterator(&buffer[0]);
    }

    const_iterator end() const
    {
        return const_iterator(&buffer[size]);
    }

    void addFirst(CBtype element)
    {
        if (!flagH)
            buffer[0] = element;
        else
        {
            CBtype* temp = new CBtype[capacity];
            temp[0] = element;
            for (int i = 0; i < size; i++)
                temp[i + 1] = buffer[i];
            for (int i = 0; i < size + 1; i++)
                buffer[i] = temp[i];
        }
        size++;
        flagH =1;
    }

    void delFirst()
    {
        if (size == 1)
            buffer[0] = NULL;
        else
        {
            CBtype* temp = new CBtype[capacity];
            for (int i = 1; i < size; i++)
                temp[i - 1] = buffer[i];
            for (int i = 0; i < size - 1; i++)
                buffer[i] = temp[i];
            delete[] temp;
        }
        size--;
    }

    void addLast(CBtype element)
    {
        if (size == 0)
            buffer[0] = element;
        else
            buffer[size] = element;
        size++;
        flagT = 1;
    }

    CBtype first()
    {
        return buffer[0];
    }

    CBtype last()
    {
        return buffer[size - 1];
    }

    void delLast()
    {
        buffer[size - 1] = 0;
        size--;
    }

    CBtype& operator[](int index) const
    {
        if (index < 0 || index > size)
            throw std::exception("out of range");
        return buffer[index];
    }

    void changeCapacity(int cap)
    {
        CBtype* temp = new CBtype[cap];
        for (auto i = 0; i < cap; i++)
            temp[i] = buffer[i];
        capacity = cap;
        for (auto i = 0; i < capacity; i++)
            buffer[i] = temp[i];
    }

};


#endif // !CH_H