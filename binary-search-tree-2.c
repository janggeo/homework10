/*[2021076029] [장정환]
	수정사항
		1)stack의 MAXSize를 초과할경우, 메시지 출력하고 returbn
		2)intialize를 먼저 할 필요없게 main에서 head동적할당
		3)freeBST함수 수정. tree에 head노드만 존재할 경우 head노드의 왼쪽 자식은 NULL,
			head->left == NULL로 변경*/
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
int freeBST(Node* head);
int insert(Node* head, int key);
int deleteNode(Node* head, int key);
void levelOrder(Node* ptr);

/*void printStack();	//stack 출력*/

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
		getchar();

		switch(command){
			//tree초기화 (head를 간접참조로 바꾸기위해 주소를 넘겨준다)
		case 'z': case 'Z':{
			initializeBST(&head);
			break;
		}
		//tree의 동적할당 해제
		case 'q': case 'Q':{
			freeBST(head);		
			break;
		}	
		//입력받은 key값을 갖는 노드 tree에 추가
		case 'i': case 'I':{
			printf("Your Key = ");
			scanf("%d", &key);
			getchar();// 버퍼비우기
			insert(head, key);		
			break;
		}
		//입력받은 key값을 가지는 노드가 있을경우 tree에서 제거
		case 'd': case 'D':{
			printf("Your Key = ");
			scanf("%d", &key);
			getchar();
			deleteNode(head, key);
			break;
		}
		//recursive Inorder 방식으로 tree출력
		case 'r': case 'R':{
			recursiveInorder(head->left);
			break;
		}
		//itearative Inorder 방식을 tree출력
		case 't': case 'T':{
			iterativeInorder(head->left);
			break;
		}
		//levelOrder 방식으로 tree출력
		case 'l': case 'L':{
			levelOrder(head->left);
			break;
		}
		//stack출력
		/*case 'p': case 'P':{
			printStack();
			break;
		}*/
		default:{
			printf("\n      >>>>>   Concentration!!   <<<<<    \n");
			break;
		}
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

int insert(Node* head, int key){
	/*tree에 새로추가할 노드 동적할당 및 초기화*/
	Node* newNode=(Node*)malloc(sizeof(Node));
	newNode->key=key;
	newNode->left=NULL;
	newNode->right=NULL;
	/*tree가 비어있을 경우*/
	if(head->left==NULL){
		head->left=newNode;	//새로운 노드를 root로 
		return 1;
	}

	Node* ptr=head->left;	//tree위를 옮겨다니며 탐색할 포인터
	Node* parentNode=NULL;	//ptr의 parentNode를 가리킬 포인터

	while(ptr !=NULL){//새로운 노드의 parentNode 구하기
		/*tree에 이미 key 값을 가지는 노드가 있을경우*/
		if(ptr->key ==key)return 1;	

		/*parentNode를 통해 ptr의 부모노드 참고*/
		parentNode=ptr;

		/*ptr의 key값이 새로운 노드의 key보다 작은경우 */
		if(ptr->key <key)
			ptr=ptr->right;	//가리키는 노드보다 큰값은 노드의 오른쪽 subtree으로 들어간다
		else
			ptr=ptr->left;	//가리키는 노드보다 작은값은 노드의 왼쪽 subtree로 들어간다
	}
	/*key값이 parentNode의 key보다 작으므로 왼쪽 자식으로 들어간다*/
	if(parentNode->key > key)
		parentNode->left=newNode;
	/*key값이 parentNode의 key보다 크기때문에 오른쪽 자식으로 들어간다*/
	else
		parentNode->right=newNode;
	
	return 1;
}

int deleteNode(Node* head, int key){
	/*root를 가리키는 head가 없거나 root노드가 없을경우*/
	if(head == NULL){
		printf("\n Nothing to delete!!\n");
		return -1;
	}
	if(head->left ==NULL){
		printf("\n Nothing to delete!!\n");
		return -1;
	}
	/*head->left is the root*/
	Node* root =head->left;

	Node* parent =NULL;
	Node* ptr =root;

	/*삭제할 ptr구하기*/
	while((ptr != NULL)&&(ptr->key !=key)){//key값을 가지는 노드를 찾거나 전부 탐색할동안 반복
		if(ptr->key !=key){
			parent = ptr;	/*save the parent*/
			if(ptr->key > key)	/*왼쪽자식이 더 작은 key 값을 가짐*/
				ptr=ptr->left;
			else
				ptr=ptr->right;	/*오른쪽 자식이 더 큰 key 값을 가짐*/
		}
	}
	/*못찾은 경우*/
	if(ptr ==NULL)
	{
		printf("No node for key [%d]\n",key);
		return -1;
	}

	/*찾은 경우*/
	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left==NULL && ptr->right ==NULL)
	{
		if(parent != NULL){
			if(parent->left ==ptr)	/*ptr이 parent의 왼쪽 자식*/
				parent->left=NULL;	/*NULL로 수정*/
			else					/*ptr이 parent의 오른쪽 자식*/
				parent->right=NULL;	/*NULL로 수정*/
		}
		else{/*ptr이 root 노드 인경우*/
			head->left =NULL;
		}
	free(ptr);
	return 1;
	}
	/**
	 * case 2: if the node to be deleted has one child
	 */
	if((ptr->left==NULL || ptr->right ==NULL))
	{
		Node* child;
		/*ptr의 자식과 parent를 연결하기위해 child에 저장*/
		if(ptr->left != NULL)
			child=ptr->left;
		else
			child=ptr->right;
		
		if(parent != NULL)
		{	
			/*ptr을 제외하고 연결*/
			if(parent->left == ptr)
				parent->left =child;
			else
				parent->right =child;
		}
		else{/*parent가 NULL, ptr이 root노드 */
			root = child;
		}
		free(ptr);
		return 1;
	}
	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */
	/*ptr이 왼쪽자식 오른쪽 자식 모두 가질경우.
		ptr을 대체할 노드를 찾아야한다.
		두가지 경우가 존재 
		1)ptr의 왼쪽 subtree에서 가장 큰값
		2)ptr의 오른쪽 subtree에서 가장 작은값
		2)을 사용하여 ptr의 대체노드를 찾는다.*/
	Node* candidate;
	parent = ptr;

	candidate=ptr->right;

	while(candidate->left != NULL)
	{	/*제일 작은 노드를 찾기*/
		parent=candidate;
		candidate=candidate->left;
	}
	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	/*candidate를 제외하고 연결*/
	if(parent->right == candidate)
		parent->right =candidate->right;
	else
		parent->left=candidate->right;
	
	/*ptr의 key 값을 candidate의 key 값으로 대체하고, candidate를 해제*/
	ptr->key=candidate->key;
	free(candidate);
	return 1;
}
void freeNode(Node* ptr)
{
	if(ptr){/*재귀적 호출로 tree의 Node 해제*/
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
		ptr=NULL;
	}
}

