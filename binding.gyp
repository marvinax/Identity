{
	"targets": [
	{
		"target_name": "hello",
		"sources": [ "hello.cpp" ],
		"include_dirs" : [
			"<!(node -e \"require('nan')\")"
		],
		"libraries": [
			"<!@(pkg-config --libs opencv)"
		],
		"conditions": [
              [ 'OS=="mac"', {
                "xcode_settings": {
                    'OTHER_CPLUSPLUSFLAGS' : ['-std=c++11','-stdlib=libc++'],
                    'OTHER_LDFLAGS': ['-stdlib=libc++'],
                    'MACOSX_DEPLOYMENT_TARGET': '10.7'
                }
            }]
        ]
	}]
}