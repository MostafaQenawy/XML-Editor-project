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

// Function to replace a substring within a string
string replace_str(const string& str, const string& from, const string& to) {
    size_t start_pos = str.find(from);
    if (start_pos != string::npos) {
        string result = str;
        result.replace(start_pos, from.length(), to);
        return result;
    }
    return str;
}

/////////////////////////////////////////////////////////////////////////////


// Function to trim leading and trailing whitespaces from a string
void trim(string& str) {
    // Trim leading whitespaces
    size_t start = 0;
    while (start < str.length() && isspace(str[start])) {
        start++;
    }
    str = str.substr(start);

    // Trim trailing whitespaces
    size_t end = str.length();
    while (end > 0 && isspace(str[end - 1])) {
        end--;
    }
    str = str.substr(0, end);
}

// Function to read a file and store its lines in a vector of strings
vector<string> fileToVector(const string& fileLoc) {
    vector<string> fileLines;

    ifstream fileStream(fileLoc); // Use ifstream constructor directly

    if (fileStream.is_open()) {
        string line;

        while (getline(fileStream, line)) {
            trim(line); // Trim leading and trailing whitespaces from the line
            fileLines.push_back(line); // Add the trimmed line to the vector
        }

        fileStream.close(); // Close the file stream when done
    } else {
        cerr << "Failed to open file: " << fileLoc << endl;
    }

    return fileLines; // Return the vector of strings containing file lines
}


//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// Function to get the open tag from a string
string getOpenTag(const string& t) {
    size_t start = t.find('<');
    size_t end = t.find('>', start);

    // Check if start and end positions are valid
    if (start != string::npos && end != string::npos &&
        t[start + 1] != '/' && t[start + 1] != '?' && t[start + 1] != '!')
    {
        // Extract the substring between start and end
        return t.substr(start + 1, end - start - 1);
    } else {
        return "FALSE";
    }
}



string getClosedTag(const string& t) {
    size_t start = t.find('/',1);
    size_t end = t.find('>', start);

    // Check if start and end positions are valid
    if (start != string::npos) {
        if (end != string::npos) {
            // Extract the substring between start and end
            string potentialClosedTag = t.substr(start + 1, end - start - 1); // Skip the '/'

            // Check if the potential closed tag contains only alphanumeric characters
            if (all_of(potentialClosedTag.begin(), potentialClosedTag.end(), ::isalnum)) {
                return potentialClosedTag;
            } else {
                // Error: '>' not found after '/'
                return "ERROR: there is an invalid charachter";
            }
        } else {
            // Error: '/' not found
            return "ERROR: '>' not found after '/'";
        }
    }

    return "FALSE";
}



// Function to extract the value from an XML-like tag
string getTagValue(const string& tag) {
    // Find the position of the closing angle bracket '>'
    size_t start = tag.find('>');

    // Find the position of the forward slash '/' after the closing angle bracket
    size_t end = tag.find('/', start);

    // Check if the opening angle bracket '>' was found
    if (start != string::npos) {
        // Calculate the length of the substring to extract based on the position of '/'
        // If '/' is not found, extract until the end of the string
        size_t length = (end != string::npos) ? end - start - 1 : string::npos;

        // Extract the substring starting from the character after '>'
        return tag.substr(start + 1, length);
    } else {
        // Return "FALSE" if the opening angle bracket '>' is not found
        return "FALSE";
    }
}


