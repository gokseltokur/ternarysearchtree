/*


	Göksel Tokur 150116049


*/
#include<stdlib.h>
#include<stdio.h>

int depthlevel = 0;

struct bin_tree {
int data;
struct bin_tree * right, * left, * mid;
};
typedef struct bin_tree node;

//insert function for the ternary search tree
void insert(node ** tree, int val){
    node *temp = NULL;
    //allocating memory for the node
    if(!(*tree)){
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = temp->mid = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }
    //if value is smaller than current node's data, node go to left child.
    if(val < (*tree)->data){
        insert(&(*tree)->left, val);
    }
    //if value is bigger than current node's data 
	//and also smaller than square of current node's data, node go to mid child.
    else if(val > (*tree)->data && val <=  ((*tree)->data)*((*tree)->data) ){
    	insert(&(*tree)->mid, val);
	}
	// if value is bigger than square of current node's data, node go to right child.
    else if(val > (*tree)->data){
        insert(&(*tree)->right, val);
    }
}

//find function to find node's depth level.
node* find(node ** p, int val){
	node **tree= p;
    if(!(*tree)){
        return NULL;
    }
    if(val < (*tree)->data){
    	printf("left -> ");
    	depthlevel++;
        find(&((*tree)->left), val);
    }
    else if(val > (*tree)->data && val <= ((*tree)->data)*((*tree)->data)){
    	printf("mid -> ");
    	depthlevel++;
    	find(&((*tree)->mid), val);
	}
    else if(val > (*tree)->data){
    	printf("right -> ");
    	depthlevel++;
        find(&((*tree)->right), val);
    }
    else if(val == (*tree)->data){
    	printf("There is %d", val);
    	printf("\nDepth Level of %d: %d\n", (*tree)->data, depthlevel);
    	depthlevel=0;
        return *tree;
    }
}

//To find minimum data of the tree.
node* findMin(node *p){
	if(p != NULL){
		while(p->left != NULL){
			p = p->left;
		}	
	}
	return p;
}

//To find maximum data of the tree.
node* findMax (node *p){
	if (p == NULL) 
		return NULL;
	if(p->right){
		findMax(p->right);
	}
	else if( !(p->right) && (p->mid)){
		findMax(p->mid);
	}
	else if( !(p->right) && !(p->mid) ){
		return p;
	}
}

node *removenode(int key, node **p); //implicit declaration.

//To control and relocate nodes of the right subtree of the current node
//while removing a node that has tree child.
node* preSearch(node **p , node **comingnode){
	if((*p) == NULL)
		return;	
	if(((*p)->left))
		preSearch(&(*p)->left, &(*comingnode));	
	if(((*p)->mid))
		preSearch(&(*p)->mid, &(*comingnode));
	if(((*p)->right))
		preSearch(&(*p)->right, &(*comingnode));
	if(((*comingnode)->data)*((*comingnode)->data) >= (*p)->data ){
		insert(&(*comingnode), (*p)->data);
		removenode((*p)->data, &(*p));		
	}
}

