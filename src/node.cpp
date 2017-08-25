#include "node.h"
Node::Node(string name,int data, Node *parent)
{
	this->children = vector<Node*>();
    this->name = name;
    this->data = data;
    this->parent = parent;
}
Node::~Node()
{
	for(uint i = 0; i < children.size(); i++)
	{
		delete children[i];
	}
	children.clear();
}
string Node::getName()
{
    return this->name;
}
int Node::getData()
{
    return this->data;
}
Node* Node::getParent()
{
	return this->parent;
}
Node* Node::getChild(string childName)
{
    Node* temp = NULL;
    for (size_t i = 0; i < children.size(); i++)
    {
        if (children.at(i)->getName() == childName)
        {
            temp = children.at(i);
        }
    }
    return temp;
}
Node* Node::getChildAt(int index)
{
	return children.at(index);
}
int Node::getNrOfChildren()
{
    return this->children.size();
}
void Node::createChild(Node *child)
{
    this->children.push_back(child);
}
vector<Node*> Node::getAllChildren()
{
    return children;
}
vector<string> Node::getAllChildrenAsString()
{
    int size = this->children.size();
    std::vector<string> allChildren;
    for (int i = 0; i < size; i++)
    {
        allChildren.push_back(this->children.at(i)->asString());
    }
    return allChildren;
}
string Node::asString()
{
    if (isFolder())
    {
        string folderName = "\033[32m" + this->name + "\033[0m";
        return folderName;
    }
    string fileName = "\033[1;34m" + this->name + "\033[0m";
    return fileName;
}
bool Node::isFolder()
{
    return this->data == -1;
}
void Node::removeChildAt(int location)
{
    children.erase(children.begin()+location);
}
