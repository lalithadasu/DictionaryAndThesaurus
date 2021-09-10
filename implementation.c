#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

void insert_meaning(struct meaning** head,char *wor,char *mean)
{
	struct meaning* node= (struct meaning*)malloc(sizeof(struct meaning));
	struct word* new=(struct word*)malloc(sizeof(struct word));
	if(node==NULL || new==NULL)
	{
		printf("Malloc Failed\n");
	}
	if(node!=NULL && new!=NULL){
	strncpy(node->sentence,mean,450);
	node->next_meaning=NULL;
	strcpy(new->w,wor);
	new->next=NULL;
	node->next_word=new;
	}

	if(*head==NULL)
	{
		*head=node;
	}
 	else
	{
		struct meaning* temp=*head;
		while(temp->next_meaning!=NULL)
		{
			temp=temp->next_meaning;
		}

		temp->next_meaning=node;
	}
}

void display_pairs(struct meaning* head)
{
	struct meaning* temp=head;
	while(temp!=NULL)
	{
		printf("\nMeaning:%s\n",temp->sentence);
		printf("Synonyms:");
		//printf("%s",temp->next_word->w);
		struct word* temp_word=temp->next_word;
		while(temp_word!=NULL)
		{
			printf("\n%s",temp_word->w);
			temp_word=temp_word->next;
		}
		printf("\n\n");
	temp=temp->next_meaning;
	}
}

void insert_synonym(struct meaning** head,char *meaning,char *syn)
{
	struct word* node=(struct word*)malloc(sizeof(struct word));

	if(node!=NULL){
	strncpy(node->w,syn,190);
	node->next=NULL;}

	struct meaning* temp1=*head;
	struct word* temp2;
	while(temp1!=NULL)
	{
		if(strncmp(temp1->sentence,meaning,450)==0)
		{
			temp2=temp1->next_word;
			while(temp2->next!=NULL)
				temp2=temp2->next;
			temp2->next=node;
			break;
		}
		temp1=temp1->next_meaning;
	}

	if(temp1==NULL)
		printf("\nMeaning not found");
	//free(word);		
}

int check_meaning(struct meaning* head,char* meaning)
{
	struct meaning* temp= head;
	while(temp!=NULL)
	{
		if(strncmp(temp->sentence,meaning,450)==0)
		{
			return 1;
		}
		temp=temp->next_meaning;
	}
	return 0;
}

int length,top;
char word[100];

struct stack s[255]; 

struct trienode* getnode()
{
  struct trienode* temp;
  int i;	
  temp=(struct trienode *)(malloc(sizeof( struct trienode)));

  if(temp!=NULL){
  for(i=0;i<255;i++)
    temp->child[i]=NULL;
  temp->endofword=0;
  strncpy(temp->meaning,"",2);}

  return temp;
}

void insert(struct trienode* root, char *key, char *m)
{
  struct trienode *curr;
  int i, index;
  
  curr = root;
  for(i=0;key[i]!='\0';i++)
   { index=(int)key[i];
	  if(curr->child[index]==NULL)
		curr->child[index]=getnode();
	curr=curr->child[index];
   }
  curr->endofword=1;
  strncpy(curr->meaning,m,450);	
}

//char ret[100]="Not Found";
void file_to_dict(struct trienode* root, struct meaning** head)
{
	 FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];

    filePointer = fopen("file.txt", "r");

    while(fgets(buffer, bufferLength, filePointer)) {
        char word[50];
        char meaning[500];
        int x=0;
        while(buffer[x]!=':')
        {
            word[x]=buffer[x];
            x++;
        }
        word[x]='\0';
        x++;

        int y=0;
        while(buffer[x]!='\0')
        {
            if(buffer[x]=='\n')
			x++;
			else{
			meaning[y]=buffer[x];
            x++;
            y++;}
        }
        meaning[y]='\0';
		insert(root,word,meaning); //add word to dictionary

        int result=check_meaning(*head,meaning);

        if(result!=0)
        insert_synonym(head,meaning,word);
        else
        insert_meaning(head,word,meaning);


		//call function to add word and meaning to thesaurus
	}
	fclose(filePointer);
}

void display(struct trienode *curr)
{int i,j;

	for(i=0;i<255;i++)
	{
		if(curr->child[i]!=NULL)
		{
			word[length++]=(char)i;
			if(curr->child[i]->endofword==1)
			{
				//print the word
				printf("\n");
				for(j=0;j<length;j++)
					printf("%c",word[j]);
			}
			display(curr->child[i]);
		}
	}
	length--;
	return;
}

void push(struct trienode *x,int k)
{
	++top;
	s[top].m=x;
	s[top].index=k;
}

struct stack pop()
{ 
	struct stack temp;
	temp=s[top--];
	return temp;
}

char* search(struct trienode * root, char *key)
{
 
 int i,index;
 struct trienode *curr;
 curr=root;
  for(i=0;key[i]!='\0';i++)
   { index=(int)key[i];
	  if(curr->child[index]==NULL)
		  return("Not Found");
	  curr=curr->child[index];
   }
   if(curr->endofword==1)
	return(curr->meaning);

   return("Not Found");
}

void search_pre(struct trienode * root, char *key)
{
 int i,index;	
 struct trienode *curr;
 curr=root;
 length=0;
  for(i=0;key[i]!='\0';i++)
   { index=(int)key[i];
	  if(curr->child[index]==NULL){
		  printf("Prefix not found\n");
		  return;
	  }
	  word[length++]=key[i];
	  curr=curr->child[index];
   }
    if(curr->endofword==1)
		printf("%s",key);
	display(curr);
}

int check(struct trienode *x)
{
	int i,count=0;
	for(i=0;i<255;i++)
	{
		if(x->child[i]!=NULL) count++;
	}
	return count;
}

