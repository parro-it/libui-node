{
    "targets": [
        {
            "target_name": "libui",
            "sources": [ "libui.cc" ],
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ],
	        "libraries": ["../libui/out/libui.so"]
        }
    ]
}
