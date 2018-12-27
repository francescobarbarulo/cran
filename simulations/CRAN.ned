//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package cran.simulations;

import cran.As;
import cran.Bbu;
import cran.Rrh;

//
// Two instances (tic and toc) of Txc connected.
//
network CRan
{
    parameters:
    	//N is the number of RRHs
        int numRRH = default(1);
        @display("bgb=441,247");
        int compressionPercentage = default(10);
    submodules:
        as: As {
            N = numRRH;
            @display("p=51,109");
        }
        bbu: Bbu {
            compressionPercentage = compressionPercentage;
            @display("p=181,109");
        }
        rrh[numRRH]: Rrh {
            compressionPercentage = compressionPercentage;
            @display("p=300,30,m,1,3");
        }
    connections:
        as.out --> {  delay = 10ms; } --> bbu.in;
        for i=0..numRRH-1 {
            bbu.out++ --> {  delay = 10ms; } --> rrh[i].in;
        }
}
