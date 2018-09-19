#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <iostream>
#include <map>
#include <string>

using namespace std;

map<string, pair<string, void *>> functions;
int main()
{
    while (true)
    {
        string command;
        cin >> command;
        if (command == "end")
        {
            return 0;
        }
        else if (command == "load")
        {
            string libname;
            cin >> libname;
            void *handle = dlopen(libname.c_str(), RTLD_LAZY);
            if (!handle)
            {
                cout << "File not found!";
                continue;
            }
            else
            {
                char **(*infoFunction)();
                infoFunction = (char **(*)())dlsym(handle, "info");
                if (!infoFunction)
                {
                    continue;
                }
                else
                {
                    char **info = infoFunction();
                    char *currentWord;
                    for (int x = 0; info[x] != nullptr; x += 2)
                    {
                        string name = info[x];
                        string type = info[x + 1];
                        functions[name] = make_pair(type, handle);
                    }
                }
            }
        }
        else
        {
            if (functions.find(command) == functions.end())
            {
                cout << "Function not found!" << endl;
            }
            else
            {
                pair<string, void*> functionInfo = functions[command];
                string argumentString = functionInfo.first;
                void *handler = functionInfo.second;
                if (argumentString == "int")
                {
                    int arg;
                    cin >> arg;
                    void (*function)(int);
                    function = (void(*)(int))dlsym(handler, command.c_str());
                    function(arg);
                }
                else if (argumentString == "float")
                {
                    float arg;
                    cin >> arg;
                    void (*function)(float);
                    function = (void(*)(float))dlsym(handler, command.c_str());
                    function(arg);
                }
                else if (argumentString == "int[]")
                {
                    int n;
                    cin >> n;
                    int *tab = new int[n];
                    for (int x=0; x<n; x++)
                    {
                        cin >> tab[x];
                    }
                    void (*function)(int, int*);
                    function = (void(*)(int, int*))dlsym(handler, command.c_str());
                    function(n, tab);
                    delete[] tab;
                }
                else if (argumentString == "float[]")
                {
                    int n;
                    cin >> n;
                    float *tab = new float[n];
                    for (int x=0; x<n; x++)
                    {
                        cin >> tab[x];
                    }
                    void (*function)(int, float*);
                    function = (void(*)(int, float*))dlsym(handler, command.c_str());
                    function(n, tab);
                    delete[] tab;
                }
            }
        }

        // const char *funcname = argv[1];
        // int a = atoi(argv[2]);
        // int b = atoi(argv[3]);
        // void *handle = dlopen(" libpow . so ", RTLD_LAZY);
        // if (!handle)
        // {
        //     fprintf(stderr, " Failed to open the library !");
        //     abort();
        // }
        // int (*function)(int, int);
        // function = dlsym(handle, funcname);
        // if (!function)
        // {
        //     fprintf(stderr, " Failed to find function % s !", funcname);
        //     abort();
        // }
        // printf("% d \ n ", function(a, b));
        // dlclose(handle);
        // return 0;
    }
}
