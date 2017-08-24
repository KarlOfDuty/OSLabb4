#include "filesystem.h"
#include <sstream>
FileSystem::FileSystem()
{
    //mMemblockDevice = MemblockDevice();
    root = new Node();
    currentDir = root;
    for (size_t i = 0; i < 250; i++)
    {
        isEmpty[i] = true;
    }
    Node *temp = new Node("folder1",-1,root);
    temp->createChild(new Node("folder2",-1,temp));
    root->createChild(temp);
    root->createChild(new Node("hejsan",-1,root));
    root->createChild(new Node("hejsan2",-1,root));
    root->createChild(new Node("hejsan3",-1,root));
    root->createChild(new Node("hejsan4",-1,root));
    root->createChild(new Node("file", 10, root));
}

FileSystem::~FileSystem()
{

}
//Creates a new file
void FileSystem::createFile(string name, Node* path)
{
    int blockLocation = -1;
    for (size_t i = 0; i < 250; i++) {
        if(isEmpty[i])
        {
            std::cout << "tom plats på i : " << i << std::endl;
            blockLocation = i;
            isEmpty[i] = false;
            i = 250;
        }
    }
    if (path != NULL)
    {
        Node *file = new Node(name,blockLocation,currentDir);
        path->createChild(file);
    }
    else
    {
        Node *file = new Node(name,blockLocation,currentDir);
        currentDir->createChild(file);

    }
}
//Creates a new folder
void FileSystem::createFolder(string name)
{
    Node *folder = new Node(name,-1,currentDir);
    currentDir->createChild(folder);
}
//Removes a file
bool FileSystem::removeFile(string name)
{
    bool fileFound = false;
    vector<Node*> allChildren = this->currentDir->getAllChildren();
    for (size_t i = 0; i < allChildren.size(); i++)
    {
        if (allChildren.at(i)->getName() == name)
        {
            if (!allChildren.at(i)->isFolder())
            {
                fileFound = true;
                Node *temp = allChildren.at(i);
                this->isEmpty[temp->getData()] = true;
                std::cout << "temp->getdata() = " << temp->getData() << std::endl;
                //std::cout << "FOUND : " << allChildren.at(i)->getName() << std::endl;
                currentDir->removeChildAt(i);
                delete temp;
            }
            else
            {
                std::cout << "Cannot remove '" << name << "': Is a directory." << std::endl;
            }
        }
    }
    return fileFound;
}
//Removes a folder if empty
bool FileSystem::removeFolder(string name)
{
    bool folderFound = false;
    vector<Node*> allChildren = this->currentDir->getAllChildren();
    for (size_t i = 0; i < allChildren.size(); i++)
    {
        if (allChildren.at(i)->getName() == name)
        {
            if (allChildren.at(i)->isFolder())
            {
                if(allChildren.at(i)->getNrOfChildren() == 0)
                {
                    folderFound = true;
                    Node *temp = allChildren.at(i);
                    currentDir->removeChildAt(i);
                    delete temp;
                }
            }
            else
            {
                std::cout << "Cannot remove '" << name << "': Not a directory." << std::endl;
            }
        }
    }
    return folderFound;
}
//Makes the current folder the node provided
void FileSystem::goToFolder(Node* path)
{
    if(path->isFolder())
    {
        currentDir = path;
    }
    else
    {
        std::cout << "Cannot go into '" << path->getName() << "': Not a directory." << std::endl;
    }
}
//Converts a stringstream to a vector of strings seperated by "/"
vector<string> FileSystem::readPath(stringstream &path)
{
	string segment;
	vector<string> segList;

	while(std::getline(path, segment, '/'))
	{
		segList.push_back(segment);
	}
	return segList;
}
//Returns the directory the path relates to
Node* FileSystem::getPath(string path)
{
    //Check if a path is added after command
    if (path.length() == 0)
    {
        return currentDir;
    }

    string segment;
	vector<string> segList;

    //Check if first char is root identifier
    if (path[0] == '/')
    {
        segList.push_back("/");
        path.erase(path.begin());
    }

    //Seperate string to find folder location
    stringstream paths(path);
    while(std::getline(paths, segment, '/'))
	  {
		    segList.push_back(segment);
    }

    Node* folderNode = currentDir;

    //If / is first then go to root
    int i = 0;
    if (segList.at(0) == "/")
    {
        folderNode = root;
        i++;
    }

    // Find the folder, if .. is found go to parent of current folder, if not found then return NULL
    for (size_t k = i; k < segList.size(); k++)
    {
		//Enter parent node
        if (segList.at(k) == "..")
        {
			if(folderNode->getParent() == NULL)
			{
				std::cout << "Parent folder does not exist." << std::endl;
				return NULL;
			}
            folderNode = folderNode->getParent();
        }
		//Enter child node
        else if (folderNode->getChild(segList.at(k)) != NULL && folderNode->getChild(segList.at(k))->isFolder())
        {
            folderNode = folderNode->getChild(segList.at(k));
        }
		//Node does not exist or is not a folder
        else
        {
            return NULL;
        }
    }
    return folderNode;
}
//Lists all directory contents
void FileSystem::ls(Node* folder)
{
    if (folder != NULL)
    {
        std::cout << "Listing directory contents" << std::endl;
		//Print all children
        std::vector<string> v = folder->getAllChildrenAsString();
        for (size_t i = 0; i < v.size(); i++)
        {
            std::cout << v.at(i) << std::endl;
        }
    }
    else
    {
        std::cout << "Folder not found." << std::endl;
    }
}
