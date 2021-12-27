#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
typedef struct Stack_tag { // структура стека
    int elem[20];
    int size;
} Stack_t;

void push(Stack_t *stack, const int value) { //добавление элеменета в стек
    stack->elem[stack->size] = value;
    stack->size++;
}

int pop(Stack_t *stack) {                   // удаление элемента из стека
    stack->size--;
    return stack->elem[stack->size];
}
int top(const Stack_t *stack) {             //значение верхнего элемента стека
    return stack->elem[stack->size - 1];
}

int empty(Stack_t *stack) {                // проверка стека на пустоту
  if(stack->size == 0)    return 1;
  else return 0;
}

int main()
{
    system("chcp 1251");
    system("cls");
    int n, i, j;
    int st = 0;
    Stack_t stack;
    stack.size = 0;// инициализаци€ стека
    char m[80];
    printf("¬ведите число вершин:");
    scanf("%d", &n);
    int *nodes; // массив вершин
    nodes= (int*)malloc(n*sizeof(int));
    for(i=0; i<n; i++){
        nodes[i]=0;
    }
    push(&stack,0);
    int smezh[n][n]; //матрица смежности
    printf("¬ведите матрицу смежности\n");
    for(i = st; i<n; i++){
        for(j = st; j<n; j++){
gt:         printf("[%d][%d] = ",i,j);
            if (!scanf("%d", &smezh[i][j])){
                printf("ќшибка, введите 1 или 0\n");
                j--;
                fflush(stdin);
            }
            else{    smezh[j][i]=smezh[i][j];
                if((smezh[i][j] == 1)||(smezh[i][j]==0)||(smezh[i][j]==-1)){
                    continue;
                }
                else {
                    printf("ќшибка, введите 1 или 0\n");
                    goto gt;
                }
            }
        }
        if(i!=(n-1))
            st++;
    }
    FILE *fp;
    printf("¬ведите название графа и его разрешение(.gv):");
    scanf("%s", m);
    fp = fopen(m,"w");
    fprintf(fp, "graph {");
    while(!empty(&stack)){
        int node = top(&stack); // берем вершину
        pop(&stack);
        if (nodes[node] == 2) continue;
        nodes[node] = 2; // отмечаем ее как посещенную
        for (int j = n-1; j >= 0; j--)
        { // провер€ем все смежные вершины дл€ нее
          if(smezh[node][j]== 1 && node == j){//провер€ем на петли
            fprintf(fp,"\"%d\" -- \"%d\";\n", node+1,j+1);
          }
          if (smezh[node][j] == 1 && nodes[j] != 2)
          { // если вершина смежна€ и не обнаружена
            push(&stack, j); // добавл€ем ее в cтек
            nodes[j] = 1; // отмечаем вершину как обнаруженную
            fprintf(fp,"\"%d\" -- \"%d\";\n", node+1,j+1);//записываем в файл
          }
        }
    }
    fprintf(fp,"}");
    return 0;
}
