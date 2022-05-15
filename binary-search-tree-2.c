/*[2021076029] [장정환]
	수정사항
		1)stack의 MAXSize를 초과할경우? 예외처리?
		2)intialize를 먼저 할 필요없게 main에서 head동적할당
		3)delete에서 제거할 노드가 없을경우 메시지 출력
		4)*/
#include<stdio.h>
#include<stdlib.h>	//malloc, free

typedef struct node{	//tree의 노드를 구성
	int key;
	struct node *left;
	struct node *right;
}Node;

/*for stack*/
#define MAX_STACK_SIZE	20
Node* stack[MAX_STACK_SIZE];
int top=-1;

Node* pop();	//stack에서 top이 가리키는 노드반환 
void push(Node* aNode);	//aNode를 stack에 추가

/*for queue*/
#define MAX_QUEUE_SIZE	20
Node* queue[MAX_QUEUE_SIZE];
int front =-1;
int rear=-1;

Node* deQueue();
void enQueue(Node* aNode);	//circular queue에 Node를 추가

int initializeBST(Node** h);	//tree를 초기화

void recursiveInorder(Node* ptr);	//recursive inorder 방식 tree출력
void iterativeInorder(Node* ptr);	//iterative inorder 방식tree출력

void printStack();

int main()
{
	char command;	//menu선택
	int key;	
	/*root노드를 가리킬 헤드포인터 동적할당 및 초기화*/
	Node* head=(Node*)malloc(sizeof(Node));
	head->key=-9999;
	head->left=NULL;
	head->right=head;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf("%c",&command);

		switch(command){
			//tree초기화 (head를 간접참조로 바꾸기위해 주소를 넘겨준다)
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		//tree의 동적할당 해제
		case 'q': case 'Q':
			freeBST(head);		
			break;
		//입력받은 key값을 갖는 노드 tree에 추가
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);		
			break;
		//입력받은 key값을 가지는 노드가 있을경우 tree에서 제거
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;
		//recursive Inorder 방식으로 tree출력
		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		//itearative Inorder 방식을 tree출력
		case 't': case 'T':
			iterativeInorder(head->left);
			break;
		//levelOrder 방식으로 tree출력
		case 'l': case 'L':
			levelOrder(head->left);
			break;
		//stack출력
		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n      >>>>>   Concentration!!   <<<<<    \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}
	
