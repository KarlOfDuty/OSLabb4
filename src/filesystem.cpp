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
    root->createChild(new Node("hejsan"));
    root->createChild(new Node("hejsan2"));
    root->createChild(new Node("hejsan3"));
    root->createChild(new Node("hejsan4"));
    root->createChild(new Node("file", 10));
}

FileSystem::~FileSystem()
{

}
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
void FileSystem::createFolder(string name)
{
    Node *folder = new Node(name,-1,currentDir);
    currentDir->createChild(folder);
}
bool FileSystem::removeFile(string name)
{
    bool fileFound = false;
    int lastSlash = -1;
    for (size_t i = 0; i < name.length(); i++)
    {
        if(name[i] == '/')
        {
            lastSlash = i;
        }
    }
    std::string fileName = name;
    fileName.erase(0,lastSlash+1);
    Node* dir = getPath(name.erase(lastSlash+1));
    vector<Node*> allChildren = dir->getAllChildren();
    for (size_t i = 0; i < allChildren.size(); i++)
    {
        if (allChildren.at(i)->getName() == fileName)
        {
            if (!allChildren.at(i)->isFolder())
            {
                fileFound = true;
                Node *temp = allChildren.at(i);
                this->isEmpty[temp->getData()] = true;
                //std::cout << "temp->getdata() = " << temp->getData() << std::endl;
                currentDir->removeChildAt(i);
                delete temp;
            }
            else
            {
                std::cout << "Cannot remove '" << name << "': Is a directory." << std::endl;
                fileFound = true;
            }
        }
    }
    return fileFound;
}
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
void FileSystem::goToFolder(Node* path)
{
    currentDir = path;
    /*
	stringstream path(name);
	vector<string> pathParts = readPath(path);
	string currentFolder = "";
	Node* currentNode = this->currentDir;
	for(int i = 0; i < pathParts.size(); i++)
	{
		if (pathParts.at(i) == "..")
		{
			if (currentNode->getParent() != NULL)
			{
				currentNode = currentNode->getParent();
			}
		}
		else
		{
			//for(int i = )
			//if(currentNode->getAllChildren())
		}
	}
    */
}
/*
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
*/
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
    // Find the folder, if .. is found go to parrent of current folder, if not found then return NULL
    for (size_t k = i; k < segList.size(); k++)
    {
        if (segList.at(k) == "..")
        {
            folderNode = folderNode->getParent();
        }
        else if (folderNode->getChild(segList.at(k)) != NULL && folderNode->getChild(segList.at(k))->isFolder())
        {
            folderNode = folderNode->getChild(segList.at(k));
            //k = segList.size();
        }
        else
        {
            folderNode = NULL;
            k = segList.size();
        }
    }
    return folderNode;
}
/*
void FileSystem::listDir()
{
    std::vector<string> v = this->currentDir->getAllChildrenAsString();
    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << v.at(i) << std::endl;
    }
}
*/
void FileSystem::ls(Node* folder)
{
    if (folder != NULL)
    {
        std::cout << "Listing directory" << std::endl;

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
