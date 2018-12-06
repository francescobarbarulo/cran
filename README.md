# CRAN
A cellular system is composed of a central processing unit (BBU), N remote radios (RRH) and N _cells_. Each RRH serves one and only one cell. An application server (AS) generates data packets having one of the _cells_ as destination. The target cell is uniformly taken from the available ones.
Each data packet has a size _s_ and a new one is generated every _t_ seconds, where _s_ and _t_ are random variables to be described later. The BBU has an interface towards the RRHs and communicates with only one of them at a time, at a speed of X bytes/s. The BBU receives data packets from the server and forwards them to the proper RRH. If the BBU interface with the RRHs is busy, data packets are queued and served using FIFO policy.
When the BBU receives data packets from the AS, the communication betwwen BBU and RRHs can happen in one of the following two modes.
a. The BBU forwards the packet to the proper RRH, which forwards it to the cell.
b. The BBU performs a compression on the data packet, reducing its size by X%; it then forwards the compressed packet to the proper RRH. Packets are then decompressed as soon as they reach the RRH. Such operation takes S seconds, where S is given by S = X x 50ms. Only one packet can be decompressed at a time. If the decompressing process is busy, incoming data packets are queued and served using a FIFO policy.

Measure at least the end-to-end delay of data packets for vatious values of S for both methods, and compare the results.

At least the following two scenarios have to be evaluated:
* Exponential distribution of _t_ and _s_;
* Lognormal distribution of _s_, exponential distribution of _t_.
