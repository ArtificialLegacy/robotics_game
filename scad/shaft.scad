include <BOSL2/std.scad>

$fs=1;
$fa=0.5;

length=60;
width=3.8;
height=6.8;
edgeRadius=1;

difference() {
    // shaft body
    union() {
        cuboid(
            [width, height, length],
            rounding=edgeRadius,
            edges=[FWD+RIGHT,BACK+RIGHT,FWD+LEFT,BACK+LEFT]
        );

        rotate([0, 0, 90]) {
            cuboid(
                [width, height, length],
                rounding=edgeRadius,
                edges=[FWD+RIGHT,BACK+RIGHT,FWD+LEFT,BACK+LEFT]
            );
        }
    }

    translate([height/2, 0, 0]) {
        zcopies(spacing=2, n=length/2) {
            sphere(d=1.5, $fn=12);
        }
    }
    translate([-height/2, 0, 0]) {
        zcopies(spacing=2, n=length/2) {
            sphere(d=1.5, $fn=12);
        }
    }
 
    translate([0, height/2, 0]) {
        zcopies(spacing=2, n=length/2-1) {
            sphere(d=1.5, $fn=12);
        }
    }
    translate([0, -height/2, 0]) {
        zcopies(spacing=2, n=length/2-1) {
            sphere(d=1.5, $fn=12);
        }
    }
}
