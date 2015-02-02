#!/bin/bash

while read line   
do   
    qrcode "$line" "$line".png
done < ids  
