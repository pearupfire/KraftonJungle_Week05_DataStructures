//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: 정렬된 링크 목록에 정수 삽입 (Insert an integer to the sorted linked list):\n");
	printf("2: 가장 최근 입력 값 인덱스 출력 (Print the index of the most recent input value):\n");
	printf("3: 정렬된 링크드 리스트 출력 (Print sorted linked list):\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("링크드 리스트에 추가할 정수를 입력하세요 (Input an integer that you want to add to the linked list): ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("연결된 목록 결과 (The resulting linked list is): ");
			printList(&ll);
			break;
		case 2:
			printf("인덱스에 값이 추가 되었습니다. (The value %d was added at index) %d\n", i, j);
			break;
		case 3:
			printf("연결된 목록 결과 (The resulting sorted linked list is): ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
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

/// @brief 정렬된 링크드 리스트에 삽입
/// @param ll 연결 리스트 포인터
/// @param item 삽입할 정수 값
/// @return 삽입된 인덱스 (실패 시 -1 반환)
int insertSortedLL(LinkedList *ll, int item)
{
	ListNode *cur;
	
	// 리스트가 비어 있는 경우
	if (ll->head == NULL)
	{
		insertNode(ll, 0, item); // 0번 인덱스에 삽입
		return 0;
	}

	cur = ll->head; // 현재 노드를 head로 초기화 
	int index = 0;  // 삽입할 위치 인덱스 변수

	// 리스트 순회하면서 삽입 위치 찾기
	while (cur != NULL)
	{ 
		// 중복된 값이 있다면 
		if (cur->item == item)
		{ 
			return -1; // 삽입 실패
		}

		// 현재 노드 값보다 작으면 해당 위치에 삽입
		if (item < cur->item)
		{
			insertNode(ll, index, item);
			return index; // 삽입 된 위치 반환
		}
		
		// 다음 노드로 이동
		cur = cur->next;
		// 인덱스 증가
		index++;
	}

	// 리스트 끝까지 탐색했을 경우
	insertNode(ll, index, item);
	return index;
}

///////////////////////////////////////////////////////////////////////////////////

/// @brief 연결 리스트 출력 함수
/// @param ll 
void printList(LinkedList *ll)
{
	ListNode *cur;

	// 연결 리스트가 없으면 종료
	if (ll == NULL)
		return;

	// 현재 노드를 리스트의 head 노드로 설정
	cur = ll->head;

	// 리스트가 비었다면 
	if (cur == NULL)
		printf("Empty");
	
	// 리스트의 null일때까지 각 노드의 값 출력
	while (cur != NULL)
	{
		printf("%d ", cur->item); // 현재 노드 데이터 출력
		cur = cur->next;		  // 다음 노드로 이동
	}
	printf("\n");
}

/// @brief 연결 리스트 초기화 함수
/// @param ll 
void removeAllItems(LinkedList *ll)
{
	// 현재 노드를 리스트의 첫 번째 노드로 설정
	ListNode *cur = ll->head;
	// 다음 노드를 임시 저장할 포인터
	ListNode *tmp;

	// 리스트가 null일때까지 반복
	while (cur != NULL)
	{
		tmp = cur->next; // 다음 노드를 tmp에 저장
		free(cur);		 // 현재 노드 메모리에서 해제
		cur = tmp;		 // 다음 노드를 현재 노드로 이동
	}
	ll->head = NULL; // 리스트가 비었다면 head를 null로 설정
	ll->size = 0; 	 // 리스트 크기 0으로 초기화
}

/// @brief 연결 리스트 
/// @param ll 찾을 연결 리스트 포인터
/// @param index 찾는 노드 인덱스
/// @return 인덱스 노드 포인터 반환, 없으면 null 반환
ListNode *findNode(LinkedList *ll, int index)
{
	ListNode *temp;

	// 리스트가 null 이거나 인덱스가 범위를 벗어나면 null 반환
	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	// 리스트의 첫 번째 노드를 temp에 저장
	temp = ll->head;

	// 리스트가 비어 있거나 인덱스가 음수인 경우 null 반환
	if (temp == NULL || index < 0)
		return NULL;

	// index 위치까지 temp를 다음 노드로 이동
	while (index > 0)
	{
		temp = temp->next;

		// 중간에 null이 나오면 잘못된 인덱스이므로 null 반환
		if (temp == NULL)
			return NULL;
		index--;
	}

	// 원하는 위치에 노드 포인터 반환
	return temp;
}

/// @brief 연결 리스트의 지정된 인덱스 위치에 새로운 노드 삽입
/// @param ll 노드를 삽입할 연결 리스트의 포인터
/// @param index index 삽입할 위치
/// @param value value 삽입할 노드의 값
/// @return 성공 시 0, 실패 시 -1
int insertNode(LinkedList *ll, int index, int value)
{
	ListNode *pre, *cur;

	// 리스트가 NULL이거나, 인덱스가 유효하지 않으면 삽입 실패
	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	// 리스트가 비어 있거나 맨 앞에 삽입하는 경우
	if (ll->head == NULL || index == 0)
	{
		cur = ll->head; // 기존 헤드를 백업 
		ll->head = malloc(sizeof(ListNode)); // 새 노드 생성
		ll->head->item = value;				 // 값 설정
		ll->head->next = cur;				 // 새 노드가 기존 헤드를 가리킴
		ll->size++;							 // 리스트 크기 증가
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	// 삽입할 위치 바로 앞 노드를 찾음
	if ((pre = findNode(ll, index - 1)) != NULL)
	{
		cur = pre->next;						// 기존  다음 노드 백업
		pre->next = malloc(sizeof(ListNode));   // 새 노드 생성
		pre->next->item = value;				// 값 설정
		pre->next->next = cur;					// 새 노드가 기존 다음 노드를 가리킴
		ll->size++;								// 리스트 크기 증가
		return 0;
	}

	return -1;
}

/// @brief 연결 리스트 지정된 인덱스 노드 제거
/// @param ll 
/// @param index 
/// @return 
int removeNode(LinkedList *ll, int index)
{
	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	// 첫 노드 제거하는 경우
	if (index == 0)
	{
		cur = ll->head->next; // 헤드 다음 노드를 저장
		free(ll->head);		  // 첫 번째 노드 메모리 해제
		ll->head = cur;		  // head를 두 번째 노드로 업데이트
		ll->size--;			  // 리스트 크기 감소

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	// 제거할 노드의 앞 노드를 찾았을 경우
	if ((pre = findNode(ll, index - 1)) != NULL)
	{
		// 예외 처리 
		if (pre->next == NULL)
			return -1;

		cur = pre->next; 	   // 제거할 노드를 가리킴
		pre->next = cur->next; // 앞 노드가 다음 노드를 가리키게 함
		free(cur);			   // 제거할 노드 메모리 해제
		ll->size--;			   // 리스트 사이즈 감소
		return 0;
	}

	return -1;
}