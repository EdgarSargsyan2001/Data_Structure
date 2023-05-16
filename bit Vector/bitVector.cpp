#include <iostream>
#include <fstream>
#include <string>
#define DEBBUG

template <typename T>
struct bitVector
{
    const static int elementBitSize = sizeof(T) * 8;
    int capacity;
    int size;
    T *bitArray;
};

template <typename T>
void log_for_debbug(const std::string name, const bitVector<T> &p, bool clear = 0)
{

#ifdef DEBBUG
    std::fstream oFile;
    oFile.open("debbug_result.txt", clear ? std::ios::out : std::ios::app); // write
    if (!oFile.is_open())
    {
        std::cout << "error: can't open output flie\n";
        return;
    }

    oFile << "function name is : " << name << '\n';
    oFile << "element Bit Size is : " << p.elementBitSize << '\n';
    oFile << "capacity is : " << p.capacity << "\n";
    oFile << "size is : " << p.size << "\n";
    oFile << "all bits count are : " << p.size * p.elementBitSize << "\n";
    if (p.size)
    {
        oFile << "bit array is : ";
        for (int i = p.size - 1; i >= 0; --i)
        {
            for (int j = p.elementBitSize - 1; j >= 0; --j)
                oFile << ((p.bitArray[i] >> j) & 1);
        }
        oFile << "\n";
    }

    oFile << "\n";
    oFile.close();
#endif
}
template <typename T>
void bit_vector_ctor(bitVector<T> &p, int bitCount)
{
    p.capacity = (bitCount / bitVector<T>::elementBitSize);
    p.size = 0;
    p.bitArray = new T[p.capacity];
    log_for_debbug("bit Vector Ctor", p, true);
}

template <typename T>
void bit_vector_Dctor(bitVector<T> &p)
{
    log_for_debbug<T>("bit Vector Dctor", p);
    delete[] p.bitArray;
}

template <typename T>
void change_vector_size(bitVector<T> &p)
{
    log_for_debbug<T>("change_vector_size", p);
    p.capacity += (p.capacity == 0) ? 1 : p.capacity;
    T *bitArrayNew = new T[p.capacity];
    for (int i = 0; i < p.size; i++)
    {
        bitArrayNew[i] = p.bitArray[i];
    }
    delete[] p.bitArray;
    p.bitArray = bitArrayNew;
    bitArrayNew = nullptr;
}

template <typename T>
void push_back(bitVector<T> &p, int elem)
{
    log_for_debbug<T>("push_back", p);
    if (p.size == p.capacity)
    {
        change_vector_size(p);
    }
    p.bitArray[p.size] = elem;
    p.size++;
}

template <typename T>
T pop_back(bitVector<T> &p)
{
    log_for_debbug<T>("pop_back", p);
    return p.bitArray[--p.size];
}

template <typename T>
bool set_bit(bitVector<T> &p, int bitCount)
{
    log_for_debbug<T>("set_bit", p);
    if (bitCount >= (p.size * bitVector<T>::elementBitSize))
        return false;

    int index = bitCount / bitVector<T>::elementBitSize;
    int rem = bitCount % bitVector<T>::elementBitSize;
    // std::cout << index << "\n";
    // std::cout << rem << "\n";
    p.bitArray[index] |= (1 << rem);
    return true;
}
template <typename T>
bool reset_bit(bitVector<T> &p, int bitCount)
{
    log_for_debbug<T>("reset_bit", p);
    if (bitCount >= (p.size * bitVector<T>::elementBitSize))
        return false;

    int index = bitCount / bitVector<T>::elementBitSize;
    int rem = bitCount % bitVector<T>::elementBitSize;
    // std::cout << index << "\n";
    // std::cout << rem << "\n";
    p.bitArray[index] &= (~(1 << rem));

    return true;
}
template <typename K, typename T>
void print_bit_vector(const bitVector<T> &p)
{
    int size = (p.size * sizeof(T)) / sizeof(K);
    if (size == 0)
    {
        std::cout << "there aren't that many bits\n";
        return;
    }
    // std::cout << "size -> " << size << "\n";
    K *ptr = (K *)p.bitArray;
    for (int i = 0; i < size; i++)
    {
        std::cout << *ptr << " ";
        ptr++;
    }
}

int main()
{
    struct bitVector<char> MyBV;
    const short cellCount = 4;
    bit_vector_ctor(MyBV, 0);

    for (int i = 0; i < cellCount; i++)
    {
        push_back(MyBV, 0);
    }

    short setBits[] = {30, 29,28,27};
    for (int i = 0; i < sizeof(setBits) / 2; i++)
    {
        if (!set_bit(MyBV, setBits[i]))
            std::cout << "there isn't bit index-> " << setBits[i] << "\n";
    }
    std::cout << "capacity -> " << MyBV.capacity << "\n";
    std::cout << "size -> " << MyBV.size << "\n";

    print_bit_vector<float>(MyBV);
    bit_vector_Dctor(MyBV);



    return 0;
}