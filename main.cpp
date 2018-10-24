#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

#define DATA_FOLDER "DataAnalysis"

int CreateFolder(char* pchPath, const char* pchName)
{
    if (NULL == pchPath || NULL == pchName) {
        return 0;
    }

    // Get work directory
    char *pchWorkPath;
    if ((pchWorkPath = getcwd(NULL, 0)) == NULL) {
        printf("Get current work path failed!\n");
        return 0;
    }

    // Get root directory
    int iCount = 0;
    for (int i = 0; i < strlen(pchWorkPath); ++i) {
        if ('/' == *(pchWorkPath + i)) {
            ++iCount;
        }

        if (3 == iCount) {
            *(pchPath + i) = *(pchWorkPath + i);
            break;
        }
        else {
            *(pchPath + i) = *(pchWorkPath + i);
        }
    }
    strcat(pchPath, DATA_FOLDER);

    // Judging the folder (DATA_FOLDER) is existed or not
    struct stat file_stat;
    int iStat = stat(pchPath, &file_stat);
    if (iStat < 0) {
        int iRet0 = mkdir(pchPath, S_IRWXU);
        if (iRet0 < 0) {
            return 0;
        }
    }

    strcat(pchPath, "/");
    strcat(pchPath, pchName);

    // Get system time and create new folder
    time_t sSystemTime = time(0);
    char pchTime[32] = "";
    strftime(pchTime, sizeof(pchTime), "-%Y%m%d-%H:%M", localtime(&sSystemTime));
    strcat(pchPath, pchTime);
    int iRet1 = mkdir(pchPath, S_IRWXU);
    if (iRet1 < 0) {
        return 0;
    }

    strcat(pchPath, "/");

    return 1;
}

int main()
{
    char pchFilePath[256] = "";
    const char pchFileName[100] = "CarData";

    int iRet = CreateFolder(pchFilePath, pchFileName);
    if (1 != iRet) {
        printf("Create new data folder failed!\n");
    }

    return 0;
}
