#include <stdio.h>
#include <stdlib.h>
// #include <search.h>
#include <stdbool.h>
//left and right null -> leaf
//main root, branchs


typedef struct tree {
  int data;
  struct tree *left, *right;
}tree;

void printTreePreOrder(tree *root) {
  if (root) {
    printf("Value: %d, Left: %p, Right: %p, Current: %p\n", root->data, root->left, root->right, root);
    printTreePreOrder(root->left);
    printTreePreOrder(root->right);
  }
}

void printSymmetric(tree *root) {
  if (root) {
    printSymmetric(root->left);
    printf("Value: %d, Left: %p, Right: %p, Current: %p\n", root->data, root->left, root->right, root);
    printSymmetric(root->right);
  }
}

void printPosOrder(tree *root) {
  if (root) {
    printPosOrder(root->left);
    printPosOrder(root->right);
    printf("Value: %d, Left: %p, Right: %p, Current: %p\n", root->data, root->left, root->right, root);
  }
}


int getData(char string[]) {
  int data;
  printf("\n%s", string);
  scanf("%d", &data);
  return data;
}

void searchData(tree *root, int data, tree **ptr) {
  if (root) {
    *ptr = root;
    if(data > root->data) {
      root = root->right;
    }
    else {
      root = root->left;
    }
    searchData(root, data, ptr);
  }
}

void insertData(tree **root, int data) {
  tree *newData = (tree*)malloc(sizeof(tree)), *ptr = NULL;
  if (newData) {
    newData->data = data;
    if (*root == NULL) {
      *root = newData;
    }
    else {
      searchData(*root, data, &ptr);
      if (ptr->data < data) {
        ptr->right = newData;
      } else if(ptr->data > data) {
        ptr->left = newData;
      }
    }
    newData->right = NULL;
    newData->left = NULL;
  }
}

int menu() {
  int op;
  do {
    printf("\n1 - inserir na arvore\n2 - printar arvore pre ordem\n3 - printar arvore pos ordem");
    printf("\n4 - printar simetrica\n5 - fim\nEScolha uma opcao acima: ");
    scanf("%d", &op);
  } while(op > 5 || op < 1);
  return op;
}

int main() {
  tree *root = NULL;
  int option, data;
  do {
    option = menu();
    system("cls||clear");
    switch (option) {
      case 1:
        data = getData("Informe um valor: ");
        insertData(&root, data);
        break;
      case 2: 
        printTreePreOrder(root);
        break;
      case 3: 
        printPosOrder(root);
        break;
      case 4: 
        printSymmetric(root);
        break;
      case 5:
        printf("\nFIMMMMMMMMMMMMMMMMMMMMMM\n");
        break;
    }
  } while(option != 5);
  return 0;
}