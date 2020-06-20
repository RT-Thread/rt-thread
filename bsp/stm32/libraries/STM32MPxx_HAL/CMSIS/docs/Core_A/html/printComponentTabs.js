var strgURL =   location.pathname;                      // path of current component

// constuctor for the array of objects
function tabElement(id, folderName, tabTxt )  {
	this.id = id;                                       // elementID as needed in html; 
	this.folderName = folderName;                       // folder name of the component 
    this.tabTxt = tabTxt;                               // Text displayed as menu on the web
	this.currentListItem = '<li id="' + this.id + '" class="current"> <a href="../..' + this.folderName + 'index.html"><span>' + this.tabTxt + '</span></a></li>';
	this.listItem = '<li id="' + this.id + '"> <a href="../..' + this.folderName + 'index.html"><span>' + this.tabTxt + '</span></a></li>';
};

// array of objects
var arr = [];

// fill array
 arr.push( new tabElement( "GEN",     "/General/html/",     "General")   );
 arr.push( new tabElement( "CORE_A",  "/Core_A/html/",      "CMSIS-Core(A)")    );
 arr.push( new tabElement( "CORE_M",  "/Core/html/",        "CMSIS-Core(M)")    );
 arr.push( new tabElement( "DRV",     "/Driver/html/",      "Driver")    );
 arr.push( new tabElement( "DSP",     "/DSP/html/",         "DSP")       );
 arr.push( new tabElement( "NN",      "/NN/html/",          "NN")       );
 arr.push( new tabElement( "RTOSv1",  "/RTOS/html/",        "RTOS v1")   );
 arr.push( new tabElement( "RTOSv2",  "/RTOS2/html/",       "RTOS v2")   );
 arr.push( new tabElement( "PACK",    "/Pack/html/",        "Pack")      );
 arr.push( new tabElement( "SVD",     "/SVD/html/",         "SVD")       );
 arr.push( new tabElement( "DAP",     "/DAP/html/",         "DAP")       );
 arr.push( new tabElement( "ZONE",    "/Zone/html/",        "Zone")      );
 
// write tabs
// called from the header file.
function writeComponentTabs()  {
  for ( var i=0; i < arr.length; i++ ) {
    if (strgURL.search(arr[i].folderName) > 0) {                    // if this is the current folder
      document.write(arr[i].currentListItem);                       // then print and hightlight the tab
    } else {                                                      
      document.write(arr[i].listItem);                              // else, print the tab
    }                                                             
  }
};
