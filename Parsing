/*
 * Name : Mohaned Khaled Hassan'
 * ID   : 2001372
 * Date : 29/12/2023
 */

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
        for (int followerID: followers) {
            cout << followerID << " ";
        }
        cout << endl;

        // Print posts
        cout << "\nPosts:" << endl;
        for (const Post &post: posts) {
            cout << "\nBody: " << post.body << endl;

            cout << "\nTopics: \n";
            for (const string &topic: post.topics) {
                cout << topic << endl;
            }
        }

        cout << "------------------------------------------------" << endl;
    }
};

vector<User> parsing(string &input) {
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

/* Test with three different forms of XML text */
int main() {
    string input1 = "<users>\n"
                    "<user>\n"
                    "<id>\n"
                    "1</id>\n"
                    "<name>\n"
                    "AhmedAli</name>\n"
                    "<posts>\n"
                    "<post>\n"
                    "<body>\n"
                    "Loremipsumdolorsitamet,consecteturadipiscingelit,seddoeiusmodtemporincididuntutlaboreetdoloremagnaaliqua.Utenimadminimveniam,quisnostrudexercitationullamcolaborisnisiutaliquipexeacommodoconsequat.</body>\n"
                    "<topics>\n"
                    "<topic>\n"
                    "economy</topic>\n"
                    "<topic>\n"
                    "finance</topic>\n"
                    "</topics>\n"
                    "</post>\n"
                    "<post>\n"
                    "<body>\n"
                    "Loremipsumdolorsitamet,consecteturadipiscingelit,seddoeiusmodtemporincididuntutlaboreetdoloremagnaaliqua.Utenimadminimveniam,quisnostrudexercitationullamcolaborisnisiutaliquipexeacommodoconsequat.</body>\n"
                    "<topics>\n"
                    "<topic>\n"
                    "solar_energy</topic>\n"
                    "</topics>\n"
                    "</post>\n"
                    "</posts>\n"
                    "<followers>\n"
                    "<follower>\n"
                    "<id>\n"
                    "2</id>\n"
                    "</follower>\n"
                    "<follower>\n"
                    "<id>\n"
                    "3</id>\n"
                    "</follower>\n"
                    "</followers>\n"
                    "</user>\n"
                    "<user>\n"
                    "<id>\n"
                    "2</id>\n"
                    "<name>\n"
                    "YasserAhmed</name>\n"
                    "<posts>\n"
                    "<post>\n"
                    "<body>\n"
                    "Loremipsumdolorsitamet,consecteturadipiscingelit,seddoeiusmodtemporincididuntutlaboreetdoloremagnaaliqua.Utenimadminimveniam,quisnostrudexercitationullamcolaborisnisiutaliquipexeacommodoconsequat.</body>\n"
                    "<topics>\n"
                    "<topic>\n"
                    "education</topic>\n"
                    "</topics>\n"
                    "</post>\n"
                    "</posts>\n"
                    "<followers>\n"
                    "<follower>\n"
                    "<id>\n"
                    "1</id>\n"
                    "</follower>\n"
                    "</followers>\n"
                    "</user>\n"
                    "<user>\n"
                    "<id>\n"
                    "3</id>\n"
                    "<name>\n"
                    "MohamedSherif</name>\n"
                    "<posts>\n"
                    "<post>\n"
                    "<body>\n"
                    "Loremipsumdolorsitamet,consecteturadipiscingelit,seddoeiusmodtemporincididuntutlaboreetdoloremagnaaliqua.Utenimadminimveniam,quisnostrudexercitationullamcolaborisnisiutaliquipexeacommodoconsequat.</body>\n"
                    "<topics>\n"
                    "<topic>\n"
                    "sports</topic>\n"
                    "</topics>\n"
                    "</post>\n"
                    "</posts>\n"
                    "<followers>\n"
                    "<follower>\n"
                    "<id>\n"
                    "1</id>\n"
                    "</follower>\n"
                    "</followers>\n"
                    "</user>\n"
                    "</users>";

    string input2 = "\n"
                    "<users>\n"
                    "    <user>\n"
                    "        <id>1</id>\n"
                    "        <name>Mohaned Khaled</name>\n"
                    "        <posts>\n"
                    "            <post>\n"
                    "                <body>\n"
                    "                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
                    "                </body>\n"
                    "                <topics>\n"
                    "                    <topic>\n"
                    "                        economy\n"
                    "                    </topic>\n"
                    "                    <topic>\n"
                    "                        finance\n"
                    "                    </topic>\n"
                    "                </topics>\n"
                    "            </post>\n"
                    "            <post>\n"
                    "                <body>\n"
                    "                    love and lolknc, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
                    "                </body>\n"
                    "                <topics>\n"
                    "                    <topic>\n"
                    "                        Love\n"
                    "                    </topic>\n"
                    "                </topics>\n"
                    "            </post>\n"
                    "        </posts>\n"
                    "        <followers>\n"
                    "            <follower>\n"
                    "                <id>2</id>\n"
                    "            </follower>\n"
                    "            <follower>\n"
                    "                <id>3</id>\n"
                    "            </follower>\n"
                    "        </followers>\n"
                    "    </user>\n"
                    "    <user>\n"
                    "        <id>2</id>\n"
                    "        <name>Sawsan Ahmed </name>\n"
                    "        <posts>\n"
                    "            <post>\n"
                    "                <body>\n"
                    "                    Ain shames de7k, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
                    "                </body>\n"
                    "                <topics>\n"
                    "                    <topic>\n"
                    "                        education\n"
                    "                    </topic>\n"
                    "                </topics>\n"
                    "            </post>\n"
                    "        </posts>\n"
                    "        <followers>\n"
                    "            <follower>\n"
                    "                <id>3</id>\n"
                    "            </follower>\n"
                    "                <follower>\n"
                    "                <id>1</id>\n"
                    "            </follower>\n"
                    "        </followers>\n"
                    "    </user>\n"
                    "    <user>\n"
                    "        <id>3</id>\n"
                    "        <name>Younes Sherif</name>\n"
                    "        <posts>\n"
                    "            <post>\n"
                    "                <body>\n"
                    "                    Real Madrid have 14 cups, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n"
                    "                </body>\n"
                    "                <topics>\n"
                    "                    <topic>\n"
                    "                        Champions Legaue\n"
                    "                    </topic>\n"
                    "                </topics>\n"
                    "            </post>\n"
                    "        </posts>\n"
                    "        <followers>\n"
                    "            <follower>\n"
                    "                <id>1</id>\n"
                    "            </follower>\n"
                    "               <follower>\n"
                    "                <id>2</id>\n"
                    "            </follower>\n"
                    "        </followers>\n"
                    "    </user>\n"
                    "</users>\n"
                    "sample.xml\n"
                    "Displaying sample.xml.";

    string input3 = "<users><user><id>1</id><name>AhmedAli</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
                   "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ul"
                   "lamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>economy</topic><topic>finance</topic></topic"
                   "s></post><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore"
                   " et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commod"
                   "o consequat.</body><topics><topic>solar_energy</topic></topics></post></posts><followers><follower><id>2</id></follower>"
                   "<follower><id>3</id></follower></followers></user><user><id>2</id><name>YasserAhmed</name><posts><post><body>Lorem ipsum"
                   " dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim"
                   " ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topi"
                   "c>education</topic></topics></post></posts><followers><follower><id>1</id></follower></followers></user><user><id>3</id>"
                   "<name>MohamedSherif</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tem"
                   "por incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi"
                   " ut aliquip ex ea commodo consequat.</body><topics><topic>sports</topic></topics></post></posts><followers><follower><id"
                   ">1</id></follower></followers></user></users>";

    vector<User> data1 = parsing(input1);
    for (const auto &user: data1) {
        user.printUser();
    }

    cout<<"\n\nTest 1 Finished.........."
          "\n|||\n"
          "|||\n"
          "|||\n"
          "|||\n"
          "|||\n"
          "|||\n\n";

    vector<User> data2 = parsing(input2);
    for (const auto &user: data2) {
        user.printUser();
    }

    cout<<"\n\nTest 2 Finished.........."
          "\n|||\n"
          "|||\n"
          "|||\n"
          "|||\n"
          "|||\n"
          "|||\n\n";

    vector<User> data3 = parsing(input3);
    for (const auto &user: data3) {
        user.printUser();
    }

    cout<<"Test 3 Finished..........\n";

    return 0;
}
