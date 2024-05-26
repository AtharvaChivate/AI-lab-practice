% Facts
even(0).
even(X) :- X > 0, X1 is X - 2, even(X1).

prime(2).
prime(3).
prime(X) :- X > 3, X mod 2 =\= 0, \+ composite(X, 3).

composite(X, Y) :- X mod Y =:= 0.
composite(X, Y) :- Y * Y < X, Y2 is Y + 2, composite(X, Y2).

% Rules
factorial(0, 1).
factorial(N, F) :- N > 0, N1 is N - 1, factorial(N1, F1), F is N * F1.

fibonacci(0, 0).
fibonacci(1, 1).
fibonacci(N, F) :- N > 1, fibonacci(N-1, F1), fibonacci(N-2, F2), F is F1 + F2.