void delete_trie(struct trienode *root,char *key)
{
 int i,k,index;	
 struct trienode *curr;
 struct stack x;
 
 curr =root;
 for(i=0;key[i]!='\0';i++)
   { index=(int)key[i];
	  if(curr->child[index]==NULL)
	  {
		 printf("Word not found..");
         return;		 
	  }
	  push(curr,index);
      curr=curr->child[index];
	}
	curr->endofword=0;
	push(curr,-1);
	
	int ch=1;
	
	while(ch==1)
	{
		x=pop();
		if(x.index!=-1)
			x.m->child[x.index]=NULL;
		if(x.m==root)//if root
		return;

		k=check(x.m);

		if((k>=1)|| (x.m->endofword==1))break;
		else free(x.m);
	}
	return;
}	

void add_to_file(char* word,char* meaning)
{
    char str[600]="";
    strncpy(str,"\n",2);
    strcat(str,word);
    strcat(str,":");
    strcat(str,meaning);
   FILE *ptr;
   ptr=fopen("file.txt","a");
   fputs(str,ptr);
   fclose(ptr);
}

void del_word(char *key)
{
	FILE *ptr,*tptr;
	ptr=fopen("file.txt","r");
	if(ptr == NULL)
    {
        printf("Unable to open file.\n");
        printf("Please check you have read/write previleges.\n");
		return;
    }
	int line=-1;
	char str[200];
	char *pos;
	while ((fgets(str, 100, ptr)) != NULL)
    {
        line++;
		strncpy(str,strtok(str, ":"),190);
		//printf("'%s'\n",str);
        // Find first occurrence of word in str
        pos = strstr(str, key);

        if (pos != NULL)
        {
            break;
        }
    }
	fclose(ptr);
	//printf("line number %d",line);
	if(!pos)
		return;
	else
		printf("'%s' has been deleted\n",str);
	int ctr=-1;
	ptr=fopen("file.txt","r");
	tptr=fopen("temp.txt","w");
	if (!tptr) 
	{
        printf("Unable to open a temporary file to write!!\n");
        fclose(ptr);
        return ;
    }
	while ((fgets(str, 100, ptr)) != NULL) 
			{
					ctr++;
					/* skip the line at given line number */
					if (ctr != line) 
					{
						//ctr++;
						fprintf(tptr, "%s", str);
						//ctr++;
					}
			}
        fclose(ptr);
        fclose(tptr);
		remove("file.txt");
		rename("temp.txt","file.txt");
		return;
}

void find_syn(struct meaning* head,char* meaning, char* word)
{
	struct meaning* temp=head;
	while(temp!=NULL)
	{
		if(strncmp(temp->sentence,meaning,450)==0)
		{
			struct word* temp2=temp->next_word;
			if(temp2->next==NULL)
			printf("\nNo synonyms for %s available",word);

			else
			{
				printf("\nSynonyms of %s are:",word);
                while(temp2!=NULL)
				{
					if(strncmp(temp2->w,word,190)!=0)
                    printf("\n%s",temp2->w);
					temp2=temp2->next;
				}
			}
			break;
		}
		temp=temp->next_meaning;
	}
}

void del_thes(struct meaning* head,char* key, char* ans)
{
	//char ans[500];
	//printf("word: %s\n",search(root,key));
	//strcpy(ans,search(root,key));
	//printf("print ans %s\n",ans);
	if(strncmp(ans,"Not found",450)==0)
	{
		//printf("compared to not found\n");
		return;
	}
	//printf("before declaration\n");
	struct meaning* temp=head;
	struct meaning* cur;
	while(temp!=NULL)
	{
		//printf("into the loop\n");
		if(strncmp(ans,temp->sentence,450)==0)
		{
			struct word* temp_word=temp->next_word;
			struct word* cur_word;
			if(strncmp(temp_word->w,key,190)==0)
			{
				temp->next_word=temp_word->next;
				//printf("Word %s has been deleted from LL\n",temp_word->w);
				break;
			}
			while((temp_word!=NULL)&&(strncmp(key,temp_word->w,190)!=0))
			{
				cur_word=temp_word;
				temp_word=temp_word->next;
			}
			
			if(temp_word!=NULL)
				cur_word->next=temp_word->next;
			//printf("Word %s has been deleted from LL\n",temp_word->w);
			free(temp_word);
			break;

		}
		temp=temp->next_meaning;
	}
	temp=head;
	if(temp->next_word==NULL)
	{
		head=temp->next_meaning;
		//printf("Meaning %s has been deleted from LL\n",temp->sentence);
		free(temp);
		return;
	}
	while(temp!=NULL && (strncmp(ans,temp->sentence,450)!=0))
	{
		cur=temp;
		temp=temp->next_meaning;
	}
	if(temp!=NULL && temp->next_word==NULL)
	{
		cur->next_meaning=temp->next_meaning;
		//printf("Meaning %s has been deleted from LL\n",temp->sentence);
		free(temp);
		return;
	}
}


void destroy(struct meaning** head )
{
	struct meaning* cur=*head;
	while(cur->next_meaning!=NULL)
	{
		struct word *temp2=cur->next_word;

		while(temp2->next!=NULL)
		{
			struct word *cur2=temp2;
			temp2=temp2->next;
			free(cur2);
		}

		free(temp2);
		cur=cur->next_meaning;
	}

	free(cur);
	*head=NULL;
}

void destroy_trie(struct trienode** root)
{
	struct trienode* temp= *root;
	
	int i;

	for(i=0;i<255;i++)
	{
		if((temp->child[i])!=NULL)
		{
			destroy_trie(&temp->child[i]);
			free(temp->child[i]);
		}
	}
}
