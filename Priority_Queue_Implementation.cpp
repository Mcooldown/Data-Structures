#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct body{
	char name[110];
	char category[20];
	float bmi;
	
	struct body *next,*prev;
};

void print(struct body *head){
	
	printf("Body Mass Index\n");
	printf("================\n");
	if(head){
		struct body *curr= head;
		
		printf("\n|%20s%8s%10s%9s%15s%6s\n","Name","|","BMI","|","Category","|");
		
		while(curr){
			printf("|%20s%8s%10.2f%9s%15s%6s\n",curr->name,"|",curr->bmi,"|",curr->category,"|");
			curr=curr->next;
		}
		printf("\n");
	}
	else{
		printf("No Data\n\n");
	}
}

void pushHead(struct body **locHead,struct body **locTail,char name[110],float bmi){
	
	struct body *curr= (struct body*)malloc(sizeof(struct body));
	strcpy(curr->name,name);
	curr->bmi= bmi;
	if(bmi<18.5){
		strcpy(curr->category,"Underweight");
	}
	else if(bmi>25){
		strcpy(curr->category,"Overweight");
	}
	else strcpy(curr->category,"Normal");
	
	curr->next=NULL;
	curr->prev=NULL;
	
	if(*locHead==NULL){
		*locHead=*locTail=curr;
	}
	else{
		curr->next=*locHead;
		(*locHead)->prev=curr;
		*locHead=curr;
	}
}

void pushTail(struct body **locHead,struct body **locTail,char name[110],float bmi){
	
	struct body *curr= (struct body*)malloc(sizeof(struct body));
	strcpy(curr->name,name);
	curr->bmi= bmi;
	if(bmi<18.5){
		strcpy(curr->category,"Underweight");
	}
	else if(bmi>25){
		strcpy(curr->category,"Overweight");
	}
	else strcpy(curr->category,"Normal");
	
	curr->next=NULL;
	curr->prev=NULL;
	
	if(*locHead==NULL){
		*locHead=*locTail=curr;
	}
	else{
		(*locTail)->next=curr;
		curr->prev=*locTail;
		*locTail=curr;
	}
}

void pushMid(struct body **locHead,struct body **locTail,char name[110],float bmi){
	
	if(!*locHead){
		pushHead(locHead,locTail,name,bmi);
	}
	else if(bmi<(*locHead)->bmi){
		pushHead(locHead,locTail,name,bmi);
	}
	else if(bmi>=(*locTail)->bmi){
		pushTail(locHead,locTail,name,bmi);
	}
	else{
		struct body *curr= (struct body*)malloc(sizeof(struct body));
		strcpy(curr->name,name);
		curr->bmi= bmi;
		if(bmi<18.5){
			strcpy(curr->category,"Underweight");
		}
		else if(bmi>25){
			strcpy(curr->category,"Overweight");
		}
		else strcpy(curr->category,"Normal");
		
		curr->next=NULL;
		curr->prev=NULL;
		
		struct body *temp= *locHead;
		while(temp->next->bmi <= bmi){
			temp=temp->next;
		}
		curr->next=temp->next;
		temp->next=curr;
		curr->next->prev=curr;
		curr->prev=temp;
	}
}

void popHead(struct body **locHead,struct body **locTail){
		
		if(*locTail==*locHead){
			*locHead=*locTail=NULL;
		}
		else{
			struct body *temp= *locHead;
			*locHead=(*locHead)->next;
			(*locHead)->prev=NULL;
			free(temp);
		}
}

void popTail(struct body **locHead,struct body **locTail){
		
		if(*locTail==*locHead){
			*locHead=*locTail=NULL;
		}
		else{
			struct body *temp= *locTail;
			*locTail=(*locTail)->prev;
			(*locTail)->next=NULL;
			free(temp);
		}
}

void popNormal(struct body **locHead,struct body **locTail){
	
	if(*locHead && (*locHead)->bmi<=25){
		struct body *temp = *locHead;
		
		while(temp->bmi<18.5){
			temp= temp->next;
			if(!temp)return;
		}
		
		while(temp->bmi>=18.5 && temp->bmi<=25){
			if(temp==*locHead)popHead(locHead,locTail);
			else if(temp ==*locTail)popTail(locHead,locTail);
			else{
				temp->prev->next=temp->next;
				temp->next->prev=temp->prev;
				free(temp);
			}
			temp=temp->next;
			if(temp==NULL)break;
		}
	}
}

void popAll(struct body **locHead,struct body **locTail){
	
	while(*locHead){
		popHead(locHead,locTail);
	}
}

int main(){
	
	struct body *head=NULL,*tail=NULL;
	int menu;
	char name[110];
	float weight;
	float height;
	int panjang;
	float bmi;
	
	do{
		print(head);
		printf("1.Add New Data\n");
		printf("2.Delete All Data in Normal Category\n");
		printf("3.Exit\n");
		printf(">>");
		scanf("%d",&menu);getchar();
		
		switch(menu){
			case 1:
				do{
					printf("Full Name [2 - 20 characters]:");
					gets(name);
					panjang=strlen(name);
				}while(panjang<2 ||panjang>20);
				
				do{
					printf("Weight[35.00 - 300.00 in Kilogram]:");
					scanf("%f",&weight);getchar();	
				}while(weight<35 ||weight>300);
				
				do{
					printf("Height[0.50 - 3.00 in Meter]:");
					scanf("%f",&height);getchar();
				}while(height<0.5 || height >3);
				
				height=height*height;
				bmi= weight/height;
//				printf("%.2f\n",bmi);
				
				pushMid(&head,&tail,name,bmi);
				
				printf("Success add new Data!\n");
				printf("\n");
				break;
			
			case 2:
				popNormal(&head,&tail);
				printf("\n");
				break;
			case 3:
				popAll(&head,&tail);
				break;
		}
		
	}while(menu!=3);
}
