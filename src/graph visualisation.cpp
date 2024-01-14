#include<bits/stdc++.h>

using namespace std;

class Post {
public:
    string body;
    vector<string> topics;
};

class User {
public:
    int ID{};
    string name;
    vector<int> followers;
    vector<Post> posts;

    User() = default;

    // Print function to display user information
    void printUser() const {
        cout << "User ID: " << ID << ", Name: " << name << endl;

        // Print followers
        cout << "\nFollowers: ";
        for (int followerID : followers) {
            cout << followerID << " ";
        }
        cout << endl;

        // Print posts
        cout << "\nPosts:" << endl;
        for (const Post& post : posts) {
            cout << "\nBody: " << post.body << endl;

            cout << "\nTopics: \n";
            for (const string& topic : post.topics) {
                cout << topic << endl;
            }
        }

        cout << "------------------------------------------------" << endl;
    }
};

vector<User> parsing(string& input) {
    vector<User> users;  // Vector to store parsed user data
    string IDstr;        // Temporary string to store ID and name

    // Loop through the input string
    for (int i = 0; i < input.length(); ++i) {

        // Check for the start of a user element
        if (input[i] == '<' && input[i + 1] == 'u') {
            User user;  // Create a new user object

            // Loop through the user element content
            for (i = i; i < input.length() &&
                !(input[i] == '<' && input[i + 1] == '/' && input[i + 2] == 'u' && input[i + 3] == 's'); ++i) {

                // Parse user ID
                if (input[i] == '<' && input[i + 1] == 'i') {
                    while (!isdigit(input[++i]));
                    IDstr = input.substr(i, input.length() - i);
                    user.ID = stoi(IDstr);
                    IDstr.clear();
                }

                // Parse user name
                if (input[i] == '<' && input[i + 1] == 'n') {
                    while (input[++i] != '>');
                    while (input[++i] < 65 || input[i] > 126);

                    while (input[i] != '<' && ((input[i] > 64 && input[i] < 123) ||
                        (input[i] == ' ' && input[i + 1] > 64 && input[i + 1] < 123)))
                        IDstr += input[i++];

                    user.name = IDstr;
                    IDstr.clear();
                }

                // Parse user followers
                if (input[i] == '<' && input[i + 1] == 'f') {
                    while (!isdigit(input[++i]));
                    IDstr = input.substr(i, input.length() - i);
                    user.followers.push_back(stoi(IDstr));
                    IDstr.clear();
                }

                // Parse user posts
                if (input[i] == '<' && input[i + 1] == 'p') {
                    i++;

                    // Loop through post elements
                    for (i = i; i < input.length() && !(input[i] == '<' && input[i + 1] == '/' && input[i + 2] == 'p' &&
                        input[i + 3] == 'o' && input[i + 4] == 's' &&
                        input[i + 5] == 't' && input[i + 6] == 's'); ++i) {

                        // Check for the start of a post element
                        if (input[i] == '<' && input[i + 1] == 'p') {
                            Post post;  // Create a new post object

                            // Loop through post content
                            for (i = i; i < input.length() &&
                                !(input[i] == '<' && input[i + 1] == '/' && input[i + 2] == 'p'); ++i) {

                                // Parse post body
                                if (input[i] == '<' && input[i + 1] == 'b') {
                                    while (input[++i] != '>');
                                    while (input[++i] < 33 || input[i] > 126);

                                    while (!(input[i] == '<' || (input[i] == ' ' && input[i + 1] == ' ') ||
                                        (input[i] < 32 || input[i] > 126)))
                                        post.body += input[i++];
                                }

                                // Parse post topics
                                else if (input[i] == '<' && input[i + 1] == 't') {
                                    i++;

                                    // Loop through topic elements
                                    for (i = i; i < input.length() &&
                                        !(input[i] == '<' && input[i + 1] == '/' && input[i + 2] == 't' &&
                                            input[i + 3] == 'o' && input[i + 4] == 'p' && input[i + 5] == 'i' &&
                                            input[i + 6] == 'c' && input[i + 7] == 's'); ++i) {

                                        string topic;  // Temporary string to store topic

                                        // Parse topic content
                                        if (input[i] == '<' && input[i + 1] == 't') {
                                            while (input[++i] != '>');
                                            while (input[++i] < 65 || input[i] > 122);

                                            while ((input[i] > 64 && input[i] < 123) ||
                                                (input[i] == ' ' && (input[i + 1] > 64 && input[i + 1] < 123)))
                                                topic += input[i++];
                                            post.topics.push_back(topic);
                                        }
                                    }
                                }
                            }
                            user.posts.push_back(post);  // Add post to user's posts
                        }
                    }
                }
            }
            users.push_back(user);  // Add user to the vector
        }
    }
    return users;  // Return the vector of parsed users
}
void generateDotFile(const vector<User>& users) {
    ofstream dotFile("user_graph.dot");

    if (!dotFile.is_open()) {
        cerr << "Error opening DOT file" << endl;
        return;
    }

    dotFile << "digraph G {" << endl;

    // Add nodes
    for (const auto& user : users) {
        dotFile << "  " << user.ID << " [label=\"" << user.name << "\\nID: " << user.ID << "\"]" << std::endl;

        // Add edges based on connections
        for (int connectedUserId : user.followers) {
            dotFile << "  " << user.ID << " -> " << connectedUserId << ";" << endl;
        }
    }

    dotFile << "}" << endl;

    dotFile.close();
}

void generateGraphImage() {
    string command = "dot -Tpng user_graph.dot -o user_graph.png";
    system(command.c_str());
}

/* Test with three different forms of XML text */
int main(){
    return 0;
}
