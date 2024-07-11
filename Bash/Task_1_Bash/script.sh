#!/bin/bash


DIR=$1


if [ -d "$DIR" ]; then
	touch "$DIR/file.jpg" "$DIR/file.png" "$DIR/file.gif" "$DIR/file.txt" "$DIR/file.doc" "$DIR/file.pdf"
	touch "$DIR/file" "$DIR/file.xy" "$DIR/file.gh"
	mkdir "$DIR/images"
	mkdir "$DIR/documents"
	mkdir "$DIR/others"
	echo "Files Created Suuccessfully"
else
	mkdir "$DIR"
fi

for file in "$DIR"/*; do
	if [ -f "$file" ]; then
		ext="${file##*.}"
		case $ext in
			jpg|png|gif)
				mv "$file" "$DIR/images/"
				;;
			txt|doc|pdf)
				mv "$file" "$DIR/documents/"
				;;
			*)
				mv "$file" "$DIR/others/"
				;;
		esac
	fi
done
			
