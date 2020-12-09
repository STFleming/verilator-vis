// Creates an array of regN
//
// author: stf

class regArray{

    constructor(svg, colour, x, y, name, num) {
        // hard coded parameters
        this.spacing = 10;
        this.reg_width = 20;

        this.svg = svg;
        this.colour = colour;
        this.x = x;
        this.y = y;
        this.name = name;
        this.num = num;

        this.registers = [];

        this.draw();
    }

    value(reg, val) { this.registers[reg].value(val); } // sets the value of a register

    draw(){
        for(var i=0; i<this.num; i++) {
            var reg = new regN(this.svg, this.colour, this.x + i*(this.spacing) + i*this.reg_width, this.y, this.name+"_reg_"+i); 
            this.registers.push(reg);
        }
    }

    remove() {
        for(var i=0; i<this.register.length; i++) {
            d3.select("#"+this.register[i].name()).remove();
        }
    }

}
