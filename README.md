# 2019-01-04-OrangeBot-Node-Cpp
A c++ module interfaces with the NODE.JS application and allows for high performance C++ native code to run on OrangeBot<br>

![alt text](https://raw.githubusercontent.com/OrsoEric/2019-01-04-OrangeBot-Node-Cpp/master/I9%20-%20Browser%20interface.PNG)

You can construct your c++ project as usual.
When the project is operational and the API passed the test bench, you can make a binding file to use the NAPI.H to expose the API to NODE.JS. From there, NODE can call the function like it would call any other module. The C++ is compiled natively by the C++ compiler. node run build takes care of the compilation and the bindings.

If you change C fines you need to recompile.
If you only change .JS or .html files, you don't need to recompile.

# HowTo
1) create project folders
	2020-01-04-OrangeBot-Cpp/
	2020-01-04-OrangeBot-Cpp/srccpp/
2) enter directory
	cd 2020-01-04-OrangeBot-Cpp/
3) initialize NODE
	npm init
4) install NODE packages
	npm install node-gyp --save-dev
	npm install node-addon-api
	npm install serialport
	npm install ws
	npm install socket.io
5) edit package.json
{
  "name": "2020-01-04-orangebot-cpp",
  "version": "1.0.0",
  "description": "",
  "main": "orangebot.js",
  "gypfile": true,
  "scripts": {
    "build": "node-gyp rebuild",
    "clean": "node-gyp clean"
  },
  "author": "",
  "license": "ISC",
  "devDependencies": {
    "node-gyp": "^5.0.7"
  },
  "dependencies": {
    "node-addon-api": "^2.0.0",
    "serialport": "^8.0.6",
    "socket.io": "^2.3.0",
    "ws": "^7.2.1"
  }
}
6) create binding.gyp
{
    "targets": [{
        "target_name": "OrangebotNodeCpp",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "srccpp/main.cpp",
			"srccpp/myclass.cpp"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}

7) Load main.cpp, myclass.cpp and myclass.h into the srccpp folder
8) Load all NODE source files. Add line to include the c++ files
	const myAddon = require('./build/Release/OrangebotNodeCpp.node');
	console.log('My custom c++ module',myAddon);
	module.exports = myAddon;
9) build cpp files in a form node can use
	npm rebuild
10) run node application
	node orangebot.js
