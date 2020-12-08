#include<stdio.h>
#include<stdlib.h>




typedef struct Node {
	int data;
	struct Node *next;
}*pNode;


pNode creatNode() {

	pNode node = (pNode)malloc(sizeof(struct Node));
	if(node == NULL) {	
		printf("malloc allocating failed\n");
		return NULL;
	}

	node->data = 0;
	node->next = NULL;	
	
	printf("allocating successfully\n");	
	return node;
}

int InsertNode(pNode head, int pos, int data) {
	if(head == NULL) {
		printf("error! linked list not exists\n");
		return -1;
	}
	pNode pointer = head;
	int i = 0;
	for( i=0; i<pos; i++) {
		if(pointer == NULL) {
			printf("element of pos not exists\n");
			return -1;
		}	
		pointer = pointer->next;	
	}	
	
	pNode ele = malloc(sizeof(struct Node));
	if(ele == NULL) {
		printf("ele allicating failed]n");	
		return -1;
	}
	
	
	ele->data = data;
	ele->next = pointer->next;
	pointer->next = ele;	
	printf("insert successfully\n");
	return 1;

}

void TraverseNode(pNode head) {
	if(head == NULL) {
		printf("linked list head not exists\n");
		return;
	}
	printf("Here comes Travering\n");
	pNode link = head;
	int i=0;
	while(link->next != NULL) {
		printf("this is the %dth element: %d\n", i++, link->data);	
		link = link->next;
	}
	return;
}



int main() {

	printf("Please choose the length of linkedlist:\n");
	int length;
	pNode head = NULL;
	head = creatNode();	
	
	scanf("%d", &length);
	int i=0;
	for(; i<length; i++) {
		InsertNode(head, i, i);
	}

	TraverseNode(head);	



}
