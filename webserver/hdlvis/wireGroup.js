// wireGroup
// A class containing a grouping of wires.
// This are wires that can be enabled and disabled
// together.
//
// author: stf

class wireGroup {

    constructor(svg, colour, name) {
        this.svg = svg;
        this.colour = colour;
        this.name = name;

        this.wires = [];
    }

    append(wire){
        this.wires.push(wire);
    }

    // asserts the whole wire group
    assert() {
        this.wires.forEach(function (item, index) {
                item.assert();
        });
    }

    // deasserts the whole wire group
    deassert() {
        this.wires.forEach(function (item, index) {
                item.deassert();
        });
    }

}
