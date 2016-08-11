"use script;"

var rootBag={
  "idbDbName":"reso",
  "idbStoreName":"reso_core",
  "idbVersion" : 8
};

(function() {
    // This function immediately runs and all variables within here are private

function PageLoad(){
      //Get a reference to the link on the page
      // with an id of "mylink"
      var a = document.getElementById("myButton");


      //Set code to run when the link is clicked
      // by assigning a function to "onclick"
      var c=function() {
        //loadMyData();
        restCall("GET","/api/parcel", HandleMyData);
        //If you don't want the link to actually
        // redirect the browser to another page,
        // "google.com" in our example here, then
        // return false at the end of this block.
        // Note that this also prevents event bubbling,
        // which is probably what we want here, but won't
        // always be the case.
        return false;
      }

      a.onclick = c;
}
function HandleMyData(status, text) {
  document.getElementById("MyData").innerHTML="Record Count="+ text.length;

  var request = indexedDB.open(rootBag.idbDbName);
  request.onsuccess = function() {
    var db = request.result;
    var tx = db.transaction(rootBag.idbStoreName, "readwrite");
    var store = tx.objectStore(rootBag.idbStoreName);

    var len = text.length;
    var jtext = parseJSON(text);
    //store.put(jtext[0]);
    var i;
    for (i = 0; i < len; i++) {
      //var addReq  = store.add(jtext[i]);
      var addReq  = store.put(jtext[i]);
      request.onerror = function() {
        // The uniqueness constraint of the "by_title" index failed.
        alert(addReq.error);
      };
    }

    tx.oncomplete = function() {
      // All requests have succeeded and the transaction has committed.
      alert('All requests have succeeded and the transaction has committed');
    };
    tx.onerror = function(){
      alert('Transaction failed');
    };
    db.close();
  };

};

var request = indexedDB.open(rootBag.idbDbName,rootBag.idbVersion);

//for some reason this event is fired each reload
//this causes createObjectStore to throw
request.onupgradeneeded = function() {
  // The database did not previously exist, so create object stores and indexes.
  var db = request.result;
  var store = db.createObjectStore(rootBag.idbStoreName, {keyPath: 'Listing.ListingKey'});
    //  var titleIndex = store.createIndex("by_title", "title", {unique: true});
    //  var authorIndex = store.createIndex("by_author", "author");

  db.close();
};

//set events
window.onload = PageLoad;

}());
