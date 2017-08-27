#include "filesystem.h"
#include <sstream>
FileSystem::FileSystem()
{
	MemBlockDevice memBlockDevice = MemBlockDevice();
    root = new Node();
    currentDir = root;
    // Node *temp = new Node("folder1",-1,root);
    // temp->createChild(new Node("folder2",-1,temp));
    // root->createChild(temp);
    // root->createChild(new Node("hejsan",-1,root));
    // root->createChild(new Node("hejsan2",-1,root));
    // root->createChild(new Node("hejsan3",-1,root));
    // root->createChild(new Node("hejsan4",-1,root));
    // root->createChild(new Node("file", 10, root));
}

FileSystem::~FileSystem()
{
	delete root;
}
//Creates a new file
bool FileSystem::createFile(string name, string data, Node* path)
{
	int dataLocation = createFileData(data);
	if(dataLocation != -1)
	{
		if (path != NULL)
	    {
	        Node *file = new Node(name,dataLocation,currentDir);
	        path->createChild(file);
			return true;
	    }
	    else
	    {
	        Node *file = new Node(name,dataLocation,currentDir);
	        currentDir->createChild(file);
			return true;
	    }
	}
	return false;
}
int FileSystem::createFileData(std::string data)
{
	if(memBlockDevice.spaceLeft() > 0)
	{
		int dataLocation = memBlockDevice.getEmptyBlockIndex();
		if(data.length() < (uint)memBlockDevice[dataLocation].size())
		{
			char* cStr = new char[memBlockDevice[dataLocation].size()]{0};
			for(uint i = 0; i < data.length(); i++)
			{
				cStr[i] = data[i];
			}
			memBlockDevice.writeBlock(dataLocation,cStr);
			delete[] cStr;
		}
		else if(data.length() > (uint)memBlockDevice[dataLocation].size())
		{
			data.erase(memBlockDevice[dataLocation].size(), data.length());
			memBlockDevice.writeBlock(dataLocation,data.c_str());
		}
		else
		{
			memBlockDevice.writeBlock(dataLocation,data.c_str());
		}
		return dataLocation;
	}
	return -1;
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
                std::cout << "temp->getdata() = " << temp->getDataLocation() << std::endl;
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
// vector<string> FileSystem::readPath(stringstream &path)
// {
// 	string segment;
// 	vector<string> segList;
//
// 	while(std::getline(path, segment, '/'))
// 	{
// 		segList.push_back(segment);
// 	}
// 	return segList;
// }
void FileSystem::format()
{
	delete root;
	root = new Node();
	memBlockDevice.reset();
}
void FileSystem::createImage(std::string realFile)
{
	ofstream filestream;
	filestream.open(realFile);
	writeDir(root, filestream);
	filestream.close();
}
//Recursive part of createImage function
void FileSystem::writeDir(Node* currentNode, ofstream &filestream)
{
	string type = "";
	string name = "";
	string children = "";
	string fileContents = "";

	name = currentNode->getName();
	children = std::to_string(currentNode->getNrOfChildren());
	if(currentNode->isFolder())
	{
		type = "folder";
		filestream << type << " " << name << " " << children << endl;
	}
	else
	{
		type = "file";
		int dataLocation = currentNode->getDataLocation();
		fileContents = memBlockDevice.readBlock(dataLocation).toString();
		filestream << type << " " << name << " " << children << " " << fileContents << endl;
	}
	for(int i = 0; i < currentNode->getNrOfChildren(); i++)
	{
		writeDir(currentNode->getChildAt(i), filestream);
	}

}
//Load an image of the filesystem
void FileSystem::loadImage(std::string realFile)
{
	format();
	vector<string> *strings = new vector<string>();
	string str = " ";
	ifstream fileStream = ifstream();

	//Read each word from the file into a vector
	fileStream.open(realFile);
	while(fileStream >> str)
	{
		strings->push_back(str);
	}
	fileStream.close();

	if(strings->size() > 0)
	{
		delete root;
		root = readDir(strings);
	}
	else
	{
		cout << "Image file not found or empty." << endl;
	}

	delete strings;
}
Node* FileSystem::readDir(vector<string>* strings, Node* parent)
{
	Node* thisNode;
	string type = "";
	string name = "";
	string children = "";
	string fileContents = "";

	type = strings->at(0);
	strings->erase(strings->begin());
	name = strings->at(0);
	strings->erase(strings->begin());
	children = strings->at(0);
	strings->erase(strings->begin());
	if(type == "folder")
	{
		//If this node is a folder continue reading it's children recursively
		thisNode = new Node(name,-1,parent);
		for(int i = 0; i < std::stoi(children); i++)
		{
			thisNode->createChild(readDir(strings,thisNode));
		}
	}
	else
	{
		//Write the file's data to the filesystem
		fileContents = strings->at(0);
		strings->erase(strings->begin());
		int dataLocation = createFileData(fileContents);
		thisNode = new Node(name,dataLocation,parent);
	}
	return thisNode;
}
void FileSystem::printData(std::string path)
{
	Node* node = getPath(path);
	if(node != NULL)
	{
		int dataLocation = getPath(path)->getDataLocation();
		if(dataLocation >= 0)
		{
			std::string data = memBlockDevice.readBlock(dataLocation).toString();
			std::cout << "'" << data << "'" << std::endl;
		}
		else
		{
			std::cout << "Cannot print file contents: Target is a directory." << std::endl;
		}
	}
	else
	{
		std::cout << "File not found." << std::endl;
	}
}
//Returns the node the path relates to
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

    Node* currentNode = currentDir;

    //If / is first then go to root
    int i = 0;
    if (segList.at(0) == "/")
    {
        currentNode = root;
        i++;
    }

    // Find the folder, if .. is found go to parent of current folder, if not found then return NULL
    for (size_t k = i; k < segList.size(); k++)
    {
		//Enter parent node
        if (segList.at(k) == "..")
        {
			if(currentNode->getParent() == NULL)
			{
				std::cout << "Parent folder does not exist." << std::endl;
				return NULL;
			}
            currentNode = currentNode->getParent();
        }
		//Enter child node
        else if (currentNode->getChild(segList.at(k)) != NULL)
        {
            currentNode = currentNode->getChild(segList.at(k));
        }
		//Node does not exist
        else
        {
            return NULL;
        }
    }
    return currentNode;
}
string FileSystem::getAbsolutePath()
{
	Node* thisNode = currentDir;
	std::stack<std::string> directories;
	//Get the names of all parent folders
	while(thisNode->getParent() != NULL)
	{
		directories.push(thisNode->getName());
		thisNode = thisNode->getParent();
	}

	stringstream ss;
	//If we are located in the root folder, return it's name
	if(directories.empty())
	{
		return thisNode->getName();
	}
	//Put the names together with slashes between in reverse order
	while(!directories.empty())
	{
		ss << "/" << directories.top();
		directories.pop();
	}
	return ss.str();
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