bool consistency_checker(string opent, string closedt, stack <string>& s)
{
    if (opent.compare("FALSE"))
    {
        s.push(opent);
    }
    if (closedt.compare("FALSE"))
    {
        if (!s.empty())
        {
            if (!closedt.compare(s.top()))
                s.pop();
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        return true;
    }
    return true;
}



bool check_consistency(const vector<string>& xml_vector) {
    stack<string> s;

    for (const auto& line : xml_vector) {
        string opent = getOpenTag(line);
        string closedt = getClosedTag(line);

        if (opent != "FALSE" || closedt != "FALSE") {
            if (!consistency_checker(opent, closedt, s)) {
                return false;
            }
        }
    }

    // Return true if the stack is empty (all tags are closed properly)
    return s.empty();
}



////////////////////////////////////////////////////////////////////////////////////////////////

// Function to check for errors in XML tags and provide details of the error type
bool error_detector(const string& opent, const string& closedt, stack<string>& s, string& error_type) {
    stack<string> temp;

    // Check if both open and closed tags are present
    if (opent != "FALSE" && closedt != "FALSE") {
        // Check if open and closed tags match
        if (opent != closedt) {
            error_type = "not matching tags: " + opent + " and " + closedt;
            return false;
        }
    }

    // Check for open tag and update stack
    if (opent != "FALSE") {
        s.push(opent);
    }

    // Check for closed tag
    if (closedt != "FALSE") {
        // Check if the stack is not empty
        if (!s.empty()) {
            // Check if the closed tag matches the top of the stack
            if (closedt == s.top()) {
                s.pop();
            } else {
                // Handle the case of mismatched tags
                while (!s.empty() && closedt != s.top()) {
                    temp.push(s.top());
                    s.pop();
                }
                if (s.empty()) {
                    // Handle the case of a missed open tag (closedt is unmatched)
                    error_type = "<" + closedt + ">";
                    while (!temp.empty()) {
                        s.push(temp.top());
                        temp.pop();
                    }
                } else {
                    // Handle the case of a missed closed tag (top of the stack is unmatched)
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
            // Handle the case of a missed closed tag (stack is empty)
            error_type = "<" + closedt + ">";
            return false; // Error at location zero
        }
        return true;
    }
    return true;
}


// Structure to store error information


// Function to detect errors in XML tags and return a vector of error information
vector<err_dataa> detect_error(const vector<string>& xml_vector) {
    vector<err_dataa> error_vector;
    stack<string> s;
    err_dataa error;

    // Loop through each line in the XML vector
    for (int i = 0; i < xml_vector.size(); i++) {
        const string& line = xml_vector[i];
        string opent = getOpenTag(line);
        string closedt = getClosedTag(line);

        // Check if tags are present
        if (opent != "FALSE" || closedt != "FALSE") {
            // Check for errors using the error_detector function
            if (!error_detector(opent, closedt, s, error.err_type)) {
                // Handle different error cases
                error.err_loc = i;
                if (error.err_type.size() > 25) //for mismatching tags
                {
                    error_vector.push_back(error);
                } else {
                    error_vector.push_back(error);
                }
            }
        }
    }

    // Process any remaining unmatched open tags
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

//////////////////////////////////////////////////////////////////////////////////////////////////

// Function to correct errors in the XML vector based on the error information
vector<string> error_corrector(const vector<string>& xml_vector, const vector<err_dataa>& error_vector) {
    int counter = 0;
    vector<string> corrected_vector;

    // Loop through each line in the XML vector
    for (int i = 0; i < xml_vector.size(); i++) {
        // Check if the current line has an error
        if (i == error_vector[counter].err_loc) {
            // Check if it's a not matching tags error
            if (error_vector[counter].err_type.size() > 25) {
                // Replace the closed tag with an open tag in the current line
                corrected_vector.push_back(replace_str(xml_vector[i], getClosedTag(xml_vector[i]), getOpenTag(xml_vector[i])));
            } else {
                // Add the error message and the original line to the corrected vector
                corrected_vector.push_back(error_vector[counter].err_type);
                corrected_vector.push_back(xml_vector[i]);
            }
            // Move to the next error if available
            if (counter < error_vector.size() - 1)
                counter++;
        } else {
            // Add the original line to the corrected vector
            corrected_vector.push_back(xml_vector[i]);
        }
    }

    // Process any remaining errors
    if (counter < error_vector.size() - 1) {
        for (int i = counter; i < error_vector.size(); i++) {
            corrected_vector.push_back(error_vector[i].err_type);
        }
    }

    return corrected_vector;
}

string printError(vector<err_dataa> error_vector) {
    stringstream ss;  // Use stringstream directly

    for (auto &i : error_vector) {
        if (i.err_type.size() > 25) {
            ss << "Error at line " << i.err_loc + 1 << ": " << i.err_type << endl;
        } else {
            ss << "Error at line " << i.err_loc + 1 << ": Missing " << i.err_type << endl;
        }
    }

    return ss.str();
}