Node* pop()
{	/*top<0인경우 stack은 비어있는상태*/
	if(top<0) return NULL;
	return stack[top--];
}

void push(Node* aNode)
{	
	if(top>=MAX_STACK_SIZE){
		printf("Queue가 가득찼습니다");
		return;
	}
	/*stack에 추가전 top을 증가시켜준다*/
	stack[++top]=aNode;
}

/*void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
		i++;
	}
}*/

int freeBST(Node* head)
{
	/*tree에 head노드만 존재할경우*/
	if(head->left == NULL)
	{
		free(head);
		return 1;
	}
	/*p는 root노드 */
	Node* p = head->left;
	/*root노드를 넘겨줘서 tree를 전부 해제*/
	freeNode(p);
	/*head노드 해제*/
	free(head);
	return 1;
}

Node* deQueue()
{	/*queue가 비어있는 경우*/
	if(front==rear){
		return NULL;
	}
	/*front 위치 조정*/
	front=(front+1)% MAX_QUEUE_SIZE;
	return queue[front];
}

void enQueue(Node* aNode)
{	/*rear위치 조정*/
	rear=(rear+1)%MAX_QUEUE_SIZE;
	if(front == rear){
		return;
	}
	/*노드 삽입*/
	queue[rear]=aNode;
}
