#:/bin/bash
gec -o server server.c -1fcg1
spawn-fcgi -p 8080 •/server
service nginx start
/bin/bash