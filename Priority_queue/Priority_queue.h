#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <vector>

template <typename T>
class Priority_queue
{
public:
    Priority_queue() = default;
    Priority_queue(std::initializer_list<T> li);

    // insert
    void push(const T &val);

    // delete
    void pop();

    // methods
    bool empty();
    void change_priority(int i, T val);

    // getters
    size_t size() const;
    T &top();

private:
    void extractMax(int i);        // shiftUp
    void heapify(int size, int i); // shiftDown

private:
    std::vector<T> data;
};

template <typename T>
Priority_queue<T>::Priority_queue(std::initializer_list<T> li)
{
    for (T el : li)
    {
        push(el);
    }
}

// insert
template <typename T>
void Priority_queue<T>::push(const T &val)
{
    data.push_back(val);
    extractMax(data.size() - 1);
}

// delete
template <typename T>
void Priority_queue<T>::pop()
{
    if (!empty())
    {
        int endI = data.size() - 1;
        data[0] = data[endI];
        data.pop_back();

        heapify(--endI, 0);
    }
}

// methods
template <typename T>
bool Priority_queue<T>::empty()
{
    return data.size() == 0;
}

template <typename T>
void Priority_queue<T>::change_priority(int i, T val)
{
    if (i < 0 || i > data.size())
    {
        return;
    }

    int oldV = data[i];
    data[i] = val;

    if (val > oldV)
    {
        extractMax(i);
    }
    else
    {
        heapify(data.size(), i);
    }
}

// getters
template <typename T>
size_t Priority_queue<T>::size() const
{
    return data.size();
}

template <typename T>
T &Priority_queue<T>::top()
{
    return data[0];
}

template <typename T>
void Priority_queue<T>::extractMax(int currI)
{
    while (currI > 0)
    {
        int pi = (currI - 1) / 2;
        if (data[currI] <= data[pi])
        {
            break;
        }
        std::swap(data[currI], data[pi]);
        currI = pi;
    }
}

template <typename T>
void Priority_queue<T>::heapify(int size, int i)
{
    int largist = i;   // parent index
    int l = i * 2 + 1; // left child index
    int r = i * 2 + 2; // right child index

    if (l <= size && data[l] > data[largist])
        largist = l;

    if (r <= size && data[r] > data[largist])
        largist = r;

    if (largist != i)
    {
        std::swap(data[i], data[largist]);
        heapify(size, largist);
    }
}

#endif // PRIORITY_QUEUE_H