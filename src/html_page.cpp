#include "html_page.h"

String getHTML(bool ledDurum) {
    String durumRenk = ledDurum ? "#00ff88" : "#ff4444";
    String durumYazi = ledDurum ? "ACIK 💡" : "KAPALI ⚫";
    
    return R"(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Kontrol</title>
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
        .durum { 
            font-size: 20px; 
            margin-bottom: 30px;
            padding: 15px 30px;
            border-radius: 10px;
            background: )" + durumRenk + R"(;
            color: #1a1a2e;
            font-weight: bold;
        }
        .butonlar { display: flex; gap: 20px; }
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
        .ac { background: #00ff88; color: #1a1a2e; }
        .kapat { background: #ff4444; color: white; }
    </style>
</head>
<body>
    <h1>🔥 ESP32 LED Kontrol</h1>
    <div class="durum">LED: )" + durumYazi + R"(</div>
    <div class="butonlar">
        <a href="/led/ac"><button class="ac">LED AÇ</button></a>
        <a href="/led/kapat"><button class="kapat">LED KAPAT</button></a>
    </div>
</body>
</html>
    )";
}
