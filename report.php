<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <!-- CSS only -->
<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-Zenh87qX5JnK2Jl0vWa8Ck2rdkQ2Bzep5IDxbcnCeuOxjzrPF/et3URy9Bv1WTRi" crossorigin="anonymous">
</head>
<body>
    <div class= "container">
        <div class= "row justify-content-center">
            <div class = "col-md-12">
                <div class = "card-header">
                    <h4>Water Level Report</h4>
                    <h5>Joel Adu-Kwarteng's Tank</h5>
                </div>
                <div class = "card-body">
                    <div class = "table-responsive">
                        <table class = "table table-bordered">
                            <thead>
                                <tr>
                                    <th>ID</th>
                                    <th>Owner ID</th>
                                    <th>Water Level</th>
                                    <th>Time</th>

                                </tr>
                            </thead>
                            <tbody>
                                <?php
                                $con = mysqli_connect("localhost", "root", "", "midsem_proj");

                                $query = "SELECT * FROM tanks ORDER BY ID DESC LIMIT 5";
                                
                                $query_run = mysqli_query($con, $query);
                                
                            if(mysqli_num_rows($query_run) > 0)  {

                                foreach($query_run as $row){

                                ?>
                                <?= 
                                    '<tr>
                                        <td>'. $row['id'] .'</td>
                                        <td>'. $row['owner_id'] . '</td>
                                        <td>'. $row['water_level'] . '</td>
                                        <td>'. $row['time'] . '</td>
                                    </tr>'
                                ?>

                                    <?php
                                }
                            }
                             else {
                                ?>
                                    <?= 
                                        '<tr>
                                            <td colspan = "4">' . "No records yet" .' </td>
                                        </tr>'
                                    ?>

                                <?php
                            } 
                                ?>

                            </tbody>

                        </table>
                    </div>
                </div>
            </div>
        </div>

    </div>
<script src="https://code.jquery.com/jquery-3.6.1.js" integrity="sha256-3zlB5s2uwoUzrXK3BT7AX3FyvojsraNFxCc2vC/7pNI=" crossorigin="anonymous"></script>
    <!-- JavaScript Bundle with Popper -->
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-OERcA2EqjJCMA+/3y+gxIOqMEjwtxJY7qPCqsdltbNJuaOe923+mo//f6V8Qbsw3" crossorigin="anonymous"></script>
</body>
</html>