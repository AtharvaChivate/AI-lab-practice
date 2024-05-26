even(0).
even(X) :- X > 0, X1 is X-1, even(X1).

prime(2).
prime(3).
prime(X) :- X > 3, X mod 2 =\=0, \+ composite(X,3).

composite(X,Y) :- X mod Y =:= 0.
composite(X,Y) :- Y *Y < X, Y2 is Y + 2, composite(X,Y2).

