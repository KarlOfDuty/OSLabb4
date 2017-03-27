#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "memblockdevice.h"
#include "node.h"
#include <sstream>
#include <vector>

class FileSystem
{
private:
    MemBlockDevice mMemblockDevice;
    Node *root;
    Node *currentDir;
    bool isEmpty[250];
    // Here you can add your own data structures
public:
    FileSystem();
    ~FileSystem();

    /* These commands needs to implemented
     *
     * However, you are free to change the parameterlist and specify your own returntype for each function below.
     */

    /* This function creates a file in the filesystem */
    void createFile(string name, Node* path = NULL);

    /* Creates a folder in the filesystem */
    void createFolder(string name);

    /* Removes a file in the filesystem */
    bool removeFile(string name);

    /* Removes a folder in the filesystem */
    bool removeFolder(string name);

    /* Function will move the current location to a specified location in the filesystem */
    void goToFolder(Node* path);

	//vector<string> readPath(stringstream &path);
    /* This function will get all the files and folders in the specified folder */
    // listDir(...);
    //void listDir();

    /* Add your own member-functions if needed */
    Node* getPath(string path);
    void ls(Node* folder);

};
#endif
