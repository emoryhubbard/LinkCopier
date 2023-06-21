// Sets a compiler option so no console window appears
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
/*Clipboard includes*/
#include <conio.h>
#include <stdio.h>
#include <cstdlib>
#include <Windows.h>
#include <winuser.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <complex>
#include <string>
/*File system includes, also include <string> if needed.
Also be sure to set your project to C++ 17:
right-click project -> properties -> C++ 17*/
#include <filesystem>
#include <iostream>
#include <sys/stat.h>
/*String includes*/
#include <regex>

using namespace std;
using namespace filesystem;

string notesDir = "C:\\Users\\edhth\\OneDrive\\Documents\\WebFundamentals\\NotesImages";
string downloadsDir = "C:\\Users\\edhth\\Downloads";

string getLastModified();
string getNewPath(string);
string getLink(string);
void setClipboard(string);

int main()
{
    string oldPath = getLastModified();
    string newPath = getNewPath(oldPath);
    rename(oldPath, newPath);
    setClipboard(getLink(newPath));
}
string getNewPath(string oldPath) {
    string newPath = oldPath.replace(oldPath.find(downloadsDir), size(downloadsDir), notesDir);
    return newPath;
}
string getLink(string newPath) {
    string link = regex_replace(newPath, regex("\\\\"), "/");
    link = regex_replace(link, regex("\\s"), "%20");
    link.insert(0, "file:///");
    return link;
}
void setClipboard(string text) {
    HANDLE glob = GlobalAlloc(GMEM_FIXED, (text.length() + 1) * sizeof(char));
    memcpy(glob, text.c_str(), text.size());

    HWND hWnd = GetDesktopWindow();
    OpenClipboard(hWnd);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, glob);
    CloseClipboard();
}
string getLastModified()
{
    string lastModified = "";

    // This structure would distinguish a file from a
    // directory
    struct stat sb;

    // Looping until all the items of the directory are
    // exhausted
    file_time_type lastModifiedTime;
    bool timeSet = false;
    for (const auto& entry : directory_iterator(downloadsDir)) {

        // Converting the path to const char * in the
        // subsequent lines
        path outfilename = entry.path();
        string outfilename_str = outfilename.string();
        const char* filePath = outfilename_str.c_str();

        // Testing whether the path points to a
        // non-directory or not. If it does, then
        // testing if was more recently modified.
        if (stat(filePath, &sb) == 0 && !(sb.st_mode & S_IFDIR)
            && timeSet == false) {
            lastModifiedTime = last_write_time(filePath);
            lastModified = filePath;
            timeSet = true;
        }
        if (stat(filePath, &sb) == 0 && !(sb.st_mode & S_IFDIR)
            && timeSet == true && last_write_time(filePath) > lastModifiedTime) {
            lastModifiedTime = last_write_time(filePath);
            lastModified = filePath;
        }
    }
    return lastModified;
}
