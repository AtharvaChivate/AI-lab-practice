:- initialization(main).

main :-
    (   father(john, paul)
    ->  write('father(john, paul) is true'), nl
    ;   write('father(john, paul) is false'), nl
    ),
    halt.

% Define the family relationships

% Facts
male(john).
male(paul).
male(mike).
male(kevin).
male(george).

female(mary).
female(linda).
female(susan).
female(kate).
female(sarah).

parent(john, paul).
parent(john, linda).
parent(mary, paul).
parent(mary, linda).
parent(paul, kevin).
parent(susan, kevin).
parent(mike, george).
parent(kate, george).
parent(linda, sarah).
parent(george, sarah).

% Rules
father(X, Y) :- male(X), parent(X, Y).
mother(X, Y) :- female(X), parent(X, Y).

child(X, Y) :- parent(Y, X).
son(X, Y) :- male(X), child(X, Y).
daughter(X, Y) :- female(X), child(X, Y).

sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.
brother(X, Y) :- male(X), sibling(X, Y).
sister(X, Y) :- female(X), sibling(X, Y).

grandparent(X, Y) :- parent(X, Z), parent(Z, Y).
grandfather(X, Y) :- male(X), grandparent(X, Y).
grandmother(X, Y) :- female(X), grandparent(X, Y).

grandchild(X, Y) :- grandparent(Y, X).
grandson(X, Y) :- male(X), grandchild(X, Y).
granddaughter(X, Y) :- female(X), grandchild(X, Y).

aunt(X, Y) :- female(X), sibling(X, Z), parent(Z, Y).
uncle(X, Y) :- male(X), sibling(X, Z), parent(Z, Y).

niece(X, Y) :- female(X), sibling(Y, Z), child(X, Z).
nephew(X, Y) :- male(X), sibling(Y, Z), child(X, Z).
