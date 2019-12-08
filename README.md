Most methods and variables are named in a way that is self-documenting, however there are a few items to note:

The queues have a built-in lock, which allows a thread to lock the queue from being used by other threads.

The producer essentially attempts to access a queue by checking this lock, 
and if it is free, it *safely* changes the lock from "free" to "occupied".
It then adds a single line, and then detaches itself from the queue and allows
other producers to access it.

The consumer threads wait for new lines added to the queue, for as long as the
queue is empty and there are still producers who are unfinished (checked via a
global variable which is *safely* modified and accessed). Once the queue is
nonempty, the consumer *safely* accesses the line, parses it, and then prints it
to stdout. The printing is done via a critical section to avoid jumbled words.