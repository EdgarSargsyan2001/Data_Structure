#ifndef STACK_H
#define STACK_H

class Stack {
public:
  Stack(const int c);
  Stack(const Stack &st);
  ~Stack();

public:
  bool empty() const;
  bool full() const;
  char top() const;
  void push(char);
  void pop();
  int get_size() const;

private:
  int size;
  int capacity;
  char *data_array;
};

#endif