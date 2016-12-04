function getXMLHTTPRequest()
{
    var request;
    
    // Lets try using ActiveX to instantiate the XMLHttpRequest object
    try{
        request = new ActiveXObject("Microsoft.XMLHTTP");
    }catch(ex1){
        try{
            request = new ActiveXObject("Msxml2.XMLHTTP");
        }catch(ex2){
            request = null;
        }
    }

    // If the previous didn't work, lets check if the browser natively support XMLHttpRequest 
    if(!request && typeof XMLHttpRequest != "undefined"){
        //The browser does, so lets instantiate the object
        request = new XMLHttpRequest();
    }

    return request;
}


function loadFile(filename, callback)
{
    var aXMLHttpRequest = getXMLHTTPRequest();
    var allData;

    if (aXMLHttpRequest)
    {
        aXMLHttpRequest.open("GET", filename, true);
        
      aXMLHttpRequest.onreadystatechange = function (aEvt) {
        if(aXMLHttpRequest.readyState == 4){
        allData = aXMLHttpRequest.responseText;
        callback(allData)
        }
      };
      
      //Lets fire off the request
        aXMLHttpRequest.send(null);
    }
    else
    {
        //Oh no, the XMLHttpRequest object couldn't be instantiated.
        alert("A problem occurred instantiating the XMLHttpRequest object.");
    }
}


var dtChanged = function(){
  start();
}

var start = function(){
  var rst = document.getElementById("dt").value;
  if(rst.length == 0){
    var rst = new Date().getTime();
    document.getElementById("dt").value = new moment(rst).format("YYYY-MM-DDThh:mm");
  }
  rst = new Date(rst).getTime()

	loadFile("./getData?startTime=" + rst, function(res){
	    var data = JSON.parse(res);
	    /*var graphData =  [
		['data1', 30, 200, 100, 400, 150, 250],
		['data2', 50, 20, 10, 40, 15, 25]
	      ];*/

	var FinalData = [
		['Value'],

	]

	for (var i = 0; i < data.length; i++){
		var row = data[i];
		var v = row.v;

		FinalData[0].push(v);

	}

		 var chart = c3.generate({
		    bindto: '#chart',
		    data: {
		      columns: FinalData
		    }
		  }); 
	})
}