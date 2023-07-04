# Fault Analysis Testing Algorithm

This C++ code implements a fault analysis testing algorithm for a combinational circuit. The algorithm takes into account potential faults in the circuit and performs simulations to identify faulty combinations. 

## Input Requirements

The code expects two input files: the circuit file and the fault input file. The circuit file contains the circuit description in a specific format, while the fault input file provides information about the faulty node and the type of fault (SA0 or SA1). 

## Implementation Details

The code follows the following steps to perform fault analysis testing:

1. Read Circuit File: The circuit file is read and processed to extract the circuit information. Each line in the file represents a node in the circuit, along with its corresponding gate type and input nodes. The circuit information is stored in a vector of pairs, where each pair contains the node name and a struct representing the gate information.

2. Read Fault Input File: The fault input file is read to extract information about the faulty node and the fault type. The faulty node is the node that is potentially affected by the fault, and the fault type can be SA0 (stuck-at-0) or SA1 (stuck-at-1).

3. Generate Input Combinations: The algorithm generates all possible combinations of values for the inputs A, B, C, and D. It creates a vector of vectors, where each inner vector represents a combination of input values.

4. Fault Analysis Testing: For each input combination generated, the algorithm performs the following steps:

   a. Initialize Node Values: An unordered map called `nodeValues` is created to store the current values of the nodes in the circuit. The values of the inputs A, B, C, and D are assigned according to the current input combination.

   b. Non-Faulty Case: The circuit is simulated without the fault. The algorithm iterates over each node in the circuit and evaluates its gate using the `evaluateCircuit` function. The output value of each node is stored in the `nodeValues` map.

   c. Faulty Case: The circuit is simulated with the fault. The algorithm follows the same procedure as the non-faulty case, but before evaluating the gate of the faulty node, it updates its value according to the fault type (SA0 or SA1).

   d. Comparison: After simulating the circuit in both the non-faulty and faulty cases, the algorithm compares the output value of node Z. If the output values differ, it means that the fault affected the circuit, and the input combination is considered faulty. The combination and the output value at node Z are written to an output file.

5. Output: The faulty combinations and their corresponding output values are written to an output file named "output.txt".


## Usage

To use this code, follow these steps:

1. Create a circuit file in the required format, specifying the nodes, gates, and connections.
2. Create a fault input file specifying the faulty node and the fault type.
3. Compile and run the code, providing the names of the circuit file and the fault input file as inputs.
4. Check the "output.txt" file to see the faulty combinations and their corresponding output values.

Note: Make sure to include the necessary input files in the same directory as the code file.
