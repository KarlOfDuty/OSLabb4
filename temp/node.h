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
    vector<Node> children;

  public:
    Node(string name, int data = -1, Node *parent = NULL);
	Node* getParent();
    void addChild(Node child);
    Node getParent();
    string asString();
    vector<string> getAllChildren();
    ~Node();
};

#endif
