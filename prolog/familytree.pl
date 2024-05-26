% Facts
male(maruti).
male(bhaskar).
male(vijay).
male(bharat).
male(shindeSir).
male(sharad).
male(pradeep).
male(deepak).
male(pratik).
male(sanju).
male(shekhar).
male(balaji).
male(sagar).
male(ajinkya).
male(atul).
male(jay).
male(akash).
male(avinash).
male(raj).
male(sham).
male(arnav).

female(shanti).
female(usha).
female(suman).
female(vandana).
female(kamal).
female(pramila).
female(apurva).
female(sakshi).
female(asha).
female(shruti).
female(prachi).
female(samru).
female(aishwarya).
female(sharda).
female(deepa).
female(priya).
female(trupti).
female(savi).
female(shreeja).


% Parent relations
parent(maruti,bhaskar).
parent(maruti,bharat).
parent(maruti,kamal).
parent(maruti,sharad).
parent(maruti,suman).
parent(bhaskar,apurva).
parent(vijay,pradeep).
parent(vijay,deepak).
parent(bharat,pratik).
parent(bharat,shruti).
parent(bharat,prachi).
parent(shindeSir,sanju).
parent(shindeSir,shekhar).
parent(sharad,priya).
parent(sharad,trupti).
parent(sharad,ajinkya).
parent(pradeep,atul).
parent(deepak,jay).
parent(deepak,akash).
parent(sanju,samru).
parent(sanju,aishwarya).
parent(shekhar,sham).
parent(balaji,shreeja).
parent(balaji,arnav).
parent(sagar,savi).
parent(avinash, raj).

parent(shanti,bhaskar).
parent(shanti,kamal).
parent(shanti,sharad).
parent(shanti,bharat).
parent(shanti,suman).
parent(usha,apurva).
parent(suman,pradeep).
parent(suman,deepak).
parent(vandana,pratik).
parent(vandana,shruti).
parent(vandana,prachi).
parent(prachi, raj).
parent(kamal,sanju).
parent(kamal,shekhar).
parent(pramila,priya).
parent(pramila,trupti).
parent(pramila,ajinkya).
parent(sakshi,atul).
parent(asha,jay).
parent(asha,akash).
parent(sharda,samru).
parent(sharda,aishwarya).
parent(deepa,sham).
parent(priya,shreeja).
parent(priya,arnav).
parent(trupti,savi).


mother(X,Y) :- parent(X,Y), female(X).
father(X,Y) :- parent(X,Y), male(X).

wife(X,Y) :- female(X), male(Y), parent(X,Z), parent(Y,Z), X \= Y.
husband(X,Y) :- male(X), female(Y), parent(X,Z), parent(Y,Z), X \= Y.

sibling(X,Y) :- parent(P,X), parent(P,Y),X \= Y.

greatgrandfather(X,Y) :- male(X), grandparent(_, Y).
greatgrandmother(X,Y) :- female(X), grandparent(_, Y).

grandparent(X,Z) :- parent(X,Y), parent(Y,Z).
grandmother(X,Z) :- parent(X,Y), parent(Y,Z), female(X).
grandfather(X,Z) :- parent(X,Y), parent(Y,Z), male(X).
secondgrandfather(X,Y) :- sibling(X,Z), grandparent(Z, Y), male(X).
secondgrandfather(X,Y) :- sibling(X,Z), grandparent(Z, Y), female(X).

uncle(X,Y) :- parent(P,Y), sibling(X,P), male(X).
seconduncle(X,Y) :- parent(P1,Y), cousin(P1,X), male(X).
aunt(X,Y) :- parent(P,Y), sister(X,P).

kaki(X, Y) :- mother(M1, Y), derani(M1, X).

cousin(X,Y) :- parent(P1,X), parent(P2,Y), sibling(P1,P2), X \= Y.
secondcousin(X,Y) :- grandparent(P1,X), grandparent(P2,Y), sibling(P1,P2).
sister(X,Y) :- female(X), sibling(X,Y).
brother(X,Y) :- male(X), sibling(X,Y).

fatherinlaw(X,Y) :- wife(Z,Y), father(X,Z),male(Y).
motherinlaw(X,Y) :- wife(Z,Y), mother(X,Z),male(Y).
brotherinlaw(X,Y) :- wife(Z,Y), brother(X,Z),male(Y).
soninlaw(X,Y) :- wife(W1,X), father(Y,W1).
secondsoninlaw(X,Y) :- husband(X,Z), uncle(Y,Z), male(Y).

derani(X,Y) :- husband(H1,X), husband(H2,Y), sibling(H1,H2).
secondderani(X,Y) :- husband(H1,X), husband(H2,Y), cousin(H1,H2).

sadu(X,Y) :- wife(W1,X), wife(W2,Y), sister(W1,W2).
niece(X,Y) :- female(X), mother(Z,X), sister(Z,Y).
nephew(X,Y) :- male(X), mother(Z,X), sister(Z,Y).