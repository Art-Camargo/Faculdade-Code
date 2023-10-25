#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
  int data;
  struct tree *left, *right;
}tree;

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

int treeHeight(tree *root) {
  int leftHeight, rightHeight;
  if (root == NULL) {
    return 0;
  } else {
    leftHeight = treeHeight(root->left);
    rightHeight = treeHeight(root->right);
    if (leftHeight > rightHeight) {
      return 1 + leftHeight;
    }
    return 1 + rightHeight;
  }
}

int menu() {
  int op;
  do {
    printf("\n\t1 - inserir na arvore\n\t2 - printar simetrica");
    printf("\n\t3 - calcular altura da arvore\n\t4 - fim\n\tEScolha uma opcao acima: ");
    scanf("%d", &op);
  } while(op > 5 || op < 1);
  return op;
}

void printSymmetric(tree *root) {
  if (root) {
    printSymmetric(root->left);
    printf("Value: %d, Left: %p, Right: %p, Current: %p\n", root->data, root->left, root->right, root);
    printSymmetric(root->right);
  }
}

int main() {
  tree *root = NULL;
  int option, data;
  do {
    option = menu();
    system("clear||cls");
    switch (option) {
      case 1:
        data = getData("Informe o dado: ");
        insertData(&root, data);
        break;
      case 2:
        printSymmetric(root);
        break;
      case 3:
        printf("\n\tAltura da arvore ->->-> %d", treeHeight(root) - 1);
        break;
      default: 
        printf("\nFim\n");
    }
  } while(option != 4);
  return 0;
}
