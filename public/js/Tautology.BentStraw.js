Tautology.BentStraw = function(scene) {
	this.radiusResolution = 40,
	this.bellowResolution = 16,

	this.radius = 2.5,
	this.shortLength = 10,
	this.longLength = 40,

	this.bellowAngle = 33/100*Math.PI,
	this.bellowRadius = 5 + (Math.PI-this.bellowAngle)/Math.PI*3;
	
	this.bellowOffset = new THREE.Vector3(-0.15, 0, 0.6);

	this.vertices = new Tautology.VectorArray();
	this.geom = null;
	this.pack = new THREE.Object3D();
	this.scene = scene;
}

Tautology.BentStraw.prototype = {
	constructor : Tautology.BentStraw,

	init : function(){
		this.vertices = new Tautology.VectorArray();
		this.vertices.init([new THREE.Vector3(0, 0, 0)]);
		this.vertices.dup(this.radiusResolution+1);
		this.vertices.flatten();
		this.vertices.dup(this.bellowResolution*2+1);

		this.updateVertices();

		var mg = new Tautology.MeshGeometry(this.vertices.array, 0, 1, 0, 1);
		this.geom = mg.generateGeom(true);

		this.pack.add(new THREE.Mesh(this.geom, inside));
		this.pack.add(new THREE.Mesh(this.geom, outside));
	},

	addModel : function(){
		this.scene.add(this.pack);
	},

	removeModel: function(){
		this.scene.remove(this.pack);
	},

	updateRadius : function(radius){
		this.radius = radius;
		this.updateVertices();
	},

	updateShortLength : function(shortLength){
		this.shortLength = shortLength;
		this.updateVertices();
	},

	updateLongLength : function(longLength){
		this.longLength = longLength;
		this.updateVertices();
	},

	updateCurvature : function(angle){
		this.bellowAngle = angle;
		this.bellowRadius = 5 + (Math.PI-this.bellowAngle)/Math.PI*3;
		this.updateVertices();
	},

	updateVertices : function(){
		_this = this;
		(this.geom != null) && (this.geom.verticesNeedUpdate = true);

		this.vertices.applyFunc(function(){
			(this.geom != null) && (this.geom.verticesNeedUpdate = true);

			// Reset the point
			this.object.set(0, 0, 0);

			// Make the points move away from center to represent the short straight part
			this.index.index[0] == 0 && this.object.add(new THREE.Vector3(-_this.shortLength, 0, 0));

			// Make the points move away from center to represent the long straight part
			if(this.index.index[0] == _this.bellowResolution*2) {
				this.object.add(new THREE.Vector3(_this.longLength, 0, 0));
			} ;

			// Move the points away from the straw centroid axis to represent the radius
			this.object.add(new THREE.Vector3(0, 0, _this.radius));

			// Move the points with odd index over bellow resolution dimension to form the bellow
			if(this.index.index[0] > 1 && this.index.index[0] < _this.bellowResolution*2 && ((this.index.index[0] & 1)==0)){
				this.object.add(_this.bellowOffset);	
			}
		
			// Rotate the points around the straw centroid axis to form the straw
			this.object.applyAxisAngle(new THREE.Vector3(1, 0, 0), 2*Math.PI*this.index.index[1]/_this.radiusResolution);		

			// Move the whole straw further to make the curved bellow.
			this.object.add(new THREE.Vector3(0, _this.bellowRadius, 0));

			// Let the bellow part rotate around the axis which the bellow curved around.
			with({index : this.index.index}){
				if(index[0] > 1 && index[0] < _this.bellowResolution*2){
					this.object.applyAxisAngle(new THREE.Vector3(0, 0, 1), -_this.bellowAngle*index[0]/(_this.bellowResolution*2));
				}
				if(index[0] == _this.bellowResolution*2){
					this.object.applyAxisAngle(new THREE.Vector3(0, 0, 1), -_this.bellowAngle*index[0]/(_this.bellowResolution*2));
				}
			}

		});

	}
}