#### WORKFLOW

## Objectives
Compare the system when the bbu performs compression (B) and when it does not (A)  
Find cases when it is better doing compression

## Assumption
Propagation times are negligible  
End-to-end delay is computed until the packet decompression is finished  
BBU switching time (time needed to change the output gate) is negligible  
Packets are not corrupted  
No packet loss at the buffer (infinite buffer)

## Factors
N remote radios  
X Bbu speed to rrh  
C compression on/off  
\[S decompression time (if it depends on packet size too) = c_perc * 50ms\]

## Verification

Step 1.  
- N = 1 RRH  
- s = const  

Focus on compression time S:  
In order to be able to compare the behaviour of the system with or without compression we have computed the break-even 
point between the end-to-end delay in A and in B, assuming there is not waiting time in both BBU and RRH.

s/X = s(1 - c_perc/100)/X + S => X = s/5

Hence, under these assumptions, X does not depend on S and in this deterministic behaviour. Compression affects
only the decompression time and it does not give any advantage on X.

In order to have a stability system we have to choose t such that 1/t < X/s (ro < 1) => t > 5s
If we increase N, in order to have only 1 job in the system and so to be sure that there are not waiting times in both queues
we have to set at least t' = t x N.
