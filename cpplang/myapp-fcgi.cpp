

#include <fcgi_stdio.h>
#include <stdlib.h>
#include <cstring>

#include "resodbutil.hpp"

#define MAX_VARS 30


#define OP(OP) strcmp(getenv("REQUEST_METHOD"),OP)==0
#define URI(URI) strcmp(getenv("SCRIPT_NAME"),URI)==0

void dump_env(void);

int main(void){

    int count = 0;
    mydb::ResoCoreQuery qry;

    while (FCGI_Accept() >= 0) {

        if ( URI("/api/parcel") ){
          if ( OP("GET") ) {
            printf("Content-type: text/plain\r\n\r\n"
                 "Request number %d was GET /api/parcel\n", ++count);
            qry.GetAll(stdout);
          }
          else {
            printf("Content-type: text/plain\r\n\r\n"
                 "Request number %d was NOT GET /api/parcel\n", ++count);
          }
        }
        else {
          printf("Content-type: text/plain\r\n\r\n"
               "Request number %d was NOT OP /api/parcel\n", ++count);
          }

        //dump_env();
    }
    return 0;
}



void dump_env(){
  char* vars[MAX_VARS] = {
//      "DOCUMENT_ROOT",
//      "GATEWAY_INTERFACE",
      "HTTP_ACCEPT",
      "HTTP_ACCEPT_ENCODING",
      "HTTP_ACCEPT_LANGUAGE",
      "HTTP_CACHE_CONTROL",
      "HTTP_CONNECTION",
      "HTTP_HOST",
      "HTTP_PRAGMA",
      "HTTP_RANGE",
      "HTTP_REFERER",
      "HTTP_TE",
      "HTTP_USER_AGENT",
      "HTTP_X_FORWARDED_FOR",
//      "PATH",
      "QUERY_STRING",
      "REMOTE_ADDR",
      "REMOTE_HOST",
      "REMOTE_PORT",
      "REQUEST_METHOD",
      "REQUEST_URI",
      "SCRIPT_FILENAME",
      "SCRIPT_NAME",
      "SERVER_ADDR",
      "SERVER_ADMIN",
      "SERVER_NAME",
      "SERVER_PORT",
      "SERVER_PROTOCOL",
      "SERVER_SIGNATURE",
      "SERVER_SOFTWARE"
  };
  int i;
  char *v;
  for (i = 0; i < MAX_VARS; ++i) {
      v = getenv(vars[i]);

      if (v == NULL)
          printf("%s: \n", vars[i]);
      else
          printf("%s: %s\n", vars[i], v);

  }
}
