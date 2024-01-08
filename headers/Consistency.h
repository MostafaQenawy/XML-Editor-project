#ifndef CONSISTENCY_H
#define CONSISTENCY_H


#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

string replace_str(const string& str, const string& from, const string& to);
void trim(string& str);
vector<string> fileToVector(const string& fileLoc);
string getOpenTag(const string& t);
string getClosedTag(const string& t);
string getTagValue(const string& tag);
bool consistency_checker(const string& opent, const string& closedt, stack<string>& s);
bool check_consistency(const vector<string>& xml_vector);
bool error_detector(const string& opent, const string& closedt, stack<string>& s, string& error_type);
struct err_dataa {
    string err_type;
    int err_loc;
};
vector<err_dataa> detect_error(const vector<string>& xml_vector);
vector<string> error_corrector(const vector<string>& xml_vector, const vector<err_dataa>& error_vector);
string printError(vector<err_dataa> error_vector);
#endif
