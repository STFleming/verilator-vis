// shows an N-bit register
//
// author: stf

class regN {

    constructor(svg, colour, x, y, name){
        // hard coded paramters
        this.height = 80;
        this.width = 20;

        this.svg = svg;
        this.colour = colour;
        this.x = x;
        this.y = y;
        this.name = name;

        this.draw();
    }

    name() { return this.name; }

    value(v) { this.value = v; } 
    value()  { return this.value; }

    draw() {
        this.svg.append("rect")
                .attr("id", this.name+"_regbox")
                .attr("x", this.x)
                .attr("y", this.y)
                .attr("width", this.width)
                .attr("height", this.height)
                .attr("stroke-width", "1.0")
                .attr("stroke", this.colour.base);

              // Register clocked
              this.svg.append("line")
                      .attr("id", this.name + "_regbox")
                      .attr("stroke", this.colour.base)
                      .attr("stroke-width", 0.6) 
                      .attr("x1", this.x + 5)
                      .attr("y1", this.y + (3*this.height)/4)
                      .attr("x2", this.x + 5 + 5)
                      .attr("y2", this.y + (3*this.height)/4 - 5)

              this.svg.append("line")
                      .attr("id", this.name + "_regbox")
                      .attr("stroke", this.colour.base)
                      .attr("stroke-width", 0.6) 
                      .attr("x1", this.x + 5)
                      .attr("y1", this.y + (3*this.height)/4)
                      .attr("x2", this.x + 5 + 5)
                      .attr("y2", this.y + (3*this.height)/4 + 5)
    }

    remove(){
        d3.selectAll("#"+this.name+"_regbox").remove();
    }

}
