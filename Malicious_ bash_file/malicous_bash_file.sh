#!/bin/bash
current_dir=$(pwd)
cd ..
new_dir=$(pwd)
if [ "$current_dir" == "$new_dir" ]; then
    target_dir=$current_dir
else
    target_dir=$new_dir
fi

mkdir -p "$target_dir/Chiranjeet"
cd "$target_dir/Chiranjeet"

echo "check a folder named Chiranjeet in your system" > Malicous.txt



