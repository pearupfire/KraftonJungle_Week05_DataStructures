
//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
///////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _QueueNode {
	BSTNode *data;
	struct _QueueNode *nextPtr;
}QueueNode; // You should not change the definition of QueueNode


typedef struct _queue
{
	QueueNode *head;
	QueueNode *tail;
}Queue; // You should not change the definition of queue

///////////////////////////////////////////////////////////////////////////////////

// You should not change the prototypes of these functions
void levelOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

BSTNode* dequeue(QueueNode **head, QueueNode **tail);
void enqueue(QueueNode **head, QueueNode **tail, BSTNode *node);
int isEmpty(QueueNode *head);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the level-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting level-order traversal of the binary search tree is: ");
			levelOrderTraversal(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void levelOrderTraversal(BSTNode* root)
{
	BSTNode *cur;
	Queue q;
	q.head = NULL;
	q.tail = NULL;
	
	if (root == NULL) // 루트가 없다면 종료
		return;
	
	enqueue(&q.head, &q.tail, root); // q에 루트 삽입

	while (!isEmpty(q.head)) // q가 비어있지 않을때 반복
	{
		cur = dequeue(&q.head, &q.tail); // q에 삽입된 노드 꺼내기 
		printf("%d ", cur->item); 		 // 현재 노드 출력

		if (cur->left != NULL)					  // 현재 노드에 왼쪽 자식이 있다면
			enqueue(&q.head, &q.tail, cur->left); // q에 삽입
		if (cur->right != NULL)			  		  // 현재 노드에 오른쪽 자식이 있다면
			enqueue(&q.head, &q.tail, cur->right);// q에 삽입
	}
}

///////////////////////////////////////////////////////////////////////////////

/// @brief 이진탐색트리에 새로운 값을 삽입하는 함수 (중복값 삽입x,)
/// @param node 트리의 루트 노드를 가리키는 이중 포인터
/// @param value 삽입할 정수 값
void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		// 동적 메모리 할당
		*node = malloc(sizeof(BSTNode));

		// 노드가 비어있으면 루트 노드에 삽입
		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		// 삽입 값이 노드보다 작다면
		if (value < (*node)->item)
		{
			// 노드의 왼쪽 자식으로 재귀 호출
			insertBSTNode(&((*node)->left), value);
		}
		// 삽입 값이 노드보다 크다면
		else if (value >(*node)->item)
		{
			// 노드의 오른쪽 자식으로 재귀 호출
			insertBSTNode(&((*node)->right), value);
		}
		else
			// 중복 값이면 리턴
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

// enqueue node
/// @brief bst 노드를 큐의 뒤쪽에 삽입하는 함수
/// @param headPtr 큐의 head를 가리키는 포인터
/// @param tailPtr 큐의 tail을 가리키는 포인터
/// @param node    큐에 삽입할 bst 노드
void enqueue(QueueNode **headPtr, QueueNode **tailPtr, BSTNode *node)
{
	// dynamically allocate memory
	// 새로운 큐 노드를 동적 할당
	QueueNode *newPtr = malloc(sizeof(QueueNode));

	// if newPtr does not equal NULL
	// 메모리 할당이 성공한 경우
	if (newPtr != NULL) {
		// 새 큐 노드에 전달받은 bst 노드포인터를 저장
		newPtr->data = node;
		// 새큐 노드의 다음 포인터 초기화
		newPtr->nextPtr = NULL;

		// if queue is empty, insert at head
		// 큐가 비어 있는 경우, head와 tail 모두 새 노드를 가리키도록 설정
		if (isEmpty(*headPtr)) {
			*headPtr = newPtr;
		}
		// 큐가 비어 있지 않다면 기존 tail 뒤에 새 노드를 연결
		else { // insert at tail
			(*tailPtr)->nextPtr = newPtr;
		}

		// tair 포인터를 새노드로 갱신
		*tailPtr = newPtr;
	}
	else {
		// 메모리 할당에 실패한 경우 오류 출력
		printf("Node not inserted");
	}
}

/// @brief 큐에서 BST노드를 하나 꺼내 반환
/// @param headPtr 큐의 head 포인터
/// @param tailPtr 큐의 tail 포인터
/// @return 큐에서 꺼낸 bst 노드 포인터를 반환
BSTNode* dequeue(QueueNode **headPtr, QueueNode **tailPtr)
{
	// headPtr이 가리키는 큐의 첫 노드에 저장된 bstnode 포인터를 가지고옴 
	BSTNode *node = (*headPtr)->data; 
	// head를 임시 포인터에 저장
	QueueNode *tempPtr = *headPtr;
	// headptr 다음 노드로 이동시켜 큐의 첫번째 노드를 제거
	*headPtr = (*headPtr)->nextPtr;

	// 큐가 비었다면 tail도 null로 설정
	if (*headPtr == NULL) {
		*tailPtr = NULL;
	}

	// 제거한 이전 head 노드를 메모라에서 해제
	free(tempPtr);

	// 큐에서 제거한 노드를 bstnode 포인터를 반환
	return node;
}

/// @brief 큐가 비어있는지 확인하는 함수
/// @param head 큐의 head 포인터
/// @return 큐가 비어있으면 1, 아니면 0을 반환
int isEmpty(QueueNode *head)
{
	return head == NULL;
}

/// @brief 이진탐색트리 삭제하는 함수
/// @param node 삭제할 노드 
void removeAll(BSTNode **node)
{
	// 노드가 널이 아니면
	if (*node != NULL)
	{
		// 노드의 왼쪽 자식을 재귀로 호출
		removeAll(&((*node)->left));
		// 노드의 오른쪽 자식을 재귀로 호출
		removeAll(&((*node)->right));
		// 자식노드의 끝부터 메모리 해제
		free(*node);
		// 노드 빈 값 처리
		*node = NULL;
	}
}
