#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
class c_exception : public std::exception {
 public:
  virtual const char * f() const throw() {
    return "The requested item does not exist.\n";
  }
};

template<typename T>
class LinkedList {
  friend class Tester;

 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL){};
    Node(const T & d, Node * n, Node * p) : data(d), next(n), prev(p){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }

  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }

  bool remove(const T & item) {
    if (head == NULL) {
      return false;
    }
    if (head->data == item) {
      Node * tmp = head->next;
      delete head;
      head = tmp;
      if (head != NULL) {
        head->prev = NULL;
      }
      else {
        tail = NULL;
      }
      size--;
      return true;
    }
    Node * curr = head;
    while (curr->next != NULL) {
      if (curr->next->data == item) {
        Node * tmp = curr->next->next;
        delete curr->next;
        curr->next = tmp;
        if (curr->next != NULL) {
          curr->next->prev = curr;
        }
        else {
          tail = curr;
        }
        size--;
        return true;
      }
      curr = curr->next;
    }
    return false;
  }
  T & operator[](int index) {
    if (index < 0 || index > size) {
      throw c_exception();
    }
    else {
      Node * curr = head;
      for (int i = 0; i < index; i++) {
        curr = curr->next;
      }
      return curr->data;
    }
  }
  const T & operator[](int index) const {
    if (index < 0 || index >= size) {
      throw c_exception();
    }
    else {
      Node * curr = head;
      for (int i = 0; i < index; i++) {
        curr = curr->next;
      }
      return curr->data;
    }
  }

  int find(const T & item) const {
    int index = 0;
    Node * curr = head;
    while (curr != NULL) {
      if (curr->data == item) {
        return index;
      }
      index++;
      curr = curr->next;
    }
    return -1;
  }
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * temp = rhs.tail;
    while (temp != NULL) {
      this->addFront(temp->data);
      temp = temp->prev;
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      while (head != NULL) {
        Node * temp = head->next;
        delete head;
        head = temp;
      }
      tail = NULL;
      size = 0;
      Node * curr = rhs.tail;
      while (curr != NULL) {
        this->addFront(curr->data);
        curr = curr->prev;
      }
      size = rhs.size;
    }
    return *this;
  }
  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
    tail = NULL;
    size = 0;
  }
  int getSize() const { return size; }
};

#endif
