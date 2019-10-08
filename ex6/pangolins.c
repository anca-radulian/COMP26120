#include <stdio.h>

struct node {
	char *object;
	char *question;
	struct node *yesNode;
	struct node *noNode;
};

struct tree {
	struct node *currentNode;
	struct tree *leftTree;
	struct tree *rightTree;
};

static void nodePrint (struct node *currentNode){
  printf("\n");
  printf("Object: %s\n", currentNode->object);

  if (currentNode->question == NULL)
	printf ("[Nothing]\n");
  else{
  printf("Question: %s\n", currentNode->question);
	if (currentNode->yesNode == NULL)
	  printf("[Nothing]\n");
	else
    printf("Yes: %s\n",currentNode->yesNode->object);
	if (currentNode->noNode == NULL)
	  printf("[Nothing]\n");
	else
  	printf("Yes: %s\n",currentNode->noNode->object);
	}

}


static void printTree(struct node* currentNode)
{
    if(currentNode == NULL)
        return;
    else
    {
        if(currentNode->question != NULL)
        {
            printf("Question: %s\n",currentNode->question);
            free(currentNode->question);
        }
        else if(currentNode->object != NULL)
        {
            printf("Object: %s\n",currentNode->object);
            free(currentNode->object);
        }

        if(currentNode->yesNode !=NULL)
        {
            printf("Yes: ");
            printTree(currentNode->yesNode);

        }
          if(currentNode->noNode !=NULL)
        {
            printf("No: ");
            printTree(currentNode->noNode);

        }

        free(currentNode);

    }
}


int main(int argc, char **argv)
{
  struct node *node1,*node2, *node3,*node4,*node5;
  node1 =(struct node *)malloc(sizeof(struct node));
  node1->object = "Rose";
  node1->question = "Does it smell?";
  node1->yesNode = node2;
  node1->noNode = node3;

  node2 =(struct node*)malloc(sizeof(struct node));
  node2->object = "Cake";
  node2->question = "Can you eat it?";
  node2->yesNode = node4;
  node2->noNode = NULL;

  node3 =(struct node*)malloc(sizeof(struct node));
  node3->object = "Cat";
  node3->question = "Does it have fur?";
  node3->yesNode = node5;
  node3->noNode = NULL;

  node4 =(struct node*)malloc(sizeof(struct node));
  node4->object = "Burger";
  node4->question = "Is it sweet?";
  node4->yesNode = NULL;
  node4->noNode = NULL;


  node5 =(struct node*)malloc(sizeof(struct node));
  node5->object = "Guitar";
  node5->question = "Can you play it?";
  node5->yesNode = NULL;
  node5->noNode = NULL;

/*

  struct tree *exampleTree;
  exampleTree->currentNode = node1;
  exampleTree->leftTree->currentNode=NULL;
  exampleTree->rightTree->currentNode= NULL;
  printTree(exampleTree->currentNode);
*/


  return 0;

}
