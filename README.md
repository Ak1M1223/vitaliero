
Building (Linux/WSL)
-----------------------
* Build VitaSDK and set it up.
* Dependencies: CMake, gcc
* Run: ```./build-all```

Installation in PSvita.
-----------------------
* Copy openlierovita.vpk to the folder of your choosing and install it through VitaShell or similar program.
* Create a folder on your vita in ```ux0:data/openliero``` and copy ```TC``` folder to it. It should look like this: ```ux0:data/openliero/TC/*```
* If you want to add levels, mods or other stuff, just place them in ```ux0:data/openliero``` directory. Folders (for mappacks) are also supported. Use original project to generate data from legacy liero.
