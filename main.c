#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
typedef struct Stack_tag { // ��������� �����
    int elem[20];
    int size;
} Stack_t;

void push(Stack_t *stack, const int value) { //���������� ��������� � ����
    stack->elem[stack->size] = value;
    stack->size++;
}

int pop(Stack_t *stack) {                   // �������� �������� �� �����
    stack->size--;
    return stack->elem[stack->size];
}
int top(const Stack_t *stack) {             //�������� �������� �������� �����
    return stack->elem[stack->size - 1];
}

int empty(Stack_t *stack) {                // �������� ����� �� �������
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
    stack.size = 0;// ������������� �����
    char m[80];
    printf("������� ����� ������:");
    scanf("%d", &n);
    int *nodes; // ������ ������
    nodes= (int*)malloc(n*sizeof(int));
    for(i=0; i<n; i++){
        nodes[i]=0;
    }
    push(&stack,0);
    int smezh[n][n]; //������� ���������
    printf("������� ������� ���������\n");
    for(i = st; i<n; i++){
        for(j = st; j<n; j++){
gt:         printf("[%d][%d] = ",i,j);
            if (!scanf("%d", &smezh[i][j])){
                printf("������, ������� 1 ��� 0\n");
                j--;
                fflush(stdin);
            }
            else{    smezh[j][i]=smezh[i][j];
                if((smezh[i][j] == 1)||(smezh[i][j]==0)||(smezh[i][j]==-1)){
                    continue;
                }
                else {
                    printf("������, ������� 1 ��� 0\n");
                    goto gt;
                }
            }
        }
        if(i!=(n-1))
            st++;
    }
    FILE *fp;
    printf("������� �������� ����� � ��� ����������(.gv):");
    scanf("%s", m);
    fp = fopen(m,"w");
    fprintf(fp, "graph {");
    while(!empty(&stack)){
        int node = top(&stack); // ����� �������
        pop(&stack);
        if (nodes[node] == 2) continue;
        nodes[node] = 2; // �������� �� ��� ����������
        for (int j = n-1; j >= 0; j--)
        { // ��������� ��� ������� ������� ��� ���
          if(smezh[node][j]== 1 && node == j){//��������� �� �����
            fprintf(fp,"\"%d\" -- \"%d\";\n", node+1,j+1);
          }
          if (smezh[node][j] == 1 && nodes[j] != 2)
          { // ���� ������� ������� � �� ����������
            push(&stack, j); // ��������� �� � c���
            nodes[j] = 1; // �������� ������� ��� ������������
            fprintf(fp,"\"%d\" -- \"%d\";\n", node+1,j+1);//���������� � ����
          }
        }
    }
    fprintf(fp,"}");
    return 0;
}
