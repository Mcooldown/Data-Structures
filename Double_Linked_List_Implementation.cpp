#include<stdio.h>
#include<stdlib.h>

struct data{
	int value;
	struct data *next,*prev;	
};

void view(struct data *head,struct data *tail){
	
	if(head){
		struct data *curr= head;
		
		printf("Head->Tail: ");
		while(curr){
			printf("%d ",curr->value);
			curr= curr->next;
		}
		printf("\nTail->Head: ");
		
		curr=tail;
		while(curr){
			printf("%d ",curr->value);
			curr= curr->prev;
		}
		printf("\n");
	}
	else printf("No data!\n");
}

void pushHead(struct data **localHead,struct data **localTail, int value){
	
	struct data *newData =(struct data*)malloc(sizeof(struct data));
	newData->value= value;
	newData->next= NULL;
	newData->prev= NULL;
	
	if(*localHead==NULL){
		*localHead= *localTail =newData;
	}
	else{
		newData->next=*localHead;
		(*localHead)->prev =newData;
		*localHead =newData;
	}
	
}

void pushTail(struct data **localHead,struct data **localTail, int value){
	
	struct data *newData =(struct data*)malloc(sizeof(struct data));
	newData->value= value;
	newData->next= NULL;
	newData->prev= NULL;
	
	if(*localHead==NULL){
		*localHead= *localTail =newData;
	}
	else{
		
		(*localTail)->next = newData;
		newData->prev= *localTail;
		*localTail= newData;
	}
	
}

void pushAfter(struct data **localHead,struct data **localTail, int value,int key){
	
	struct data *newData =(struct data*)malloc(sizeof(struct data));
	newData->value= value;
	newData->next= NULL;
	newData->prev=NULL;
	
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
			curr->next->prev=newData;
			curr->next=newData;
			newData->prev=curr;
		}
		else printf("Key not found!\n");
	}

}

void pushBefore(struct data **localHead,struct data **localTail, int value,int key){
	
	struct data *newData =(struct data*)malloc(sizeof(struct data));
	newData->value= value;
	newData->next= NULL;
	newData->prev=NULL;
	
	if(*localHead==NULL){
		printf("No Data!\n");
		return;
	}
	else if(key==(*localHead)->value)pushHead(localHead,localTail,value);
	else{
		
		struct data *curr= *localHead;
		
		while(curr &&curr->next && curr->value!=key){
			curr=curr->next;
		}
		
		if(curr->value==key){
			newData->next=curr;
			newData->prev=curr->prev;
			curr->prev->next=newData;
			curr->prev=newData;
		}
		else printf("Key not found!\n");
	}
	
}

void popHead(struct data **localHead,struct data **localTail){
	
	if(*localHead){
		
		if(*localHead==*localTail){
			free(*localTail);
			*localHead=*localTail=NULL;
			
		}else{
			struct data *temp= *localHead;
		
			(*localHead)= temp->next;
			(*localHead)->prev=NULL;
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
		
		struct data *temp= *localTail;
		*localTail= temp->prev;
		(*localTail)->next= NULL;
		free(temp);
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
				temp->next->prev=curr;
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
		printf("Available Data:\n");
		view(head,tail);
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
