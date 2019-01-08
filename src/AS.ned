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

package cran;

simple As
{
    parameters:
        //N is the number of RRHs
        int N;
        //if exponentialDistribution is true the size distribution is exponential otherwise is lognormal
        bool exponentialDistribution = default(true);
        //exponential
        double meanExponentialSize = default(1000); // -> 1000 bytes
        //lognormal
        double meanLognormalSize = default(7); // -> about 1000 bytes 
        double varianceLognormalSize = default(0.1);
        //mean interArrivalTime between packets to the AS
        double interArrivalTime @unit(s) = default(1.5s);
    gates:
        output out;
}

