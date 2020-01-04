{
    "targets": [{
        "target_name": "OrangebotNodeCpp",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "srccpp/orangebot_node_bindings.cpp",
			"srccpp/ob.cpp",
			"srccpp/uniparser.cpp",
			"srccpp/debug.cpp"
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
