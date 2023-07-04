#include <bits/stdc++.h>
using namespace std;

struct Gate {
    string type;
    string input1;
    string input2;
};

// Evaluate value of combinational gate
int evaluateCircuit(const Gate &gate, unordered_map<string, int> &nodeValues) {
    int result;
    //cout << gate.type << " " << gate.input1 << "gap" << gate.input2 << '\n';
    if(gate.type == "~") {
        result = !nodeValues[gate.input1];
    }
    else if(gate.type == "&") {
        result = nodeValues[gate.input1] & nodeValues[gate.input2];
    }
    else if(gate.type == "|") {
        result = nodeValues[gate.input1] | nodeValues[gate.input2];
    }
    else if(gate.type == "^") {
        result = nodeValues[gate.input1] ^ nodeValues[gate.input2];
    }
    cout << result << '\n';
    return result;
}

//Simulate value of node according to the fault 
void simulateCicuit(const Gate &gate, unordered_map<string, int> &nodeValues, const string& node, const string& faultNode, bool isFaulty, int faultType) {
    int gateValue = evaluateCircuit(gate, nodeValues);

    if(node == faultNode && isFaulty ) {
        nodeValues[node] = faultType;
    }
    else {
        nodeValues[node] = gateValue;
    }
}

int main( ) {

    //Output file
    ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        cout << "Unable to create output file." << endl;
        
    } else {

    // Getting and reading the circuit file 
    // extracting data in required format
    string circuitFile;
    cout << "Enter the circuit file: \n";
    cin >>  circuitFile;
    vector<pair<string, Gate>> circuit;
    Gate gate;
    ifstream file(circuitFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if(!line.empty()) {
                line.erase(remove(line.begin(), line.end(), ' '), line.end());
                size_t equalpos = line.find("=");
                string internalNode = line.substr(0, equalpos);
                
                size_t notpos = line.find("~");
                if(notpos != string::npos) {
                gate.type = "~";
                gate.input1 = line.substr(notpos+1);
                gate.input2 = "";
                }
                else {
                    size_t gatepos = line.find("|");
                    if(gatepos == string::npos) {

                        gatepos = line.find("&");

                        if(gatepos == string::npos) {

                            gatepos = line.find("^");
                        }
                    }
                    gate.type = line[gatepos];
                    gate.input1 = line.substr(equalpos+1, gatepos - equalpos -1);
                    gate.input2 = line.substr(gatepos+1);
                }
                circuit.push_back({internalNode, gate});

            }
        }
        file.close();
    } else {
        cout << "Unable to open circuit file." << endl;
        return 0;
    }

    //Getting fault input file and extracting data in its required format
    string faultInputFile;
    cout << "Enter the fault input file: ";
    cin >> faultInputFile;

    vector<string> faultInput;
    ifstream faultFile(faultInputFile);
    if (faultFile.is_open())
    {
        string line;
        while (getline(faultFile, line))
        {
            if (!line.empty())
            {
                line.erase(remove(line.begin(), line.end(), ' '), line.end());
                size_t equalsPos = line.find('=');
                string value = line.substr(equalsPos + 1);
                faultInput.push_back(value);
            }
        }
    }
    faultFile.close();


    string faultNode = faultInput[0];
    string stuckAt = faultInput[1];
    int faultType;
    if( stuckAt == "SA0") faultType = 0;
    else faultType = 1;

    // Generate the combinations of A, B, C, D
    vector<vector<int>> combinations;
    for (int i = 0; i < 16; ++i)
    {
        vector<int> combination(4);
        combination[0] = (i >> 3) & 1; // A
        combination[1] = (i >> 2) & 1; // B
        combination[2] = (i >> 1) & 1; // C
        combination[3] = i & 1;        // D
        combinations.push_back(combination);
    }

    for (const auto &combination : combinations) {

        unordered_map<string, int> nodeValues;
        nodeValues["A"] = combination[0];
        nodeValues["B"] = combination[1];
        nodeValues["C"] = combination[2];
        nodeValues["D"] = combination[3];
        
        // If the fault was not there
        for (const auto &Node : circuit) {
            const string &node = Node.first;
            const Gate &gate = Node.second;
            simulateCicuit(gate, nodeValues, node,  faultNode, false, faultType);

        }
        int expectedOutput = nodeValues["Z"]; 

        //if fault was present
        for (const auto &Node : circuit) {
            const string node = Node.first;
            const Gate gate = Node.second;
            simulateCicuit(gate, nodeValues, node,  faultNode, true, faultType);

        }
        int faultOutput = nodeValues["Z"]; 

        if( faultOutput != expectedOutput) {
            outputFile << "[A, B, C, D] = [" << combination[0] << " " << combination[1] << " " << combination[2] << " " << combination[3] << "], ";
            outputFile << "Z = " << faultOutput << endl;
        }
    }

    outputFile.close();
    }
}
