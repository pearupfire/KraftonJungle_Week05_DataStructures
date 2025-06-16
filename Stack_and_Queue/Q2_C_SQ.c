//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MIN_INT -1000
//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;	// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;	// You should not change the definition of LinkedList

typedef struct _stack
{
	LinkedList ll;
}Stack;  // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void createStackFromLinkedList(LinkedList *ll , Stack *stack);
void removeEvenValues(Stack *s);

void push(Stack *s , int item);
int pop(Stack *s);
int isEmptyStack(Stack *s);
void removeAllItemsFromStack(Stack *s);

void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	Stack s;

	c = 1;
	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initalize the stack as an empty stack
	s.ll.head = NULL;
	s.ll.size = 0;

	printf("1: Insert an integer into the linked list:\n");
	printf("2: Create the stack from the linked list:\n");
	printf("3: Remove even numbers from the stack:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			createStackFromLinkedList(&ll, &s); // You need to code this function
			printf("The resulting stack is: ");
			printList(&(s.ll));
			break;
		case 3:
			removeEvenValues(&s); // You need to code this function
			printf("The resulting stack after removing even integers is: ");
			printList(&(s.ll));
			removeAllItemsFromStack(&s);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItemsFromStack(&s);
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}


//////////////////////////////////////////////////////////////////////////////////

void createStackFromLinkedList(LinkedList *ll, Stack *s)
{
	removeAllItemsFromStack(s);
	ListNode *cur = ll->head;

	while (cur != NULL)
	{
		push(s, cur->item);
		cur = cur->next;
	}
}

void removeEvenValues(Stack *s)
{
	Stack temp; 		 // 홀수를 임시로 담을 스택
	temp.ll.head = NULL; // 초기화
	temp.ll.size = 0;

	while (!isEmptyStack(s)) // 스택이 안 비었다면
	{
		int value = pop(s);  // pop한 값을 value에

		if (value % 2 != 0)  // 홀수라면
			push(&temp, value); // 임시 스택에 push
	}
	
	while (!isEmptyStack(&temp)) // 임시 스택이 빌때까지
	{
		push(s, pop(&temp)); // 기존 스택에 임시 스택을 pop하면서 넣기
	}
}

//////////////////////////////////////////////////////////////////////////////////

/// @brief 스택 맨 위에 값 추가
/// @param s 값을 넣을 스택 포인터
/// @param item 추가할 정수
void push(Stack *s, int item)
{
	insertNode(&(s->ll), 0, item); 
}

/// @brief 스택의 맨 위 값을 제거하고 반환
/// @param s 값을 꺼낼 스택 포인터
/// @return 스택에서 꺼낸 정수 값, 스택이 비어있으면 -1000 반환
int pop(Stack *s)
{
	int item;
	if (s->ll.head != NULL)
	{
		item = ((s->ll).head)->item;
		removeNode(&(s->ll), 0);
		return item;
	}
	else
		return MIN_INT;
}

/// @brief 스택이 비어있는지 확인
/// @param s 
/// @return 비어있으면 1, 아니면 0
int isEmptyStack(Stack *s)
{
	if ((s->ll).size == 0)
		return 1;
	else
		return 0;
}

/// @brief 스택의 모든 항목 제거 및 메모리 해제
/// @param s 
void removeAllItemsFromStack(Stack *s)
{
	if (s == NULL)
		return;
	while (s->ll.head != NULL)
	{
		pop(s);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

/// @brief 연결 리스트를 모두 출력
/// @param ll 연결 리스트 포인터
void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

/// @brief 연결 리스트의 모든 노드를 제거하고 메모리 해제
/// @param ll 연결 리스트 포인터
void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

/// @brief 연결 리스트에 주어진 인덱스 해당 노드를 찾음
/// @param ll 
/// @param index 찾을 노드의 인덱스
/// @return 해당 노드 포인터, 존재하지 않으면 NULL 반환
ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

/// @brief 연결 리스트의 지정된 인덱스에 값을 가진 새 노드를 삽입
/// @param ll 대상 연결 리스트 포인터
/// @param index 삽입할 위치
/// @param value 삽입할 값
/// @return 성공 0, 실패 -1
int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		if (ll->head == NULL)
		{
			exit(0);
		}
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		if (pre->next == NULL)
		{
			exit(0);
		}
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

/// @brief 연결 리스트 지정된 인덱스 노드 제거
/// @param ll 연결리스트 포인터
/// @param index 제거할 인덱스
/// @return 성공 0, 실패 -1
int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}