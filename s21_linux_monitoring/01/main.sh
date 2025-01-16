#!/bin/bash

if [[ $1 =~ ^-?[0-9]+$ ]]
then
echo "Error, parameter is a number."
else
echo "Hello, $1!"
fi
