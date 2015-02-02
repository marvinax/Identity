Tautology.Canvas = function(divElementID){
	
	this.canvas = new fabric.Canvas(divElementID, {
		width : $('#'+divElementID).parent().width(),
		height: 200
	});
	
}

Tautology.Canvas.prototype = {
	constructor : Tautology.Canvas,

	init : function(){
	    var c = this.canvas.getElement(); // canvas = fabric.Canvas
    
	    var w = c.width, h = c.height;

	    c.style.width ='100%';
		c.style.height='100%';
		  // ...then set the internal size to match
		c.width  = this.canvas.offsetWidth;
		c.height = this.canvas.offsetHeight;

	    c.setAttribute('width', w*window.devicePixelRatio);
	    c.setAttribute('height', h*window.devicePixelRatio);
	    c.getContext('2d').scale(window.devicePixelRatio, window.devicePixelRatio);

	},

	add : function(url){
	    fabric.Image.fromURL(url, function(img) {
	    	img._element.crossOrigin = 'Anonymous';
	    	img._originalElement.crossOrigin = 'Anonymous';
		    if(img.height > this.canvas.height){
		        img.scale(img.height/this.canvas.height * 0.1);
		    }
		    this.canvas.add(img);
	    }.bind(this)); 
	}
}