include <BOSL2/std.scad>
include <BOSL2/gears.scad>
use <./lib/shaft_lock.scad>

$fa=1;
$fs=0.5;

teeth=7;

lockWidth=4;
lockHeight=7;
shaftTolerance=0.2;

gear_clearance=1.1;
gear_backlash=2;

d = outer_radius(circ_pitch=8, teeth=teeth) * 2  - gear_backlash;

difference() {
    spur_gear(
        circ_pitch=8, teeth=teeth, thickness=4,
        clearance=gear_clearance, backlash=gear_backlash
    );

    translate([0, 0, -2.1]) {
        difference() {
            cylinder(h=2.1, d=d);
            translate([0, 0, -0.1]) {
                cyl(h=2.3, d2=d, d1=d-6.75, center=false);
            }
        }
    }

    difference() {
        cylinder(h=2.1, d=d);
        translate([0, 0, -0.1]) {
            cyl(h=2.3, d1=d, d2=d-6.75, center=false);
        }
    }

    shaftlock(4, lockWidth, lockHeight, shaftTolerance, shaftTolerance);
}
