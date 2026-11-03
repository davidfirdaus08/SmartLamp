#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define RELAY_PIN D1

const char* ssid = "DF SmartLamp";
const char* password = "12345678";

ESP8266WebServer server(80);
bool lampState = false;

void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="id">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Smart Lamp Control</title>
<style>
  :root {
    --bg-color: #eef2f5;
    --card-bg: #ffffff;
    --text-main: #333333;
    --text-sub: #888888;
    --primary-on: #ff9f43;
    --primary-off: #a4b0be;
    --shadow-light: #ffffff;
    --shadow-dark: #d1d9e6;
  }

  * { box-sizing: border-box; margin: 0; padding: 0; user-select: none; }

  body {
    font-family: 'Segoe UI', Roboto, Helvetica, Arial, sans-serif;
    background: var(--bg-color);
    height: 100vh;
    display: flex;
    align-items: center;
    justify-content: center;
    color: var(--text-main);
  }

  .container {
    width: 100%;
    max-width: 320px;
    padding: 20px;
  }

  .card {
    background: var(--card-bg);
    border-radius: 30px;
    padding: 40px 30px;
    box-shadow: 
      10px 10px 20px var(--shadow-dark), 
      -10px -10px 20px var(--shadow-light);
    text-align: center;
    transition: all 0.3s ease;
  }

  .header {
    margin-bottom: 30px;
  }

  h1 {
    font-size: 1.5rem;
    font-weight: 700;
    margin-bottom: 5px;
    letter-spacing: 1px;
  }

  p.subtitle {
    font-size: 0.9rem;
    color: var(--text-sub);
  }

  .lamp-icon-wrapper {
    position: relative;
    width: 120px;
    height: 120px;
    margin: 0 auto 40px;
    border-radius: 50%;
    background: var(--bg-color);
    box-shadow: 
      5px 5px 10px var(--shadow-dark), 
      -5px -5px 10px var(--shadow-light);
    display: flex;
    align-items: center;
    justify-content: center;
    transition: all 0.5s ease;
  }

  .card[data-state="on"] .lamp-icon-wrapper {
    box-shadow: 
      inset 5px 5px 10px rgba(0,0,0,0.1), 
      inset -5px -5px 10px rgba(255,255,255,0.5),
      0 0 30px rgba(255, 159, 67, 0.6);
    background: linear-gradient(145deg, #fff5e6, #ffe0b2);
  }

  .lamp-svg {
    width: 60px;
    height: 60px;
    fill: var(--primary-off);
    transition: fill 0.4s ease, filter 0.4s ease;
  }

  .card[data-state="on"] .lamp-svg {
    fill: var(--primary-on);
    filter: drop-shadow(0 0 8px var(--primary-on));
  }

  .control-panel {
    display: flex;
    flex-direction: column;
    gap: 15px;
  }

  .status-badge {
    display: inline-block;
    padding: 8px 16px;
    border-radius: 20px;
    font-size: 0.85rem;
    font-weight: 600;
    margin-bottom: 10px;
    transition: all 0.3s ease;
  }
  
  .card[data-state="on"] .status-badge {
    background: rgba(255, 159, 67, 0.15);
    color: #e67e22;
  }
  
  .card[data-state="off"] .status-badge {
    background: #f1f2f6;
    color: var(--text-sub);
  }

  .action-btn {
    background: var(--bg-color);
    border: none;
    width: 100%;
    padding: 18px;
    border-radius: 15px;
    font-size: 1rem;
    font-weight: 600;
    color: var(--text-main);
    cursor: pointer;
    box-shadow: 
      6px 6px 12px var(--shadow-dark), 
      -6px -6px 12px var(--shadow-light);
    transition: all 0.2s ease;
    outline: none;
    text-decoration: none;
    display: block;
  }

  .action-btn:active {
    box-shadow: 
      inset 4px 4px 8px var(--shadow-dark), 
      inset -4px -4px 8px var(--shadow-light);
    transform: translateY(2px);
  }

  .card[data-state="on"] .action-btn {
    color: #d35400;
  }
  
  .card[data-state="off"] .action-btn {
    color: #2f3542;
  }

</style>
</head>
<body>

<div class="container">
  <div class="card" id="ui-card" data-state=")rawliteral";

  if (lampState) {
    html += "on";
  } else {
    html += "off";
  }

  html += R"rawliteral(">
    
    <div class="header">
      <h1>DF SMART LAMP</h1>
      <p class="subtitle">Kontrol Wi-Fi</p>
    </div>

    <div class="lamp-icon-wrapper">
      <svg class="lamp-svg" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg">
        <path d="M12,2A7,7,0,0,0,5,9c0,2.38,1.19,4.47,3,5.74V17a1,1,0,0,0,1,1h6a1,1,0,0,0,1-1V14.74C17.81,13.47,19,11.38,19,9A7,7,0,0,0,12,2ZM14,19H10V18h4Zm0-5.55V16H10V13.45C8.25,12.53,7,10.68,7,9a5,5,0,0,1,10,0C17,10.68,15.75,12.53,14,13.45Z"/>
        <path d="M9,21a1,1,0,0,0,1,1h4a1,1,0,0,0,0-2H10A1,1,0,0,0,9,21Z"/>
      </svg>
    </div>

    <div class="status-text" style="margin-bottom:20px;">
    )rawliteral";

  if (lampState) {
    html += "<span class='status-badge'>Lampu Menyala</span>";
  } else {
    html += "<span class='status-badge'>Lampu Mati</span>";
  }

  html += R"rawliteral(
    </div>

    <div class="control-panel">
    )rawliteral";

  if (lampState) {
    html += "<a href='/off' class='action-btn' onclick='toggleLamp(event, this)'>MATIKAN</a>";
  } else {
    html += "<a href='/on' class='action-btn' onclick='toggleLamp(event, this)'>NYALAKAN</a>";
  }

  html += R"rawliteral(
    </div>
  </div>
</div>

<script>
  function toggleLamp(e, element) {
    e.preventDefault();
    
    var url = element.getAttribute('href');
    var card = document.getElementById('ui-card');
    var statusBadge = document.querySelector('.status-badge');
    var actionBtn = document.querySelector('.action-btn');
    var isTurningOn = (url === '/on');

    if (isTurningOn) {
      card.setAttribute('data-state', 'on');
      statusBadge.textContent = "Lampu Menyala";
      actionBtn.textContent = "MATIKAN";
      actionBtn.setAttribute('href', '/off');
    } else {
      card.setAttribute('data-state', 'off');
      statusBadge.textContent = "Lampu Mati";
      actionBtn.textContent = "NYALAKAN";
      actionBtn.setAttribute('href', '/on');
    }

    fetch(url).then(response => {
      if(!response.ok) {
        console.error("Gagal menghubungi perangkat");
      }
    }).catch(error => {
      console.error("Error:", error);
    });
  }
</script>

</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

void handleOn() {
  lampState = true;
  digitalWrite(RELAY_PIN, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOff() {
  lampState = false;
  digitalWrite(RELAY_PIN, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);

  WiFi.softAP(ssid, password);

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();
}

void loop() {
  server.handleClient();
}