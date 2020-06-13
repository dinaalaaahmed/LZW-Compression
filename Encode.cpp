
using namespace std;
#include <iostream> 
#include <queue> 
#include <fstream>
#include<string>
#include <unordered_map> 
#include <chrono> 
using namespace std::chrono; 


vector<unsigned int> encoding(string s1)
{
    unordered_map <string,int> dictionary;
    string s = "";
    for(int i=0;i<256;i++){
		s += char(i);
		dictionary[s] = i;
    }

    s = ""; 
    char c;
    vector <unsigned int> o;
    int code = 256;
    for(int i=0; i<s1.size(); i++){
        c = s1[i];
        if(dictionary.find(s+c) != dictionary.end()){
            s += c; 
        }
        else{
            o.push_back(dictionary[s]);
            dictionary[s+c]=code++;
            s = c;
        }
    }
    o.push_back(dictionary[s]);
    return o;
}

int main()
{
    // starting the timer of encoding
    auto start = high_resolution_clock::now(); 

	string text;
    ifstream myfile;
    cout<<"please change the path to the encode file\n";
    string path = "D:/multi/enwik8";
    myfile.open(path);

    // reading input file
    if (myfile.is_open()) {
        string line;
        while (getline(myfile, line)) {
            text += line;
			text += '\n';
        }
        text.pop_back();
        myfile.close();
    }
	
	fstream outFile("encoding.bin", ios::binary | ios::in | ios::trunc|ios::out);

    // LZW encoding
    vector<unsigned int> output_code = encoding(text);

    // outputing the encoded vector into a binary file
    for (int i = 0; i < output_code.size(); i++) {
		outFile.write((char*)&output_code[i], 3);
  
       
	}

    // stoping the timer then output encoding time
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<seconds>(stop - start); 
    cout << "encoding time: "<<duration.count() << endl;

	return 0;
    

}
