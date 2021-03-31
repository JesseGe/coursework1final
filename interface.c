/* This is the interface funtions. before login, the interface is start, after login the ui will change to ui_after_login.*/
#include"interface.h"

#include "book_management.h"
#include "user_management.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_LEN  128
User* loginuser;


void ui_after_login();
void start()
{
	int a;
	int check;
	do
	{
		printf("Please choose an option: \n1) Regsiter\n2) Login\n3) Search for books\n4) Librarian login\n5) Quit\nOption: ");
		int check = scanf("%1d", &a);
		getchar();
		if(check == 0)
		{
			printf("Sorry, the option you intered was invalid, please try again.\n");
		}
		else
		{
			User* head=(User*)malloc(sizeof(User));
			FILE *fp;
			char acf[BUF_LEN];
			char name1[BUF_LEN];
			char username1[BUF_LEN];
			char password1[BUF_LEN];
			fp = fopen("account.dat", "r");
			if (!fp)
			{
				fprintf(stderr, "Error when opening account.dat\n");
				return;
			}
			if (fgets(acf, BUF_LEN, fp) == NULL)
			{
				fprintf(stderr, "Error in reading: books.dat\n");
				return; 
			}
			User* temp = head;
			while(feof(fp) == 0)
			{
				sscanf(acf,"%s\n", name1);
				//Load name
				fgets(acf, BUF_LEN, fp);
				sscanf(acf,"%s\n", username1);
				//Load username
				fgets(acf, BUF_LEN, fp);
				sscanf(acf, "%s\n", password1);
				//load paddword
				User* c=(User*)malloc(sizeof(User));
				strcpy(c-> name, name1);
				strcpy(c-> username, username1);
				strcpy(c-> password, password1);
				c-> next = NULL;
				temp-> next = c;
				temp = c;
				fgets(acf, BUF_LEN, fp);
			}
			fclose(fp);//creat a link
			FILE* file;
			file = fopen("book.dat", "r");
			Book* headb=(Book*)malloc(sizeof(Book));
			Book*tempb;
			if(load_books(file, headb) == 1)
			{
				printf("Error in reading: books.dat\n");
				return;
			}
			int i = a;
			switch(i)
			{
				case 1: if(Rogister(head) == 1)
				{
					ui_after_login(headb);
				}
					break;
				case 2: if(Login(head) == 1)
				{
					ui_after_login(headb);
				}
				    break;
				case 3: Searchforbooks(headb);
					break;
				case 4: if(sp_account() == 1)
				{
					do
					{
						printf("Please choose your option:\n1) add a book\n2) remove a book\n3) Quit\n");
						int check = scanf("%1d", &a);
						getchar();
						if(check == 0)
						{
							printf("Sorry, the option you intered was invalid, please try again.\n");
						}
						else
						{
							int i = a;
							char title[200];
							char author[60];
							char year[20];
							char copies[10];
							char x[150];
							switch(i)
							{
								case 1: printf("Please inter the title:");
								gets(title);
								printf("Please inter the author:");
								gets(author);
								printf("Please inter the year:");
								gets(year);
								printf("Please inter the copies:");
								gets(copies);
								strcat(title, " ");
								strcat(title, author);
								strcat(title, " ");
								strcat(title, year);
								strcat(title, " ");
								strcat(title, copies);
								if(add_book(headb, title) == 0){
									if(store_books(file, headb) == 0)
									{
										printf("Add successfully.\n");
									}
									else{
										printf("store error.\n");
									}
								}
								else{
									printf("add error.\n");
								}
									break;
								case 2: 
								printf("Please inter the title:");
								gets(title);
								tempb = headb;
								int checkp =0;
								while(tempb!= NULL)
								{
									tempb = tempb->next;
									if(strcmp(tempb->title, title) == 0)
									{
										remove_book(headb, title);
										if(store_books(file, headb) == 0)
										{
											printf("Book removed.\n");
											checkp = 1;
											break;
										}
									}
								}
								if(checkp != 1)
								{
									printf("Sorry, this book doesn't exsite.\n");
								}
								break;
								default: break;
							}
							break;
						}
					}while(a != 3);
				}
				break;
				default: break;
			}
			temp = head;
			User* temp1 = head;
			while(temp!=NULL)
			{
				temp1 = temp;
				temp = temp->next;
				free(temp1);
			}
			tempb = headb;
			Book* tempb1 = headb;
			while(temp!=NULL)
			{
				temp1 = temp;
				temp = temp->next;
				free(tempb1->title);
				free(tempb1->authors);
				free(tempb1);
			}
		}
	}while(a != 5);
}


