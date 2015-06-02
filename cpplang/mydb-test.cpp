//mydb copyright 2015 joe wehrli

#include <initializer_list>
#undef _GLIBCXX_HAVE_GETS

//#include <stdio.h>
#include <cstdio>
//#include <stdlib.h>
#include <string>
#include "mydb.hpp"

int main() 
{
    mydb::Context con;

    con.Open();

    printf("Opened mydb ver %d on host %s\n",1,"mls1");

    /*
    char data[3];
    data[0]='a';
    data[1]='b';
    data[2]='c';
    */
    int i = 69;
 
    std::string strKey="69";
    std::string strData = "abc";
    const char* key = strKey.c_str();
    const char* data = strData.c_str();
    //con.Write(sizeof(int), &i, sizeof(data), data);
    con.Write(strKey.length(), (void*)key, strData.length(), (void*)data);

    char *data2;
    //con.GetCopy(sizeof(int), &i, (void**) &data2);
    con.GetCopy(strKey.length(), (void*)key, (void**) &data2);

    printf("KeyLen%d StringLen %d = %s\n",strKey.length(), (char*)data2);

    delete data2;


    return 0;
}
