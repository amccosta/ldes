/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldlinklist.inl - Inline File

    Description: Linked list class.

    v1.0 - 04/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation

    v1.1 - 14/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Added the 'DeleteContents' functionality
         - Implemented the 'AddSorted' member function
         - Implemented the 'RemoveAllNodes' member function
*/

#ifndef _LD_LINKLIST_INL
#define _LD_LINKLIST_INL

#include "ldlinklist.h"

#ifndef NULL
#define NULL 0
#endif

// Default constructor
template <class Type>
ldLListNode<Type>::ldLListNode()
{
    Contents = NULL;
    NextNode = NULL;
}

// Constructor from pointer
template <class Type>
ldLListNode<Type>::ldLListNode(const Type *contents)
{
    Contents = const_cast<Type *>(contents);
    NextNode = NULL;
}

// Private search method
template <class Type>
ldLListNode<Type> *ldLinkList<Type>::FindNode(const Type *contents) const
{
    ldLListNode<Type> *node = FirstNode;
    bool              found = false;

    while(!found && node != NULL)
    {
        if(contents != node->Contents) node = node->NextNode;
        else found = true;
    }

    if(found) return node;

    return NULL;
}

// Default constructor
template <class Type>
ldLinkList<Type>::ldLinkList(bool delCont)
{
    FirstNode   = NULL;
    LastNode    = NULL;
    CurrentNode = NULL;

    Size = 0;

   _DeleteContents = delCont;
}

// Destructor
template <class Type>
ldLinkList<Type>::~ldLinkList()
{
    Delete();
}

// Adds a node to the list. Does not affect the current node unless this is the first
// node added to the list, in which case this becomes the current node, as well as the first.
template <class Type>
bool ldLinkList<Type>::AddNode(const Type *contents)
{
    if(contents == NULL) return false;

    ldLListNode<Type> *newNode = new ldLListNode<Type>(contents);
    if(newNode == NULL) return false;

    if(FirstNode == NULL)       // This is the first node in the list
    {
        FirstNode   = newNode;
        CurrentNode = newNode;
    }
    else                        // This is not the first node in the list
    {
        LastNode->NextNode = newNode;
    }

    LastNode = newNode;
    Size++;

    return true;
}

// Adds a node to the list, immediately after the current node.
// Then sets the current node to be the one just added.
template <class Type>
bool ldLinkList<Type>::AddCurrentNode(const Type *contents)
{
    if(contents == NULL) return false;

    ldLListNode<Type> *newNode = new ldLListNode<Type>(contents);
    if(newNode == NULL) return false;

    if(CurrentNode == NULL) CurrentNode = LastNode;

    if(FirstNode == NULL)               // Insert the first node
    {
        FirstNode = newNode;
        LastNode  = newNode;
    }
    else if(CurrentNode == LastNode)    // Insert in last
    {
        LastNode->NextNode = newNode;
        LastNode = newNode;
    }
    else                                // Insert in the middle
    {
        newNode->NextNode = CurrentNode->NextNode;
        CurrentNode->NextNode = newNode;
    }

    CurrentNode = newNode;
    Size++;

    return true;
}

// Adds a node to the list. To maintain a sorted list this must be the only
// 'add' function. Then sets the current node to be the one just added.
template <class Type>
bool ldLinkList<Type>::AddSorted(const Type *contents)
{
    if(contents == NULL) return false;

    ldLListNode<Type> *newNode = new ldLListNode<Type>(contents);
    if(newNode == NULL) return false;

    if(FirstNode == NULL)               // Insert the first node
    {
        FirstNode = newNode;
        LastNode  = newNode;
    }
    else
    {
        CurrentNode = FirstNode;
        ldLListNode<Type> *prevCurNode = FirstNode;

        while(CurrentNode != NULL)
        {
            if(newNode->Contents->Importance > CurrentNode->Contents->Importance) break;

            prevCurNode = CurrentNode;
            CurrentNode = CurrentNode->NextNode;
        }

        if(CurrentNode == NULL)         // Insert in last
        {
            LastNode->NextNode = newNode;
            LastNode = newNode;
        }
        else                            // Insert in the middle
        {
            newNode->NextNode = prevCurNode->NextNode;
            prevCurNode->NextNode = newNode;
        }
    }

    CurrentNode = newNode;
    Size++;

    return true;
}

// Removes the specified node from the list
template <class Type>
Type *ldLinkList<Type>::RemoveNode(const Type *contents)
{
    if(SetCurrentNode(contents) == false) return NULL;
    return RemoveCurrentNode();
}

// Removes the current node from the list
template <class Type>
Type *ldLinkList<Type>::RemoveCurrentNode()
{
    if(CurrentNode == NULL) return NULL;

    ldLListNode<Type> *next = CurrentNode->NextNode;

    Type *contents = CurrentNode->Contents;

    if(FirstNode == LastNode)           // This is the unique node in the list
    {
        delete FirstNode;

        FirstNode = NULL;
        LastNode  = NULL;
    }
    else if(CurrentNode == FirstNode)   // This is the first node in the list
    {
        delete FirstNode;

        FirstNode = next;
    }
    else if(CurrentNode == LastNode)    // This is the last node in the list
    {
        ldLListNode<Type> *prev = FirstNode;

        while(prev->NextNode != LastNode) prev = prev->NextNode;

        delete LastNode;

        LastNode = prev;
        LastNode->NextNode = NULL;
    }
    else                                // This is a middle node in the list
    {
        ldLListNode<Type> *prev = FirstNode;

        while(prev->NextNode != CurrentNode) prev = prev->NextNode;

        prev->NextNode = CurrentNode->NextNode;

        delete CurrentNode;
    }

    Size--;
    CurrentNode = next;
    return contents;
}

