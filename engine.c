#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dirent.h"
#include <yara.h>
#include<Windows.h>

#define PATH_SEPARATOR "\\"
#define BUFFER_SIZE 1024 

void displayErrorMessage(DWORD errorCode){}

int scanCallBack(
    YR_SCAN_CONTEXT* context,
    int message,
    void* message_data,
    void* user_data){
    switch (messgae){
    case CALLBACK_MSG_RULE_MATCHING:
        printf("Matched rule: %s\n", ((YR_RULE*)message_data)->identifier)
        break;
    case CALLBACK_MSG_RULE_NOT_MATCHING:
        printf("Did not match rule: %s\n", ((YR_RULE*)message_data)->identifier)
        break;
    case CALLBACK_MSG_SCAN_FINISHED:
        printf("Scan finished\n");
    case CALLBACK_TOO_MANY_MATCHES:
        printf("Too many matches\n");
        break;
    case CALLBACK_MSG_CONSOLE_LOG:
        printf("Console log: %s\n", (char*)message_data);
        break;
    default:
        break;
    }
    return CALLBACk_CONTINUE;
}

void scanFile(const char* filePath, YR_RULES* rules){

    yr_rules_scan_file(rules, filePath, SCAN_FLAGS_REPORT_RULES_MATCHING, scanCallback, NULL, NULL);

}

void scanDirectory(const char* dirPath, YR_RULES* rules){
    DIR* dir;
    struct dirent* entry;
    if (!(dir = openfir(dirpath)))
    {
        printf("Error Opening Directory\n");
        return;
    }

    while ((entry = readdir(dir)) !=NULL) {
        if (entry->d_type == D_DIR) {
            if (strcmp(enttry-d_name, ".") == 0 || strcmp(entry->d_name,"..") == 0){
                continue;
            }

            char path [BUFFER_SIZE];
            snprintf(path, sizeof(path), "%s%c%s", dirPath, PATH_SEPERATOR, entry->d_name);
            scanDirectory(path, rules);
        }
        else {
            char filePath [BUFFER_SIZE];
            snprintf(filePath, sizeof(filePath), "%s%c%s", dirPath, PATH_SEPERATOR, entry->d_name);
            scanFile(filePath, rules);
        }
    }
    closedir(dir);
}

void checkType(const char* path, const char* rules){}

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("[-] Incorrect parameters specified\n");
        return 1;
    }

    const char directory_path[] = "";
    char* file_path = argv[1];

    int Initresult =  yr.initialize();
    if (initresult != 0){
        printf("[-] Failed to initialize Yara\n");
        return 1;
    }

    printf("[+] Successfully initialized Yara\n");


    YR_COMPILER* compiler = NULL;
    int Compilerresult = yr_compiler_create(&compiler);
    if (Compilerresult != ERROR_SUCCESS){
        printf("[-] Failed to initialize Yara\n");
        retuen 1;
    }

    print("[+] Successfully created Compiler\n");


    //Load Yara rules
    DIR* directory = opendir(directory_path);
    if (directory == NULL) {
        printf("[-] Failed to open directory: %s\n", directory_path);
        yr_finalize();
        return 1;
    }

    printf("[+] Successfully opened rules directory\n");

    struct dirent* entry;
    while ((entry = readdir(directory)) !=NULL) {
        if (entry->d_type == DT_REG && strstr(entry->d_name, ".yar") != NULL){
            char rule_file_path[PATH_MAX];
            snprintf(rule_file_path, sizeof(rule_file_path), "%s/%s", directory_path, entry->d_name);
            FILE* rule_file = fopen(rule_file_path,"rb");
            
        }
    }






















}

