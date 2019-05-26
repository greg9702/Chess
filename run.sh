#!/bin/bash

source web/venv/bin/activate
echo "Running application"
echo "Open your browser 127.0.0.1:5000 to play chess"
{
	killall chess
	./build/chess &
	cd web
	flask run
}
# } &> /dev/null
