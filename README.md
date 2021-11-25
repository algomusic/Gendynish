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

Files are included for a monophonic version using the analog output on the PlayGround Express that provides more dynamic variation.

Details are published in this academic paper:
Brown, Andrew R. 2019. [“Gendynish: Stochastic Synthesis on the Arduino.”](https://research-repository.griffith.edu.au/bitstream/handle/10072/397128/Brown442028-Published.pdf?sequence=5) In Proceedings of the International Symposium on Electronic Art. Gwangju, Korea: ISEA International.
