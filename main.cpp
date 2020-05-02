/**
 * 
 * */

#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <bits/stdc++.h>

using namespace std;

bool isAnagrame(string a, string b);
void pars_args(int argc, char **argv);
bool compare_nocase (const std::string& first, const std::string& second);

string D_PARAM;
int EXIT_CODE = 1;

struct my_tolower
{
    char operator()(char c) const
    {
        return tolower(static_cast<unsigned char>(c));
    }
};


int main(int argc, char** argv){

    pars_args(argc,argv);

    map<int, stack<string>> map_dico;
    stack<string> section_dico;

    string word_file;
    int lengt_word_file;
    ifstream dico (D_PARAM);
    if (dico.is_open())
    {
        while ( getline (dico,word_file) )
        {
            //cout << word_file << endl;
            lengt_word_file = word_file.size();

            if(map_dico.find(lengt_word_file) != map_dico.end()){
                map_dico.at(lengt_word_file).push(word_file);
            } else {
                stack<string> new_section;
                new_section.push(word_file);
                map_dico[lengt_word_file] = new_section;
            }
        }
    }
    else return 3;

    dico.close();

    cout << "Dico pret " << endl;
    string word;
    int word_id;

    while(cin >>  word)
    {

        list<string> test;
        list<string>::iterator it;
        //cout << word << endl;
        word_id = word.size();
        if(word_id<1){
            exit(EXIT_CODE);
        }

        if(map_dico.count(word_id) > 0){
            section_dico = (stack<string>) map_dico.at(word_id);
        }


        while (section_dico.size() > 0) {
            string a = section_dico.top();
            if (isAnagrame(word, a)) {
                test.push_back(a);
            }
            section_dico.pop();
        }

        test.sort(compare_nocase);
        for (it = test.begin(); it != test.end(); ++it)
            std::cout << *it << endl;
    }

    return EXIT_CODE;
}

bool isAnagrame(string a, string b){

    transform(a.begin(), a.end(), a.begin(), my_tolower());
    transform(b.begin(), b.end(), b.begin(), my_tolower());

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    for (int i = 0; i < int(a.length()); i++)
        if (a[i] != b[i])
            return false;
    EXIT_CODE = 0;
    return true;
}

void pars_args(int argc, char **argv){

    if (argc < 3 ){
        exit(2);
    }

    if(argv[1][0] != '-' || argv[1][1] != 'd' ){
        exit(2);
    }

    D_PARAM = argv[2];

}

bool compare_nocase (const std::string& first, const std::string& second)
{
    unsigned int i=0;
    while ( (i<first.length()) && (i<second.length()) )
    {
        if (tolower(first[i])<tolower(second[i])) return true;
        else if (tolower(first[i])>tolower(second[i])) return false;
        ++i;
    }
    return ( first.length() < second.length() );
}