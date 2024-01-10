#include <iostream>
#include <initializer_list>

template<typename T>
class Node {
public:
    T data;
    Node<T>* prev;
    Node<T>* next;

    Node(T value) {
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};


template <typename T>
class QueueBasedOnArray
{
public:
    using Iterator = T*;

    QueueBasedOnArray();
    explicit QueueBasedOnArray(unsigned size);
    QueueBasedOnArray(const QueueBasedOnArray& other);
    QueueBasedOnArray(QueueBasedOnArray&& other) noexcept;
    QueueBasedOnArray(std::initializer_list<T> ilist);
    ~QueueBasedOnArray();

    QueueBasedOnArray& operator=(const QueueBasedOnArray& other);
    QueueBasedOnArray& operator=(QueueBasedOnArray&& other) noexcept;
    QueueBasedOnArray& operator=(std::initializer_list<T> ilist);

    int GetSize() const;
    bool Push(const T& element);
    bool Pop(T& element);
    bool Peek(T& element);

    Iterator begin();
    const Iterator begin() const;
    Iterator end();
    const Iterator end() const;

    const T& operator[](int index) const;
    T& operator[](int index);

private:
    T* arr;
    int count;
};

template <typename T>
QueueBasedOnArray<T>::QueueBasedOnArray() : arr(nullptr), count(0) { }

template <typename T>
QueueBasedOnArray<T>::QueueBasedOnArray(unsigned size) : count(size)
{
    arr = new T[size];
}

template <typename T>
QueueBasedOnArray<T>::~QueueBasedOnArray()
{
    if (count > 0)
        delete[] arr;
}

template <typename T>
QueueBasedOnArray<T>::QueueBasedOnArray(const QueueBasedOnArray& other)
{
    arr = new T[other.count];
    count = other.count;
    for (int i = 0; i < count; ++i)
    {
        arr[i] = other.arr[i];
    }
}

template <typename T>
QueueBasedOnArray<T>::QueueBasedOnArray(QueueBasedOnArray&& other) noexcept
{
    arr = other.arr;
    count = other.count;
    other.arr = nullptr;
    other.count = 0;
}

template <typename T>
QueueBasedOnArray<T>::QueueBasedOnArray(std::initializer_list<T> ilist)
    : arr(new T[ilist.size()]), count(ilist.size())
{
    int i = 0;
    for (const auto& element : ilist)
    {
        arr[i++] = element;
    }
}

template <typename T>
int QueueBasedOnArray<T>::GetSize() const
{
    return count;
}

template <typename T>
bool QueueBasedOnArray<T>::Push(const T& element)
{
    T* temp = new T[count + 1];
    for (int i = 0; i < count; ++i)
    {
        temp[i] = arr[i];
    }
    temp[count] = element;

    delete[] arr;
    arr = temp;
    count++;

    return true;
}

template <typename T>
bool QueueBasedOnArray<T>::Pop(T& element)
{
    if (count == 0)
    {
        return false;
    }

    element = arr[0];
    for (int i = 0; i < count - 1; ++i)
    {
        arr[i] = arr[i + 1];
    }
    T* temp = new T[count - 1];
    for (int i = 0; i < count - 1; ++i)
    {
        temp[i] = arr[i];
    }

    delete[] arr;
    arr = temp;
    count--;

    return true;
}

template <typename T>
bool QueueBasedOnArray<T>::Peek(T& element)
{
    if (count == 0)
    {
        return false;
    }

    element = arr[0];
    return true;
}

template <typename T>
typename QueueBasedOnArray<T>::Iterator QueueBasedOnArray<T>::begin()
{
    return Iterator(arr);
}

template <typename T>
const typename QueueBasedOnArray<T>::Iterator QueueBasedOnArray<T>::begin() const
{
    return Iterator(arr);
}

template <typename T>
typename QueueBasedOnArray<T>::Iterator QueueBasedOnArray<T>::end()
{
    return Iterator(arr + count);
}

template <typename T>
const typename QueueBasedOnArray<T>::Iterator QueueBasedOnArray<T>::end() const
{
    return Iterator(arr + count);
}

template <typename T>
const T& QueueBasedOnArray<T>::operator[](int index) const
{
    return arr[index];
}

template <typename T>
T& QueueBasedOnArray<T>::operator[](int index)
{
    return arr[index];
}

template <typename T>
QueueBasedOnArray<T>& QueueBasedOnArray<T>::operator=(const QueueBasedOnArray& other)
{
    if (this != &other)
    {
        delete[] arr;
        arr = new T[other.count];
        count = other.count;
        for (int i = 0; i < count; ++i)
        {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

template <typename T>
QueueBasedOnArray<T>& QueueBasedOnArray<T>::operator=(QueueBasedOnArray&& other) noexcept
{
    if (this != &other)
    {
        delete[] arr;
        arr = other.arr;
        count = other.count;
        other.arr = nullptr;
        other.count = 0;
    }
    return *this;
}

template <typename T>
QueueBasedOnArray<T>& QueueBasedOnArray<T>::operator=(std::initializer_list<T> ilist)
{
    delete[] arr;
    arr = new T[ilist.size()];
    count = ilist.size();
    int i = 0;
    for (const auto& element : ilist)
    {
        arr[i++] = element;
    }
    return *this;
}

int main()
{
    // Тестирование конструкторов
    QueueBasedOnArray<int> queueDefault;
    QueueBasedOnArray<int> queueExplicit(5);
    QueueBasedOnArray<int> queueInitializer = { 10, 20, 30, 40, 50 };

    // Тестирование оператора присваивания для списка инициализации
    queueDefault = { 70, 1000, 1001 };

    // Тестирование методов Push, Pop, Peek
    queueDefault.Push(1050);
    queueDefault.Push(2500);
    queueDefault.Push(3555);

    int poppedValue;
    if (queueDefault.Pop(poppedValue))
        std::cout << "Popped value: " << poppedValue << std::endl;
    else
        std::cout << "Queue is empty, cannot pop." << std::endl;

    int peekedValue;
    if (queueDefault.Peek(peekedValue))
        std::cout << "Peeked value: " << peekedValue << std::endl;
    else
        std::cout << "Queue is empty, cannot peek." << std::endl;

    // Вывод размеров очередей
    std::cout << "The size of queueDefault: " << queueDefault.GetSize() << std::endl;
    std::cout << "The size of queueExplicit: " << queueExplicit.GetSize() << std::endl;
    std::cout << "The size of queueInitializer: " << queueInitializer.GetSize() << std::endl;

    // Вывод элементов очередей с использованием итераторов
    std::cout << "Elements of queueDefault: ";
    for (QueueBasedOnArray<int>::Iterator iter = queueDefault.begin(); iter != queueDefault.end(); ++iter)
        std::cout << *iter << " ";
    std::cout << std::endl;

    std::cout << "Elements queueInitializer: ";
    for (QueueBasedOnArray<int>::Iterator iter = queueInitializer.begin(); iter != queueInitializer.end(); ++iter)
        std::cout << *iter << " ";
    std::cout << std::endl;

    return 0;
}