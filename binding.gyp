{
	"targets": [
		{
			"target_name": "liblibui",
			"sources": [ "libui.cc" ],
			"include_dirs": [
				"<!(node -e \"require('nan')\")"
			],
			"libraries": ["-Wl,-rpath, ../libui/out/libui.so.0"]
		}
	]
}
