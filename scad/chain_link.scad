include <BOSL2/std.scad>

$fa=1;
$fs=0.25;

edgeRadius=1;

snapWidth=0.2;
fullCutoutHeight=1.3;

innerpin=2;
pinTolerance=0.45;

difference() {
    union() {
        // left outer plate
        cuboid([1, 6, 5], anchor=[-1, -1, -1], rounding=2.5, edges=[TOP+FWD, BOT+FWD]);
        translate([0, 6, 0])  {
            cuboid([1, 1, 5], anchor=[-1, -1, -1], chamfer=1, edges=[BACK+LEFT]);
        }

        // right outer plate
        translate([8, 0, 0]) {
            cuboid([1, 6, 5], anchor=[-1, -1, -1], rounding=2.5, edges=[TOP+FWD, BOT+FWD]);
        }
        translate([8, 6, 0]) {
            cuboid([1, 1, 5], anchor=[-1, -1, -1], chamfer=1, edges=[BACK+RIGHT]);
        }

        // inner plates
        translate([1.5, 7, 0]) {
            cuboid([1, 6, 5], anchor=[-1, -1, -1], rounding=2.5, edges=[TOP+BACK, BOT+BACK]);
        }
        translate([6.5, 7, 0]) {
            cuboid([1, 6, 5], anchor=[-1, -1, -1], rounding=2.5, edges=[TOP+BACK, BOT+BACK]);
        }

        // inner chamfers
        translate([1, 6.25, 0]) {
            cuboid([1.5, 0.75, 5], anchor=[-1, -1, -1], chamfer=0.75, edges=[FWD+RIGHT]);
        }
        translate([6.5, 6.25, 0]) {
            cuboid([1.5, 0.75, 5], anchor=[-1, -1, -1], chamfer=0.75, edges=[FWD+LEFT]);
        }

        // outer pin
        translate([2, 10.5, 2.5]) {
            rotate([0, 90, 0]) {
                cylinder(h=5, d=5);
            }
        }

        // inner pin
        translate([1, 2.5, 2.5]) {
            rotate([0, 90, 0]) {
                cylinder(h=7, d=innerpin);
            }
        }
    }
 
    // inner pin slot
    translate([0.9, 10.5, 2.5]) {
        rotate([0, 90, 0]) {
            cylinder(h=7.2, d=innerpin+pinTolerance);
        }
    }

    // snap cutout
    translate([0.9, 10.25-(innerpin-snapWidth)/2, 2.5]) {
        cube([7.2, innerpin-snapWidth, 3.6]);
    }

    // full cutout
    translate([0.9, 10.25-(innerpin+pinTolerance)/2, 5.1-fullCutoutHeight]) {
        cuboid([7.2, innerpin+pinTolerance, fullCutoutHeight], anchor=[-1, -1, -1], rounding=1, edges=[BOT+FWD, BOT+BACK]);
    }
}
