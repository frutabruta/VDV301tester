function druhyBod(distance, x, y) {
    distance=distance/1000;
    console.log("distance"+distance);
    var equator = 6378 * 2 * Math.PI;    /* delka rovniku (km) */
    var yrad = Math.PI * y / 180;        /* zemepisna sirka v radianech */
    var line = equator * Math.cos(yrad); /* delka rovnobezky (km) na ktere lezi stred kruznice */
    var angle = 360 * distance / line;       /* o tento uhel se po rovnobezce posuneme */

    var x2 = x + angle;
    var point2 = SMap.Coords.fromWGS84(x2, y);
    return point2;

}

function kruznice(bod, polomer) {
    
    console.log(bod);
    var circle = new SMap.Geometry(SMap.GEOMETRY_CIRCLE, null, [bod, druhyBod(polomer, bod.x, bod.y)]);
    return circle;
}

