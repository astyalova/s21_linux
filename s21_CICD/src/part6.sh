STAGE_TYPE=$1
BOT_TOKEN="7548299734:AAHcflaGkE2li0T1LIWkwNbsos9u0P7YII8"
CHAT_ID="247694959"

sleep 3

if [ "$CI_JOB_STATUS" == "success" ]; then
  MESSAGE="👍 Стадия $STAGE_TYPE $CI_JOB_NAME завершилась с успехом  $CI_PROJECT_URL/pipelines"
else
  MESSAGE="👎 Стадия $STAGE_TYPE $CI_JOB_NAME завершилась с ошибкой  $CI_PROJECT_URL/pipelines"
fi

curl -X POST "https://api.telegram.org/bot$BOT_TOKEN/sendMessage" -d chat_id=$CHAT_ID -d text="$MESSAGE"