//File Name: BST312.h
//
//Go Fish Program
//EE 312
/* Student information for project:
 *
 * Replace <NAME> with your name.
 *
 * On my honor, Aditya Khanna, this programming project is my own work
 * and I have not provided this code to any other student.
 *
 * Name: Aditya Khanna
 * email address: adityakhanna22@yahoo.com
 * UTEID: ak34642
 * Section 5 digit ID: 16225
 */
// A Simple Implementation of a Binary Search Tree

#ifndef BST312_H
#define BST312_H

#include <cstdlib>  // Provides size_t
#include <iostream>
#include <vector>

using namespace std;

template<class ItemType>
class BST312
{
public:

    BST312();

    //Copy constructor
    BST312(const BST312 & src);

    ~BST312();

/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
    void makeEmpty();

/****************************
isEmpty

Function: Checks to see if there are any items in the BST.
Preconditions: BST has been initialized
Postconditions: Returns true if there are no items in the BST, else false.
*****************************/
    bool isEmpty() const;

/****************************
isFull

Function: Determines if you have any more room to add items to the BST
Preconditions: BST has been initialized
Postconditions: Returns true if there is no more room to add items, else false
*****************************/
    bool isFull() const;

/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full.
Postconditions: newItem is in the proper position for a BST.
*****************************/
    void insertItem(const ItemType &);

/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
    void deleteItem(const ItemType& newItem);

/****************************
countNodes

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
    int countNodes();

/****************************
preOrderTraversal

Function: Returns the preOder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> preOrderTraversal();

/****************************
inOrderTraversal

Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> inOrderTraversal();

/****************************
postOrderTraversal

Function: returns the postOder (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> postOrderTraversal();

/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
*****************************/

    bool isItemInTree(const ItemType& item);


private:
    struct TreeNode
    {
        ItemType data;
        TreeNode* left;
        TreeNode* right;
    };

    TreeNode* root;


    void insertItem(TreeNode*& t, const ItemType& newItem);
    void inOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    int countNodes(TreeNode* t) const;
    void deleteNode(TreeNode*& node);
    void makeEmpty(TreeNode*& t);
    void deleteItem(TreeNode*& t, const ItemType& newItem);
    void getPredecessor(TreeNode* t, ItemType& data);
    void preOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void postOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void copyTree(TreeNode*& copy, const TreeNode *originalTree);
    bool isItemInTree(TreeNode*& t, const ItemType& item);
};

/*******************************
//Function implementations
********************************/

//Default Constructor
//Inputs: None
//Outputs/Results: Creates an empty Binary Search Tree
template<class ItemType>
BST312<ItemType>::BST312 ()
{
    root = NULL;
}

//Copy Constructor
//Inputs: Binary Search Tree to be copied
//Outputs/Results: Creates a copy of the Binary Search Tree
template<class ItemType>
BST312<ItemType>::BST312(const BST312 & src)
{
    copyTree(root, src.root);
}

//Destructor
//Inputs: None
//Outputs/Results: Destructs the Binary Search Tree and deallocates memory associated with the Binary Search Tree Object
template<class ItemType>
BST312<ItemType>::~BST312()
{
    makeEmpty();
}

//copyTree
//Inputs: Pointer to BST node to be copied and pointer to BST node to be copied into
//Outputs/Results: Creates a default Card (Ace of Spades)
template<class ItemType>
void BST312<ItemType>::copyTree(TreeNode*& copy, const TreeNode* originalTree)
{
    if (originalTree == NULL)
        copy = NULL;
    else
    {
        copy = new TreeNode;
        copy->data = originalTree->data;

        copyTree(copy->left, originalTree->left);
        copyTree(copy->right, originalTree->right);
    }
}

//deleteNode
//Inputs: Pointer to BST node
//Outputs/Results: Delete BST node and memory associated with it
template<class ItemType>
void BST312 <ItemType>::deleteNode(TreeNode*& t)
{
    ItemType info;
    TreeNode *tempPtr;

    tempPtr = t;

    if (t->left == NULL)
    {
        t = t->right;
        delete tempPtr;
    }
    else if (t->right == NULL)
    {
        t = t->left;
        delete tempPtr;
    }
    else
    {
        getPredecessor(t->left, info);
        t->data = info;
        deleteItem(t->left, info);
    }
}

//getPredecessor
//Inputs: Pointer to BST node and ItemType data
//Outputs/Results: Finds Largest in Left Subtree
template<class ItemType>
void BST312 <ItemType>::getPredecessor(TreeNode* t, ItemType& data)
{
    while (t->right != NULL)
    {
        t = t->right;
    }
    data = t->data;
}

//deleteItem
//Inputs: Pointer to BST node and ItemType data
//Outputs/Results: Deletes BST node with ItemType value if present
template<class ItemType>
void BST312 <ItemType>::deleteItem(TreeNode*& t, const ItemType& newItem)
{
    if (t == NULL)
        return;
    else if (newItem < t->data)
        deleteItem(t->left, newItem);
    else if (newItem > t->data)
        deleteItem(t->right, newItem);
    else
        deleteNode(t);
}

//deleteItem
//Inputs: ItemType data
//Outputs/Results: Deletes BST node with ItemType value if present
template<class ItemType>
void BST312 <ItemType>::deleteItem(const ItemType& newItem)
{
    deleteItem(root, newItem);
}

