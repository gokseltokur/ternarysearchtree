# ternarysearchtree
A special type of ternary tree.

Consider a TST where the only difference with a binary search tree is that
a key that is greater than the current node’s key but less than or equal to the square
of it is located at the middle child of the node. More formally expressed,

Key(LCA) < Key(A) < Key(MCA) ≤ (Key(A))^2 < Key(RCA)
