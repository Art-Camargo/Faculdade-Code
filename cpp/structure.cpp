#include <iostream>
class Node {
  public:
    int value;
    Node* next;
};

int getValue() {
  int value;
  std::cout << "Informe um valor inteiro: ";
  scanf("%d", &value);
  return value;
};

Node* createNode(bool withValue) {
  Node* newNode = new Node(); 
  newNode->next = nullptr;
  if (withValue) {
    int value = getValue();
    newNode->value = value;
  }
  return newNode;
}




int main() {
  Node *mainNode = createNode(false);
  
}