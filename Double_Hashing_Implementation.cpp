#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Assignment No.1
//Name : Vincent Hadinata
//NIM : 2301850430
//Class: LB01

int hashing(char hash[][110],char string[110],int check[],int size){

	int i=0,total=0;
	while(string[i]){//menjumlahkan ASCII dari string
		total=total+string[i];
		i++;
	}
	
	int key;//return value index
	int key1=total%size;
	int key2;
	
	if(check[key1]==0){
		check[key1]=1;
		return key1;
	}
	else if(size==2){
		key2=total%(size-1);
		check[key2]=1;
		return key2;
	}
	else{
		if(size%2==1){
			key2=total%(size-1);
			for(int j=0;j<size;j++){//mencari index
				key= (key1+j*key2)%size;
			
				if(check[key]==0){
					check[key]=1;
					return key;
				}
			
			}	
		}
		else{
			key2=total%(size-2);
			for(int j=0;j<size;j++){//mencari index
				key= (key1+j*key2)%size;
			
				if(check[key]==0){
					check[key]=1;
					return key;
				}
			
			}	
		}	
			
	}
		
	return -1;
}

void print(char hash[][110],int check[],int size){
	
	system("cls");
	printf("Hash Table\n");
	printf("======================================\n");
	printf(" Idx|\tString\n");
	printf("======================================\n");
	for(int i=0;i<size;i++){
		
		if(check[i]==1){
			printf("%3d |\t%s\n",i,hash[i]);
		}else{
			printf("%3d |\n",i);
		}
		printf("======================================\n");
		
	}
	printf("Press Enter to continue...");
	getchar();
}

int main(){
	//initial variable table size
	int m;
	printf("Input table size: ");
	scanf("%d",&m);getchar();
	
	//membuat array untuk penyimpanan string
	char hash[m][110]={};
	int check[m]={};//tanda apakah array telah terisi
	
	char string[110]={};//string penampung
	
	int choose=-1;
	do{
		system("cls");
		printf("Double Hashing - Vincent Hadinata - 2301850430\n");
		printf("==================================\n");
		printf("1.Store Value\n");
		printf("2.Show Hash Table\n");
		printf("3.Exit\n");
		printf("Choose >> ");
		scanf("%d",&choose);getchar();
		
		switch(choose){
			case 1:
				system("cls");
				printf("Input string: ");
				gets(string);
				int key;
				key = hashing(hash,string,check,m);

				if(key==-1){
					printf("String cannot be placed\n");
				}
				else{
					strcpy(hash[key],string);//masukkan string ke hash
					printf("String successfully placed at index %d\n",key);
				}
				printf("Press enter to continue...");
				getchar();
				break;
			case 2:
				print(hash,check,m);
				break;
		}
		
	}while(choose!=3);
	
	return 0;
}
