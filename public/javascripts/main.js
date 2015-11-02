$("#upload-image").fileinput({
	uploadUrl: '/uploadImage/',
	uploadAsyc : true,
	showPreview: false
}).on('filebatchuploadsuccess', function(event, data, previewID, index){
	$('body').append('<img src="/images/original.jpg" width=20%>');
	$('body').append('<img src="/images/compensated.jpg" width=20%>');
	$('body').append('<img src="/images/contours.jpg" width=20%><p>');
	$('body').append('<img src="/images/pre-warped.jpg" width=20%><p>');
	// $('body').append('<span>'+data.response.file+' '+data.response.score+'</span>');
	// $('body').append('<img src="/images/'+data.response.file.replace('tif', 'jpg')+'"><p>');
});
