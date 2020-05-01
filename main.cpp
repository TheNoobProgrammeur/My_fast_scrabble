/**
 * 
 * */

#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <csignal>
#include <bits/stdc++.h>

using namespace std;

void my_handler(int s);
bool isAnagrame(string a, string b);
void pars_args(int argc, char **argv);
bool compare_nocase (const std::string& first, const std::string& second);

string D_PARAM;
bool active = true;

int main(int argc, char** argv){



    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);

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
            lengt_word_file = word_file.length();

            if(map_dico.find(lengt_word_file) != map_dico.end()){
                section_dico = (stack<string>) map_dico.at(lengt_word_file);
                section_dico.push(word_file);
                map_dico[lengt_word_file] = section_dico;
            } else {
                stack<string> new_section;
                new_section.push(word_file);
                map_dico[lengt_word_file] = new_section;
            }
        }
    }
    else return 3;
    dico.close();

    string word;
    int word_id;

    while(active)
    {

        list<string> test;
        list<string>::iterator it;

        getline (cin, word);

        word_id = word.size();
        section_dico = (stack<string>) map_dico.at(word_id);

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

    return 0;
}

void my_handler(int s){
    printf("Caught signal %d\n",s);
    printf("Exit Programme %d\n",s);
    active = false;
    exit(0);
}

bool isAnagrame(string a, string b){

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    for (int i = 0; i < int(a.length()); i++)
        if (a[i] != b[i])
            return false;

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