void ui_after_login(Book* head)
{
	int a;
	int check;
	char book[60];
	char acf[128];
	FILE *fp;
	fp = fopen("bbook.dat", "r");
	if (!fp)
	{
		fprintf(stderr, "Error when opening bbook.dat\n");
		return;
	}
	BorrowUser* head1 =(BorrowUser*)malloc(sizeof(BorrowUser));
	BorrowUser* temp = head1;
	fgets(acf, BUF_LEN, fp); 
	while(feof(fp) == 0)
	{
		BorrowUser* c = (BorrowUser*)malloc(sizeof(BorrowUser));
		sscanf(acf, "%s %s", c->username, c-> title);
		c->next = NULL;
		temp->next = c;
		temp = c;
		fgets(acf, BUF_LEN, fp); 
	}
	fclose(fp);
	do
	{
		printf("Please choose your option:\n1) borrow a book\n2) return a book\n3) search a book\n4) Quit\n");
		int check = scanf("%1d", &a);
		getchar();
		if(check == 0)
		{
			printf("Sorry, the option you intered was invalid, please try again.\n");
		}
		else
		{
			int i = a;
			switch(i)
			{
				case 1: printf("Please enter the book you want to borrow: ");
						gets(book);
						Book* y = head; temp = head1;
						while(temp->next)
						{
							temp = temp->next;
							if(strcmp(temp->username, loginuser->username) == 0)
							{
								printf("You've borrowed one book, return it first\n");
								temp = head1;
								BorrowUser* temp1 = head1;
								while(temp!=NULL)
								{
									temp1 = temp;
									temp = temp->next;
									free(temp1);
								}
								return;
							}
						}
						while(y->next)
						{
							y =y->next;
							if(strcmp(y->title, book) == 0)
							{
								if(y->copies >= 0)
								{
									Borrow_book(y, loginuser);
									y->copies = y->copies-1;
									FILE* file;
									store_books(file, head);
									printf("You've borrowed the book.\n");
									temp = head1;
									BorrowUser* temp1 = head1;
									while(temp!=NULL)
									{
										temp1 = temp;
										temp = temp->next;
										free(temp1);
									}
									return;
								}
								printf("The book you want to borrow has lent out.\n");
								temp = head1;
								BorrowUser* temp1 = head1;
								while(temp!=NULL)
								{
									temp1 = temp;
									temp = temp->next;
									free(temp1);
								}
								return;
							}
						}
						printf("Sorry, we didn't find your book.\n");
					break;
				case 2: printf("Please enter the book you want to return: ");
				gets(book);
				temp = head1;
				while(temp!=NULL)
				{
					temp = temp->next;
					if(strcmp(temp->username, loginuser->username) == 0)
					{
						if(strcmp(temp->title, book) == 0)
						{
							Return_book(head1, loginuser);
							y = head->next;
							while(strcmp(y->title, book) != 0)
							{
								y = y->next;
							}
							y->copies = y->copies+1;
							FILE* file;
							store_books(file, head);
							printf("Successfully!\n");
							temp = head1;
							BorrowUser* temp1 = head1;
							while(temp!=NULL)
							{
								temp1 = temp;
								temp = temp->next;
								free(temp1);
							}
							return;
						}
						else
						{
							printf("You didn't borrow this book.\n");
							temp = head1;
							BorrowUser* temp1 = head1;
							while(temp!=NULL)
							{
								temp1 = temp;
								temp = temp->next;
								free(temp1);
							}
							return;
						}
					}
				}
				printf("No seach a book.\n");
				    break;
				case 3: Searchforbooks(head);
					break;
				default: break;
			}
		}
	}while(a != 4);
}