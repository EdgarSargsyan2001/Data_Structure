#include "stack.h"

Stack::Stack(int c) : size(0) {
  if (c <= 0) {
    c = 100;
  }
  capacity = c;
  data_array = new char[capacity];
}

Stack::Stack(const Stack &st)
    : size(st.size), capacity(st.capacity), data_array(new char[capacity]) {
  for (int i = 0; i < size; i++) {
    data_array[i] = st.data_array[i];
  }
}

Stack::~Stack() { delete[] data_array; }

bool Stack::empty() const { return size == 0; }

bool Stack::full() const { return size == capacity; }
char Stack::top() const { return data_array[size - 1]; }

void Stack::push(char obj) {
  if (full()) {
    return;
  }
  data_array[size] = obj;
  size++;
}
void Stack::pop() {
  if (empty()) {
    return;
  }
  size--;
}
int Stack::get_size() const { return size; }

