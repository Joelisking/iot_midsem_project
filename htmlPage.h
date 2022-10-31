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
        <p id="waterLevels" style="text-align: center; background-color:turquoise; padding:10px;"></p>
    <div>
        <h2 style="text-align: center">Motor Controller</h2>

        <div class="text-center" style="align-items: center;">
          <button id='Auto' onclick='manStart()' class="btn btn-primary"> Start Manually </button>
          <button id='Man Start' onclick='manStop()' class="btn btn-success"> Stop Manually </button>
          <button id='Man Stop' onclick='autoMode()' class="btn btn-warning"> Auto Mode </button>
         </div>

     <div>
        <h2 style="text-align: center">Water Level Report</h2>
        <div style="align-items: center;" class="d-flex justify-content-center">
            <a href="http://localhost/iot/report.php" target="_blank">
                <button class="btn btn-danger" id='Report'> View Report </button>
            </a>
        </div>
    </div>
     

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

    function manStart(){
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function() {};
      xhr.open("GET", "manStart", true);
      xhr.send();
    }

    function manStop(){
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function() {};
    //   if (this.readyState == 4 && this.status == 200) {}
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
)";