// Removes all the nodes from the list
template <class Type>
void ldLinkList<Type>::RemoveAll()
{
    if(FirstNode == NULL) return;

    CurrentNode = FirstNode;

    while(CurrentNode != NULL)
    {
        FirstNode = CurrentNode->NextNode;

        delete CurrentNode;

        CurrentNode = FirstNode;
    }

    // FirstNode    = NULL;     (NULL in the end of while cycle)
    // CurrentNode  = NULL;     (NULL in the end of while cycle)
    LastNode        = NULL;
    Size            = 0;
}

// Deletes the specified node from the list
template <class Type>
bool ldLinkList<Type>::DeleteNode(const Type *contents)
{
    if(SetCurrentNode(contents) == false) return false;

    return DeleteCurrentNode();
}

// Deletes the current node from the list
template <class Type>
bool ldLinkList<Type>::DeleteCurrentNode()
{
    Type *contents = RemoveCurrentNode();
    if(contents != NULL)
    {
        if(_DeleteContents) delete contents;

        return true;
    }

    return false;
}

// Deletes all the nodes from the list
template <class Type>
void ldLinkList<Type>::Delete()
{
    if(FirstNode == NULL) return;

    if(!_DeleteContents)
    {
        RemoveAll();
        return;
    }

    CurrentNode = FirstNode;

    while(CurrentNode != NULL)
    {
        FirstNode = CurrentNode->NextNode;

        delete CurrentNode->Contents;
        delete CurrentNode;

        CurrentNode = FirstNode;
    }

    // FirstNode    = NULL;     (NULL in the end of while cycle)
    // CurrentNode  = NULL;     (NULL in the end of while cycle)
    LastNode        = NULL;
    Size            = 0;
}

// Returns the first node in the list, and sets the current node to the first one.
template <class Type>
Type *ldLinkList<Type>::GetFirstNode() const
{
    if(FirstNode == NULL) return NULL;

    CurrentNode = FirstNode;
    return CurrentNode->Contents;
}

// Returns the first node in the list, but does not set the current node to the first one.
template <class Type>
Type *ldLinkList<Type>::PeekFirstNode() const
{
    if(FirstNode == NULL) return NULL;

    return FirstNode->Contents;
}

// Returns the last node in the list, and sets the current node to the last one.
template <class Type>
Type *ldLinkList<Type>::GetLastNode() const
{
    if(LastNode == NULL) return NULL;

    CurrentNode = LastNode;
    return CurrentNode->Contents;
}

// Returns the last node in the list, but does not set the current node to the last one.
template <class Type>
Type *ldLinkList<Type>::PeekLastNode() const
{
    if(LastNode == NULL) return NULL;

    return LastNode->Contents;
}

// Returns the previous node in the list, and sets the current node to this one.
template <class Type>
Type *ldLinkList<Type>::GetPrevNode() const
{
    if(CurrentNode == NULL || CurrentNode == FirstNode) return NULL;

    ldLListNode<Type> *prev = FirstNode;

    while(prev->NextNode != CurrentNode) prev = prev->NextNode;

    CurrentNode = prev;

    return CurrentNode->Contents;
}

// Returns the previous node in the list without changing the current node
template <class Type>
Type *ldLinkList<Type>::GetPrevNode(const Type *contents) const
{
    ldLListNode<Type> *node = FindNode(contents);
    if(node == NULL || node == FirstNode) return NULL;

    ldLListNode<Type> *prev = FirstNode;

    while(prev->NextNode != node) prev = prev->NextNode;

    return node->Contents;
}

// Returns the next node in the list, and sets the current node to this one
template <class Type>
Type *ldLinkList<Type>::GetNextNode() const
{
    if(CurrentNode == NULL || CurrentNode == LastNode) return NULL;

    CurrentNode = CurrentNode->NextNode;

    return CurrentNode->Contents;
}

// Returns the next node in the list without changing the current node
template <class Type>
Type *ldLinkList<Type>::GetNextNode(const Type *contents) const
{
    ldLListNode<Type> *node = FindNode(contents);
    if(node == NULL || node == LastNode) return NULL;

    node = node->NextNode;

    return node->Contents;
}

// Sets the specified node as the current one
template <class Type>
bool ldLinkList<Type>::SetCurrentNode(const Type *contents) const
{
    CurrentNode = FindNode(contents);

    return (CurrentNode != NULL);
}

// Returns the current node in the list
template <class Type>
Type *ldLinkList<Type>::GetCurrentNode() const
{
    if(CurrentNode == NULL) return NULL;

    return CurrentNode->Contents;
}

// Gets number of nodes in list
template <class Type>
uint32 ldLinkList<Type>::GetSize() const
{
    return Size;
}

// Speficies if the nodes' contents can be deleted
template <class Type>
void ldLinkList<Type>::DeleteContents(bool flag)
{
    _DeleteContents = flag;
}

#endif  // _LD_LINKLIST_INL
