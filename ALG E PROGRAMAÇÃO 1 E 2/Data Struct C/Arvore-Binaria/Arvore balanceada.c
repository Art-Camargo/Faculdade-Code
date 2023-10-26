#include <stdio.h>
#include <stdlib.h>
#define MENU_SIZE 7


#ifdef __linux 
#include <unistd.h>
#endif


#ifdef _WIN32
#include <windows.h>
#endif

/*
                ATIVIDADE ESCRITA 1 -> JULIO AUGUSTO E ARTUR DE CAMARGO!!!!!
                                               
↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧
↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧
↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧
↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧
↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧
↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧
↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧
↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧↧
                                                 está correto, caso haja algum char especial. <3
                              
a)          A           Nível 0     Altura 2    | b)        A       Nível 0     Altura 2
        /   |   \                               |         /   \
       B    C    D      Nível 1     Altura 1    |        B     C    Nível 1     Altura 1
     /   \       |                              |       / \    |
    E     F      G      Nível 2     Altura 0    |      D   E   F    Nível 2     Altura 0
                                                |
    i.   Grau dos nós:          2               |   i.   Grau dos nós:          2
    ii.  Grau da árvore:        3               |   ii.  Grau da árvore:        2
    iii. Folhas da árvore:      4               |   iii. Folhas da árvore:      3
    iv.  Raíz da árvore:        1               |   iv.  Raíz da árvore:        1
    v.   Nível 0:               3               |   v.   Nível 0:               2
         Nível 1:               3               |        Nível 1:               3
    vi.  Altura da árvore       2               |   vi.  Altura da árvore       2
    vii. É uma árvore binária? Não              |   vii. É uma árvore binária? Sim

    A altura máxima de uma árvore binária com n nós é:          n-1
    A altura mínima de uma árvore binária com n nós é:     log2 (n) - 1

↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥
↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥
↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥
↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥
↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥
↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥
↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥
↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥
↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥↥


*/



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

void mySleep(int sleepMs) {
  #ifdef linux 
      usleep(sleepMs * 1000);   
  #endif
  #ifdef _WIN32
      Sleep(sleepMs);
  #endif
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
    printf("\n\t3 - calcular altura da arvore\n\t4 - Quantidade de nos da arvore\n\t5 - Quantidade de folhas");
    printf("\n\t6 - remover as folhas\n\t7 - fim\n\tEScolha uma opcao acima: ");
    scanf("%d", &op);
  } while(op > MENU_SIZE || op < 1);
  return op;
}

void printSymmetric(tree *root) {
  if (root) {
    printSymmetric(root->left);
    printf("Value: %d, Left: %p, Right: %p, Current: %p\n", root->data, root->left, root->right, root);
    printSymmetric(root->right);
  }
}

int countNodeFromTree(tree *root) {
  if (root) {
    int leftCount, rightCount;
    leftCount = countNodeFromTree(root->left);
    rightCount = countNodeFromTree(root->right);
    return 1 + leftCount + rightCount;
  }
  return 0;
}

int countLeaveFromTree(tree *root) {
  if (root) {
    int leftCount, rightCount;
    leftCount = countLeaveFromTree(root->left);
    rightCount = countLeaveFromTree(root->right);
    if (!root->left && !root->right) {
      return 1;
    }
    return leftCount + rightCount;
  }
  return 0;
}

void removeLeaveFromTree(tree **root) {
  if (*root) {
    if (!(*root)->left && !(*root)->right) {
      free(root);
      *root = NULL;
    }
    else {
      removeLeaveFromTree(&(*root)->left);
      removeLeaveFromTree(&(*root)->right);
    }
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
      case 4: 
        printf("\nQuantidade de nos da arvore ->->-> %d", countNodeFromTree(root));
        break;
      case 5:
        printf("\nQuantidade de folhas de uma arvore ->->-> %d", countLeaveFromTree(root));
        break;
      case 6:
        printf("\nRemovendo as folhas das arvores...");
        mySleep(2000);
        removeLeaveFromTree(&root);
        break;
      default: 
        printf("\nFim\n");
    }
  } while(option != 7);
  return 0;
}
