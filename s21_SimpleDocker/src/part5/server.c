#include "fcgi_stdio.h"
#include <stdlib.h>


int main(void)
{
    while (FCGI_Accept() >= 0)
    {
        printf("Content-type: text/html\r\nStatus: 200 OK\r\n\r\nHello World!");
    }

    return 0;
}

//docker run -it -p 80:01 -v /Users/anastasia/Desktop/проекты/DO5_SimpleDocker-1/src/part4/nginx.conf:/opt/homebrew/etc/nginx/nginx.conf -d new_server: 1.0 bash