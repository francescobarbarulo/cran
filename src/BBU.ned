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

simple Bbu
{
    parameters:
        double speed = default(1000); // bytes/s
        bool enableCompression = default(false);
        int compressionPercentage = default(10);
        
        @signal[responseTime](type=long);
   	    @statistic[responseTimeBbuStat](source="responseTime"; record=mean;);
   	    
   	    @signal[waitingTime](type=long);
   	    @statistic[waitingTimeBbuStat](source="waitingTime"; record=mean;);
   	    
   	    @signal[bbuJobs](type=long);
   	    @statistic[bbuJobsStat](source="bbuJobs"; record=mean;);
    gates:
        input in;
        output out[];
}