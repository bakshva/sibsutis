#!/bin/bash

read -rsn5 -p "Нажмите кнопку: " key
echo -n "$key" | hexdump -C