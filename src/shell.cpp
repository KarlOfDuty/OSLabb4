#include <iostream>
#include <sstream>
#include <string>
#include "filesystem.h"

const int MAXCOMMANDS = 8;
const int NUMAVAILABLECOMMANDS = 15;

std::string availableCommands[NUMAVAILABLECOMMANDS] = {
    "quit","format","ls","create","cat","createImage","restoreImage",
    "rm","cp","append","mv","mkdir","cd","pwd","help"
};

/* Takes usercommand from input and returns number of commands, commands are stored in strArr[] */
int parseCommandString(const std::string &userCommand, std::string strArr[]);
int findCommand(std::string &command);
std::string help();

int main(void) {

	std::string userCommand, commandArr[MAXCOMMANDS];
	std::string user = "user@DV1492";    // Change this if you want another user to be displayed
	std::string currentDir = "/";    // current directory, used for output
    FileSystem filesystem;
    bool bRun = true;

    do {
        std::cout << user << ":" << currentDir << "$ ";
        getline(std::cin, userCommand);

        int nrOfCommands = parseCommandString(userCommand, commandArr);
        if (nrOfCommands > 0) {

            int cIndex = findCommand(commandArr[0]);
            switch(cIndex) {

            case 0: // quit
                bRun = false;
                std::cout << "Exiting\n";
                break;
            case 1: // format
                // Call fileSystem.format()
                break;
            case 2: // ls
            {
                // Call filesystem.ls()
                userCommand = userCommand.erase(0,3);
                filesystem.ls(filesystem.getPath(userCommand));
                break;
            }
            case 3: // create
            {
                userCommand = userCommand.erase(0,7);
                string fileName = userCommand;
                int lastSlash = -1;
                for (size_t i = 0; i < fileName.length(); i++)
                {
                    if (fileName[i] == '/')
                    {
                        lastSlash = i;
                    }
                }
                if (fileName.length() > 0)
                {
                    if (lastSlash != -1)
                    {
                        fileName.erase(0,lastSlash+1);
                        userCommand.erase(lastSlash+1);
                        filesystem.createFile(fileName,filesystem.getPath(userCommand));
                    }
                    else
                    {
                        filesystem.createFile(fileName);
                    }
                }
                else
                {
                    std::cout << "Must specify file name." << std::endl;
                }
                break;
            }
                break;
            case 4: // cat
                break;
            case 5: // createImage
                break;
            case 6: // restoreImage
                break;
            case 7: // rm
            {
                std::string fileName = userCommand;
                fileName.erase(0,3);
                if (!filesystem.removeFile(fileName))
                {
                    std::cout << "rm: " << fileName << ": Could not find file." << std::endl;
                }
            }
                break;
            case 8: // cp
                break;
            case 9: // append
                break;
            case 10: // mv
                break;
            case 11: // mkdir
            {
                std::string folderName = userCommand;
                folderName.erase(0,6);
                filesystem.createFolder(folderName);
                break;
            }
            case 12: // cd
            {
                userCommand = userCommand.erase(0,3);
                if (userCommand.length() > 0)
                {
                    if (filesystem.getPath(userCommand) != NULL)
                    {
                        filesystem.goToFolder(filesystem.getPath(userCommand));
                    }
                    else
                    {
                        std::cout << "Folder not found." << std::endl;
                    }
                }
                else
                {
                    std::cout << "No path specified." << std::endl;
                }
                break;
            }
                break;
            case 13: // pwd
                break;
            case 14: // help
                std::cout << help() << std::endl;
                break;
            default:
                std::cout << "Unknown command: " << commandArr[0] << std::endl;
            }
        }
    } while (bRun == true);

    return 0;
}

int parseCommandString(const std::string &userCommand, std::string strArr[]) {
    std::stringstream ssin(userCommand);
    int counter = 0;
    while (ssin.good() && counter < MAXCOMMANDS) {
        ssin >> strArr[counter];
        counter++;
    }
    if (strArr[0] == "") {
        counter = 0;
    }
    return counter;
}
int findCommand(std::string &command) {
    int index = -1;
    for (int i = 0; i < NUMAVAILABLECOMMANDS && index == -1; ++i) {
        if (command == availableCommands[i]) {
            index = i;
        }
    }
    return index;
}

std::string help() {
    std::string helpStr;
    helpStr += "OSD Disk Tool .oO Help Screen Oo.\n";
    helpStr += "-----------------------------------------------------------------------------------\n" ;
    helpStr += "* quit:                             Quit OSD Disk Tool\n";
    helpStr += "* format;                           Formats disk\n";
    helpStr += "* ls     <path>:                    Lists contents of <path>.\n";
    helpStr += "* create <path>:                    Creates a file and stores contents in <path>\n";
    helpStr += "* cat    <path>:                    Dumps contents of <file>.\n";
    helpStr += "* createImage  <real-file>:         Saves disk to <real-file>\n";
    helpStr += "* restoreImage <real-file>:         Reads <real-file> onto disk\n";
    helpStr += "* rm     <file>:                    Removes <file>\n";
    helpStr += "* cp     <source> <destination>:    Copy <source> to <destination>\n";
    helpStr += "* append <source> <destination>:    Appends contents of <source> to <destination>\n";
    helpStr += "* mv     <old-file> <new-file>:     Renames <old-file> to <new-file>\n";
    helpStr += "* mkdir  <directory>:               Creates a new directory called <directory>\n";
    helpStr += "* cd     <directory>:               Changes current working directory to <directory>\n";
    helpStr += "* pwd:                              Get current working directory\n";
    helpStr += "* help:                             Prints this help screen\n";
    return helpStr;
}
