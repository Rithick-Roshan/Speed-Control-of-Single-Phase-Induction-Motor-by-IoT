// Import the functions you need from the SDKs you need
import { initializeApp } from "https://www.gstatic.com/firebasejs/10.12.2/firebase-app.js";
import { getAnalytics } from "https://www.gstatic.com/firebasejs/10.12.2/firebase-analytics.js";
import { getDatabase, ref, update, onValue } from "https://cdnjs.cloudflare.com/ajax/libs/firebase/10.12.2/firebase-database.js";

// Your web app's Firebase configuration
const firebaseConfig = {
  apiKey: "AIzaSyCJnL-foz2wXDkCREZka-_nQ49kaOoDm0c",
  authDomain: "fan-regulation-c667a.firebaseapp.com",
  databaseURL: "https://fan-regulation-c667a-default-rtdb.firebaseio.com",
  projectId: "fan-regulation-c667a",
  storageBucket: "fan-regulation-c667a.appspot.com",
  messagingSenderId: "647689224853",
  appId: "1:647689224853:web:e695c1b051540c6158919c",
  measurementId: "G-WRC0GJ90S1"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);
const db = getDatabase(app);

// DOM Element for the fan
let fanElement = document.getElementById('fan');

// Function to set the fan speed
function setSpeed(speed) {
  let animationDuration;

  switch (speed) {
    case 0:
      animationDuration = '0s';
      console.log("Fan off");
      break;
    case 1:
      animationDuration = '2s';
      console.log("Fan speed: Low");
      break;
    case 2:
      animationDuration = '1s';
      console.log("Fan speed: Medium");
      break;
    case 3:
      animationDuration = '0.5s';
      console.log("Fan speed: High");
      break;
    default:
      animationDuration = '0s';
      console.error("Invalid speed value");
  }

  fanElement.style.animationDuration = animationDuration;

  // Send the speed to the ESP8266
  fetch(`/setSpeed?s=${speed}`)
    .then(response => response.text())
    .then(data => console.log(data))
    .catch(error => console.error('Error:', error));
}

// jQuery Event listeners for the buttons
$("#off").click(function() {
  update(ref(db), { speeddb: 0 });
});

$("#s1").click(function() {
  update(ref(db), { speeddb: 1 });
});

$("#s2").click(function() {
  update(ref(db), { speeddb: 2 });
});

$("#s3").click(function() {
  update(ref(db), { speeddb: 3 });
});

// Real-time listener to update fan speed from database
onValue(ref(db, 'speeddb'), (snapshot) => {
  const speed = snapshot.val();
  setSpeed(speed);
});
