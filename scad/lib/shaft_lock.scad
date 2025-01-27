
module shaftlock(thickness, width, height, tol1, tol2) {
    cube([width+tol1, height+tol2, thickness+0.2], center=true);
 
    rotate([0, 0, -90]) {
        cube([width+tol1, height+tol2, thickness+0.2], center=true);
    }
}
