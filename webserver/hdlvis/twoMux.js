// A two input MUX visualisation
//
// author: stf

class twoMux {
    constructor(svg, colour, x, y, name) {
        // hardcoded parameters
        this.x_len = 20;
        this.y_len = 120; 
        this.y_diff = 20;

        this.svg = svg;
        this.colour = colour;
        this.x = x;
        this.y = y;

        this.name = name;

        this.draw();
    }

    in1_X() { return this.x + this.x_len; }
    in1_Y() { return this.y + this.y_len/4; }

    in2_X() { return this.x + this.x_len; }
    in2_Y() { return this.y + (3*this.y_len)/4; }

    draw() {
        
        // output side
        this.svg.append("line")
                .attr("id", this.name+"_muxbox")
                .attr("x1", this.x)
                .attr("y1", this.y + this.y_diff)
                .attr("x2", this.x)
                .attr("y2", this.y + this.y_len - this.y_diff)
                .attr("stroke", this.colour.base)
                .attr("stroke-width", 1.5);
        
        // input side
        this.svg.append("line")
                .attr("id", this.name+"_muxbox")
                .attr("x1", this.x + this.x_len)
                .attr("y1", this.y)
                .attr("x2", this.x + this.x_len)
                .attr("y2", this.y + this.y_len)
                .attr("stroke", this.colour.base)
                .attr("stroke-width", 1.5);

        // top angled
        this.svg.append("line")
                .attr("id", this.name+"_muxbox")
                .attr("x1", this.x)
                .attr("y1", this.y + this.y_diff)
                .attr("x2", this.x + this.x_len)
                .attr("y2", this.y)
                .attr("stroke", this.colour.base)
                .attr("stroke-width", 1.5);

        // bottom angled
        this.svg.append("line")
                .attr("id", this.name+"_muxbox")
                .attr("x1", this.x)
                .attr("y1", this.y + this.y_len - this.y_diff)
                .attr("x2", this.x + this.x_len)
                .attr("y2", this.y + this.y_len)
                .attr("stroke", this.colour.base)
                .attr("stroke-width", 1.5);

    }

}
