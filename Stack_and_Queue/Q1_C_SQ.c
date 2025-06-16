//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

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


typedef struct _queue
{
	LinkedList ll;
} Queue;  // You should not change the definition of Queue

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void createQueueFromLinkedList(LinkedList *ll, Queue *q);
void removeOddValues(Queue *q);

void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *q);
void removeAllItemsFromQueue(Queue *q);

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
	Queue q;

	c = 1;

	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initialize the Queue as an empty queue
	q.ll.head = NULL;
	q.ll.size = 0;


	printf("1: Insert an integer into the linked list:\n");
	printf("2: Create the queue from the linked list:\n");
	printf("3: Remove odd numbers from the queue:\n");
	printf("0: Quit:\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the List: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			createQueueFromLinkedList(&ll, &q); // You need to code this function
			printf("The resulting queue is: ");
			printList(&(q.ll));
			break;
		case 3:
			removeOddValues(&q); // You need to code this function
			printf("The resulting queue after removing odd integers is: ");
			printList(&(q.ll));
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItemsFromQueue(&q);
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

void createQueueFromLinkedList(LinkedList *ll, Queue *q)
{
	removeAllItemsFromQueue(q);
	ListNode *cur = ll->head;

	while (cur != NULL)
	{
		enqueue(q, cur->item);
		cur = cur->next;
	}
}

void removeOddValues(Queue *q)
{
	if (q == NULL) 
		return;
	
	ListNode *cur;	
	int totalSize = q->ll.size;
	int count = 0;

	while (count < totalSize)
	{
		int result = dequeue(q);

		if (result % 2 == 0)
			enqueue(q, result);

		count++;
	}
}

//////////////////////////////////////////////////////////////////////////////////

/// @brief 큐에 값 추가 (리스트의 끝에 삽입)
/// @param q 큐의 포인터
/// @param item 값
void enqueue(Queue *q, int item) 
{
	insertNode(&(q->ll), q->ll.size, item);
}

/// @brief 큐 값 제거 후 반환 (맨 앞에 제거)
/// @param q 
/// @return 제거된 정수 값 (큐가 비었다면 -1 반환)
int dequeue(Queue *q) 
{
	int item;

	// 큐가 비어있지 않는 경우에
	if (!isEmptyQueue(q)) {
		// 큐의 맨앞에 있는 값을 임시 저장
		item = ((q->ll).head)->item;
		// 연결 리스트의 첫 노드를 제거하여 큐에서 제거
		removeNode(&(q->ll), 0);
		// 제거된 값을 반환
		return item;
	}
	
	// 큐가 비어 있으면 -1 반환
	return -1;
}

/// @brief 큐가 비어 있는지 확인
/// @param q 
/// @return 비어있다면 1, 아니면 0
int isEmptyQueue(Queue *q) 
{
	// 큐의 연결 리스트 크기가 0이면 큐는 비어 있음
	if ((q->ll).size == 0)
		return 1;
	return 0;
}

/// @brief 큐의 모든 항복 제거
/// @param q 
void removeAllItemsFromQueue(Queue *q)
{
	int count, i;

	// 큐 포인터가 null이면 작업x
	if (q == NULL)
		return;
	
	// 현재 큐에 들어 있는 요소 수를 저장
	count = q->ll.size;

	// 큐의 요소 만큼 반복해서 제거
	for (i = 0; i < count; i++)
		dequeue(q);
}

/// @brief 큐의 연결 리스트 항목 출력
/// @param ll 
void printList(LinkedList *ll)
{
	ListNode *cur;

	// 예외 처리
	if (ll == NULL)
		return;
	
	// 현재 노드를 리스트의 head로
	cur = ll->head;

	// null이면 비었음 
	if (cur == NULL)
		printf("Empty");
	
	// null이 아니면, 모두 출력
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}

	printf("\n");
}

/// @brief 연결 리스트의 모든 노드를 제거하고 메모리 해제
/// @param ll 연결리스트의 포인터
void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	// 순회 하면서 메모리 해제
	while (cur != NULL)
	{
		tmp = cur->next; // 다음 노드 임시 저장
		free(cur);		 // 현재 노드 메모리 해제
		cur = tmp;		 // 다음 노드로 이동
	}

	// 리스트 상태 초기화
	ll->head = NULL; 
	ll->size = 0;
}

/// @brief 연결 리스트의 인덱스에 해당 노드 반환
/// @param ll 연결 리스트의 포인터
/// @param index 찾는 노드의 인덱스
/// @return 찾는 노드 포인터, 없으면 null
ListNode *findNode(LinkedList *ll, int index)
{
	ListNode *temp;

	// 리스트가 null, 인덱스 범위가 벗어난 경우 null 반환 (예외처리)
	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	// temp를 리스트의 head로 초기화
	temp = ll->head;

	// 예비 체크
	if (temp == NULL || index < 0)
		return NULL;

	// 원하는 인덱스까지 temp를 한칸 씩 다음 노드로 이동 
	while (index > 0)
	{
		temp = temp->next;

		// 이동 중에 null을 만나면 해당 노드가 없다는 뜻이므로 null 반환
		if (temp == NULL)
			return NULL;
		
		// 인덱스 감소
		index--;
	}

	// 해당 노드 포인터 반환 
	return temp;
}

/// @brief 연결 리스트의 주어진 위치에 새 노드를 삽입
/// @param ll 연결 리스트의 포인터
/// @param index 삽입할 위치
/// @param value 삽입할 값
/// @return 성공 시 0, 실패 시 -1
int insertNode(LinkedList *ll, int index, int value)
{
	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0)
	{
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		if (ll->head == NULL)
			exit(0);

		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		if (pre->next == NULL)
			exit(0);

		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

/// @brief 연결 리스트에서 주어진 인덱스의 노드 제거
/// @param ll 연결리스트 포인터
/// @param index 제거할 위치 
/// @return 성공 시 0, 실패 시 -1
int removeNode(LinkedList *ll, int index)
{
	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0)
	{
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{
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