#include <stdio.h>
// stdlib is required for atoi/system & etc
#include <stdlib.h>
#include <string.h>	
// time.h is require for sleep function
#include <time.h>

/*
	structure which will hold book info. Data will be temporary stored here
	memebers are name, author, id & price
	The no. of book records the structure can hold is upto 1000 
*/

struct bookinfo{
	char name[30],author[20];
	int id, price;
}book[1000];

// function incase ID is not found
int notfound(){
	printf("\nBook not found!");
	printf("\nReturning to Main Menu..");
	sleep(4);
	return 0;
}

/* 
	A generic Wait function instead of force exiting
	This is used when dsiplaying results where user needs to look at it long enough
*/
int wait(){
	int exit1;
	wait:
	printf("\nPress 0 to return to main menu: ");
	scanf("%d",&exit1);
	if (exit1==0)
		return 0;
	else
		goto wait;

}


// Choice Function - uses switch statement at core
int choiceCase(int choice){
	FILE *fcs;
	// Clears the Command Prompt/terminal in Windows
	system("cls");

	/* 
		Open the data.csv file
		A CSV file is a comma separated file which can be opened
		in notepad, excel & etc. Easy to store & retrieve data from
	   Incase the file is not found, i.e NULL is returned
	   We create the file with name data.csv and skip to close part
	*/
	fcs = fopen("data.csv","r");
	if (fcs == NULL){
		printf("File Not Found.");
		printf("\nCreating New File..");
		fcs = fopen("data.csv","w");
		goto newfc;
	}
	// Defines the maximum length of the line
	char line[1024];
	int j=0,inid,foundflag=0;
	// pointers for usage in strtok to temporary store data
	char *bid,*bname,*bauth,*bprice;
	printf("\nReading Books Record..\n");
	// Reads until End Of File is not reached
	while (fgets(line, 1024, fcs)!=NULL){
		/*
			strtok splits a string using a delimiter, here it is comma (,)
			in CSV file, a comma is used to define additional column
			we are storing data in char pointer var
			and then copying them to the book struct array
		*/
		bid = strtok(line,",");
		bname=strtok(NULL, ",");
		bauth=strtok(NULL, ",");
		bprice=strtok(NULL, ",");
		// atoi is used to convert a string to integer
		book[j].id = atoi(bid);
		strcpy(book[j].name,bname);
		strcpy(book[j].author,bauth);
		book[j].price = atoi(bprice);
		j++;
	}
	newfc:
	fclose(fcs);
	switch (choice){
		case 1: 
			// Open the file in Append Mode with new data written from new line
			fcs = fopen("data.csv","a+");
			printf("\nNumber Of Books to Add: ");
			scanf("%d",&inid);
			for(int i=0;i<inid;i++){
				printf("\nEnter Book Id: ");
				scanf("%d",&book[i].id);
				getchar();
				printf("Enter Book name: ");
				gets(book[i].name);
				printf("Enter Book Author: ");
				gets(book[i].author);
				printf("Enter Book Price (in rupee): ");
				scanf("%d",&book[i].price);
				fprintf(fcs, "%d,%s,%s,%d\n", book[i].id,book[i].name,book[i].author,book[i].price);
			}
			fclose(fcs);
			printf("\nNew Records have been added successfully");
			printf("\nReturning to main menu..");
			sleep(3);
			return 0;
		case 2:
			printf("\nEnter Book ID to Edit: ");
			scanf("%d",&inid);
			for(int s=0;s<j;s++){
				if(inid==book[s].id){
					foundflag++;
					printf("Editing Data for Book ID: %d & Book Name: %s",book[s].id,book[s].name);
					printf("\n\nEnter new Book Id: ");
					scanf("%d",&book[s].id);
					getchar();
					printf("Enter New Book name: ");
					gets(book[s].name);
					printf("Enter new Book Author: ");
					gets(book[s].author);
					printf("Enter new Book Price (in rupee): ");
					scanf("%d",&book[s].price);
					break;
				}
			}
			if (foundflag==1){
				printf("\nWriting Changes.. ");
				fcs = fopen("data.csv","w");
				for(int s=0;s<j;s++){
					fprintf(fcs, "%d,%s,%s,%d\n", book[s].id,book[s].name,book[s].author,book[s].price);
				}
				fclose(fcs);
				printf("\nReturning to Main Menu..");
				sleep(3);
				return 0;
			} 
			else {
				notfound();
				return 0;
			}

		case 3:
			printf("\n");
			for(int s=0;s<j;s++){
				printf("**************************");
				printf("\n\nBook ID: %d \nBook Name: %s \nBook Author: %s \nBook Price: %d\n",book[s].id,book[s].name,book[s].author,book[s].price);
				printf("\n**************************");
			
			}
			wait();
			break;
		case 4:
			printf("\nEnter the Book ID to delete: ");
			scanf("%d",&inid);
			getchar();
			int ss;
			for(ss=0;ss<=j;ss++){
				if(inid==book[ss].id){
					foundflag++;
					break;
				}
			}
			if (foundflag==1){
				char confirmdel;
				printf("Are You sure You want to delete book id: %d and book name: %s",book[ss].id,book[ss].name);
				printf("\nPress Y to confirm delete or Press any other key to exit: ");
				scanf("%c",&confirmdel);
				if ((confirmdel == 'Y')||(confirmdel=='y')){
					printf("\nWriting Changes.. ");
					fcs = fopen("data.csv","w");
					for(int kk=0;kk<j;kk++){
						if(kk==ss){
							// Skip the ID to delete
							kk++;
							fprintf(fcs, "%d,%s,%s,%d\n", book[kk].id,book[kk].name,book[kk].author,book[kk].price);
						}
						else
							fprintf(fcs, "%d,%s,%s,%d\n", book[kk].id,book[kk].name,book[kk].author,book[kk].price);
					}
					fclose(fcs);
				}
				else
					printf("Not Deleting the Record.");
				printf("\nReturning to Main Menu..");
				sleep(3);
				return 0;
			} 
			else
				notfound();
		case 5:
			case5:
			printf("\nPlease choose an option to search Book details: ");
			int searchopt;
			printf("\n1. By Book ID\n2. By Book Name\n3. By Book Author\n0. Exit\nYour Option: ");
			scanf("%d",&searchopt);
			if (searchopt==1){
				printf("\nEnter Book ID to Search: ");
				printf("%d",&inid);
				for(int s=0;s<=j;s++){
					if(inid==book[s].id){
					foundflag++;
					printf("**************************");
					printf("\n\nBook ID: %d \nBook Name: %s \nBook Author: %s \nBook Price: %d\n",book[s].id,book[s].name,book[s].author,book[s].price);
					printf("\n**************************");
					break;
					}
				}
			}
			else if (searchopt==2){
				getchar();
				char searchname[30];
				printf("\nEnter Book Name to search: ");
				gets(searchname);
				for(int s=0;s<=j;s++){
					if(strcmp(searchname,book[s].name)==0){
					foundflag++;
					printf("**************************");
					printf("\n\nBook ID: %d \nBook Name: %s \nBook Author: %s \nBook Price: %d\n",book[s].id,book[s].name,book[s].author,book[s].price);
					printf("\n**************************");
					break;
					}
				}
			}
			else if (searchopt==3){
				getchar();
				char searchauth[20];
				printf("\nEnter Book Author to search: ");
				gets(searchauth);
				int mm;
				// while loop to print all books of the author
				while (mm<j){
					if(strcmp(searchauth,book[mm].author)==0){
						foundflag=1;
						printf("**************************");
						printf("\n\nBook ID: %d \nBook Name: %s \nBook Author: %s \nBook Price: %d\n",book[mm].id,book[mm].name,book[mm].author,book[mm].price);
						printf("\n**************************");
					}
					mm++;
				}
			}
			else if (searchopt==0){
				break;
			}
			else{
				printf("\n\nPlease choose a valid Option or Enter 0 to exit\n");
				goto case5;
			}

			if (foundflag==1){
				wait();
				break;
			}
			else
				notfound();
	}
}


// Driver Code
int main(){
	START:system("cls");
	int opt;
	printf("\n\n\n\t\tWelcome To Bookshop Management System");
	printf("\n\n\nWhat Would like to Do?\n");
	printf("\n1. Add Book Record");
	printf("\n2. Edit A Book Record");
	printf("\n3. Show the Entire Book Record");
	printf("\n4. Delete A Book Record");
	printf("\n5. Search a Book Record");
	printf("\n0. For Exit");
	printf("\n\nPlease enter your Option: ");
	scanf("%d",&opt);
	checkopt: 
	if (opt==0){
		printf("Exiting..");
		goto END;
	}
	else if((opt<6)&&(opt>=1)){
		choiceCase(opt);
		goto START;
	}
	else{
		printf("\nPlease Enter A Valid number or press 0 to exit. ");
		scanf("%d",opt);
		goto checkopt;
	}
	END:
	return 0;
}