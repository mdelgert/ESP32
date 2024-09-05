#ifndef SETTINGSPAGEHTML_H
#define SETTINGSPAGEHTML_H

const char* settingsPageHTML = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Device Settings</title>
    <style>
        body {
            background-color: #121212;
            color: #FFFFFF;
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 20px;
        }
        h1 {
            color: #BB86FC;
        }
        label {
            display: block;
            margin: 10px 0 5px;
        }
        input[type="text"], input[type="password"], input[type="checkbox"] {
            width: 100%;
            padding: 10px;
            margin: 5px 0 20px;
            background-color: #333333;
            color: #FFFFFF;
            border: none;
            border-radius: 5px;
        }
        button {
            padding: 10px 20px;
            background-color: #03DAC6;
            color: #121212;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }
        button:hover {
            background-color: #018786;
        }
        .form-container {
            max-width: 500px;
            margin: auto;
        }
    </style>
</head>
<body>
    <div class="form-container">
        <h1>Device and WiFi Settings</h1>
        <form id="settingsForm">
            <h2>Device Settings</h2>
            <label for="deviceName">Device Name</label>
            <input type="text" id="deviceName" name="deviceName" value="atom1" required>

            <label for="setupMode">Setup Mode</label>
            <input type="checkbox" id="setupMode" name="setupMode" checked>

            <label for="admin">Admin Username</label>
            <input type="text" id="admin" name="admin" value="admin" required>

            <label for="password">Admin Password</label>
            <input type="password" id="password" name="password" value="password" required>

            <h2>WiFi Settings</h2>
            <label for="ssid">WiFi SSID</label>
            <input type="text" id="ssid" name="ssid" value="ssid" required>

            <label for="wifiPassword">WiFi Password</label>
            <input type="password" id="wifiPassword" name="wifiPassword" value="password" required>

            <button type="button" onclick="submitSettings()">Save Settings</button>
        </form>
        <div id="status"></div>
    </div>

    <script>
        function submitSettings() {
            const deviceName = document.getElementById('deviceName').value;
            const setupMode = document.getElementById('setupMode').checked;
            const admin = document.getElementById('admin').value;
            const password = document.getElementById('password').value;
            const ssid = document.getElementById('ssid').value;
            const wifiPassword = document.getElementById('wifiPassword').value;

            const settings = {
                "device": {
                    "name": deviceName,
                    "setup_mode": setupMode,
                    "admin": admin,
                    "password": password
                },
                "wifi": {
                    "ssid": ssid,
                    "password": wifiPassword
                }
            };

            const xhr = new XMLHttpRequest();
            xhr.open("POST", "/settings/update", true);
            xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
            xhr.onreadystatechange = function () {
                if (xhr.readyState === 4 && xhr.status === 200) {
                    document.getElementById("status").innerText = "Settings saved successfully!";
                } else if (xhr.readyState === 4) {
                    document.getElementById("status").innerText = "Failed to save settings!";
                }
            };
            xhr.send(JSON.stringify(settings));
        }
    </script>
</body>
</html>
)rawliteral";

#endif  // SETTINGSPAGEHTML_H
