#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <map>
#include <unordered_set>

using namespace std;

void read_file(string, vector<string> &);
void read_file(string, unordered_set<string> &);

int main ()
{
    //Reads stop words file and put them into a vector

    unordered_set<string> stop_words;

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

    //Splits the phrases and add each word to a map, with it's scores and couters

    map<string,pair<int,int>> words; //<word,pair<total_score,counter>>

    for(int i = 0; i < (train_set_raw.size() - 1); i++)
    {

        istringstream iss(train_set_raw[i]);
        vector<string> train_set_clean((istream_iterator<string>(iss)), istream_iterator<string>());

        int score = stoi(train_set_clean[0]);

        for(int j = 1; j < (train_set_clean.size() - 1); j++)
        {

            if ((words.find(train_set_clean[j]) == words.end()) && (stop_words.find(train_set_clean[j]) == stop_words.end())) //Checks if word is already in the map and if it's a stop word
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

    //Creates a map with the pair <word,score>

    map<string,int> words_scores;
    map<string,pair<int,int>>::iterator it;

    for(it = words.begin(); it != words.end(); it++)
    {
        words_scores[it->first] = it->second.first / it->second.second;
    }

    map<string,int>::iterator it2;

    for(it2 = words_scores.begin(); it2 != words_scores.end(); it2++)
        cout << it2->second << endl;

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

void read_file(string file_name, unordered_set<string> & unord)
{
    string str;
	ifstream infile;

	infile.open (file_name);

    while(!infile.eof()) // To get you all the lines.
    {
        getline(infile,str); // Saves the line in STRING.
        unord.insert(str);
    }

	infile.close();
}
