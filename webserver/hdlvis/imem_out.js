// imem_out
// shows the current instruction at the output of the instruction memory
//
// author: stf

class imemOut{

        constructor(svg, colour, x, y, name, pc, cancel_y){
                this.svg = svg;
                this.colour = colour;
                this.x = x;
                this.y = y;

                this.cancel_y = cancel_y; // the x pos of the cancel signal
                
                this.pc = pc; // reference to the program counter

                this.draw();
        }

        draw(){
                this.svg.append("rect")
                        .attr("id", this.name+"_boundbox")
                        .attr("x", this.x - 30 )
                        .attr("y", this.y - 20)
                        .attr("width", 170)
                        .attr("height", 35)
                        .attr("stroke", this.colour.base)
                        .attr("stroke-dasharray", ("3,3"));

                // Wire to the program counter
                this.biWire1 = new wire(this.svg, this.colour,
                                        this.x + 145, this.y,
                                        this.pc.getBiX() + 60, this.y,
                                        this.name + "_biwire1", false
                                       );

                this.biWire2 = new wire(this.svg, this.colour,
                                        this.pc.getBiX() + 60, this.y,
                                        this.pc.getBiX() + 60, this.pc.getBiY(),  
                                        this.name + "_biwire2", false 
                                       );

                this.biWire3 = new wire(this.svg, this.colour,
                                        this.pc.getBiX() + 60, this.pc.getBiY(),  
                                        this.pc.getBiX() + 5,  this.pc.getBiY(),
                                        this.name + "_biwire3", true 
                                       );

                this.biWire_mux = new wire(this.svg, this.colour,
                                        this.pc.getBiX() + 60, this.pc.getBiY() + 40,  
                                        this.pc.getBiX() - 85,  this.pc.getBiY() + 40,
                                        this.name + "_biwire_mux", true 
                                       );



                this.biWires = new wireGroup(this.svg, this.colour, this.name + "_biwires"); 
                this.biWires.append(this.biWire1);
                this.biWires.append(this.biWire2);
                this.biWires.append(this.biWire3);
                this.biWires.append(this.biWire_mux);

                this.svg.append("text")
                        .attr("id", this.name+"_text")
                        .attr("x", this.x)
                        .attr("y", this.y)
                        .attr("fill", this.colour.base)
                        .text("")
                        .attr("font-family", "sans-serif")
                        .attr("font-size", "18px")
                        .attr("fill", this.colour.base); 

               // Wire from the cancel signal
               this.cancelWire = new wire(this.svg, this.colour,
                                          this.x + 40, this.cancel_y,
                                          this.x + 40, this.y + 25,
                                          "imem_cancelwire", true);

        }

        biAssert(valid){
               if(valid == 1)
                    this.biWires.assert();
               else
                    this.biWires.deassert();

        }

        cancelInst(valid) {
            if(valid == 1) { 
                d3.select("#" +this.name +"_text").attr("text-decoration", "line-through");
                this.cancelWire.assert();
            } else {
                d3.select("#" +this.name +"_text").attr("text-decoration", "");
                this.cancelWire.deassert();
            }
        }

        updateInst(new_text) {
                d3.select("#"+this.name+"_text").text(new_text);
        }

        remove() {
                d3.select("#"+this.name+"_text").remove();
        }
}
