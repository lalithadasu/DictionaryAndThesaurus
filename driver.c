#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"


int length,top;
int main()
{   
	char key[100];
    char m[500];
	struct trienode *root;
	int ch=1;
	
	root=getnode();
    struct meaning *head= NULL;
	file_to_dict(root,&head);
	while(ch!=0)
	{
    printf("\n\n---------------------------------------------------------------------------------------------------");
	printf("\n1. Insert");
    printf("\n2. Display");
    printf("\n3. Search meaning");
    printf("\n4. Delete word");
    printf("\n5. Display prefix");
    printf("\n6. Display meaning-synonyms");
    printf("\n7. Display synonyms of a word\n");

    int y=scanf("%d",&ch);
	if(y!=1)
	return 0;

    switch(ch)
    { 
case 1: {
			input:
			   printf("Enter the string: ");
			   int x=scanf(" %[^\n]s",key);
			   int check=1;
			   for(int i=0;key[i]!='\0';i++)
               {
				   if(!isalpha(key[i]))
				   {
					   check=0;
					   printf("Enter alphabetic string!!\n");
					   break;
				   }
			   }
			   if(check==0)
			   goto input;
			   
			   if(x!=1)
				break;


			   printf("Enter the meaning: ");
			   x=scanf(" %[^\n]s",m);

			   if(x!=1)
			   break;

			   insert(root, key,m);
               int result=check_meaning(head,m);
               //printf("word is %s and check is %d",m,result);

               if(result!=0)
               insert_synonym(&head,m,key);
               else
               insert_meaning(&head,key,m);

			   add_to_file(key,m);
			}break;

	case 2: {length=0;
			 printf("The words stored in the dictionary are: ");
			 display(root); 
			}break;

	case 3: {     printf("Enter the string for search: ");
			   int x=scanf(" %[^\n]%*c", key);

			   if(x!=1)
			   break;

               char search_value[500];
			   strcpy(search_value,search(root, key));
               if(strcmp(search_value,"Not Found")!=0)
               {
                   printf("\nMeaning is: %s",search_value);
               }
			   else
               printf("%s",search_value);
			}break;

	case 4: {
			printf("Enter the word for deletion..\n");
			int x=scanf("%s",key);

			if(x!=1)
			break;
			top=0;
			char search_value[500];
			strcpy(search_value,search(root, key));

			if(strcmp(search_value,"Not Found")!=0)
			{ 	delete_trie(root,key);
				del_thes(head,key,search_value);
				del_word(key);
			}
			
			else
			printf("\n%s",search_value);
	}
			break;
	
	case 5: {
		    length=0;
			printf("Enter the string for search ..\n");
			int x=scanf("%s",key);

			if(x!=1)
			break;

			search_pre(root, key);
	}break;

    case 6: {
                if(head!=NULL)
				display_pairs(head);
            }break;

    case 7: {
                printf("Enter the string for search: ");
			   int x=scanf(" %[^\n]s",key);
			   if(x!=1)
			   break;

               char search_value[500];
			   strcpy(search_value,search(root, key));
               if(strcmp(search_value,"Not Found")!=0)
               {
                   find_syn(head,search_value,key);
               }
               else
               printf("%s",search_value);
            }break;

	

	default: {
			ch=0;
			destroy(&head);
			destroy_trie(&root);
			//exit(0);
    		}
    	}
  }
  return 0;
}
