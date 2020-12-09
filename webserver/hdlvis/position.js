// A simple position class
//
// author: stf

class pos {
    construction(x,y) {
        this.x = x;
        this.y = y;
    }

    x() { return x; }
    y() { return y; }
    x(new_x) { this.x = new_x; }
    y(new_y) { this.y = new_y; }
}
