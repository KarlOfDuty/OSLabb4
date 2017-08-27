#ifndef NODE_H
#define NODE_H

using namespace std;

#include <vector>
#include <iostream>
#include <string>

class Node
{
private:
    int dataLocation;
    string name;
    Node *parent;
    vector<Node*> children;

  public:
    Node(string name = "/", int dataLocation = -1, Node *parent = NULL);
    string getName();
    int getDataLocation();
    int getNrOfChildren();
    void createChild(Node *child);
    Node* getParent();
    Node* getChild(string childName);
	Node* getChildAt(int index);
    vector<Node*> getAllChildren();
    vector<string> getAllChildrenAsString();
    string asString();
    bool isFolder();
    void removeChildAt(int location);
	void removeChild(std::string childName);
    ~Node();
};

#endif
