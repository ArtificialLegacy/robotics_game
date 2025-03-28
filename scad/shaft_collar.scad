include <BOSL2/std.scad>

use <./lib/shaft_lock.scad>

$fa=1;
$fs=0.5;

thickness=2;
width=2;

cornerRadius=2;

lockWidth=4;
lockHeight=7;
shaftTolerance=0.2;

dimple=0.8;

cutout=0.6;

radius=lockHeight/2+width;

union() {
    difference() {
        // collar body and shaft lock
        translate([radius, radius, 0]) {
            cylinder(h=thickness, d=lockHeight+width*2);
        }
        translate([radius, radius, thickness/2]) {
            shaftlock(thickness, lockWidth, lockHeight, shaftTolerance, shaftTolerance);
        }

         // cutout
        translate([radius, width*1.5+lockHeight-0.1, thickness/2]) {
            cuboid([cutout, width+0.2, thickness+0.2]);
        }
    }

    // dimples
    translate([radius-lockHeight/2-shaftTolerance/2, radius, thickness/2]) {
        sphere(d=dimple, $fn=12);
    }
    translate([radius+lockHeight/2+shaftTolerance/2, radius, thickness/2]) {
        sphere(d=dimple, $fn=12);
    }
}
