{
	"targets": [
	{
		"target_name": "alignator",
		"sources": [
			"src/alignator.cpp",
			"src/customResize.cpp",
			"src/compensateGradient.cpp",
			"src/QRLocator.cpp"
		],
		"include_dirs" : [
			"<!(node -e \"require('nan')\")",
			"/Applications/MATLAB_R2014b.app/extern/include/",
			"/Applications/MATLAB_R2014b.app/toolbox/vision/visionrt/export/include/visionrt/"
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
