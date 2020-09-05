#! /iusr/bin/bash 

clear
bash clean.sh
cmake . && make && ./VULKAN_Tests/VULKAN_Tests 