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

network CRan
{
    parameters:
    	// number of RRHs
        int numRRH = default(1);
    submodules:
        as: As {
            N = numRRH;
        }
        bbu: Bbu;
        rrh[numRRH]: Rrh;
    connections:
        as.out --> {  delay = 10ms; } --> bbu.in;
        for i=0..numRRH-1 {
            bbu.out++ --> {  delay = 10ms; } --> rrh[i].in;
        }
}
