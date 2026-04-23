/* Program name: Product Sorting Linked List (unorderedLinkedList.h)
* Author: Dalila Ait fella
* Date last updated: 4/22/2026
* Purpose: Implements an unordered linked list with merge sort using function pointers for comparison.
*/

#ifndef UNORDERED_H
#define UNORDERED_H

#include <stdexcept>
#include "linkedlist.h"

template <class t>
class unorderedLinkedList : public linkedListType<t>
{
public:
    enum directionType { FORWARD, BACKWARD };

    unorderedLinkedList(directionType = FORWARD);

    void insert(const t &newInfo);
    void deleteNode(const t &deleteItem);
    bool search(const t &searchItem) const;

    void mergeSort(int (*func)(t &, t &));

private:
    directionType direction;

    void insertFirst(node<t> *newNode);
    void insertLast(node<t> *newNode);

    void recMergeSort(node<t> *&start, int (*func)(t &, t &));
    void divideList(node<t> *left, node<t> *&right);
    node<t> *mergeList(node<t> *left, node<t> *right, int (*func)(t &, t &));
};

/ constructor  /
template <class t>
unorderedLinkedList<t>::unorderedLinkedList(directionType d) : direction(d) {}

/ insert /
template <class t>
void unorderedLinkedList<t>::insert(const t &newInfo)
{
    node<t> *newNode = new node<t>;
    newNode->data = new t(newInfo);
    newNode->link = nullptr;

    if (this->isEmptyList())
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else if (direction == FORWARD)
    {
        insertLast(newNode);
    }
    else
    {
        insertFirst(newNode);
    }

    this->count++;
}

/  delete  /
template <class t>
void unorderedLinkedList<t>::deleteNode(const t &deleteItem)
{
    node<t> *current;
    node<t> *trailCurrent;
    bool found;

    if (this->isEmptyList())
        throw std::out_of_range("Cannot delete from empty list");

    if (*(this->head->data) == deleteItem)
    {
        current = this->head;
        this->head = this->head->link;

        if (this->head == nullptr)
            this->tail = nullptr;
    }
    else
    {
        found = false;
        trailCurrent = this->head;
        current = this->head->link;

        while (current != nullptr && !found)
        {
            if (*(current->data) == deleteItem)
                found = true;
            else
            {
                trailCurrent = current;
                current = current->link;
            }
        }

        if (!found)
            throw std::out_of_range("Item not found");

        trailCurrent->link = current->link;

        if (current == this->tail)
            this->tail = trailCurrent;
    }

    delete current;
    this->count--;
}

/ search /
template <class t>
bool unorderedLinkedList<t>::search(const t &searchItem) const
{
    node<t> *current = this->head;

    while (current != nullptr)
    {
        if (*(current->data) == searchItem)
            return true;

        current = current->link;
    }

    return false;
}

/ helpers /
template <class t>
void unorderedLinkedList<t>::insertFirst(node<t> *newNode)
{
    newNode->link = this->head;
    this->head = newNode;
}

template <class t>
void unorderedLinkedList<t>::insertLast(node<t> *newNode)
{
    this->tail->link = newNode;
    this->tail = newNode;
}

/ MERGE SORT /
template <class t>
void unorderedLinkedList<t>::mergeSort(int (*func)(t &, t &))
{
    recMergeSort(this->head, func);

    if (this->head == nullptr)
        this->tail = nullptr;
    else
    {
        this->tail = this->head;
        while (this->tail->link != nullptr)
            this->tail = this->tail->link;
    }
}

/ recursive merge sort /
template <class t>
void unorderedLinkedList<t>::recMergeSort(node<t> *&start, int (*func)(t &, t &))
{
    node<t> *otherStart;

    if (start != nullptr && start->link != nullptr)
    {
        divideList(start, otherStart);

        recMergeSort(start, func);
        recMergeSort(otherStart, func);

        start = mergeList(start, otherStart, func);
    }
}

/ divide /
template <class t>
void unorderedLinkedList<t>::divideList(node<t> *left, node<t> *&right)
{
    node<t> *middle;
    node<t> *current;

    if (left == nullptr || left->link == nullptr)
        right = nullptr;
    else
    {
        middle = left;
        current = left->link;

        if (current != nullptr)
            current = current->link;

        while (current != nullptr)
        {
            middle = middle->link;
            current = current->link;

            if (current != nullptr)
                current = current->link;
        }

        right = middle->link;
        middle->link = nullptr;
    }
}

/ merge /
template <class t>
node<t> *unorderedLinkedList<t>::mergeList(node<t> *left, node<t> *right, int (*func)(t &, t &))
{
    node<t> *newHead;
    node<t> *lastSmall;

    if (left == nullptr)
        return right;
    if (right == nullptr)
        return left;

    if (func(*(left->data), *(right->data)) <= 0)
    {
        newHead = left;
        left = left->link;
    }
    else
    {
        newHead = right;
        right = right->link;
    }

    lastSmall = newHead;

    while (left != nullptr && right != nullptr)
    {
        if (func(*(left->data), *(right->data)) <= 0)
        {
            lastSmall->link = left;
            left = left->link;
        }
        else
        {
            lastSmall->link = right;
            right = right->link;
        }

        lastSmall = lastSmall->link;
    }

    if (left == nullptr)
        lastSmall->link = right;
    else
        lastSmall->link = left;

    return newHead;
}

#endif