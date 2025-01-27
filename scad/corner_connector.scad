include <BOSL2/std.scad>

$fa=1;
$fs=0.5;

holeWidth = 2;
holeLengthA = 1;
holeLengthB = 1;

cornerRadius = 2;
edgeRadius = 2;

union() {
    cuboid([holeWidth * 10, 5, 5], anchor=[-1, -1, -1], rounding=edgeRadius, edges=[BOT+FWD]);

    translate([0, 0, 0]) {
        face(holeWidth, holeLengthA+1, [BACK+RIGHT, BACK+LEFT]);
    }

    translate([0, 5, 0]) {
        rotate([90, 0, 0]) {
            face(holeWidth, holeLengthB+1, [BACK+RIGHT, BACK+LEFT]);
        }
    }
}

module face(width, length, e) {
    difference() {
        translate([0, 5, 0]) {
            cuboid(
                [width*10, length*10 - 5, 5],
                anchor=[-1,-1,-1],
                rounding=cornerRadius,
                edges=e
            );
        }
        
        for (x = [1:1:length-1]) {
            for (y = [0:1:width-1]) {
                translate([5 + 10*y, 5 + 10*x, 2.5])
                    cylinder(h=5, r=1.75, center=true);
            }
        }
        
        for (x = [0:1:length-2]) {
            for (y = [0:1:width-2]) {
                translate([10 + 10*y, 10 + 10*x, 2.5])
                    cylinder(h=5, r=4, center=true);
            }
        }
    }
}