//makeEmpty
//Inputs: Pointer to BST node
//Outputs/Results: Makes BST object empty and deallocates memory associated with it
template<class ItemType>
void BST312 <ItemType>::makeEmpty(TreeNode*& t)
{
    if (t->left != NULL)
    {
        makeEmpty(t->left);
    }
    if (t->right != NULL)
    {
        makeEmpty(t->right);
    }
    delete t;
}

//makeEmpty
//Inputs: None
//Outputs/Results: Makes BST object empty and deallocates memory associated with it
template<class ItemType>
void BST312 <ItemType>::makeEmpty()
{
    makeEmpty(root);
    root = NULL;
}

//isEmpty
//Inputs: None
//Outputs/Results: Checks if BST object is empty and returns a boolean value of the condition
template<class ItemType>
bool BST312 <ItemType>::isEmpty() const
{
    return (root == NULL);
}

//isFull
//Inputs: None
//Outputs/Results: Checks if BST object is full and returns a boolean value of the condition
template<class ItemType>
bool BST312 <ItemType>::isFull() const
{
    try
    {
        TreeNode *temp = new TreeNode;
        delete temp;
        return false;
    }
    catch (std::bad_alloc)
    {
        return true;
    }

}

//insertItem
//Inputs: Pointer to BST node and ItemType data
//Outputs/Results: Inserts a new node into the tree
template<class ItemType>
void BST312 <ItemType>::insertItem(TreeNode*& t, const ItemType& newItem)
{
    if (t == NULL)
    {
        t = new TreeNode;
        t->data = newItem;
    }
    else if (t->data > newItem)
    {
        insertItem(t->left, newItem);
    }
    else if (t->data < newItem)
    {
        insertItem(t->right, newItem);
    }
}

//insertItem
//Inputs: ItemType data
//Outputs/Results: Inserts a new node into the tree
template<class ItemType>
void BST312 <ItemType>::insertItem(const ItemType& newItem)
{
    insertItem(this->root, newItem);
}

//countNodes
//Inputs: Pointer to BST node
//Outputs/Results: Returns integer value of how many nodes are in the BST
template<class ItemType>
int BST312 <ItemType>::countNodes(TreeNode* t) const
{
    int count = 0;
    if (t == NULL)
    {
        return 0;
    }
    else
    {
        count++;
        count += countNodes(t->left);
        count += countNodes(t->right);
    }
    return count;
}

//countNodes
//Inputs: None
//Outputs/Results: Returns integer value of how many nodes are in the BST
template<class ItemType>
int BST312 <ItemType>::countNodes()
{
    //TreeNode* copy = this->root;
    countNodes(this->root);
}

//preOrderTraversal
//Inputs: Pointer to BST node and Vector of ItemType
//Outputs/Results: Lists all of the nodes in the BST in preOrder in the Vector
template<class ItemType>
void BST312 <ItemType>::preOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    if (t != NULL)
    {
        result.push_back(t->data);
        preOrderTraversal(t->left, result);
        preOrderTraversal(t->right, result);
    }
}

//preOrderTraversal
//Inputs: None
//Outputs/Results: Returns Vector of ItemType with all nodes of BST in preOrder
template<class ItemType>
vector<ItemType> BST312 <ItemType>::preOrderTraversal()
{
    vector<ItemType> result;
    preOrderTraversal(this->root, result);
    return result;
}

//inOrderTraversal
//Inputs: Pointer to BST node and Vector of ItemType
//Outputs/Results: Lists all of the nodes in the BST inOrder in the Vector
template<class ItemType>
void BST312 <ItemType>::inOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    if (t != NULL)
    {
        inOrderTraversal(t->left, result);
        result.push_back(t->data);
        inOrderTraversal(t->right, result);
    }
}

//inOrderTraversal
//Inputs: None
//Outputs/Results: Returns Vector of ItemType with all nodes of BST inOrder
template<class ItemType>
vector<ItemType> BST312 <ItemType>::inOrderTraversal()
{
    vector<ItemType> result;
    inOrderTraversal(this->root, result);
    return result;
}

//postOrderTraversal
//Inputs: Pointer to BST node and Vector of ItemType
//Outputs/Results: Lists all of the nodes in the BST in postOrder in the Vector
template<class ItemType>
void BST312 <ItemType>::postOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    if (t != NULL)
    {
        postOrderTraversal(t->left, result);
        postOrderTraversal(t->right, result);
        result.push_back(t->data);
    }
}

//postOrderTraversal
//Inputs: None
//Outputs/Results: Returns Vector of ItemType with all nodes of BST in postOrder
template<class ItemType>
vector<ItemType> BST312 <ItemType>::postOrderTraversal()
{
    vector<ItemType> result;
    postOrderTraversal(this->root, result);
    return result;
}

//isItemInTree
//Inputs: Pointer to BST node and ItemType item to be checked
//Outputs/Results: Checks the BST if the ItemType item is in the tree and return true if it is (and false otherwise)
template<class ItemType>
bool BST312 <ItemType>::isItemInTree(TreeNode*& t, const ItemType& item)
{
    if (t == NULL)
    {
        return false;
    }
    else if (t->data == item)
    {
        return true;
    }
    else if (t->data > item)
    {
        return isItemInTree(t->left, item);
    }
    else if (t->data < item)
    {
        return isItemInTree(t->right, item);
    }
}

//isItemInTree
//Inputs: ItemType item to be checked
//Outputs/Results: Checks the BST if the ItemType item is in the tree and return true if it is (and false otherwise)
template<class ItemType>
bool BST312 <ItemType>::isItemInTree(const ItemType& item)
{
    return isItemInTree(this->root, item);
}

#endif

