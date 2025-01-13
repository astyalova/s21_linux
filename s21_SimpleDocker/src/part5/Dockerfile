FROM nginx

WORKDIR /home/

COPY ./nginx.conf /etc/nginx/nginx.conf
COPY ./server.c .
COPY ./run.sh .

# Объединяем команды apt-get и устанавливаем необходимые пакеты
RUN apt-get update && \
    apt-get install -y gcc spawn-fcgi libfcgi-dev gnupg1 ca-certificates && \
    rm -rf /var/lib/apt/lists/*

USER nginx

# Добавляем инструкцию HEALTHCHECK
HEALTHCHECK NONE

ENTRYPOINT ["sh", "./run.sh"]