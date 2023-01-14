#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t myqueue;
  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      myqueue.push(new Node(i, counts[i]));
    }
  }
  if (myqueue.size() == 0) {
    return NULL;
  }
  while (myqueue.size() > 1) {
    Node * left = myqueue.top();
    myqueue.pop();
    Node * right = myqueue.top();
    myqueue.pop();
    Node * tree = new Node(left, right);
    myqueue.push(tree);
  }
  return myqueue.top();
}
