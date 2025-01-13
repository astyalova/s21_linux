### Part 1. Настройка **gitlab-runner**

- подняла вирутальную машину

![alt text](screen/1.png)

![alt text](screen/2.png)

- Дальше я скачала gitlab-runner
``curl -L "https://packages.gitlab.com/install/repositories/runner/gitlab-runner/script.deb.sh" | sudo bash
``

![alt text](screen/3.png)

- Следующий шаг устнановить gitlab runner:
``sudo apt install gitlab-runner``

![alt text](screen/4.png)

- Запустила gitlab-runner 
``sudo gitlab-runner start ``

- Зарегистрировалсь 
``sudo gitlab-runner register ``

![alt text](screen/5.png)

### Part 2. Сборка

- Перенесла дирректории cat и grep из проекта C2_SimpleBashUtils

- Создала файл gitlab-ci.yml в корне дирректории 

![alt text](screen/6.png)
 
 - Запустила pipline:

 ![alt text](screen/7.png)

 ### Part 3. Тест кодстайла

 - Напиши этап для CI, который запускает скрипт кодстайла (clang-format).

  ![alt text](screen/8.png)

- Перед этим установливаю на ВМ clang-format:
``` sudo apt-get install clang-format ```

- В данной ситуации тест на кодстайл прошел:


![alt text](screen/9.png)

Вывод утилиты clang-format.

![alt text](screen/10.png)


### Part 4. Интеграционные тесты

- Напиши этап для CI, который запускает твои интеграционные тесты из того же проекта.

- Написала этап

![alt text](screen/11.png)


- Запускаю этап

![alt text](screen/12.png)

- Вывод пайплайна

- у кэта тесты проходят полностью 

![alt text](screen/13.png)

- у грепа не все тесты

![alt text](screen/14.png)



### Part 5. Этап деплоя

**== Задание ==**

- Подняла вторую виртуальную машину *Ubuntu Server 22.04 LTS*.

![alt text](screen/15.png)

Написать этап для **CD**, который «разворачивает» проект на другой виртуальной машине.

- Изменяю файл /etc/netplan/50-cloud-init.yaml на обеих машинах:

![alt text](screen/16.png)

-  Перенастраиваю сетевые адаптеры обеих машин следующим образом:

![alt text](screen/18.png)

- Проверяю соедение

![alt text](screen/17.png)

- Скачиваю на вторую виртуальную машину, иначе ключ не перекинется
``` sudo apt-get install ssh ```
- Захожу на первой машине под пользователя gitlab-runner
``` sudo su gitlab-runner ```
- Создаю ключ (ssh-keygen) и копируем его на вторую машину
``` ssh-copy-id lyraa@10.10.0.2 ``` 

![alt text](screen/19.png)

- Теперь могу подключаться ко второй машине через ssh без необходимости ввода пароля:

![alt text](screen/20.png)

- На второй машине дам права для папки /usr/local/bin/ командой 
``` sudo chmod -R 777 /usr/local/bin ``` 

![alt text](screen/21.png)

- Написанный скрипт

![alt text](screen/22.png)

- В файле _gitlab-ci.yml_ добавила этап запуска написанного скрипта.

![alt text](screen/23.png)

- Пайплайн:

![alt text](screen/24.png)

- Получила готовые к работе приложения из проекта *C2_SimpleBashUtils* (s21_cat и s21_grep) на второй виртуальной машине:

![alt text](screen/25.png)

Сохранила дампы образов виртуальных машин:

![alt text](screen/26.png)

### Part 6. Дополнительно. Уведомления

- Напиcала @botfather, чтобы создать бота и получить его токен:

![alt text](screen/27.png)

- Добавляю в скрипт:

![alt text](screen/27.png)

- Пишу своему боту

![alt text](screen/30.png)

- Мне нужно получить id чата. Для этого в адресной строке браузера забиваю https://api.telegram.org/bot<тут_твой_токен>/getUpdates, он показывает последние изменения в чате, там и достаю айди чата

![alt text](screen/29.png)

- Дальше скрипт пишу

![alt text](screen/32.png)

- Бот показывает уведомления

![alt text](screen/31.png)

