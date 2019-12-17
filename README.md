# queue

This is a 2-part project. 

Part 1: Queue implementation
A queue is a linear structure that adheres to a First In First Out (FIFO) order. Our queue is implemented using LinkedList node structs, and retains private pointers to the head and rear elements. It supports the following main operations:

1. Enqueue: Adds an item to the queue
2. Dequeue: Removes an item from the front of the queue (throws exception if empty)
3. Front: Gets the front item from queue
4. Size: Returns number of elements

Part 2: Bus matches given preference lists

Introduction: 
We are planning a bus trip. We have some number of people who are going to ride the bus.
The number of people going is an even number. Half of them want to sit on an aisle seat and
half want to sit in a window seat. These are the only two types of seats.
Everyone who wants a window seat has ranked the “aisle seat people” from most-preferred to
least-preferred to sit next to, and the people who prefer an aisle seat have done similar for their
window-preferring friends. Our goal is to have an acceptable seating arrangement, where an
unacceptable seating arrangement is one where there is a person A assigned to an aisle seat
and a person W assigned to a window seat, not sitting next to person A. However, person A
would prefer to sit next to W instead of whoever A is paired with, and W would prefer to sit with
A instead of whoever W is paired with.
Any seating arrangement with no unacceptable situations is acceptable.
We need only come up with pairings: who is sitting next to who. We do not need to decide
which row or side of the bus.

Input format: 
The input is formatted in the following fashion:
● The first line of input is half the number of people who are going for the bus trip.

● Call that value n for purposes of this format.

● The next n lines of input each contain a permutation of integers 1 through n, separated
by a space. Each line represents the ith window person's pref list. 

○ The ith line (start counting at 1) contains the preference list for window person #i.

● The next n lines of input each contain a permutation of integers 1 through n, separated
by a space, representing the ith aisle person’s preference list.


Implementation Details: 
Our output is a map of matches (key = window person #, value = aisle person #). Starting with a queue of window people, we loop until that queue is empty. For the front of the queue W, we consider the 1st person A in W's pref list who W has not interacted with yet. If A doesn't have a buddy, pair W and A tentatively. If A has a seat buddy but prefers W, pair W and A, and put A's old partner back into the queue. If A prefers the current seat buddy to W, put W back into the queue.

