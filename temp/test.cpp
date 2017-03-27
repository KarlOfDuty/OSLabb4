#include <iostream>
#include "node.h"
int main()
{
    Node temp = Node("/");
    //std::cout << temp.asString() << std::endl;
    temp.createChild(Node("hejsan"));
    temp.createChild(Node("hejsan2"));
    temp.createChild(Node("hejsan3"));
    temp.createChild(Node("hejsan4"));
    std::vector<string> v = temp.getAllChildren();
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v.at(i) << std::endl;
    }
    /*
    Node temp = Node();
    //Node test2 = Node(2);
    for (int i = 0; i < 100; i++) {
        temp.createChild(Node(i));
    }
    */
  return 0;
}
