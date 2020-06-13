
using namespace std;
#include <iostream> 
#include <queue> 
#include <fstream>
#include<string>
#include <unordered_map> 
#include <chrono> 
using namespace std::chrono; 

void decoding(vector< int> op,ofstream& file)
{
	unordered_map<int, string> dictionary;

    string s = "";    
	for (int i = 0; i < 256; i++) {
		s += char(i);
		dictionary[i] = s;
	}

	int prev = op[0], curr;
	s = dictionary[prev];
	char c = s[0];
	file << s;
	int code = 256;
	for (int i = 1; i < op.size(); i++) {
		curr = op[i];
	    s = dictionary[curr];
		file << s;
		c = s[0];
		dictionary[code++] = dictionary[prev] + c;
		prev = curr;
	}
}
int main()
{
    // starting the timer of decoding
    auto start = high_resolution_clock::now(); 

    vector<int>output;
    fstream infile("encoding.bin", ios::binary | ios::in );
	infile.seekg(0);
    int x=0;

    // reading the binary file 
	while (infile.read((char*)&x, 3)) {
        output.push_back(x);
    }

	ofstream file("output.txt",ios::trunc);


    // LZW decoding then write on the ouput file to convert text back
	decoding(output, file);

    // stoping the timer then outputing decoding time
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<seconds>(stop - start); 
    cout << "decoding time: "<<duration.count() << endl;

    return 0;

}