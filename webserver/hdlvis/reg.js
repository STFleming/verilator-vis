// A simple 1-bit register
//
// author: stf

class oneBitReg {

        constructor(svg, colour, name, x, y, in_y, out_x) {
                // constant hardcoded parameters
                this.width = 30;
                this.height = 70;

                this.svg = svg;
                this.colour = colour;
                this.name = name;
                this.x = x;
                this.y = y;

                this.in_y = in_y;
                this.out_x = out_x;

                this.draw();

                // input wire
                this.inWire = new wire(svg, colour, 
                                       this.x + this.width/2,
                                       this.in_y,
                                       this.x + this.width/2,
                                       this.y - 5,
                                       this.name + "_inwire",
                                       true);

               // output wire
               this.outWire = new wire(svg, colour,
                                       this.x,
                                       this.y + this.height/2,
                                       this.out_x,
                                       this.y + this.height/2,
                                       this.name + "_outwire");
        }

        assertInput(valid) {
            if(valid == 1)
             this.inWire.assert();
            else 
             this.inWire.deassert();
        }

        assertOutput(valid) {
            if(valid == 1)
                this.outWire.assert();
            else
                this.outWire.deassert();
        }
        
        outX() { return this.out_x; }
        outY() { return this.y + this.height/2; }

        draw() {
                this.svg.append("rect")
                        .attr("id", this.name+"_regbox")
                        .attr("x", this.x)
                        .attr("y", this.y)
                        .attr("width", this.width)
                        .attr("height", this.height)
                        .attr("stroke", this.colour.base)
                        .attr("stroke-width", 1.0); 

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
        
}
