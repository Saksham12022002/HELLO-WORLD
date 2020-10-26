#include<stdio.h>
#include<stdlib.h>
struct Node{
int key;
struct Node* left;
struct Node* right;
char lthread,rthread;
};
//This insertion will return root the node back
//it makes thread and remove thread wherever needed
struct Node* insert(struct Node* root,int key) 
{
 //First we will check whether a duplicate is already present or not
struct Node* cur=root;
struct Node* parent=NULL;
 //search the key
while(cur!=NULL)
 {
if(key==(cur->key))
 {
printf("Key already inserted ! Try different key\n");
return root;
 }
parent=cur;
 //Traverse to left subtree
if(key<(cur->key))
 {
if(cur->lthread=='n'){
cur=cur->left;
 }
else
 {
break;
 }
 }
 //Traverse to right subtree
else
 {
if(cur->rthread=='n'){
cur=cur->right;
 }
else{
break;
 }
 } 
 }
 //now we are out of loop,now we have to insert the key
struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
temp->key=key;
temp->lthread='y';
temp->rthread='y';
 //base case, if tree is empty
if(parent==NULL)
 {
root=temp;
temp->left=NULL;
temp->right=NULL;
 }
 //if key to be inserted in left
else if(key<(parent->key))
 {
temp->left=parent->left;
temp->right=parent;
parent->lthread='n';
parent->left=temp;
 }
 // if key to be inserted in right of its parent
else
 {
temp->left=parent;
temp->right=parent->right;
parent->rthread='n';
parent->right=temp;
 }
 //at last return root of tree
return root; 
}
//Total three cases for deletion caseA ,caseB and caseC
struct Node* caseA(struct Node* root, struct Node* parent,struct Node* cur)
{
 // If Node to be deleted is root
if (parent==NULL)
root=NULL;
 // If Node to be deleted is left
 // of its parent
else if (cur==parent->left) {
parent->lthread = 'y';
parent->left = cur->left;
 }
else {
parent->rthread = 'y';
parent->right = cur->right;
 }
 // Free memory and return new root
free(cur);
return root;
}
//case B, it also required inSucc and inPred
// Returns inorder successor using left
// and right children (Used in deletion)
struct Node* inSucc(struct Node* ptr)
{
if (ptr->rthread=='y')
return ptr->right;
ptr = ptr->right;
while (ptr->lthread=='n')
ptr = ptr->left; 
return ptr;
}
struct Node* inPred(struct Node* ptr)
{
if (ptr->lthread=='y')
return ptr->left;
ptr = ptr->left;
while (ptr->rthread=='n')
ptr = ptr->right;
return ptr;
}
struct Node* caseB(struct Node* root, struct Node* parent,struct Node* cur)
{
struct Node* child;
 // Initialize child Node to be deleted has
 // left child.
if (cur->lthread=='n')
child = cur->left;
 // Node to be deleted has right child.
else
child=cur->right;
 // Node to be deleted is root Node.
if (parent==NULL)
root=child;
 // Node is left child of its parent.
else if (cur==parent->left)
parent->left = child;
else
parent->right = child;
 // Find successor and predecessor 
struct Node* s = inSucc(cur);
struct Node* p = inPred(cur);
 // If cur has left subtree.
if (cur->lthread=='n'){
p->right = s;
 }
 // If cur has right subtree.
else {
if(cur->rthread=='n'){
s->left = p;
 }
 }
free(cur);
return root;
}
//case C
struct Node* caseC(struct Node* root, struct Node* parent,struct Node* cur)
{
 // Find inorder successor and its parent.
struct Node* parsucc=cur;
struct Node* succ=cur->right;
 // Find leftmost child of successor
while (succ->left!=NULL) {
parsucc=succ;
succ=succ->left;
 }
cur->key=succ->key;
if (succ->lthread =='y'&&succ->rthread=='y')
root = caseA(root, parsucc, succ);
else 
root = caseB(root, parsucc, succ);
return root;
}
struct Node* delete(struct Node* root,int key)
{
 //initialize parent NULL and curr=root;
struct Node* parent=NULL;
struct Node* cur=root;
int isFind=0;
 //Traverse tree to search key
while(cur!=NULL)
 {
if(key==(cur->key))
 {
isFind=1;
break;
 }
 //if not found
parent=cur;
 //traverse left subtree
if(key<(cur->key))
 {
if(cur->lthread=='n'){
cur=cur->left;
 }
else{
break;
 }
 }
 //traverse right subtree
else{ 
if(cur->rthread=='n'){
cur=cur->right;
 }
else{
break;
 }
 }
 }
if(isFind==0)
 {
printf("Key not Present,Try again!");
 }
 //if deleted has two children
else if(cur->lthread=='n'&&cur->rthread=='n')
 {
root=caseC(root,parent,cur);
 }
 //have only left child
else if(cur->lthread=='n')
 {
root=caseB(root,parent,cur);
 }
 //have only right child
else if(cur->rthread=='n')
 {
root=caseB(root,parent,cur);
 }
 //if have no child
else
 {
root=caseA(root,parent,cur);
 } 
return root;
}
//Preorder traversal of Threaded binary tree
void preorder(struct Node* root)
{
if(root==NULL)return;
printf("%d ",root->key);
if(root->lthread=='n'){
preorder(root->left);
 }
if(root->rthread=='n'){
preorder(root->right);
 }
}
//inorder traversal of threaded binary tree
void inorder(struct Node* root)
{
if(root==NULL)
 {
printf("Tree is empty\n");
 }
struct Node* ptr=root;
while(ptr->lthread=='n'){
ptr=ptr->left;
 }
while(ptr!=NULL){
printf("%d ",ptr->key);
ptr=inSucc(ptr);
 }
} 
int main()
{
int choice,num;
struct Node* root=NULL;
do
{
printf("\n\n1.Insert a node in Tree\n");
printf("2.Delete a node from Tree\n");
printf("3.Display Preorder traversal of Tree\n");
printf("4.Display inorder traversal of Tree\n");
printf("5.Exit\n");
printf("Enter your choice : ");
scanf("%d",&choice);
switch(choice)
 {
case 1:
printf("Enter the key to insert : ");
scanf("%d",&num);
root=insert(root,num);
break;
case 2:
printf("Enter key to be deleted : ");
scanf("%d",&num);
root=delete(root,num);
break;
case 3:
printf("Preorder Traversal of Trees is :\n ");
preorder(root);
printf("\n");
break;
case 4:
printf("Inorder Traversal of Trees is :\n ");
inorder(root);
printf("\n");
break; 
case 5: break;
default:
printf("Invalid choice, Try again");
 }}
 while (choice!=5);
} 
