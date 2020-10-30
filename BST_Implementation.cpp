#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct data{
	
	char name[110];
	int id;
	
	struct data *left,*right;
}*root=NULL;

struct data* tnode(char name[110],int id){
	
	struct data *newNode= (struct data*)malloc(sizeof(struct data));
	newNode->id=id;
	strcpy(newNode->name,name);
	newNode->left=NULL;
	newNode->right=NULL;
	
	return newNode;
}

void insert(char name[110],int id){
	
	struct data *newNode = tnode(name,id);
	
	if(!root)root=newNode;
	else{
		struct data *curr= root;
		
		while(curr){
			if(id <curr->id){
				if(curr->left)curr=curr->left;
				else {
					curr->left=newNode;
					break;	
				}
			}
			else{
				if(curr->right)curr=curr->right;
				else{
					curr->right=newNode;
					break;
				} 
			}
		}
	}
	
}

s

int main(){
	
	int menu;
	int panjang;
	char name[110]={};
	int id;
	
	do{
		system("cls");
		printf("BST Implementation\n");
		printf("1.Insert Data\n");
		printf("2.Delete Data\n");
		printf("3.Show All Data\n");
		printf("4.Exit\n");
		printf("Choose >> ");
		
		scanf("%d",&menu);
		getchar();
	
		switch(menu){
			case 1:
				system("cls");
				do{
					printf("Input name [5-20 characters]: ");
					gets(name);
					panjang=strlen(name);
				}while(panjang<5 || panjang >20);
				
				do{
					printf("Input ID Number :");
					scanf("%d",&id);getchar();
				}while(id<0);
				
				insert(name,id);
				printf("Data successfully inserted\nPress enter to continue...");
				getchar();
				break;
			case 2:
				system("cls");
				do{
					printf("Input ID Number to be deleted:");
					scanf("%d",&id);getchar();
				}while(id<0);
				
				del(id);
				printf("Press enter to continue");
				getchar();
				break;
			case 3:
				system("cls");
				
				if(root)show(root);
				else printf("No Data\n");
				printf("Press enter to continue...");
				getchar();
				break;
			case 4:
				break;
			default:
				printf("Input must be number from 1-5!\n");
				getchar();
				break;
		}
		
	}while(menu!=4);
	return 0;
}
