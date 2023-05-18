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
/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
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
		printf("                [----- [������] [2019068057] -----]              \n");
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

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* ��� �޸� ���� */
int freeList(listNode* h){

	listNode* now = h->rlink;  //����Ʈ�� �̵��� now ���
	listNode* prev = NULL;  //now�� ���� ���

	while(now != h) {  //����Ʈ�� �� ���� ���鼭
		prev = now;  //prev�� now�� ����
		now = now->rlink;  //now�� ���� ĭ���� �̵�
		free(prev);  //now���� prev �޸� ��ȯ
	}
	free(now);  //������ ��� �޸� ��ȯ

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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {

	listNode* new = (listNode*)malloc(sizeof(listNode));  //�� ��� new ���� �� �޸� �Ҵ�
	new->key = key;
	new->llink = NULL;
	new->rlink = NULL;

	if(h->rlink == h) {  //���� ����Ʈ�� ����־����� ������ ���� ������ ����
		new->llink = h;
		new->rlink = h;
		h->llink = new;
		h->rlink = new;

		return 1;
	}

	listNode* tail = h->llink;  //���� �������̾��� ��� tail
	new->llink = tail;  //�� ����� llink�� tail�� ����Ű�� ����
	new->rlink = h;  //�� ����� rlink�� ����带 ����Ű�� ����
	tail->rlink = new;  //tail�� ���� ��尡 �� ��尡 �ǰ� ����
	h->llink = new;  //������� ���� ��尡 �� ��尡 �ǰ� ����

	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {

	listNode* del = h->llink;  //������ ��� del
	listNode* tail = del->llink;  //���� �� ������ ��尡 �� tail

	if(del == h) {  //����Ʈ�� ��������� �����޽��� ���
		printf("nothing to delete");
		return 1;
	}

	tail->rlink = h;  //������ ��尡 �� tail�� ���� ��尡 ����尡 �ǰ� ����
	h->llink = tail;  //������� ���� ��尡 tail��尡 �ǰ� ����

	free(del);  //������ ����� �޸� ��ȯ

	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {

	listNode* new = (listNode*)malloc(sizeof(listNode));  //�� ��� new ���� �� �޸� �Ҵ�
	new->key = key;
	new->llink = NULL;
	new->rlink = NULL;

	listNode* sec = h->rlink;  //�ι�° ��尡 �� sec

	new->llink = h;  //�� ����� llink�� ����带 ����Ű�� ����
	new->rlink = sec;  //�� ����� rlink�� �ι�° ��尡 �� sec�� ����Ű�� ����
	h->rlink = new;  //������� ���� ��尡 �� ��尡 �ǰ� ����
	sec->llink = new;  //�ι�° ����� ���� ��尡 �� ��尡 �ǰ� ����

	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {

	listNode* del = h->rlink;  //������ ��� del
	listNode* fir = del->rlink;  //ù��° ��尡 �� fir

	if(del == h) {  //����Ʈ�� ��������� �����޽��� ���
		printf("nothing to delete");
		return 1;
	}

	fir->llink = h;  //ù��° ����� ���� ��尡 ����尡 �ǰ� ����
	h->rlink = fir;  //������� ���� ��尡 ù��° ��尡 �� fir�� �ǰ� ����

	free(del);  //������ ��� del �޸� ��ȯ

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {




	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {

	listNode* new = (listNode*)malloc(sizeof(listNode));  //�� ��� new ���� �� �޸� �Ҵ�
	new->key = key;
	new->llink = NULL;
	new->rlink = NULL;

	listNode* now = h->rlink;  //����Ʈ�� �̵��� now
	listNode* prev = NULL;  //now�� �ڵ��� prev

	if(now == h) {  //����Ʈ�� ����־����� ������ ���� ������ ����
		h->llink = new;
		h->rlink = new;
		new->llink = h;
		new->rlink = h;
		return 1;
	}

	while(now != h) {  //����Ʈ�� �� ���� ���鼭
		if(now->key >= new->key) {  //now�� key���� �Է��� key������ Ŭ ���
			if(now == h->rlink) {  //�ٵ� now�� ù��° ��忴�ٸ�
				insertFirst(h, key);  //ù��° ��带 �����ϴ� �Լ� ���
			}
			else {
				prev = now->llink;  //prev�� now�� ���� ���� ����
				new->llink = prev;  //�� ����� llink�� prev�� ����Ű�� ����
				new->rlink = now;  //�� ����� rlink�� now�� ����Ű�� ����
				prev->rlink = new;  //prev�� ���� ��尡 �� ��尡 �ǰ� ����
				now->llink = new;  //now�� ���� ��尡 �� ��尡 �ǰ� ����
			}
			return 0;
		}

		now = now->rlink;  //���� ���� �̵�
	}

	insertLast(h, key);  //����Ʈ���� �Է��� key������ ū ���� ã�� ���ϸ� ����Ʈ �������� ��� �����ϴ� �Լ� ���

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {

	listNode* now = h->rlink;  //����Ʈ�� �̵��� now
	listNode* prev = now->llink;  //now�� ���� ��� prev
	listNode* next = now->rlink;  //now�� ���� ��� next

	if(now == h) {  //����Ʈ�� ����־��ٸ� �����޽��� ���
		printf("nothing to delete");
		return 1;
	}

	while(now != h) {  //����Ʈ�� �� ���� ���鼭
		if(now->key == key) {  //�Է��� key���� ���� ��带 ã����
			prev->rlink = next;  //now�� ���� ����� rlink�� now�� ���� ��带 ����Ű�� ����
			next->llink = prev;  //now�� ���� ����� llink�� now�� ���� ��带 ����Ű�� ����
			free(now);  //now ��� �޸� ��ȯ
			return 1;
		}
		prev = now;  //prev, now, next ��带 �� ĭ ������ �̵�
		now = now->rlink;
		next = now->rlink;
	}

	return 0;
}

