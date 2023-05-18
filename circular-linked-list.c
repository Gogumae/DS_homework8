/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  School of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("                [----- [이찬희] [2019068057] -----]              \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 모든 메모리 해제 */
int freeList(listNode* h){

	listNode* now = h->rlink;  //리스트를 이동할 now 노드
	listNode* prev = NULL;  //now의 이전 노드

	while(now != h) {  //리스트를 한 바퀴 돌면서
		prev = now;  //prev를 now로 설정
		now = now->rlink;  //now를 다음 칸으로 이동
		free(prev);  //now였던 prev 메모리 반환
	}
	free(now);  //마지막 노드 메모리 반환

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	listNode* new = (listNode*)malloc(sizeof(listNode));  //새 노드 new 선언 및 메모리 할당
	new->key = key;
	new->llink = NULL;
	new->rlink = NULL;

	if(h->rlink == h) {  //만약 리스트가 비어있었으면 유일한 노드로 헤드노드와 연결
		new->llink = h;
		new->rlink = h;
		h->llink = new;
		h->rlink = new;

		return 1;
	}

	listNode* tail = h->llink;  //원래 마지막이었던 노드 tail
	new->llink = tail;  //새 노드의 llink가 tail을 가리키게 설정
	new->rlink = h;  //새 노드의 rlink가 헤드노드를 가리키게 설정
	tail->rlink = new;  //tail의 다음 노드가 새 노드가 되게 설정
	h->llink = new;  //헤드노드의 이전 노드가 새 노드가 되게 설정

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	listNode* del = h->llink;  //삭제할 노드 del
	listNode* tail = del->llink;  //삭제 후 마지막 노드가 될 tail

	if(del == h) {  //리스트가 비어있으면 오류메시지 출력
		printf("nothing to delete");
		return 1;
	}

	tail->rlink = h;  //마지막 노드가 될 tail의 다음 노드가 헤드노드가 되게 설정
	h->llink = tail;  //헤드노드의 이전 노드가 tail노드가 되게 설정

	free(del);  //삭제할 노드의 메모리 반환

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* new = (listNode*)malloc(sizeof(listNode));  //새 노드 new 선언 및 메모리 할당
	new->key = key;
	new->llink = NULL;
	new->rlink = NULL;

	listNode* sec = h->rlink;  //두번째 노드가 될 sec

	new->llink = h;  //새 노드의 llink가 헤드노드를 가리키게 설정
	new->rlink = sec;  //새 노드의 rlink가 두번째 노드가 될 sec을 가리키게 설정
	h->rlink = new;  //헤드노드의 다음 노드가 새 노드가 되게 설정
	sec->llink = new;  //두번째 노드의 이전 노드가 새 노드가 되게 설정

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	listNode* del = h->rlink;  //삭제할 노드 del
	listNode* fir = del->rlink;  //첫번째 노드가 될 fir

	if(del == h) {  //리스트가 비어있으면 오류메시지 출력
		printf("nothing to delete");
		return 1;
	}

	fir->llink = h;  //첫번째 노드의 이전 노드가 헤드노드가 되게 설정
	h->rlink = fir;  //헤드노드의 다음 노드가 첫번째 노드가 될 fir이 되게 설정

	free(del);  //삭제할 노드 del 메모리 반환

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {




	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	listNode* new = (listNode*)malloc(sizeof(listNode));  //새 노드 new 선언 및 메모리 할당
	new->key = key;
	new->llink = NULL;
	new->rlink = NULL;

	listNode* now = h->rlink;  //리스트를 이동할 now
	listNode* prev = NULL;  //now를 뒤따라갈 prev

	if(now == h) {  //리스트가 비어있었으면 유일한 노드로 헤드노드와 연결
		h->llink = new;
		h->rlink = new;
		new->llink = h;
		new->rlink = h;
		return 1;
	}

	while(now != h) {  //리스트를 한 바퀴 돌면서
		if(now->key >= new->key) {  //now의 key값이 입력한 key값보다 클 경우
			if(now == h->rlink) {  //근데 now가 첫번째 노드였다면
				insertFirst(h, key);  //첫번째 노드를 삽입하는 함수 사용
			}
			else {
				prev = now->llink;  //prev를 now의 이전 노드로 설정
				new->llink = prev;  //새 노드의 llink가 prev를 가리키게 설정
				new->rlink = now;  //새 노드의 rlink가 now를 가리키게 설정
				prev->rlink = new;  //prev의 다음 노드가 새 노드가 되게 설정
				now->llink = new;  //now의 이전 노드가 새 노드가 되게 설정
			}
			return 0;
		}

		now = now->rlink;  //다음 노드로 이동
	}

	insertLast(h, key);  //리스트에서 입력한 key값보다 큰 값을 찾지 못하면 리스트 마지막에 노드 삽입하는 함수 사용

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	listNode* now = h->rlink;  //리스트를 이동할 now
	listNode* prev = now->llink;  //now의 이전 노드 prev
	listNode* next = now->rlink;  //now의 다음 노드 next

	if(now == h) {  //리스트가 비어있었다면 오류메시지 출력
		printf("nothing to delete");
		return 1;
	}

	while(now != h) {  //리스트를 한 바퀴 돌면서
		if(now->key == key) {  //입력한 key값을 가진 노드를 찾으면
			prev->rlink = next;  //now의 이전 노드의 rlink를 now의 다음 노드를 가리키게 설정
			next->llink = prev;  //now의 다음 노드의 llink를 now의 이전 노드를 가리키게 설정
			free(now);  //now 노드 메모리 반환
			return 1;
		}
		prev = now;  //prev, now, next 노드를 한 칸 앞으로 이동
		now = now->rlink;
		next = now->rlink;
	}

	return 0;
}

