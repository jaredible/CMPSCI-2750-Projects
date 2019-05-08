#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "stack.h"

struct Stack
{
	int top;
	unsigned capacity;
	int *array;
};

struct Stack *createStack(unsigned capacity)
{
	struct Stack *stack = (struct Stack*) malloc(sizeof(struct Stack)); // Allocate memory based on size of Stack struct
	stack->capacity = capacity; // Set the specified capacity
	stack->top = -1; // Top is -1 by default
	stack->array = (int*) malloc(stack->capacity * sizeof(int)); // Allocate stack integer array based on capacity
	return stack; // Return the Stack
}

int isFull(struct Stack *stack)
{
	return stack->top == stack->capacity - 1; // Stack is full if top value == capacity - 1
}

int isEmpty(struct Stack *stack)
{
	return stack->top == -1; // If top == -1 then stack is empty
}

int isDuplicate(struct Stack *stack, int item)
{
	int *entry;
	for (entry = stack->array; *entry != '\0'; ++entry) // Loop all numbers in stack array
		if (*entry == item) return 1; // If one item matches then return true
	return 0; // Return item not a duplicate
}

void push(struct Stack *stack, int item)
{
	if (isFull(stack) || isDuplicate(stack, item)) return; // Don't push item if stack is full or item already exists in stack
	stack->array[++stack->top] = item; // Add item to stack
}

int pop(struct Stack *stack)
{
	if (isEmpty(stack)) return INT_MIN; // Don't pop if stack is empty
	return stack->array[stack->top--]; // Remove top of stack and return that integer
}
