// Stack.h Templates to define stacks
#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include<iostream>
#include<memory>
#include<cstring>
#include"CText.h"

template <typename T>
class Stack
{
  private:
    // Nested class
    class Node
    {
      public:
        T item {};                             // The object stored in this node
        Node* next {};                         // Pointer to next node

        Node(const T& item) : item {item} {}   // Create a node from an object
    };

    Node* head {};                             // Points to the top of the stack
    int counter{0};                             
  public:
    Stack() = default;                         // Default constructor
    Stack(const Stack& stack);                 // Copy constructor
    ~Stack();                                  // Destructor
    Stack& operator=(const Stack& rhs);        // Assignment operator

    void push(const T& item);                  // Push an object onto the stack
    T pop();                                   // Pop an object off the stack
	bool isEmpty() const;                      // Empty test
    int getCount();                            // Return number of objects in stack
};

// Copy constructor
template <typename T>
Stack<T>::Stack(const Stack& stack)
{
  if (stack.head)
  {
    head = new Node {*stack.head};             // Copy the top node of the original
    Node* oldNode {stack.head};                // Points to the top node of the original
    Node* newNode {head};                      // Points to the node in the new stack

    while ((oldNode = oldNode->next))          // If it's nullptr, it's the last node
    {     
      newNode->next = new Node{*oldNode};      // Duplicate it
      newNode = newNode->next;                 // Move to the node just created
    }
  }
}

// Destructor
template <typename T>
Stack<T>::~Stack()
{
  while (!isEmpty()) pop();
}


// Push an object onto the stack
template <typename T>
void Stack<T>::push(const T& item)
{
  Node* node{new Node(item)};                  // Create the new node
  node->next = head;                           // Point to the old top node
  head = node;                                 // Make the new node the top
  counter++;
}

// Pop an object off the stack
template <typename T>
T Stack<T>::pop()
{
  if (isEmpty())                               // If it's empty
    throw std::logic_error {"Stack empty"};    // Pop is not valid so throw exception

  Node* temp {head};                           // Save address of top node and its item
  T item {head->item};
  head = head->next;                           // Make next node the top
  delete temp;                                 // Delete the previous top node
  counter--;
  return item;                                 // Return the top object
}

template <typename T>
bool Stack<T>::isEmpty() const
{
  return head == nullptr;
}

template <typename T>
int Stack<T>::getCount()
{
  return counter;
}
#endif