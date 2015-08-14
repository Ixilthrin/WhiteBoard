This project is intended to be a general white board program providing cloud storage.

The programming language used is C++ and the required libraries are SDL, OpenGL, cURL,
and rapidjson.

The build and run step is as follows:
g++ frustum.cc -lcurl -lGL -lSDL -lSDL_ttf -lSDL_image -I/usr/include/SDL GL_SDL_WindowManager.cc SDLEventDispatcher.cc TextureUtil.cc TextModel.cc WhiteBoard.cc ProjectManager.cc main.cc && ./a.out

When you run you must first type in a user name and password.
Then you will see a list of your projects with a colorful dynamic background.

I used Fedora for this project so installation instructions may vary.

Installing the Libraries

Install g++
sudo dnf install gcc-c++

Install SDL
sudo dnf install SDL*

Install rapidjson
sudo dnf install rapidjson

Install Dev Tools
sudo dnf groupinstall 'Development Tools'

Install curl
Found the development installer at:
http://rpm.pbone.net/index.php3/stat/4/idpl/29615208/dir/fedora_22/com/libcurl-devel-7.40.0-3.fc22.x86_64.rpm.html
Then I typed the following and the header files were installed succesfully:
sudo rpm -i libcurl-devel-7.40.0-3.fc22.x86_64.rpm


