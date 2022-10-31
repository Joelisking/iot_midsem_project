char theHtmlCode[] PROGMEM = R"(

<!DOCTYPE html>
<html>

<head>
    <title>Dashboard</title>
</head>
<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-Zenh87qX5JnK2Jl0vWa8Ck2rdkQ2Bzep5IDxbcnCeuOxjzrPF/et3URy9Bv1WTRi" crossorigin="anonymous">
<body>
    <div style="color: white; background-color: brown; text-align: center; padding: 10px;">
        <h1>Water Level Monitoring</h1>
    </div>
        <h2 style="text-align: center;">Current Water Level:</h2>
        <p id="waterLevels" style="text-align: center; background-color:turquoise; padding:10px;">\</p>
    <div>
        <h2 style="text-align: center">Motor Controller</h2>
        <div>
          <button id='Auto' onclick='manStart(id)'> Start Manually </button>
          <button id='Man Start' onclick='manStop(id)'> Stop Manually </button>
          <button id='Man Stop' onclick='autoMode(id)'> Auto Mode </button>
     

    <script>

    setInterval(function(){ tank1(); }, 500);
    function tank1(){
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
      document.getElementById("waterLevels").innerHTML = this.responseText;
        }
      };
       xhr.open('GET', "theWaterLevel", true);
       xhr.send();
    }

//    function manStart(){
//      var xhr = new XMLHttpRequest();
//      xhr.onreadystatechange = function() {};
//      xhr.open("GET", "manStart", true);
//      xhr.send();
//    }

      function autoStart(butn) {
         var URL, variab, text;
         if (butn == 'AutoStart') {
            URL = 'AutoStart';
         }
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function (butn) {
                if (this.readyState == 4 && this.status == 200)
                    document.getElementById(variab).innerHTML = this.
                        responseText;
            };
            xhr.open('GET', URL, true);
            xhr.send();

    function manStop(){
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function() {};
      if (this.readyState == 4 && this.status == 200) {}
      xhr.open("GET", "manStop", true);
      xhr.send();
    }

    function autoMode(){
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function() {};
      xhr.open("GET", "autoMode", true);
      xhr.send();
    }
    </script>

    </body>
</html>



<!-- 


        function sendData(butn) {
            var URL, variab, text;
            if (butn == 'light') {
                URL = 'AutoURL';
                variab = 'light';
            }
            else if (butn == 'Manual') {
                URL = 'ManualURL';
                variab = 'Manual';
            }
            if (butn == 'light' || butn == 'Manual') { // change button class and text 
                var state = document.getElementById(butn).className;
                state = (state == 'btn on' ? 'btn off' : 'btn on');
                text = (state == 'btn on' ? ' OFF' : ' ON');
                document.getElementById(butn).className = state;
                document.getElementById(butn).innerHTML = text;
            }
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function (butn) {
            if (this.readyState == 4 && this.status == 200)
                document.getElementById(variab).innerHTML = this.
                esponseText;
            };
            xhr.open('GET', URL, true);
            xhr.send();
        }
    </script>


 -->





)";
