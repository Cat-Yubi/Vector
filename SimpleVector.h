#pragma once
#include <algorithm>
#include <stdexcept>

template<typename T>
void Safe_Delete_Array(T& pPointer)
{
    if (nullptr != pPointer)
    {
        delete[] pPointer;
        pPointer = nullptr;
    }
}

template <typename T>
class CSimpleVector : public CBase
{
private:
    T* m_Data = { nullptr };
    _int m_iCurrentSize = { 0 };
    _int m_iCapacity = { 10 };

public:
    CSimpleVector(_int iCapacity = 10);
    CSimpleVector(const CSimpleVector& other);
    virtual ~CSimpleVector();

    void Push_Back(const T& data);
    void Resize(_int newCapacity);
    _int Capacity() const;
    _int Size() const;
    void Clear();
    void Sort();

    T& operator[](_int index);
    T& At(_int index);
};

template<typename T>
CSimpleVector<T>::CSimpleVector(_int iCapacity)
{
    m_Data = new T[iCapacity];
    m_iCapacity = iCapacity;
    m_iCurrentSize = 0;
}

template<typename T>
CSimpleVector<T>::~CSimpleVector()
{
    Safe_Delete_Array(m_Data);
}

template<typename T>
CSimpleVector<T>::CSimpleVector(const CSimpleVector& other)
{
    m_iCapacity = other.m_iCapacity;
    m_iCurrentSize = other.m_iCurrentSize;
    m_Data = new T[m_iCapacity];

    for (_int i = 0; i < m_iCurrentSize; ++i)
        m_Data[i] = other.m_Data[i];
}

template <typename T>
void CSimpleVector<T>::Push_Back(const T& data)
{
    if (m_iCurrentSize >= m_iCapacity)
        Resize(m_iCapacity + 5);

    m_Data[m_iCurrentSize++] = data;
}

template <typename T>
void CSimpleVector<T>::Resize(_int newCapacity)
{
    if (newCapacity <= m_iCapacity)
        return;

    T* newData = new T[newCapacity];

    for (_int i = 0; i < m_iCurrentSize; ++i)
        newData[i] = m_Data[i];

    Safe_Delete_Array(m_Data);

    m_Data = newData;
    m_iCapacity = newCapacity;
}

template <typename T>
T& CSimpleVector<T>::At(_int index)
{
    if (index < 0 || index >= m_iCurrentSize)
        throw out_of_range("Index out of range"); //에러 날리기

    return m_Data[index];
}

template <typename T>
T& CSimpleVector<T>::operator[](_int index)
{
    return At(index);
}

template <typename T>
_int CSimpleVector<T>::Size() const
{
    return m_iCurrentSize;
}

template <typename T>
_int CSimpleVector<T>::Capacity() const
{
    return m_iCapacity;
}

template <typename T>
void CSimpleVector<T>::Clear()
{
    m_iCurrentSize = 0;
}

template <typename T>
void CSimpleVector<T>::Sort()
{
    sort(m_Data, m_Data + m_iCurrentSize);
}