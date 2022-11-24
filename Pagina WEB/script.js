// Your web app's Firebase configuration
  const firebaseConfig = {
  apiKey: "AIzaSyBs3V_GcW_q6gKgvQL2WXvhZlOWqOvFKmE",
  authDomain: "esp32-ab718.firebaseapp.com",
  databaseURL: "https://esp32-ab718-default-rtdb.firebaseio.com",
  projectId: "esp32-ab718",
  storageBucket: "esp32-ab718.appspot.com",
  messagingSenderId: "580651130213",
  appId: "1:580651130213:web:60963b10826eac083a558c"
};
  // Initialize Firebase
  firebase.initializeApp(firebaseConfig);

$(document).ready(function(){
	var database = firebase.database();
	var LED1;
	var LED2;
	var LED3;
	var LED4;
	database.ref().on("value", function(snap){
		LED1 = snap.val().test.LED1;
		LED2 = snap.val().test.LED2;
		LED3 = snap.val().test.LED3;
		LED4 = snap.val().test.LED4;
		if(LED1 == "1"){
			document.getElementById("unact").style.display = "none";
			document.getElementById("act").style.display = "block";
		} else {
			document.getElementById("unact").style.display = "block";
			document.getElementById("act").style.display = "none";
		}
		if(LED2 == "1"){
			document.getElementById("unact1").style.display = "none";
			document.getElementById("act1").style.display = "block";
		} else {
			document.getElementById("unact1").style.display = "block";
			document.getElementById("act1").style.display = "none";
		}
		if(LED3 == "1"){
			document.getElementById("unact2").style.display = "none";
			document.getElementById("act2").style.display = "block";
		} else {
			document.getElementById("unact2").style.display = "block";
			document.getElementById("act2").style.display = "none";
		}
		if(LED4 == "1"){
			document.getElementById("unact3").style.display = "none";
			document.getElementById("act3").style.display = "block";
		} else {
			document.getElementById("unact3").style.display = "block";
			document.getElementById("act3").style.display = "none";
		}
	});

	$(".toggle-btn").click(function(){
		var firebaseRef = firebase.database().ref().child("/test/LED1");
		if(LED1 == 1){
			firebaseRef.set(0);
			LED1 = 0;
		} else {
			firebaseRef.set(1);
			LED1 = 1;
		}
	})
	$(".toggle-btn1").click(function(){
		var firebaseRef = firebase.database().ref().child("/test/LED2");
		if(LED2 == 1){
			firebaseRef.set(0);
			LED2 = 0;
		} else {
			firebaseRef.set(1);
			LED2 = 1;
		}
	})
	$(".toggle-btn2").click(function(){
		var firebaseRef = firebase.database().ref().child("/test/LED3");
		if(LED3 == 1){
			firebaseRef.set(0);
			LED3 = 0;
		} else {
			firebaseRef.set(1);
			LED3 = 1;
		}
	})
	$(".toggle-btn3").click(function(){
		var firebaseRef = firebase.database().ref().child("/test/LED4");
		if(LED4 == 1){
			firebaseRef.set(0);
			LED4 = 0;
		} else {
			firebaseRef.set(1);
			LED4 = 1;
		}
	})
});