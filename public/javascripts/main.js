$("#upload-image").fileinput({
	uploadUrl: '/uploadImage/',
	uploadAsyc : true,
	showPreview: false
}).on('filebatchuploadsuccess', function(event, data, previewID, index){
	$('body').append('<span>'+data.response.file+' '+data.response.score+'</span>');
	$('body').append('<img src="/images/'+data.response.file.replace('tif', 'jpg')+'"><p>');
});
