#include "html_page.h"

String getHTML(bool ledState) {
    String stateColor = ledState ? "#00ff88" : "#ff4444";
    String stateText = ledState ? "ON 💡" : "OFF ⚫";
    
    return R"(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Control</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body { 
            font-family: Arial; 
            text-align: center; 
            background: #1a1a2e;
            color: white;
            min-height: 100vh;
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
        }
        h1 { margin-bottom: 30px; font-size: 28px; }
        .status { 
            font-size: 20px; 
            margin-bottom: 30px;
            padding: 15px 30px;
            border-radius: 10px;
            background: )" + stateColor + R"(;
            color: #1a1a2e;
            font-weight: bold;
        }
        .buttons { display: flex; gap: 20px; }
        a { text-decoration: none; }
        button {
            font-size: 22px;
            padding: 20px 50px;
            border: none;
            border-radius: 15px;
            cursor: pointer;
            font-weight: bold;
            transition: transform 0.2s;
        }
        button:hover { transform: scale(1.05); }
        .on { background: #00ff88; color: #1a1a2e; }
        .off { background: #ff4444; color: white; }
    </style>
</head>
<body>
    <h1>🔥 ESP32 LED Control</h1>
    <div class="status">LED: )" + stateText + R"(</div>
    <div class="buttons">
        <a href="/led/on"><button class="on">LED ON</button></a>
        <a href="/led/off"><button class="off">LED OFF</button></a>
    </div>
</body>
</html>
    )";
}
