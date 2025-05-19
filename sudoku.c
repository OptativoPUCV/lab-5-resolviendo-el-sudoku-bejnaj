#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      int val = n->sudo[i][j];
      if (val == 0) continue;
      for (int k = 0; k < 9; k++) {
        if ((k != j && n->sudo[i][k] == val) || (k != i && n->sudo[k][j] == val))
          return 0;
      }
      int subcuadro = (i / 3) * 3 + (j / 3);
      for (int p = 0; p < 9; p++) {
        int RevisarI = 3 * (subcuadro / 3) + (p / 3);
        int RevisarJ = 3 * (subcuadro % 3) + (p % 3);
        if ((RevisarI != i || RevisarJ != j) && n->sudo[RevisarI][RevisarJ] == val)
          return 0;
      }
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  for (int i=0;i<9;i++){
    for (int j=0;j<9;j++){
      if (n->sudo[i][j]==0){
        for (int k=1;k<=9;k++){
          Node* posibleNodo = copy(n);
          posibleNodo->sudo[i][j] = k;
          if (is_valid(posibleNodo)) pushBack(list, posibleNodo);
        }
        return list;
      }
    }
  }
  return list;
}


int is_final(Node* n){
  for (int i=0;i<9;i++){
    for (int j=0;j<9;j++){
      if (n->sudo[i][j]==0)
        return 0;
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* stack = createStack();
  push(stack, initial);
  while (!is_empty(stack)){
    Node* n = top(stack);
    pop(stack);
    (*cont)++;
    if (is_final(n)){
      return n;
    }
    List* adj = get_adj_nodes(n);
    Node *node = first(adj);
    while (node != NULL){
      Node* newNode = (Node*) node;
      if (is_valid(newNode)){
        push(stack, newNode);
      }
      node = next(adj);
    }
    clean(adj);
  }
  return NULL;
}

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/