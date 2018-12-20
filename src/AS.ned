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
        //if enableCompression is true the message will be decompressed by the RRH
        bool enableCompression = default(false);
        //if expSize is true the size distribution is exponential otherwise is lognormal
        bool expSize = default(true);
        //size mean
        double pktSize = default(1000);
        //size variance 
        double varSize = default(3);
        //mean interArrivalTime between packets to the AS
        double interArrivalTime @unit(ms) = default(1000ms);
    gates:
        output out;
}

