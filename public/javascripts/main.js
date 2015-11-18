// var $ = require('jquery');
var pufpatch = require('./pufpatch')
var fileinput = require('./vendors/fileinput.min.js');

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

$('#upload-test').click(function() {
	$('html,body').animate({
		scrollTop: $('#' + $(this).attr("target")).offset().top
	}, 300);
	return false;
});


$('#generate-qr').click(function(){
	var copies = $('#copies').val();
	// console.log(pufpatch);
	var ids = pufpatch.save();

	$.get("/createEntries/", {
		title : $('#title').val(),
		isbn : $('#isbn').val(),
		author : $('#author').val(),
		print : $('#print').val(),
		amount : $('#amount').val(),
		edition : $('#edition').val(),
		ids : ids
	})
})


$('#upload-sheet').fileinput({
	uploadUrl: '/uploadSheet/',
	uploadAsyc : true,
	showPreview: false,
	showCaption: false,
	browseLabel: "上传原始标签打印页 (仅供调试)",
	browseClass: "btn btn-success"	
}).on('filebatchuploadsuccess', function(event, data, previewID, index){
	var names = data.response.names;

	$.get("/createEntries/", {
		title : $('#title').val(),
		isbn : $('#isbn').val(),
		author : $('#author').val(),
		print : $('#print').val(),
		amount : $('#amount').val(),
		edition : $('#edition').val(),
		ids : names
	})

});

$("#upload-original").fileinput({
	uploadUrl: '/uploadOriginal/',
	uploadAsyc : true,
	showPreview: false,
	// showCaption: false,
	browseLabel: "上传原始标签",
	browseClass: "btn btn-primary"
}).on('filebatchuploadsuccess', function(event, data, previewID, index){
	var successResult = data.response.result;
	var success = successResult.map(function(e, i){
		return "编号"+ e.entry +"\n标题: "+ e.type+"\n作者: " + e.author + "\nISBN: " + e.isbn + "\n版次" + e.edition + "\n印次" + e.print
	}).join("\n\n");

	var failedResult = data.response.failed;
	var failure = failedResult.join("\n")

	$('#original-result').val(successResult.length+'个标签原始图像成功上传\n\n'+success
					+"\n\n以下" + failedResult.length + "个标签原始图像无法识别，请检查\n\n" + failure);
});

$("#upload-tobetest").fileinput({
	uploadUrl: '/uploadTobeTest/',
	uploadAsyc : true,
	showPreview: false,
	showCaption: false,
	browseLabel: "拍摄验证图像",
	browseClass: "btn btn-primary"
}).on('filebatchuploadsuccess', function(event, data, previewID, index){
	var info = data.response.doc;
	var infoString = "编号"+ info.entry +"\n标题: "+ info.type+"\n作者: " + info.author + "\nISBN: " + info.isbn + "\n版次" + info.edition + "\n印次" + info.print
	$("#test-info").val(infoString);
	$('#test-result').html('<img src="'+data.response.file+'"><p><p>'+data.response.file+' '+data.response.score+'</p>');
});
