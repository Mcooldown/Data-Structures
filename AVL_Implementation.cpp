#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct data{
	int height;
	char name[110];
	int key;
	struct data *left,*right;
};

int getHeight(struct data *root){
	if(root==NULL)return 0;
	else return root->height;
}

int max(int a,int b){
	
	if(a>=b)return a;
	else return b;
}

int getBF(struct data *root){
	if(root==NULL)return 0;
	else return getHeight(root->left)-getHeight(root->right);
}

struct data *rightRotate(struct data *root){
	
	struct data *newRoot = root->left;
	struct data *childNewRoot = newRoot->right;
	
	newRoot->right= root;
	root->left=childNewRoot;
	
	newRoot->height = max(getHeight(newRoot->left),getHeight(newRoot->right))+1;
	root->height = max(getHeight(root->left),getHeight(root->right))+1;
	
	return newRoot;
}

struct data *leftRotate(struct data *root){
	struct data *newRoot = root->right;
	struct data *childNewRoot = newRoot->left;
	
	newRoot->left= root;
	root->right = childNewRoot;
	
	newRoot->height = max(getHeight(newRoot->left),getHeight(newRoot->right))+1;
	root->height = max(getHeight(root->left),getHeight(root->right))+1;
	
	return newRoot;
}

struct data *createNode(char name[],int key){
	
	struct data *newNode = (struct data*)malloc(sizeof(struct data));
	newNode->key=key;
	newNode->height=1;
	strcpy(newNode->name,name);
	newNode->left=newNode->right=NULL;

	return newNode;
}

struct data *pengganti(struct data *root){
	
	struct data *curr = root->left;
	while(curr->right !=NULL){
		curr=curr->right;
	}
	return curr;
}

struct data *insert(struct data *root, char name[],int key){
	if(root==NULL)return createNode(name,key);
	else if(key < root->key) root->left = insert(root->left,name,key);
	else root->right= insert(root->right, name, key);
	
	
	root->height = max(getHeight(root->left),getHeight(root->right))+1;
	int bFactor = getBF(root);
	
	if(bFactor >1 && key < root->left->key){
		return rightRotate(root);
	}
	if(bFactor < -1 && key> root->right->key){
		return leftRotate(root);
	}
	if (bFactor > 1 && key > root->left->key){
		root->left= leftRotate(root);
		return rightRotate(root);
	}
	if(bFactor < -1 && key < root->left->key){
		root->right= rightRotate(root);
		return leftRotate(root);
	}
	return root;
}

struct data *deleteNode(struct data *root,int key){
	if (root == NULL) return NULL; // tidak ketemu...
	if (key < root->key) {
		root->left = deleteNode(root->left, key);
	} else if (key > root->key) {
		root->right = deleteNode(root->right, key);
	} else {
		
		// ketemu. mari kita mulai delete...
		
		// case 1 : tidak punya anak
		// case 2 : hanya punya anak kiri
		// case 3 : hanya punya anak kanan
		if ((root->left == NULL) || (root->right == NULL)) {
			
			struct data *temp = NULL;
			if (root->left != NULL) temp = root->left;
			else temp = root->right;
			
			if (temp == NULL) {
				// pasti tidak punya anak
				// ini adalah case 1
				temp = root;
				root = NULL;
			} else {
				// ini adalah case 2 dan case 3
				*root = *temp;
			}
			free(temp);
			
		} else {
			// ini case ke 4
			// ada 2 anak, maka kita ambil suksesor/predesesor
			// terserah
			
			struct data *temp = pengganti(root);
			root->key = temp->key;
			
			// delete
			root->left = deleteNode(root->left, temp->key);
		}
	}

	if (root == NULL) return root;
	
	// Kita perlu fix height dlsbnya
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	int bfactor = getBF(root);
	
	if (bfactor > 1 && getBF(root->left) >= 0) {
		return rightRotate(root);
	}
	if (bfactor > 1 && getBF(root->left) < 0) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if (bfactor < -1 && getBF(root->right) <= 0) {
		return leftRotate(root);
	}
	if (bfactor < -1 && getBF(root->right) > 0) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

void printAll(struct data *root){
	
	if(root){
		printAll(root->left);
		printf("%d. %s\n",root->key,root->name);
		printAll(root->right);
	}
}

int main(){
	
	struct data *root = NULL;
	int menu,key;
	char name[110]={};
	do{
		system("cls");
		printf("AVL Tree Implementation\n");
		printf("1.Insert\n");
		printf("2.Delete\n");
		printf("3.View All Data\n");
		printf("4.Exit\n");
		printf("Choose >> ");
		scanf("%d",&menu);getchar();
		
		switch(menu){
			case 1:
				system("cls");
				printf("Input Name: ");
				gets(name);
				printf("Input Key: ");
				scanf("%d",&key);getchar();
				root = insert(root,name,key);
				printf("Succesfully inserted, Enter to continue\n");
				getchar();
				break;
			case 2:
				printf("Input delete key: ");
				scanf("%d",&key);getchar();
				root = deleteNode(root,key);
				break;
			case 3:
				system("cls");
				if(root==NULL){
					printf("Data empty\n");
				}
				else{
					printAll(root);
				}
			
				printf("Enter to continue");
				getchar();
				break;
		}
	}while(menu!=4);
}
