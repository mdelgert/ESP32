// webpage.h
#ifndef WEBPAGE_H
#define WEBPAGE_H

const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <style>
    body {
      background-color: #121212;
      color: #E0E0E0;
      font-family: Arial, sans-serif;
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh;
      margin: 0;
    }
    .container {
      text-align: center;
      background-color: #1E1E1E;
      padding: 20px;
      border-radius: 10px;
      box-shadow: 0px 0px 10px 2px rgba(0,0,0,0.7);
    }
    input[type='text'], input[type='password'] {
      width: 80%;
      padding: 10px;
      margin: 10px 0;
      border: 1px solid #333;
      border-radius: 5px;
      background-color: #333;
      color: #E0E0E0;
    }
    input[type='submit'] {
      background-color: #6200EE;
      color: #E0E0E0;
      padding: 10px 20px;
      border: none;
      border-radius: 5px;
      cursor: pointer;
    }
    input[type='submit']:hover {
      background-color: #3700B3;
    }
  </style>
</head>
<body>
  <div class='container'>
    <h1>Enter WAP and PASSWORD</h1>
    <form action="/submit" method="POST">
      WAP: <br><input type="text" name="wap"><br>
      PASSWORD: <br><input type="password" name="password"><br>
      <input type="submit" value="Submit">
    </form>
  </div>
</body>
</html>
)rawliteral";

#endif
