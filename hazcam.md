The following are crude notes on setup for Hazcam video streaming on a rover. Assumes you have a regular USB camera, not a Raspberry PI camera.  

## Video streaming
https://www.linux-projects.org/uv4l/installation/ DOES NOT WORK ON RPI4 /  64bit


Instead use mjpg_streamer. Note that _most_ pi stuff having to do with streaming will be about the rpi cameras which have dedicated libraries. USB cameras are "webcams" and A) considered less good B) work different.

My method as of Dec 2023
Install mjpg_streamer
Following instructions here: https://www.sigmdel.ca/michel/ha/rpi/guide_rpios_03_en.html#video-streamer


sudo apt install libjpeg-dev cmake
git clone https://github.com/jacksonliam/mjpg-streamer
cd mjpeg-streamer
cd mjpg-streamer-experimental
make
sudo make install
mjpg_streamer -o "output_http.so -p 8085" -i "input_uvc.so"
We specify inputs and outputs by indicating which LIBRARY to load. I love it.

on client computer
http://192.168.0.59:8085/?action=stream