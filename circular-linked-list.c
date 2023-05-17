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

/* 메모리 해제 */
int freeList(listNode* h){

	h->llink->rlink = h->rlink;  //노드 h의 왼쪽 노드의 rlink를 h의 오른쪽 노드를 가리키게
	h->rlink->llink = h->llink;  //노드 h의 오른쪽 노드의 llink를 h의 왼쪽 노드를 가리키게
	free(h);  //메모리 반환

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

	listNode* new = (listNode*)malloc(sizeof(listNode));  //추가할 노드 new 메모리 할당
	new->key = key;
	new->llink = h->llink;  //h의 이전 노드를 new의 이전 노드로 설정
	new->llink->rlink = new;  //new의 이전 노드의 rlink가 new를 가리키게
	new->rlink = h;  //new의 다음 노드가 h가 되게 설정

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	listNode* deleted = h->llink;  //h의 왼쪽 노드를 deleted 노드로

	if(deleted == h) {  //만약 헤드노드밖에 없으면 오류메시지 출력
		printf("Deletion of head node is not permitted.");
		return 0;
	}

	freeList(deleted);  //deleted 노드 삭제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* new = (listNode*)malloc(sizeof(listNode));  //추가할 노드 new 메모리 할당
	new->key = key;
	new->llink = h;  //new의 이전 노드를 h로 설정
	new->rlink = h->rlink;  //new의 다음 노드를 h의 다음 노드로 설정
	h->rlink = new;  //h의 다음 노드를 new로 수정

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	listNode* deleted = h->rlink;  //h의 오른쪽 노드를 deleted 노드로

	if(deleted == h) {  //만약 헤드노드밖에 없으면 오류메시지 출력
		printf("Deletion of head node is not permitted.");
		return 0;
	}

	freeList(deleted);  //deleted 노드 삭제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

	listNode* now = h->rlink;
	listNode* prev = h->rlink;
	listNode* temp = h->rlink;

	



	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	listNode* new = (listNode*)malloc(sizeof(listNode));  //신규 노드 new 메모리 할당
	new->key = key;
	
	listNode* now = h->rlink;  //리스트를 이동할 now 노드

	if(now->rlink == h) {  //만약 리스트가 비어있으면
		h->rlink = new;  //헤드노드의 좌우 노드를 new로
		h->llink = new;
		new->llink = h;  //new의 좌우 노드를 헤드노드로
		new->rlink = h;
	}

	while(now->rlink != h) {  //한 바퀴를 돌면서
		if(new->key > now->key) {  //만약 new의 key가 now의 key보다 크면
			now->llink->rlink = new;  //now의 이전 노드의 다음 노드를 new로 수정
			new->llink = now->llink;  //new의 llink를 now의 이전 노드로 설정
			new->rlink = now;  //new의 rlink를 now로 설정
			now->llink = new;  //now의 llink를 new로 설정
		}
		now = now->rlink;  //아니면 다음 노드로 이동
	}

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	listNode* now = h->rlink;  //리스트를 이동할 now 노드

	if(now->rlink = h) {  //만약 리스트가 비어있으면 오류메시지 출력
		printf("nothing to delete");
		return 0;
	}

	while(now->rlink != h) {  //한 바퀴를 돌면서
		if(now->key == key) {  //만약 입력된 key와 노드의 key가 같다면
			freeList(now);  //노드 반환
			return 1;
		}
		else {
			now = now->rlink;  //아니면 다음 노드로 이동
		}
	}

	return 0;
}

