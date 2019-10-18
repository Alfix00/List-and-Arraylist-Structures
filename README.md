# List-and-Arraylist-Structures
List and Arraylist structures with functions (push, pop, alloc, free, merge) written in C

-------------------------------------------------------------------------------------------------------------------------------------

# Info

Consider the abstract data type List, defined in terms of the following operations:

- Check if the list is empty in O (1)
- Insertion at the end of the list in O (1)
- Insertion of an element in the i-th position of the list in O (n)
- Deletion of the item at the end of the list in O (1)
- Deletion of the element in the i-th position in the list in O (n)
- Recovery of the element in the i-th position in the list (without deleting the element from the list) in O (n)
- Recovery of the number of elements of the list in O (1)
- Creation of an iterator for the list in O (1)

The list can contain objects of any type and not known a priori.

An iterator is an abstract data type that allows iterating over a container of some kind. An iterator must make the following operations available:

- Check if the iterator is still valid in O (1) (an iterator is initialized so as to refer to the head of the list and becomes invalid when it is moved beyond the end of the list).
- Retrieve the current element in O (1)
- Move the iterator to the next element in O (1)


We realize in C two alternative implementations for the abstract data type List (and, consequently for the iterator on it).

In particular:

- both implementations must offer:
    - a function to create an empty list;
    - one to destroy it (with consequent deallocation of the associated memory);
    - a function to destroy an iterator (with consequent deallocation of the associated memory);
    - all and only the operations specified above; these operations must be performed using functions with the same signature in both libraries;
- an implementation must create lists with dynamic (ie resizable) arrays; the other implementation must implement the lists via linked records.


### Unit Testing

Implement the algorithm unit tests according to the indications suggested in the Unit Testing document.

### Use of implemented libraries

Implement an algorithm _merge_ that accepts in input a sorting criterion and two lists ordered according to this sorting criterion and returns in output a new list, corresponding to the merger of the two input lists and ordered according to the same criterion.

The implemented algorithm must be able to be executed * without modifications * on each of the two implementations for the abstract data type List produced according to the above specifications.

### Unit Testing

Implement the unit tests for the function that implements _merge_ according to the indications suggested in the Unit Testing document.
