#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct data{
	
	char sim;
	struct data *next,*prev;
};

struct data *insert(char sim){
	
	struct data *newNode= (struct data*)malloc(sizeof(struct data));
	newNode->sim=sim;
	newNode->next=NULL;
	newNode->prev=NULL;
	
	return newNode;
}

void print(struct data *head){
	
	if(head){
		
		struct data *curr=head;
		while(curr){
			printf("%c",curr->sim);
			curr=curr->next;
		}
		
	}
	printf("\n");
}

void printPrev(struct data *tail){
	
	if(tail){
		
		struct data *curr=tail;
		while(curr){
			printf("%c",curr->sim);
			curr=curr->prev;
		}
		
	}
	printf("\n");
}

void pushTail(struct data **head, struct data **tail,char sim){
	
	struct data *newNode= insert(sim);
	
	if(!(*head)){
		*head=*tail=newNode;
	}else{
		(*tail)->next=newNode;
		newNode->prev=*tail;
		*tail=newNode;
	}
}

void popTail(struct data **head, struct data **tail){
	
	if(*head){
		
		if(*head==*tail){
			free(*tail);
			*tail=*head=NULL;
		}else{
				struct data *temp= *tail;
				*tail=(*tail)->prev;
				(*tail)->next=NULL;
				free(temp);
		}
	
	}
}


int main(){
	
	struct data *head1=NULL,*head2=NULL,*tail1=NULL,*tail2=NULL;
	char kata[110];
	gets(kata);
	
	int tanda[110]={};
	tanda['+']=1;
	tanda['-']=1;
	tanda['*']=2;
	tanda['/']=2;
	tanda['^']=2;
	
	
	//POSTFIX
	int i=0;
	while(kata[i]){
		
		
		if(kata[i]>='A'&&kata[i]<='Z'){
			pushTail(&head1,&tail1,kata[i]);
			
		}
		else if(kata[i]=='('){
			pushTail(&head2,&tail2,kata[i]);
		}
		else if(kata[i]==')'){
			while(tail2->sim!='('){
				pushTail(&head1,&tail1,tail2->sim);
				popTail(&head2,&tail2);
			}
			popTail(&head2,&tail2);
		}
		else{
			while(tail2 && tanda[kata[i]]<=tanda[tail2->sim]){
					
				pushTail(&head1,&tail1,tail2->sim);
				popTail(&head2,&tail2);
				}
		
			pushTail(&head2,&tail2,kata[i]);

		}
		i++;
	}
	while(tail2!=NULL){
		pushTail(&head1,&tail1,tail2->sim);
		popTail(&head2,&tail2);
		
	}
	
	struct data *head3=NULL,*tail3=NULL;
	
	printf("Postfix:");
	print(head1);
	
	//PREFIX
	i=strlen(kata)-1;
	while(kata[i]){
		
		
		if(kata[i]>='A'&&kata[i]<='Z'){
			pushTail(&head3,&tail3,kata[i]);
			
		}
		else if(kata[i]==')'){
			pushTail(&head2,&tail2,kata[i]);
		}
		else if(kata[i]=='('){
			while(tail2->sim!=')'){
				pushTail(&head3,&tail3,tail2->sim);
				popTail(&head2,&tail2);
			}
			popTail(&head2,&tail2);
		}
		else{
			while(tail2 && tanda[kata[i]]<tanda[tail2->sim]){
					
				pushTail(&head3,&tail3,tail2->sim);
				popTail(&head2,&tail2);
				}
		
			pushTail(&head2,&tail2,kata[i]);

		}
		i--;
	}

	while(tail2!=NULL){
		pushTail(&head3,&tail3,tail2->sim);
		popTail(&head2,&tail2);
		
	}

	printf("Prefix:");
	printPrev(tail3);
	
	
	return 0;
}
