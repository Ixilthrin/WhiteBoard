#include "ProjectManager.h"
#include "WhiteBoard.h"

#include <curl/curl.h>
#include <rapidjson/document.h>


#include <string.h>

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <iostream>

using namespace std;

string authServer("https://authserverdev.bluebeam.com/auth/token");
string publicApi("https://studioapi-dev.bluebeam.com/publicapi/v1/");

string authToken("");

string projectsUri("projects");


struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  mem->memory = (char*) realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}

static WhiteBoard *thisWhiteBoard = 0;

void getAuthToken()
{

    CURL *curl;
    CURLcode res;
 
    struct MemoryStruct chunk;
 
    chunk.memory = (char*) malloc(1); 
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curl, CURLOPT_URL, authServer.c_str());

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    curl_easy_setopt(curl, CURLOPT_POST, 1);

    string pword_field("grant_type=password&username=");
    pword_field += thisWhiteBoard->getUName();
    pword_field += "&password=";
    pword_field += thisWhiteBoard->getPWord();

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, pword_field.c_str());

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
    }
    else 
    {
        printf("%lu bytes retrieved\n", (long)chunk.size);

        string output(chunk.memory);
        rapidjson::Document d;
        cout << output << endl;
        d.Parse<0>(output.c_str());

        authToken = d["access_token"].GetString();
    }

    free(chunk.memory);
    curl_easy_cleanup(curl);
}

void getProjects()
{
 
    CURL *curl;
    CURLcode res;

    struct MemoryStruct chunk;
 
    chunk.memory = (char*) malloc(1); 
    chunk.size = 0; 
 
 
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        struct curl_slist *headerChunk = NULL;
        string header("authorization: bearer ");
        header += authToken;
        headerChunk = curl_slist_append(headerChunk, header.c_str());
        res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerChunk);
        curl_easy_setopt(curl, CURLOPT_URL, (publicApi + projectsUri).c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
        }
        else 
       {
 
            printf("%lu bytes retrieved\n", (long)chunk.size);

            string output(chunk.memory);
            rapidjson::Document d;
cout << output << endl;
            d.Parse<0>(output.c_str());

            const rapidjson::Value& projects = d["Projects"];

            for (rapidjson::SizeType i = 0; i < projects.Size(); i++) 
            {
                string projectOutput("");
                projectOutput += projects[i]["Name"].GetString();
                projectOutput += "    ";
                projectOutput += projects[i]["Id"].GetString();
                thisWhiteBoard->addString(projectOutput);
                cout << "Name: " << projects[i]["Name"].GetString() << "   Id: " << projects[i]["Id"].GetString() << endl;
            }
 
        }

        curl_slist_free_all(headerChunk);
        free(chunk.memory);
        curl_easy_cleanup(curl);
    }
}

void ProjectManager::fetchProjects(WhiteBoard *board)
{
    thisWhiteBoard = board;
    getAuthToken();
    getProjects();
}
