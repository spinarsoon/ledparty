var artnetsrv = require('./artnet-node/lib/artnet_server');
var piblaster = require('pi-blaster.js');

//pin assosiaciated with ligth from 0 to 15
var pin_GPIO = [2,3,4,14,15,17,18,19,20,27,21,22,23,24,25];
//array associating each one of the 256 level to a percentage PWM, with an anti-log law for LEDs
var led_anti_log=[];
var light_values=[];
//init the array
var number_of_lamp=15;

init_log_array();
init_light_array();

console.log("Artnet server is listening.");

var srv = artnetsrv.listen(6454, function(msg, peer) {
  debug_outputs(msg);
  for(i=0; i<msg.length; i++){
    value = msg.data[i];
    if(light_values[i] != value){
      light_values[i] = value;
      piblaster.setPwm(pin_GPIO[i],dmxToPercentValue(value));
    }
  }



});
function init_log_array(){
  //pre-compute the anti-log array for performance
  for(i=1; i<=256; i++){
    led_anti_log[i-1]=1-log(256,257-i);
  }
}
function init_light_array(){
  for(i=0; i<number_of_lamp; i++){
    light_values[i]=0;
  }
}
function log(b, n) {
  return Math.log(n) / Math.log(b);
}
function debug_outputs(msg){
  console.log("-----------------");
  console.log("Sequence: " + msg.sequence);
  console.log("Physical: " + msg.physical);
  console.log("Universe: " + msg.universe);
  console.log("Length: " + msg.length);
  console.log("Data: " + msg.data);
  console.log("-----------------");
}
