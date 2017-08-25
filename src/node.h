#ifndef NODE_H
#define NODE_H

using namespace std;

#include <vector>
#include <iostream>
#include <string>

class Node
{
private:
    int data;
    string name;
    Node *parent;
    vector<Node*> children;

  public:
    Node(string name = "/", int data = -1, Node *parent = NULL);
    string getName();
    int getData();
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
    ~Node();
};

#endif
