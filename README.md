# Gendynish
An homage to dynamic stochastic synthesis on the Arduino microprocessor

Written by Andrew R. Brown in 2018

The Gendynish algorithm on the Arduino produces sounds similar to Iannis Xenakis’ 
dynamic stochastic synthesis but is technically only ‘in the spirit’ of that process 
and is not a literal reconstruction.

A pin on the microprocessor can produce monophonic output. To maintain the independence 
for multiple pin output the timing of the pulse wave frequency is controlled within 
the main loop of the code, rather than by manipulating the microprocessor timers. This is 
inefficient computationally but allows more polyphonic timbral flexibility. 
