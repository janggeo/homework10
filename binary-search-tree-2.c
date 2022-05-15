/*[2021076029] [장정환]
	수정사항
		1)stack의 MAXSize를 초과할경우? 예외처리?
		2)intialize를 먼저 할 필요없게 main에서 head동적할당
		 */
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

void printStack();	//stack 출력

int main()
{
	printf("-----[2021076029] [장정환]-----");
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
		printf(" Initialize BST       = z       \n");
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

int initializeBST(Node** h){
	/*tree가 비어있지 않는 경우*/
	if(*h != NULL)
		freeBST(*h);
	/*head를 새롭게 동적할당 및 초기화*/
	*h=(Node*)malloc(sizeof(Node));
	(*h)->left=NULL; //root
	(*h)->right=*h;
	(*h)->key=-9999;

	/*stack의 top과 queue의 front,rear도 초기화*/
	top=-1;
	front=rear=-1;

	return 1;
}

void recursiveInorder(Node* ptr)
{	/*재귀적 중위순회 방식으로 출력*/
	if(ptr){
		recursiveInorder(ptr->left);
		printf(" [%d] ",ptr->key);
		recursiveInorder(ptr->right);
	}
}
void iterativeInorder(Node* node)
{
	for(;;)//무한 루프
	{
		for(; node; node = node->left){ //node가 null이 아닌동안 
			push(node);	//stack에 node를 추가
		}
		node=pop();	//stack에서 top이 가리키는 node를 꺼낸다
		
		if(!node) break; //stack에서 꺼낸게 없을 시 break
		printf(" [%d] ",node->key);

		node= node->right;
	}
}
void levelOrder(Node* ptr)
{	
	/*front와 rear 사용전 초기화*/
	front=-1;
	rear=-1;
	if(!ptr) return; /*empty tree*/

	enQueue(ptr);	//queue에 추가 

	/*queue를 이용해 childe보다 sibling을 먼저 방문*/
	for(;;)
	{
		ptr=deQueue();	/*먼저 넣은 Node 꺼낸다*/
		if(ptr){
			printf(" [%d] ",ptr->key);

			if(ptr->left)	/*왼쪽 자식 존재할경우 queue에 추가*/
				enQueue(ptr->left);
			if(ptr->right)	/*오른쪽 자식 존재할 경우 queue에 추가*/
				enQueue(ptr->right);
		}
		else	
			break;
	}
}

Node* pop()
{
	if(top<0) return NULL;
	return stak[top--];
}

void push(Node* aNode)
{
	++check;
	stack[++top]=aNode;
}
void printStack()
{
	int i = 0;
	printf("%d",check);
	printf("--- stack ---\n");
	while(i <= check)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
		i++;
	}
}
int freeBST(Node* head)
{
	/*head->right로 수정*/
	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}

