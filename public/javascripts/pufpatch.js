// var $ = require('jquery');
var JSZip = require("jszip");
// require('./vendors/qrcode.min.js');
var qr = new QRCode(document.getElementById("qrcode"));
var saver = require('./vendors/filesaver');


module.exports = (function(){

	var canvas, ctx;
	var init = function(){
		canvas = $('canvas#drawingArea').get(0);
		canvas.height = 480;
		canvas.width = 180;
		canvas.style.height = 480;
		canvas.style.width = 180;

		ctx = canvas.getContext('2d');
		ratio = 2;
		
		$(canvas)
			.attr("width", ctx.canvas.width * ratio)
			.attr("height", ctx.canvas.height * ratio)		
	}


	var redraw = function(id, message, number){

		qr.clear();
		qr.makeCode(id+"-"+number);
		ctx.clearRect(0, 0, 160*ratio, 460*ratio)

		ctx.lineWidth=3;
		for(var i = 0; i < 4; i++){		
			ctx.beginPath();
			ctx.arc(145*ratio, (30 + i*130) * ratio ,(9.5 + ((i+1)%2) * 4.5) * ratio,0,2*Math.PI);
			ctx.stroke();
			ctx.beginPath();
			ctx.arc(15*ratio, (30 + i*130) * ratio, 9.5*ratio, 0, 2*Math.PI);
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

		ctx.drawImage($('#qrcode > canvas').get(0), 25*ratio, 170*ratio, 110*ratio, 110*ratio);
	}


	var generateId = function(len) {
		var arr = new Uint8Array((len || 40) / 2);
		window.crypto.getRandomValues(arr);
		return [].map.call(arr, function(n) { return n.toString(16); }).join("");
	}

	init();
	redraw(0);

	return {
		save : function(){
			var zip = new JSZip();

			ids = []

			for(var i = 0; i < parseInt($('#copies').val()); i++){

				var id = generateId(8);
				ids.push(id);

				redraw(id, i);

				var savable = new Image();
					savable.src = canvas.toDataURL();

				zip.file("image-"+i+".png", savable.src.substr(savable.src.indexOf(',')+1), {base64: true});
			}

			$.get("/createEntries", {data : payload}, function(){
				console.log('entries created');
			})
			
			var content = zip.generate({type: "blob"});
				saver.saveAs(content, "images.zip");

			return ids;
		}
	}


})();