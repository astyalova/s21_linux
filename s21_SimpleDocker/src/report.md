##### Возьми официальный докер-образ с **nginx** и выкачай его при помощи `docker pull`.
 ![alt text](./screen/1.png)<br>
##### Проверь наличие докер-образа через `docker images`.
 ![alt text](./screen/2.png)<br>
##### Запусти докер-образ через `docker run -d [image_id|repository]`.
 ![alt text](./screen/14.png)<br>
##### Проверь, что образ запустился через `docker ps`.
 ![alt text](./screen/13.png)<br>
##### Посмотри информацию о контейнере через `docker inspect [container_id|container_name]`.
 ![alt text](./screen/11.png)<br>
##### По выводу команды определи и помести в отчёт размер контейнера, список замапленных портов и ip контейнера.
 ![alt text](./screen/3.png)<br>
  ![alt text](./screen/16.png)<br>
   ![alt text](./screen/15.png)<br>
##### Останови докер образ через `docker stop [container_id|container_name]`.
 ![alt text](./screen/12.png)<br>
##### Проверь, что образ остановился через `docker ps`.
 ![alt text](./screen/10.png)<br>
##### Запусти докер с портами 80 и 443 в контейнере, замапленными на такие же порты на локальной машине, через команду *run*.
 ![alt text](./screen/7.png)<br>
##### Проверь, что в браузере по адресу *localhost:80* доступна стартовая страница **nginx**.
 ![alt text](./screen/5.png)<br>
##### Перезапусти докер контейнер через `docker restart [container_id|container_name]`.
 ![alt text](./screen/4.png)<br>
##### Проверь любым способом, что контейнер запустился.

## Part 2. Операции с контейнером

##### Прочитай конфигурационный файл *nginx.conf* внутри докер контейнера через команду *exec*.
![alt text](./screen/25.png)<br>
##### Создай на локальной машине файл *nginx.conf*.
##### Настрой в нем по пути */status* отдачу страницы статуса сервера **nginx**.
![alt text](./screen/17.png)<br>

##### Скопируй созданный файл *nginx.conf* внутрь докер-образа через команду `docker cp`.
![alt text](./screen/18.png)<br>
##### Перезапусти **nginx** внутри докер-образа через команду *exec*.
![alt text](./screen/19.png)<br>
##### Проверь, что по адресу *localhost:80/status* отдается страничка со статусом сервера **nginx**.
![alt text](./screen/20.png)<br>
##### Экспортируй контейнер в файл *container.tar* через команду *export*.
![alt text](./screen/21.png)<br>
##### Останови контейнер.
![alt text](./screen/22.png)<br>
##### Удали образ через `docker rmi [image_id|repository]`, не удаляя перед этим контейнеры.
![alt text](./screen/23.png)<br>
##### Удали остановленный контейнер.
![alt text](./screen/24.png)<br>
##### Импортируй контейнер обратно через команду *import*.
![alt text](./screen/26.png)<br>
##### Запусти импортированный контейнер.
![alt text](./screen/27.png)<br>
##### Проверь, что по адресу *localhost:80/status* отдается страничка со статусом сервера **nginx**.
![alt text](./screen/28.png)<br>

## Part 3. Мини веб-сервер

##### Напиши мини-сервер на **C** и **FastCgi**, который возвращает страничку с надписью `Hello World!`.

![alt text](./screen/29.png)<br>
##### Запусти написанный мини-сервер через *spawn-fcgi* на порту 8080.

![alt text](./screen/30.png)<br>
##### Напиши свой *nginx.conf*, который будет проксировать все запросы с 81 порта на *127.0.0.1:8080*.

![alt text](./screen/31.png)<br>
- Это файл конфигурации был написан в соотвествии с папками на моем компе, так как nginx был установлен через brew, а этот файл конфигураций уже исправлен в контейнере под то расположение папок.

![alt text](./screen/32.png)<br>
- Создала контейнер командой docker run -d -p 81:81 nginx, в которой докер ран создает и запускае  контейнер, флаг -d запускает контейнер в фоновом режиме, -p 81:81 связывает порт 81 на вашем хосте с портом 81 внутри контейнера.

- Скопировала файл сервера и конфигурационный в контейнер

![alt text](./screen/33.png)<br>
- Зашла в контейнер

![alt text](./screen/34.png)<br>
- Установила необходимые инструменты командой
apt update
apt install -y build-essential libfcgi-dev
apt install -y vim

- Скомпилировала server.c 

![alt text](./screen/35.png)<br>
- Запустила через spawn-fcgi

![alt text](./screen/36.png)<br>
- Перезапустила

![alt text](./screen/37.png)<br>
- Проверила, что в браузере по localhost:81 отдается написанная вами страничка

![alt text](./screen/38.png)<br>
![alt text](./screen/39.png)<br>

## Part 4. Свой докер
- Создала докерфайл и entrypoint

![alt text](./screen/40.png)<br>

![alt text](./screen/41.png)<br>

- Собрала написанный докер-образ через `docker build` при этом указав имя и тег.

![alt text](./screen/42.png)<br>

- Проверила через `docker images`, что все собралось корректно.

![alt text](./screen/43.png)<br>

- Запустила собранный докер-образ с маппингом 81 порта на 80 на локальной машине и маппингом папки *./nginx* внутрь контейнера по адресу, где лежат конфигурационные файлы **nginx**'а.

![alt text](./screen/44.png)<br>

- Проверила, что по localhost:80 доступна страничка написанного мини сервера.

![alt text](./screen/45.png)<br>

- Проверила, что теперь по *localhost:80/status* отдается страничка со статусом **nginx**

![alt text](./screen/46.png)<br>

## Part 5. **Dockle**

После написания образа никогда не будет лишним проверить его на безопасность.
- Устанавливаю докли командой

brew install dockle

- Командой 

dockle run -rm -v /var/run/docker.sock:/var/run/docker.sock goodwithtech/dockle new_server:1.0

- Сканирую образ из предыдущего задания

![alt text](./screen/47.png)<br>

- Исправила докер файл

![alt text](./screen/48.png)<br>

- Проверила

![alt text](./screen/49.png)<br>

## Part 6. Базовый **Docker Compose**

- Для начала необходимо устновить docker-compose, если он не устновился с docker. 

![image.png](images/50.png)

- Потом необходимо остановить существующие к контейнеры.

- Командой docker stop [id_container]

- Напишем конфигурационный файл docker-compose.yml

 ![image.png](images/51.png)

 - Пересобираем командой 'sudo docker compose build' и запускам 'docker compose up -d':

  ![image.png](images/52.png)

  ![image.png](images/53.png)

  - Контейнеры поднялись, проверяем в барузере ответ:

  ![image.png](images/54.png)
