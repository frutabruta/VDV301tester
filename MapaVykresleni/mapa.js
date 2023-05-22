var stred = SMap.Coords.fromWGS84(14.41, 50.08);
var mapa = new SMap(JAK.gel("mapa"), stred, 15);
mapa.addDefaultLayer(SMap.DEF_BASE).enable();
mapa.addDefaultControls();




/* nachystame dve vrstvy: pro znacky a pro cary */
var vyparsovanyJson = JSON.parse(dataj);
znackyPole = vyparsovanyJson.polozky;

var q = 0;

for (var k = 0; k < znackyPole.length; k++) {
    var mLayer = new SMap.Layer.Marker();
    var gLayer = new SMap.Layer.Geometry();
    var tLayer = new SMap.Layer.Geometry();
    var kLayer = new SMap.Layer.Geometry();

    var souradnicovySystem = znackyPole[k].souradnicovySystem;


    if (znackyPole[k].vykresliTrasu) {
        mapa.addLayer(tLayer).enable();
    }

    if (znackyPole[k].vykresliBody) {
        mapa.addLayer(mLayer).enable();
    }

    if (znackyPole[k].vykresliSpojnici) {
        mapa.addLayer(gLayer).enable();
    }

    if (znackyPole[k].vykresliRadius) {
        mapa.addLayer(kLayer).enable();
    }


    znacky = znackyPole[k].data;
    //console.log(znacky);
    console.log(znacky.length);
    var lineCoords = [];
    console.log("k=", k);

    if (znacky.length > 0) {
        for (var i = 0; i < znacky.length; i++) {
            console.log("i=", i);


            var cardData = znacky[i];
            var coords2;
            if (souradnicovySystem == "WGS84") {
                coords2 = SMap.Coords.fromWGS84(cardData.lng, cardData.lat);
            }
            else {
                coords2 = SMap.Coords.fromJTSK(cardData.lng, cardData.lat);
            }



            lineCoords.push(coords2);

            /* vyrobit znacku */
            var rodic = JAK.mel("div");
            var obrazek = JAK.mel("img", { src: SMap.CONFIG.img + "/marker/drop-red.png" });
            rodic.appendChild(obrazek);

            var popisek = JAK.mel("div", {}, { position: "absolute", left: "0px", top: "2px", textAlign: "center", width: "22px", color: "white", fontWeight: "bold" });
            popisek.innerHTML = cardData.kapka;
            rodic.appendChild(popisek);

            var marker = new SMap.Marker(coords2, null, { title: cardData.title, url: rodic });
            var card = new SMap.Card();

            card.getHeader().innerHTML = cardData.title;
            card.getBody().innerHTML = cardData.cont;
            marker.decorate(SMap.Marker.Feature.Card, card);

            mLayer.addMarker(marker);
            const polomer = 0.1;
            if (typeof cardData.radius !== 'undefined') {
                var circle0 = kruznice(coords2, cardData.radius);
                kLayer.addGeometry(circle0);

            }
        }
            var line = new SMap.Geometry(SMap.GEOMETRY_POLYLINE, null, lineCoords);
            gLayer.addGeometry(line);
            q = q + 1;

           
        
         mapa.setCenter(lineCoords[0]);
    }
    else {
        console.log("datova sada je prazdna");
    }



}

//znackyPole.forEach((znacky) => {vykresli(znacky)});

function closeMe() {
    window.open("", "_self");
    window.close();
}


var box = document.createElement("div");
//box.innerHTML = "<button></button><textarea></textarea><button><strong>Vykreslit</strong></button>";

box.innerHTML = vyparsovanyJson.popis;

// <h1>spoj</h1><table><tr><td>linka</td><td>337</td></tr><tr><td>spoj</td><td>1007</td></tr></table>
box.id = "boxik";
mapa.getContainer().appendChild(box);
