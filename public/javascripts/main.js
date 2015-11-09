(function($) {

	$.fn.visible = function(partial) {

		var $t            = $(this),
		$w            = $(window),
		viewTop       = $w.scrollTop(),
		viewBottom    = viewTop + $w.height(),
		_top          = $t.offset().top,
		_bottom       = _top + $t.height(),
		compareTop    = partial === true ? _bottom : _top,
		compareBottom = partial === true ? _top : _bottom;

		return ((compareBottom <= viewBottom) && (compareTop >= viewTop));

	};

})(jQuery);

// For QR functionality
qrcode = new QRCode(document.getElementById("qrcode"));

var canvas = $('canvas#drawingArea').get(0);
	canvas.height = 460;
	canvas.width = 160;
	canvas.style.height = 460;
	canvas.style.width = 160;

var ctx = canvas.getContext('2d');
	if(window.devicePixelRatio != 1){	
		$(canvas)
			.attr("width", ctx.canvas.width * window.devicePixelRatio)
			.attr("height", ctx.canvas.height * window.devicePixelRatio)
	}


function redraw(ctx, img, ratio){	

	ctx.lineWidth=2;
	for(var i = 0; i < 4; i++){		
		ctx.beginPath();
		ctx.arc(15*ratio, (30 + i*130) * ratio ,(10 + ((i+1)%2) * 3) * ratio,0,2*Math.PI);
		ctx.stroke();
		ctx.beginPath();
		ctx.arc(145*ratio, (30 + i*130) * ratio, 10*ratio, 0, 2*Math.PI);
		ctx.stroke();
	}

	ctx.beginPath();
	ctx.moveTo(15*ratio,  30*ratio);
	ctx.lineTo(15*ratio,  420*ratio);
	ctx.lineTo(145*ratio, 420*ratio);
	ctx.lineTo(145*ratio, 30*ratio);
	ctx.lineTo(15*ratio,  30*ratio);
	ctx.moveTo(15*ratio,  160*ratio);
	ctx.lineTo(145*ratio, 160*ratio);
	ctx.moveTo(15*ratio,  290*ratio);
	ctx.lineTo(145*ratio, 290*ratio);
	ctx.stroke();
	ctx.drawImage(img, 25*ratio, 170*ratio, 110*ratio, 110*ratio);
}

function generateId(len) {
	var arr = new Uint8Array((len || 40) / 2);
	window.crypto.getRandomValues(arr);
	return [].map.call(arr, function(n) { return n.toString(16); }).join("");
}

/* smooth scrolling sections */
$('#qr').click(function() {
	$('html,body').animate({
		scrollTop: $('#' + $(this).attr("target")).offset().top
	}, 300);
	return false;
});

$('#upload-orig').click(function() {
	$('html,body').animate({
		scrollTop: $('#' + $(this).attr("target")).offset().top
	}, 300);
	return false;
});


$("#upload-original").fileinput({
	uploadUrl: '/uploadOriginal/',
	uploadAsyc : true,
	showPreview: false,
	showCaption: false,
	browseLabel: "上传原始标签",
	browseClass: "btn btn-primary btn-lg"
}).on('filebatchuploadsuccess', function(event, data, previewID, index){
	$().after('<span>'+data.response.file+' '+data.response.score+'</span>');
});

$("#upload-tobetest").fileinput({
	uploadUrl: '/uploadTobeTest/',
	uploadAsyc : true,
	showPreview: false,
	showCaption: false,
	browseLabel: "拍摄验证图像",
	browseClass: "btn btn-primary btn-lg"
}).on('filebatchuploadsuccess', function(event, data, previewID, index){
	$('body').append('<span>'+data.response.file+' '+data.response.score+'</span>');
	$('body').append('<img src="/images/'+data.response.file.replace('tif', 'jpg')+'"><p>');
});