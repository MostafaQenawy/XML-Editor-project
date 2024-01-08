#include "Consistency.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

const string FALSE_STR = "FALSE";

string replace_str(const string& str, const string& from, const string& to) {
    size_t start_pos = str.find(from);
    if (start_pos != string::npos) {
        string result = str;
        result.replace(start_pos, from.length(), to);
        return result;
    }
    return str;
}

void trim(string& str) {
    size_t start = 0;
    while (start < str.length() && isspace(str[start])) {
        start++;
    }
    str = str.substr(start);

    size_t end = str.length();
    while (end > 0 && isspace(str[end - 1])) {
        end--;
    }
    str = str.substr(0, end);
}

string getOpenTag(const string& tag) {
    size_t start = tag.find('<');
    size_t end = tag.find('>', start);

    if (start != string::npos && end != string::npos &&
        tag[start + 1] != '/' && tag[start + 1] != '?' && tag[start + 1] != '!')
    {
        return tag.substr(start + 1, end - start - 1);
    } else {
        return FALSE_STR;
    }
}

string getClosedTag(const string& tag) {
    size_t start = tag.find('/', 1);
    size_t end = tag.find('>', start);

    if (start != string::npos) {
        if (end != string::npos) {
            return tag.substr(start + 1, end - start - 1);
        } else {
            return "ERROR: '>' not found after '/'";
        }
    }

    return FALSE_STR;
}

vector<string> fileToVector(const string& fileLoc) {
    vector<string> fileLines;

    ifstream fileStream(fileLoc);

    if (fileStream.is_open()) {
        string line;

        while (getline(fileStream, line)) {
            trim(line);
            fileLines.push_back(line);
        }

        fileStream.close();
    } else {
        cerr << "Failed to open file: " << fileLoc << endl;
    }

    return fileLines;
}

string getTagValue(const string& tag) {
    size_t start = tag.find('>');
    size_t end = tag.rfind('<');

    if (start != string::npos && end != string::npos && start < end) {
        return tag.substr(start + 1, end - start - 1);
    } else {
        return "FALSE";
    }
}

bool isMatchingPair(const string& openTag, const string& closeTag) {
   return openTag.substr(1, openTag.length() - 2) == closeTag.substr(2, closeTag.length() - 3);
}

bool consistency_checker(const string& openTag, const string& closeTag, stack<string>& s) {
    vector<err_dataa> errorVector;
    if (openTag != FALSE_STR) {
        s.push(openTag);
    }

    if (closeTag != FALSE_STR) {
        if (!s.empty()) {
            if (isMatchingPair(s.top(), closeTag)) {
                s.pop();
            } else {
                err_dataa error;
                error.err_type = "Not matching tags: " + s.top() + " and " + closeTag;
                error.err_loc = -1; // Set to -1 to indicate this error is not associated with a specific line
                errorVector.push_back(error);
                return false;
            }
        } else {
            err_dataa error;
            error.err_type = "Mismatched closing tag or missing opening tag: " + closeTag;
            error.err_loc = -1; // Set to -1 to indicate this error is not associated with a specific line
            errorVector.push_back(error);
            return false;
        }
    }

    return true;
}


bool check_consistency(const vector<string>& xml_vector, vector<err_dataa>& error_vector) {
 stack<string> s;

 for (int i = 0; i < xml_vector.size(); i++) {
    const string& line = xml_vector[i];
    string openTag = getOpenTag(line);
    string closedTag = getClosedTag(line);

    if (!openTag.empty() && openTag != FALSE_STR) {
         s.push(openTag);
    }

    if (!closedTag.empty() && closedTag != FALSE_STR) {
         if (!s.empty()) {
             string expectedClosingTag = s.top();
             if (expectedClosingTag == closedTag) {
                s.pop();
             } else {
                err_dataa error;
                error.err_type = "Mismatched closing tag or missing opening tag: Expected " + expectedClosingTag + ", got " + closedTag;
                error.err_loc = i;
                error_vector.push_back(error);
             }
         } else {
             err_dataa error;
             error.err_type = "Mismatched closing tag or missing opening tag: No opening tag for " + closedTag;
             error.err_loc = i;
             error_vector.push_back(error);
         }
    }
 }

 return error_vector.empty();
}






bool error_detector(const string& opent, const string& closedt, stack<string>& s, string& error_type) {
  stack<string> temp;

  if (opent != FALSE_STR && closedt != FALSE_STR) {
      if (opent != closedt) {
          error_type = "Not matching tags: " + opent + " and " + closedt;
          return false;
      }
  }

  if (opent != FALSE_STR) {
      s.push(opent);
  }

  if (closedt != FALSE_STR) {
      if (!s.empty()) {
          if (closedt == s.top()) {
              s.pop();
          } else {
              while (!s.empty() && closedt != s.top()) {
                temp.push(s.top());
                s.pop();
              }
              if (s.empty()) {
                error_type = "<" + closedt + ">";
                while (!temp.empty()) {
                    s.push(temp.top());
                    temp.pop();
                }
              } else {
                s.pop();
                while (!temp.empty()) {
                    s.push(temp.top());
                    temp.pop();
                }
                error_type = "</" + s.top() + ">";
                s.pop();
              }
              return false;
          }
      } else {
          error_type = "<" + closedt + ">";
          return false;
      }
  }

  return true;
}

vector<err_dataa> detect_error(const vector<string>& xml_vector) {
    vector<err_dataa> error_vector;
    stack<string> s;
    err_dataa error;

    for (int i = 0; i < xml_vector.size(); i++) {
        const string& line = xml_vector[i];
        string openTag = getOpenTag(line);
        string closedTag = getClosedTag(line);

        if (openTag != FALSE_STR || closedTag != FALSE_STR) {
            if (!error_detector(openTag, closedTag, s, error.err_type)) {
                error.err_loc = i;
                error_vector.push_back(error);
            }
        }
    }

    int i = xml_vector.size();
    while (!s.empty()) {
        string err = "</" + s.top() + ">";
        error.err_type = err;
        error.err_loc = i;
        error_vector.push_back(error);
        i++;
        s.pop();
    }

    return error_vector;
}

vector<string> error_corrector(const vector<string>& xml_vector, const vector<err_dataa>& error_vector) {
 vector<string> corrected_vector;
 stack<string> s; // Stack to hold opened tags
 int counter = 0;

 for (int i = 0; i < xml_vector.size(); i++) {
     const string& line = xml_vector[i];
     string openTag = getOpenTag(line);
     string closedTag = getClosedTag(line);

     if (openTag != FALSE_STR) {
         s.push(openTag);
     }
     if (closedTag != FALSE_STR) {
         if (!s.empty() && closedTag == s.top()) {
             s.pop();
         }
     }

     if (i == error_vector[counter].err_loc) {
         if (error_vector[counter].err_type.size() > 25) {
             corrected_vector.push_back(replace_str(xml_vector[i], getClosedTag(xml_vector[i]), getOpenTag(xml_vector[i])));
         } else {
             corrected_vector.push_back("<"+xml_vector[i]);
         }

         if (counter < error_vector.size() - 1) {
             counter++;
         }
     } else {
         corrected_vector.push_back(xml_vector[i]);
     }
 }

 // Append missing closing tags
 while (!s.empty()) {
     string closingTag = "</" + s.top() + ">";
     corrected_vector.push_back(closingTag);
     s.pop();
 }

 return corrected_vector;
}



string printError(const vector<err_dataa>& error_vector) {
    stringstream ss;

    for (const auto& i : error_vector) {
        ss << "Error at line " << i.err_loc + 1 << ": " << i.err_type << endl;
    }

    return ss.str();
}
