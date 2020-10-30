#include<stdio.h>
#include<stdlib.h>

struct data{
	int value;
	struct data *next;	
};

void view(struct data *head){
	
	if(head){
		struct data *curr= head;
		
		while(curr){
			printf("%d ",curr->value);
			curr= curr->next;
		}
		printf("\n");
	}
	else printf("No data!\n");
}

void pushHead(struct data **localHead,struct data **localTail, int value){
	
	struct data *newData =(struct data*)malloc(sizeof(struct data));
	newData->value= value;
	newData->next= NULL;
	
	if(*localHead==NULL){
		*localHead= *localTail =newData;
	}
	else{
		newData->next=*localHead;
		*localHead =newData;
	}
	(*localTail)->next=NULL;
}

void pushTail(struct data **localHead,struct data **localTail, int value){
	
	struct data *newData =(struct data*)malloc(sizeof(struct data));
	newData->value= value;
	newData->next= NULL;
	
	if(*localHead==NULL){
		*localHead= *localTail =newData;
	}
	else{
		
		(*localTail)->next = newData;
		*localTail= newData;
	}
	
	(*localTail)->next= NULL;
	
}

void pushAfter(struct data **localHead,struct data **localTail, int value,int key){
	
	struct data *newData =(struct data*)malloc(sizeof(struct data));
	newData->value= value;
	newData->next= NULL;
	
	if(*localHead==NULL){
		printf("No Data!\n");
		return;
	}
	else if(key==(*localTail)->value)pushTail(localHead,localTail,value);
	else{
		
		struct data *curr= *localHead;
		
		while(curr && curr->next && curr->value!=key){
			curr=curr->next;
		}
		
		if(curr->next){
			newData->next=curr->next;
			curr->next=newData;
		}
		else printf("Key not found!\n");
	}
	
	(*localTail)->next= NULL;
	
}

void pushBefore(struct data **localHead,struct data **localTail, int value,int key){
	
	struct data *newData =(struct data*)malloc(sizeof(struct data));
	newData->value= value;
	newData->next= NULL;
	
	if(*localHead==NULL){
		printf("No Data!\n");
		return;
	}
	else if(key==(*localHead)->value)pushHead(localHead,localTail,value);
	else{
		
		struct data *curr= *localHead;
		
		while(curr && curr->next && curr->next->value!=key){
			curr=curr->next;
		}
		
		if(curr->next){
			newData->next=curr->next;
			curr->next=newData;
		}
		else printf("Key not found!\n");
	}
	
	(*localTail)->next= NULL;
	
}

void popHead(struct data **localHead,struct data **localTail){
	
	if(*localHead){
		
		if(*localHead==*localTail){
			free(*localTail);
			*localHead=*localTail=NULL;
			
		}else{
			struct data *temp= *localHead;
		
			(*localHead)= temp->next;
			free(temp);
		}
		
	}
	else printf("No Data!\n");
}

void popTail(struct data **localHead, struct data **localTail){
	
	if(*localHead){
		
		if(*localHead==*localTail){
			free(*localTail);
			*localHead=*localTail=NULL;
		}else{
			struct data *temp= *localHead;
			while(temp->next!=*localTail){
			temp= temp->next;
			}
		
		free(*localTail);
		*localTail= temp;
		(*localTail)->next= NULL;
		}
		
	}
	else printf("No Data!\n");
}

void popKey(struct data **localHead,struct data **localTail,int key){
	
	if(*localHead){
		
		if(key==(*localHead)->value)popHead(localHead,localTail);
		else if(key== (*localTail)->value)popTail(localHead,localTail);
		
		else{
			struct data *curr= *localHead;
			
			while(curr && curr->next &&curr->next->value!=key){
				curr=curr->next;
			}
			
			if(curr->next){
				struct data *temp= curr->next;
				curr->next=temp->next;
				free(temp);
			}else{
				printf("Key not found!\n");
			}
		}
		
	}
	else printf("No Data!\n");
}

int main(){
	
	struct data *head=NULL,*tail=NULL;
	int menu=-1,value,key;
	
	do{
		printf("Available Data: ");
		view(head);
		printf("\n");
		printf("1.Push Head\n");
		printf("2.Push Tail\n");
		printf("3.Push After\n");
		printf("4.Push Before\n");
		printf("5.Pop Head\n");
		printf("6.Pop Tail\n");
		printf("7.Pop Key\n");
		printf("8.Exit\n");
		
		scanf("%d",&menu);getchar();
		
		switch(menu){
			case 1:
				printf("Value: ");
				scanf("%d",&value);
				pushHead(&head,&tail,value);
				break;
				
			case 2:
				printf("Value: ");
				scanf("%d",&value);
				pushTail(&head,&tail,value);
				break;
			
			case 3:
				
				printf("Value: ");
				scanf("%d",&value);getchar();
				printf("Key: ");
				scanf("%d",&key);
				pushAfter(&head,&tail,value,key);
				break;
			
			case 4:
				
				printf("Value: ");
				scanf("%d",&value);getchar();
				printf("Key: ");
				scanf("%d",&key);
				pushBefore(&head,&tail,value,key);
				break;
			
			case 5:
				popHead(&head,&tail);
				break;
				
			case 6:
				popTail(&head,&tail);
				break;
			
			case 7:
				printf("Key: ");
				scanf("%d",&key);
				popKey(&head,&tail,key);
				break;
		}
		
	}while(menu!=8);
	
	return 0;
}
