#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <map>

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

    //Removes bad characters and lowers all the strings

    regex bad_chars ("[^0-9A-Za-z ]");

    for(int i = 0; i < train_set_raw.size(); i++)
    {
        train_set_raw[i] = regex_replace(train_set_raw[i],bad_chars," ");

        transform(train_set_raw[i].begin(), train_set_raw[i].end(), train_set_raw[i].begin(), ::tolower);
    }

    //Splits the phrases and add each word to a map

    map<string,pair<int,int>> words; //<word,total_score,counter>

    for(int i = 0; i < (train_set_raw.size() - 1); i++)
    {

        istringstream iss(train_set_raw[i]);
        vector<string> train_set_clean((istream_iterator<string>(iss)), istream_iterator<string>());

        int score = stoi(train_set_clean[0]);

        for(int j = 1; j < (train_set_clean.size() - 1); j++)
        {

            if (words.find(train_set_clean[j]) == words.end())
            {
                words[train_set_clean[j]] = pair<int,int>(score,1);

            }
            else
            {
                words[train_set_clean[j]].first += score;
                words[train_set_clean[j]].second++;
            }
        }
    }

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
