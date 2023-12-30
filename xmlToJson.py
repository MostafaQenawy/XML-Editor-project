#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include <map>

// Struct representing a node in an XML-like structure
struct Node {
    std::string name;           // Name of the node
    std::string content;        // Content of the node (for leaf nodes)
    std::vector<Node> children; // Children nodes

    // Default constructor
    Node() = default;

    // Constructor with a specified name
    explicit Node(std::string n) : name(std::move(n)) {}

    // Add a child node to the current node
    void addChild(const Node& node) {
        children.push_back(node);
    }

    // Check if the node is a leaf (has no children)
    bool isLeaf() const {
        return children.empty();
    }

    // Repeat a string a certain number of times
    std::string repeat(const std::string& str, int times) const {
        std::string result;
        for (int i = 0; i < times; ++i) {
            result += str;
        }
        return result;
    }

    // Convert the node and its children to a JSON-like string
    std::string toJSON(int indent = 0) const {
        std::stringstream ss;

        // Wrap the whole structure in the root name if it's the root node
        if (indent == 0 && !name.empty()) {
            indent += 1;
            ss <<  "{\n" <<  repeat("  ", indent)  << "\"" << name << "\": ";
        }

        if (isLeaf()) {
            ss << "\"" << content << "\"";
        } else {
            if (!isLeaf()) ss << "{\n"; // Begin object notation for non-leaf

            std::map<std::string, std::vector<Node>> groupedChildren;
            for (const auto& child : children) {
                groupedChildren[child.name].push_back(child);
            }

            for (auto it = groupedChildren.begin(); it != groupedChildren.end(); ++it) {
                if (it->second.size() == 1) {
                    // Output for a single child with indentation
                    ss << repeat("  ", indent + 1) << "\"" << it->first << "\": " << it->second[0].toJSON(indent + 1);
                } else {
                    // Output for multiple children with an array
                    ss << repeat("  ", indent + 1) << "\"" << it->first << "\": [\n";
                    for (size_t i = 0; i < it->second.size(); ++i) {
                        ss << repeat("  ", indent + 2) << it->second[i].toJSON(indent + 2);
                        if (i < it->second.size() - 1) ss << ",";
                        ss << "\n";
                    }
                    ss << repeat("  ", indent + 1) << "]";
                }
                ss << (std::next(it) == groupedChildren.end() ? "\n" : ",\n");
            }

            if (!isLeaf()) ss << repeat("  ", indent) << "}"; // End object notation for non-leaf
        }

        if (indent == 1 && !name.empty()) {
            ss << "\n}"; 
        }

        return ss.str();
    }
};

// Parse an XML-like string and construct a tree of nodes
Node parseXML(const std::string& xml) {
    std::stack<Node> stack;
    std::string temp;
    Node root;
    bool isTag = false;

    for (char ch : xml) {
        if (ch == '<') {
            // Handle the beginning of a tag
            if (!temp.empty()) {
                size_t start = temp.find_first_not_of(" \n\r\t");
                size_t end = temp.find_last_not_of(" \n\r\t");
                if (start != std::string::npos && end != std::string::npos)
                    stack.top().content = temp.substr(start, end - start + 1);
                temp.clear();
            }
            isTag = true;
        } else if (ch == '>') {
            // Handle the end of a tag
            if (!stack.empty() && temp[0] == '/') {
                // Pop the completed node from the stack
                Node completedNode = stack.top();
                stack.pop();
                if (stack.empty()) {
                    root = completedNode;
                } else {
                    stack.top().addChild(completedNode);
                }
            } else {
                // Push a new node onto the stack
                stack.push(Node(temp));
            }
            temp.clear();
            isTag = false;
        } else if (!isTag && ch == '\n') {
            // Skip newline characters
            continue;
        } else {
            // Accumulate characters within a tag
            temp += ch;
        }
    }
    return root;
}
