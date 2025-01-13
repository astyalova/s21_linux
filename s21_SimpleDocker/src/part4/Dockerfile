FROM nginx
WORKDIR /home/
COPY ./nginx.conf ./
COPY ./server.c ./
COPY ./run.sh ./
RUN apt-get update && apt-get install -y gcc spawn-fcgi libfcgi-dev
ENTRYPOINT ["sh", "-/run.sh"]