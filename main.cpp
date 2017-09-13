#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>

using namespace std;

void read_file(string, vector<string> &);

int main ()
{
    //Reads stop words file and put them into a vector

    vector<string> stop_words;
    read_file("stopWords.txt", stop_words);

    //Reads train set file and put it into a vector

    vector<string> train_set_raw;
    read_file("trainSet.txt", train_set_raw);
    cout << train_set_raw[2] << endl;

    //Removes bad characters and lowers all the strings

    regex bad_chars ("[^0-9A-Za-z ]");

    for (int i = 0; i < train_set_raw.size(); i++)
    {
        train_set_raw[i] = regex_replace(train_set_raw[i],bad_chars," ");
        transform(train_set_raw[i].begin(), train_set_raw[i].end(), train_set_raw[i].begin(), ::tolower);
    }

    istringstream iss(train_set_raw[2]);
    vector<string> train_set_clean((istream_iterator<string>(iss)), istream_iterator<string>());
    for (string s : train_set_clean)
        cout << s << endl;
    //Splits the phrases

    /*
    for(int i = 0; i < train_set_raw.size(); i++)
    {
        istringstream iss(train_set_raw[i]);
        vector<string> train_set_clean((istream_iterator<string>(iss)), istream_iterator<string>());
    }
    */

}

//Reads a file and put it's content into a given vector
void read_file(string file_name, vector<string> & vec)
{
    string str;
	ifstream infile;

	infile.open (file_name);

    while(!infile.eof()) // To get you all the lines.
    {
        getline(infile,str); // Saves the line in STRING.
        vec.push_back(str);
    }

	infile.close();
}