//Function to remove a node from tree
node *removenode(int key, node **p){
	node *temp;
	// if tree is empty return error message.
	if((*p) == NULL){
		printf("Empty tree");
		return;
	}
	// this block of code finds correct location of the node that is wanted to remove.
	if(key < (*p)->data){
		removenode(key, &(*p)->left);
	}
	else if(key > (*p)->data && key <=  ((*p)->data)*((*p)->data) ){
		removenode(key, &(*p)->mid);
	}
	else if(key > (*p)->data){
		removenode(key, &(*p)->right);
	}
	else if(key == (*p)->data){
		//Remove case for node that has no child.	
		if( !((*p)->left) && !((*p)->mid) && !((*p)->right) ){
			//printf("\n--\n");
			(*p) = NULL;		 			
		}
		
		//Remove case for node that has left child.
		else if ( (((*p)->left) && !((*p)->mid) && !((*p)->right)) ){
			//printf("\nL\n");
			temp=findMax((*p)->left);
			(*p)->data = temp->data;
			temp=removenode((*p)->data, &(*p)->left);
			
		}
		//Remove case for node that has left, right childs.
		else if(((*p)->left) && !((*p)->mid) && ((*p)->right) ){
			//printf("\nLR\n");
			node *maxleft;
			maxleft = findMax((*p)->left);
			(*p)->data = (maxleft)->data;
			removenode((*p)->data, &(*p)->left);
			//free(maxleft);  // ?????????????????
		}
		//Remove case for node that has mid child.
		else if( (!((*p)->left) && ((*p)->mid) && !((*p)->right))){
			//printf("\nM\n");
			temp=findMin((*p)->mid);
			(*p)->data = temp->data;
			temp=removenode((*p)->data, &(*p)->mid);
				
		}
		//Remove case for node that has left, mid childs
		else if ( (((*p)->left) && ((*p)->mid) && !((*p)->right)) ){
			//printf("\nLM\n");
			node *minmid;
			minmid = findMin((*p)->mid);
			(*p)->data = (minmid)->data;
			removenode((*p)->data, &(*p)->mid);
			//free(minmid);  // ???????????????
		}
		//Remove case for node that has left, right childs.
		else if(!((*p)->left) && !((*p)->mid) && ((*p)->right)){
			//printf("\nR\n");
			temp=findMin((*p)->right);
			(*p)->data = temp->data;
			temp=removenode((*p)->data, &(*p)->right);
			
		}
		//Remove case for node that has mid, right childs or left, mid, right childs.
		else if( (!((*p)->left) && ((*p)->mid) && ((*p)->right)) || (((*p)->left) && ((*p)->mid) && ((*p)->right))){
			//printf("\nMR-LMR\n");
			node *minmid;
			minmid = findMin((*p)->mid);
			(*p)->data = (minmid)->data;
			removenode((*p)->data, &(*p)->mid);			
			//free(minmid);  // ???????????????	
			 preSearch(&((*p)->right), &(*p)); // &&&&&&&&&&&
		}
		return (*p);
	}
}

//Function to write tree preorder traversal
void preOrder(node *p){
	if(p == NULL){
		printf("EMPTY");
		return;
   }
	printf("%d ", p->data);
	if((p->left)){
		//printf("left");
		preOrder(p->left);
	}
	if((p->mid)){
		//printf("mid");
		preOrder(p->mid);
	}
	if((p->right)){
		//printf("right");
		preOrder(p->right);
	}
}

//Function to write tree inorder traversal
void inOrder(node *p){
	if(p == NULL){
		printf("EMPTY");
		return;
    }
	if((p->left)){
		//printf("left");
		inOrder(p->left);
	}
	if((p->mid)){
		//printf("mid");
		inOrder(p->mid);
	}
	printf("%d ", p->data);
	if((p->right)){
		//printf("right");
		inOrder(p->right);
	}
}

//Function to write tree postorder traversal
void postOrder(node *p){
	if(p == NULL){
		printf("EMPTY");
		return;
    }
	if((p->left)){
		//printf("left");
		postOrder(p->left);
	}
	if((p->mid)){
		//printf("mid");
		postOrder(p->mid);
	}
	if((p->right)){
		//printf("right");
		postOrder(p->right);
	}
	printf("%d ", p->data);
}

//Main function
int main(){
	FILE *file = fopen("input.txt" , "r");
	if(file == NULL){
		printf("ERROR, file does not exist.");
	}
	
	node *root;
	root = NULL;
	int i = 0;
	while (!feof (file)){  
      fscanf (file, "%d", &i);
      insert(&root, i);
      printf("%d\n", i);
    }
	printf("\nAll of nodes inserted to the tree successfully.\n");
	printf("Preorder\n");
	preOrder(root);
	printf("\n\nPostorder\n");
	postOrder(root);
	printf("\n\nInorder\n");
	inOrder(root);
	
	// MENU
	int choice;
	while(1){
		printf("\nWhat do you want to do?\n  -Enter 1 to remove a node from tree.\n  -Enter 2 to find a node in tree.\n");
		scanf("%d", &choice);
		
		if(choice == 1){
			printf("Which node do you want to remove?\n");
			int rnode;
			scanf("%d", &rnode);
			removenode(rnode, &root);
			printf("Node is removed. New tree is;");
			printf("\n------------------------------------------");
			printf("\nPreorder\n");
			preOrder(root);
			printf("\n\nPostorder\n");
			postOrder(root);
			printf("\n\nInorder\n");
			inOrder(root);
			printf("\n------------------------------------------");
		}
		if(choice == 2){
			printf("Which node do you want to find out?\n");
			int fnode;
			node* fn;
			scanf("%d", &fnode);
			printf("Root -> ");
			fn = find(&root, fnode);
			if(!fn){
				printf("There is no %d", fnode);
				depthlevel=0;
			}
		}
	}
	return 0 ;
}

/*


	Göksel Tokur 150116049


*/
