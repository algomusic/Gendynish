# Gendynish
An homage to dynamic stochastic synthesis on the Arduino microprocessor

Written by Andrew R. Brown in 2018

The Gendynish algorithm on the Arduino produces sounds similar to Iannis Xenakis’ 
dynamic stochastic synthesis but is technically only ‘in the spirit’ of that process 
and is not a literal reconstruction.

A pin on the microprocessor can produce monophonic output. To maintain the independence 
of the four pins outputs the timing of the pulse wave frequency was controlled within 
the main loop of the code, not by manipulating the microprocessor timers. This is 
inefficient computationally but allows more polyphonic flexibility. 
