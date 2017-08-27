#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "memblockdevice.h"
#include "node.h"
#include <sstream>
#include <vector>
#include <stack>
#include <fstream>

class FileSystem
{
private:
	MemBlockDevice memBlockDevice;
    Node *root;
    Node *currentDir;
    // Here you can add your own data structures
public:
    FileSystem();
    ~FileSystem();

    /* These commands needs to implemented
     *
     * However, you are free to change the parameterlist and specify your own returntype for each function below.
     */

    /* This function creates a file in the filesystem */
    bool createFile(string name, string data, Node* path = NULL);

	int createFileData(std::string data);

    /* Creates a folder in the filesystem */
    void createFolder(string name);

    /* Removes a file in the filesystem */
    void removeFile(string path);

    /* Removes a folder in the filesystem */
    //bool removeFolder(string name);

    /* Function will move the current location to a specified location in the filesystem */
    void goToFolder(Node* path);

    /* Add your own member-functions if needed */
	void format();
	void createImage(std::string realFile);
	void writeDir(Node* currentNode, ofstream &filestream);
	void loadImage(std::string realFile);
	Node* readDir(vector<string> *strings, Node* parent = NULL);
	void printData(std::string path);
    Node* getPath(string path);
	string getAbsolutePath();
	void copy(Node* originalNode, Node* destinationDir);
    void ls(Node* folder);
};
#endif
