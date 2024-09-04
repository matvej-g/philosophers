# philosophers

The Dining Philosophers Problem is a classic synchronization problem in computer science, introduced by Edsger Dijkstra in 1965, that illustrates challenges in concurrent resource sharing.

Imagine five philosophers sitting around a circular table, where each philosopher alternates between three activities: eating, sleeping and thinking. In front of each philosopher is a plate of food, and between each pair of philosophers is a single fork. To eat,
a philosopher needs to pick up both forks adjacent to them (one on their left and one on their right). After eating, they put the forks down and return to thinking.

The challenge is to design a multi thread environment system where philosophers can eat without causing deadlock (where no philosopher can proceed because they're all waiting for forks) or starvation (where some philosophers never get a chance to eat because others monopolize the forks).

This problem demonstrates key concepts in concurrent programming such as mutual exclusion, deadlock, resource contention, and fairness in accessing shared resources.
