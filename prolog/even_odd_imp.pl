% Facts for even numbers
even(0).
even(X) :- X > 0, X1 is X - 2, even(X1).

% Facts and rules for prime numbers
prime(2).
prime(3).
prime(X) :- X > 3, X mod 2 =\= 0, \+ composite(X, 3).

composite(X, Y) :- X mod Y =:= 0.
composite(X, Y) :- Y * Y < X, Y2 is Y + 2, composite(X, Y2).

% Rule for calculating factorial
factorial(0, 1).
factorial(N, F) :- N > 0, N1 is N - 1, factorial(N1, F1), F is N * F1.

% Rules for calculating Fibonacci numbers
fibonacci(0, 0).
fibonacci(1, 1).
fibonacci(N, F) :- N > 1, N1 is N - 1, N2 is N - 2, fibonacci(N1, F1), fibonacci(N2, F2), F is F1 + F2.

% Initialization for testing
:- initialization(main).

main :-
    % Test even number predicate
    ( even(4) -> write('4 is even'), nl ; write('4 is not even'), nl ),
    ( even(5) -> write('5 is even'), nl ; write('5 is not even'), nl ),
    
    % Test prime number predicate
    ( prime(5) -> write('5 is prime'), nl ; write('5 is not prime'), nl ),
    ( prime(4) -> write('4 is prime'), nl ; write('4 is not prime'), nl ),
    
    % Test factorial predicate
    factorial(5, F5),
    write('Factorial of 5 is '), write(F5), nl,
    
    % Test Fibonacci predicate
    fibonacci(5, Fib5),
    write('Fibonacci of 5 is '), write(Fib5), nl,

    halt.  % Terminate the program
