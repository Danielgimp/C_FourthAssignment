#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// define character size
#define CHAR_SIZE 26

// A Trie node
struct Trie
{
	int isLeaf;	// 1 when node is a leaf node
	struct Trie* character[CHAR_SIZE];
	int counter;
};

// Function that returns a new Trie node
struct Trie* getNewTrieNode()
{
	struct Trie* node = (struct Trie*)malloc(sizeof(struct Trie));
	node->isLeaf = 0;

	for (int i = 0; i < CHAR_SIZE; i++)
		node->character[i] = NULL;

	return node;
}

// Iterative function to insert a string in Trie
void insert(struct Trie *head, char* str)
{
	
	// start from root node
	struct Trie* curr = head;
	curr->counter=0;
	while (*str)
	{
		// create a new node if path doesn't exists
		if (curr->character[*str - 'a'] == NULL)		
			curr->character[*str - 'a'] = getNewTrieNode();
					
		// go to next node
		curr = curr->character[*str - 'a'];
		curr->counter=curr->counter+1;
		//printf("The Letter %c count is: %d\n",*str,curr->counter);

		// move to next character
		str++;
	}

	// mark current node as leaf
	curr->isLeaf = 1;
}


int wordRep(struct Trie* head, char* str)
{	
	int i=0;
	int size=strlen(str)+1;
	//printf("String Size is: %d\n",size);
	int letter_count[size];

	// return 0 if Trie is empty
	if (head == NULL)
		return 0;
	struct Trie* curr=(struct Trie*)malloc((sizeof(head)));
	curr=head;
	while (*str)
	{
		printf("h \n");
		// go to next node
		curr = head->character[*str - 'a'];
		//printf("Nubmer Is: %d \n",curr->counter);
		int temp=head->counter;
		letter_count[i]=temp;
		// if string is invalid (reached end of path in Trie)
		if (curr == NULL)
			return 0;

		// move to next character
		str++;
		i++;
	}
	
	// if current node is a leaf and we have reached the
	// end of the string, return 1
	for(int i=0;i<size-1;i++)
	{
		//printf("%d \t",letter_count[i]);
		if(letter_count[i]!=letter_count[i+1]) return 1;
	}
	if(curr->isLeaf==1) return curr->counter;
	return 1;
}

void printWord(struct Trie* head,char* word, int pos)
{		
   		word[pos] = '\0';
		char tmp[strlen(word)];
		int count=wordRep(head,"");
		sprintf(tmp,"\t %d",count);
		strcat(word, tmp);
		printf("%s \n",word);
	
		
}

void printAllWords(struct Trie* head,char *word,int pos)
{
		
		if(head == NULL) return;
	
		if(head->isLeaf==1) 
		{
		printWord(head,word,pos);
		
		}
		for(int i=0; i<CHAR_SIZE ; i++)
   		{
      		if(head->character[i] != NULL)
        	{
         	word[pos] = i+'a';

         	printAllWords(head->character[i], word, pos+1);
      		}
			     		     		     		
   		}
}

void printAllWordsReverse(struct Trie* head,char *word,int pos)
{
		
		if(head == NULL) return;
	
		if(head->isLeaf==1) 
		{
		printWord(head,word,pos);
		
		}
		for(int i=CHAR_SIZE-1; i>=0 ; i=i-1)
   		{
      		if(head->character[i] != NULL)
        	{
         	word[pos] = i+'a';
         	printAllWordsReverse(head->character[i], word, pos+1);
      		}
			     		     		     		
   		}
}



// Trie Implementation in C - Insertion, Searching and Deletion
int main(int argc, char *argv[])
{
	
	if(argc!=1 && argc!=2)
	{

		printf("Wrong Usage! Correct Usage is %s r(R) (Or without r,R) \n",argv[0]);
		return 0;
	}
	

	

	struct Trie* head = getNewTrieNode();
	char *text = NULL, *tmp = NULL;
    size_t size = 0, index = 0;
    int ch = EOF;

    while (ch) {
        ch = getc(stdin);

        /* Check if we need to stop. */
        if (ch == EOF)  ch = 0;

        /* Check if we need to expand. */
        if (size <= index) {
            size += 1024; //expand size with size+1024 (arbitrary value)
            tmp = realloc(text, size); //make tmp be in size of "size"
            if (!tmp) {
                free(text);
                text = NULL;
                break;
            }
            
            text = tmp; //text is now temp
        }
        if(ch>=65 && ch<=90) ch=ch+32;
		if((ch>=97 && ch<=122) || (ch==' ' || ch=='.' || ch==',' || ch=='\n')) text[index] = ch;
        index++;
    }

    int str_size=strlen(text);
    //printf("str_size %d \n",str_size);
    int i = 0;
    char *p = strtok (text, " .,'\n'");
    char *words[str_size];

    while (p != NULL)
    {
        words[i] = p;
        i++;
        p = strtok(NULL, " .,'\n'");
    }
   
	for (int j = 0; j < i; j++) 
	{
		insert(head,words[j]);
		
	}
	
	if(argv[1]!=NULL)
	{
		if(strcmp(argv[1],"R")==0) argv[1]="r";
		if(strcmp(argv[1],"r")!=0)
		{
	    printf("Wrong Usage! Correct Usage is %s r(R) (Or without r,R) \n",argv[0]);
		return 0;
		}
		if(strcmp(argv[1],"r")==0)
		printAllWordsReverse(head,*words,0);
	}
	else
	printAllWords(head,*words,0);
	
	
	return 0;
}