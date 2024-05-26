% Define symptoms
symptom(fever).
symptom(cough).
symptom(sore_throat).
symptom(runny_nose).
symptom(headache).
symptom(fatigue).

% Define rules for diagnosis
cold :- symptom(fever), symptom(cough), symptom(runny_nose), not(flu).
flu :- symptom(fever), symptom(cough), symptom(sore_throat), symptom(fatigue).

% Define predicates to query the system
diagnose :- cold, write('You may have a cold.'), nl.
diagnose :- flu, write('You may have the flu.'), nl.
diagnose :- write('Your symptoms do not match any known conditions.'), nl.

% Example usage
% ?- symptom(fever), symptom(cough), diagnose.
