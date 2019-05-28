#!/bin/bash

project_path=$(pwd)
# echo $project_path
# build cpp app
echo "Building app..."
if [ -d "build" ]; then
	echo "Build directory exists"
else
	mkdir build
fi
cd build
cmake ..
make

#build flask app
cd ..
cd web
if [ -d "venv" ]; then
	echo "Virtual enviroment exists"
else
	virtualenv -p python3 venv
	source venv/bin/activate
	pip install -r requirements.txt
	export FLASK_APP=app.py
fi

echo "Build sucessfully"
