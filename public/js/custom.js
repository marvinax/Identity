/* Theme Name: Worthy - Free Powerful Theme by HtmlCoder
 * Author:HtmlCoder
 * Author URI:http://www.htmlcoder.me
 * Version:1.0.0
 * Created:November 2014
 * License: Creative Commons Attribution 3.0 License (https://creativecommons.org/licenses/by/3.0/)
 * File Description: Place here your custom scripts
 */

var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera( 45, window.innerWidth / window.innerHeight, 0.1, 1000 );
var renderer = new THREE.WebGLRenderer({ antialias: true});

var startTime = Date.now();

//assignings happen here
//more info on https://github.com/mrdoob/three.js/wiki/Uniforms-types
var tuniform = {
    iGlobalTime:    { type: 'f', value: 0.1 }
};

var myMaterial = new THREE.ShaderMaterial({
    uniforms: uniforms,
    vertexShader: document.getElementById( 'vs' ).textContent,
    fragmentShader: document.getElementById( 'fs' ).textContent
});

camera.position.z = 0.40;
var itemGeometry = new THREE.PlaneGeometry( window.innerWidth / (window.innerWidth+window.innerHeight), window.innerHeight / (window.innerWidth+window.innerHeight), 0);
var itemCube = new THREE.Mesh( itemGeometry, myMaterial );
scene.add( itemCube );

renderer.setSize( 300, 300 );
$('#view').append( renderer.domElement );


function render() {

    requestAnimationFrame(render);
    uniforms.time.value = (Date.now() - startTime)/1000;        
    renderer.render(scene, camera);

}
render();
