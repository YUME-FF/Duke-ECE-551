#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    IntList il;
    il.addFront(1);
    assert(il[0] == 1);
    assert(il.head != NULL);
    assert(il.head == il.tail);
    assert(il.getSize() == 1);
    il.addFront(2);
    assert(il[0] == 2);
    assert(il[1] == 1);
    assert(il.getSize() == 2);
    assert(il.head->next->next == NULL);
    assert(il.head->next->prev == il.head);
    assert(il.tail == il.head->next);
  }
  void testAddBack() {
    IntList il;
    il.addBack(1);
    assert(il[0] == 1);
    assert(il.head != NULL);
    assert(il.head == il.tail);
    assert(il.getSize() == 1);
    il.addBack(2);
    assert(il[0] == 1);
    assert(il[1] == 2);
    assert(il.getSize() == 2);
    assert(il.head->next->next == NULL);
    assert(il.head->next->prev == il.head);
    assert(il.tail == il.head->next);
  }
  void testRule() {
    IntList il1;
    il1.addBack(1);
    il1.addFront(2);

    //Initial
    IntList il2(il1);
    assert(il2.getSize() == 2);
    assert(il2[0] == 2);
    assert(il2[1] == 1);
    assert(il2.head->next->next == NULL);
    assert(il2.head->next->prev == il2.head);
    assert(il2.tail == il2.head->next);

    //operater =
    IntList il3;
    il3 = il1;
    assert(il3.getSize() == 2);
    assert(il3[0] == 2);
    assert(il3[1] == 1);
    assert(il3.head->next->next == NULL);
    assert(il3.head->next->prev == il3.head);
    assert(il3.tail == il3.head->next);

    il1.addFront(3);
    il3 = il1;
    assert(il3.getSize() == 3);
    assert(il3[0] == 3);
    assert(il3[1] == 2);
    assert(il3[2] == 1);
    assert(il3.head->data == 3);
    assert(il3.tail->data == 1);
    assert(il3.tail->prev == il3.head->next);
    assert(il3.tail == il3.head->next->next);
  }
  void testRemove() {
    //il1:3213
    IntList il1;
    il1.addFront(3);
    il1.addFront(1);
    il1.addFront(2);
    il1.addFront(3);
    assert(il1[0] == 3);
    assert(il1[1] == 2);
    assert(il1[2] == 1);
    assert(il1[3] == 3);
    assert(il1.getSize() == 4);

    //il1: 3213 -> 213
    bool isRemove = il1.remove(3);
    assert(isRemove == true);
    assert(il1.getSize() == 3);
    assert(il1[0] == 2);
    assert(il1[1] == 1);
    assert(il1[2] == 3);
    assert(il1.head->data == 2);
    assert(il1.head->next->data == 1);
    assert(il1.head->next->prev == il1.head);

    //il1:213 -> 23
    bool isRemove2 = il1.remove(1);
    assert(isRemove2 == true);
    assert(il1.getSize() == 2);
    assert(il1[0] == 2);
    assert(il1[1] == 3);
    assert(il1.head->data == 2);
    assert(il1.head->next->data == 3);
    assert(il1.head->next->prev == il1.head);

    //il1:23 -> 23
    bool isRemove3 = il1.remove(5);
    assert(isRemove3 == false);
    assert(il1.getSize() == 2);
    assert(il1[0] == 2);
    assert(il1[1] == 3);

    //il1:23 -> 2
    bool isRemove4 = il1.remove(3);
    assert(isRemove4 == true);
    assert(il1.getSize() == 1);
    assert(il1[0] == 2);
    assert(il1.head->next == NULL);
    assert(il1.head->prev == NULL);
    assert(il1.head == il1.tail);

    //il1:2 -> NULL
    bool isRemove5 = il1.remove(2);
    assert(isRemove5 == true);
    assert(il1.getSize() == 0);
    assert(il1.head == NULL);
    assert(il1.tail == NULL);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testRule();
  t.testRemove();
  return EXIT_SUCCESS;
}
