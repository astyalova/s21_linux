#!/bin/bash
chmod +x info.sh
bash info.sh
echo ""
echo "Do you want to save? y/n"
read answer
if [ $answer == "y" ] || [ $answer == "Y" ]; then
    bash write_to_file.sh
else
    exit 
fi