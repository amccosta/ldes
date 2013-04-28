/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldlinklist.h - Header File

    Description: Linked list class.

    v1.0 - 04/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation

    v1.1 - 14/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Added the 'DeleteContents' functionality
         - Implemented the 'AddSorted' member function
         - Implemented the 'RemoveAllNodes' member function
*/

#ifndef _LD_LINKLIST_H
#define _LD_LINKLIST_H

#include "ldtypes.h"

// Linked list node
template <class Type>
class ldLListNode
{
    public:

        Type               *Contents;            // Contents of node
        ldLListNode<Type>  *NextNode;            // Pointer to next node

        // Default constructor
        ldLListNode();

        // Constructor from pointer
        ldLListNode(const Type *contents);      // Node to add
};

// Linked list class
template <class Type>
class ldLinkList
{
    private:

                ldLListNode<Type>  *FirstNode;                      // Pointer to first node
                ldLListNode<Type>  *LastNode;                       // Pointer to last node
        mutable ldLListNode<Type>  *CurrentNode;                    // Pointer to current node

                uint32              Size;                           // List size (number of nodes)
                bool                _DeleteContents;                // If true deletes the nodes' contents

        // Private search method
        ldLListNode<Type> *FindNode(const Type *contents) const;    // Node to search

    public:

        // Default constructor
        ldLinkList(bool delCont = true);                            // Delete contents' flag

        // Destructor
        ~ldLinkList();

        // Adds a node to the list. Does not affect the current node unless this is the first
        // node added to the list, in which case this becomes the current node, as well as the first.
        bool AddNode(const Type *contents);                         // Node to add

        // Adds a node to the list, immediately after the current node.
        // Then sets the current node to be the one just added.
        bool AddCurrentNode(const Type *contents);                  // Node to add

        // Adds a node to the list. To maintain a sorted list this must be the only
        // 'add' function. Then sets the current node to be the one just added.
        bool AddSorted(const Type *contents);                       // Node to add

        // Removes the specified node from the list
        Type *RemoveNode(const Type *contents);                     // Node to remove

        // Removes the current node from the list
        Type *RemoveCurrentNode();

        // Removes all the nodes from the list
        void RemoveAll();

        // Deletes the specified node from the list
        bool DeleteNode(const Type *contents);                      // Node to delete

        // Deletes the current node from the list
        bool DeleteCurrentNode();

        // Deletes all the nodes from the list
        void Delete();

        // Returns the first node in the list, and sets the current node to the first one.
        Type *GetFirstNode() const;

        // Returns the first node in the list, but does not set the current node to the first one.
        Type *PeekFirstNode() const;

        // Returns the last node in the list, and sets the current node to the last one.
        Type *GetLastNode() const;

        // Returns the last node in the list, but does not set the current node to the last one.
        Type *PeekLastNode() const;

        // Returns the ldevious node in the list, and sets the current node to this one.
        Type *GetPrevNode() const;

        // Returns the ldevious node in the list without changing the current node
        Type *GetPrevNode(const Type *contents) const;              // Current node

        // Returns the next node in the list, and sets the current node to this one
        Type *GetNextNode() const;

        // Returns the next node in the list without changing the current node
        Type *GetNextNode(const Type *contents) const;              // Current node

        // Sets the specified node as the current one
        bool SetCurrentNode(const Type *contents) const;            // Node to make current

        // Returns the current node in the list
        Type *GetCurrentNode() const;

        // Gets number of nodes in list
        uint32 GetSize() const;

        // Speficies if the nodes' contents can be deleted
        void DeleteContents(bool flag);                             // Delete contents' flag
};

#include "ldlinklist.inl"

#endif  // _LD_LINKLIST_H
