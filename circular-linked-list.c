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

/* �޸� ���� */
int freeList(listNode* h){

	h->llink->rlink = h->rlink;  //��� h�� ���� ����� rlink�� h�� ������ ��带 ����Ű��
	h->rlink->llink = h->llink;  //��� h�� ������ ����� llink�� h�� ���� ��带 ����Ű��
	free(h);  //�޸� ��ȯ

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

	listNode* new = (listNode*)malloc(sizeof(listNode));  //�߰��� ��� new �޸� �Ҵ�
	new->key = key;
	new->llink = h->llink;  //h�� ���� ��带 new�� ���� ���� ����
	new->llink->rlink = new;  //new�� ���� ����� rlink�� new�� ����Ű��
	new->rlink = h;  //new�� ���� ��尡 h�� �ǰ� ����

	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {

	listNode* deleted = h->llink;  //h�� ���� ��带 deleted ����

	if(deleted == h) {  //���� �����ۿ� ������ �����޽��� ���
		printf("Deletion of head node is not permitted.");
		return 0;
	}

	freeList(deleted);  //deleted ��� ����

	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {

	listNode* new = (listNode*)malloc(sizeof(listNode));  //�߰��� ��� new �޸� �Ҵ�
	new->key = key;
	new->llink = h;  //new�� ���� ��带 h�� ����
	new->rlink = h->rlink;  //new�� ���� ��带 h�� ���� ���� ����
	h->rlink = new;  //h�� ���� ��带 new�� ����

	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {

	listNode* deleted = h->rlink;  //h�� ������ ��带 deleted ����

	if(deleted == h) {  //���� �����ۿ� ������ �����޽��� ���
		printf("Deletion of head node is not permitted.");
		return 0;
	}

	freeList(deleted);  //deleted ��� ����

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {

	listNode* now = h->rlink;
	listNode* prev = h->rlink;
	listNode* temp = h->rlink;

	



	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {

	listNode* new = (listNode*)malloc(sizeof(listNode));  //�ű� ��� new �޸� �Ҵ�
	new->key = key;
	
	listNode* now = h->rlink;  //����Ʈ�� �̵��� now ���

	if(now->rlink == h) {  //���� ����Ʈ�� ���������
		h->rlink = new;  //������� �¿� ��带 new��
		h->llink = new;
		new->llink = h;  //new�� �¿� ��带 ������
		new->rlink = h;
	}

	while(now->rlink != h) {  //�� ������ ���鼭
		if(new->key > now->key) {  //���� new�� key�� now�� key���� ũ��
			now->llink->rlink = new;  //now�� ���� ����� ���� ��带 new�� ����
			new->llink = now->llink;  //new�� llink�� now�� ���� ���� ����
			new->rlink = now;  //new�� rlink�� now�� ����
			now->llink = new;  //now�� llink�� new�� ����
		}
		now = now->rlink;  //�ƴϸ� ���� ���� �̵�
	}

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {

	listNode* now = h->rlink;  //����Ʈ�� �̵��� now ���

	if(now->rlink = h) {  //���� ����Ʈ�� ��������� �����޽��� ���
		printf("nothing to delete");
		return 0;
	}

	while(now->rlink != h) {  //�� ������ ���鼭
		if(now->key == key) {  //���� �Էµ� key�� ����� key�� ���ٸ�
			freeList(now);  //��� ��ȯ
			return 1;
		}
		else {
			now = now->rlink;  //�ƴϸ� ���� ���� �̵�
		}
	}

	return 0;
}

