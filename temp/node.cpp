#include "node.h"
Node::Node(string name,int data, Node *parent)
{
    this->name = name;
    this->data = data;
    this->parent = parent;
}
Node::~Node()
{

}
Node* Node::getParent()
{
		return this->parent;
}
void Node::createChild(Node child)
{
    this->children.push_back(child);
}
vector<string> Node::getAllChildren()
{
    int size = this->children.size();
    std::vector<string> allChildren;
    for (int i = 0; i < size; i++)
    {
        allChildren.push_back(this->children.at(i).asString());
    }
    return allChildren;
}
string Node::asString()
{
    return this->name;
}
