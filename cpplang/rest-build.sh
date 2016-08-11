
#/usr/bin/clang-3.5 -g -std=c++14 -I/home/joe/appsrv/cpplang -o mydb-test mydb-test.cpp mydb.cpp -llmdb -lstdc++

#/usr/bin/clang-3.5 -g -std=c++14 -I/home/joe/appsrv/cpplang -o myapp.fcgi myapp-fcgi.cpp mydb.cpp -llmdb -lstdc++ -lfcgi

#/usr/bin/clang-3.5 -g -std=c++14 -I/home/joe/appsrv/cpplang -o resodb-test resodb-test.cpp resodbutil.cpp mydb.cpp /home/joe/microjson/microjson-1.3/mjson.o -llmdb -lstdc++ -lfcgi
#/usr/bin/clang-3.5 -g -std=c++14 -I/home/joe/appsrv/cpplang -o myapp.fcgi myapp-fcgi.cpp resodbutil.cpp mydb.cpp /home/joe/microjson/microjson-1.3/mjson.o -llmdb -lstdc++ -lfcgi

/usr/bin/g++ -g -std=c++11 -I/home/joe/appsrv/cpplang -o resodb-test resodb-test.cpp resodbutil.cpp mydb.cpp -llmdb -lstdc++ -lfcgi
/usr/bin/g++ -g -std=c++11 -I/home/joe/appsrv/cpplang -o myapp.fcgi myapp-fcgi.cpp resodbutil.cpp mydb.cpp -llmdb -lstdc++ -lfcgi
