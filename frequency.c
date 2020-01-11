#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Iterative function to search a string in Trie. It returns 1
// if the string is found in the Trie, else it returns 0
int search(struct Trie* head, char* str)
{

	// return 0 if Trie is empty
	if (head == NULL)
		return 0;

	struct Trie* curr = head;
	while (*str)
	{
		// go to next node
		curr = curr->character[*str - 'a'];
		
		// if string is invalid (reached end of path in Trie)
		if (curr == NULL)
			return 0;

		// move to next charstracter
		str++;
	}

	// if current node is a leaf and we have reached the
	// end of the string, return 1
	return curr->isLeaf;
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

// returns 1 if given node has any children
int haveChildren(struct Trie* curr)
{
	for (int i = 0; i < CHAR_SIZE; i++)
		if (curr->character[i])
			return 1;	// child found

	return 0;
}

// Recursive function to delete a string in Trie
int deletion(struct Trie **curr, char* str)
{
	// return if Trie is empty
	if (*curr == NULL)
		return 0;

	// if we have not reached the end of the string
	if (*str)
	{
		// recur for the node corresponding to next character in
		// the string and if it returns 1, delete current node
		// (if it is non-leaf)
		if (*curr != NULL && (*curr)->character[*str - 'a'] != NULL &&
			deletion(&((*curr)->character[*str - 'a']), str + 1) &&
			(*curr)->isLeaf == 0)
		{
			if (!haveChildren(*curr))
			{
				free(*curr);
				(*curr) = NULL;
				return 1;
			}
			else {
				return 0;
			}
		}
	}

	// if we have reached the end of the string
	if (*str == '\0' && (*curr)->isLeaf)
	{
		// if current node is a leaf node and don't have any children
		if (!haveChildren(*curr))
		{
			free(*curr); // delete current node
			(*curr) = NULL;
			return 1; // delete non-leaf parent nodes
		}

		// if current node is a leaf node and have children
		else
		{
			// mark current node as non-leaf node (DON'T DELETE IT)
			(*curr)->isLeaf = 0;
			return 0;	   // don't delete its parent nodes
		}
	}

	return 0;
}

void printAllWords(struct Trie* head,char *word,int pos)
{

	if(head == NULL) return ;
	
		
		if(head->isLeaf==1) 
		{
		word[pos] = '\0';
		char tmp[strlen(word)];
		//printf("Size Of tmp:%ld \t",strlen(word));
		strcpy(tmp,word);
		printf("%s \t %d \n",tmp,wordRep(head,""));
			
		}
		for(int i=0; i<CHAR_SIZE; i++)
   		{
      		if(head->character[i] != NULL)
        	{
         	word[pos] = i+'a';
         	printAllWords(head->character[i], word, pos+1);
      		}
   		}
}




// Trie Implementation in C - Insertion, Searching and Deletion
int main(int argc, char *argv[])
{
	
	if(argc!=1 && argc!=2)
	{

		printf("Wrong Usage! Correct Usage is %s r (Or without r) \n",argv[0]);
		return 0;
	}

	char *arg=argv[1];
	printf(" %s \n",arg);
	if(strcmp(argv[1],"r")!=0)
	{
		printf("Not r");
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
        //printf(" %d ",ch);
        text[index] = ch;
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
		//wordRep(head,words[j]);
		//printf("%s \t %d \n", words[j],wordRep(head,words[j]));
	}
	
	
	//char *words[i];
	printAllWords(head,*words,0);
	return 0;
}