% Facts
father(john, peter).
father(john, mary).
mother(lisa, peter).
mother(lisa, mary).
male(peter).
female(mary).

% Rules
parent(X, Y) :- father(X, Y); mother(X, Y).
sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).
ancestor(X, Y) :- parent(X, Y).
ancestor(X, Y) :- parent(X, Z), ancestor(Z, Y).
