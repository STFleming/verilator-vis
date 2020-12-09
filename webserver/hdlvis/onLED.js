// onLED
// An LED to show when the system has booted and started
//
// author: stf

class onLED{

        constructor(svg, colour, x, y, name) {
                // constant parameters
                this.border = 3;
                this.size = 8;

                this.svg = svg;
                this.colour = colour;
                this.x = x;
                this.y = y;
                this.name = name;

                this.draw();
        }

        draw() {
                this.svg.append("circle")
                        .attr("id", this.name + "_ledlight")
                        .attr("cx", this.x)
                        .attr("cy", this.y)
                        .attr("r", this.size)
                        .attr("fill", colour.env)
                        .attr("opacity", 0.4)
                        .style("stroke", "#808080")
                        .style("stroke-width", this.border);

                this.svg.append("text")
                        .attr("id", this.name + "_ontext")
                        .attr("x", this.x + this.size + 5)
                        .attr("y", this.y + this.size/2 + 5)
                        .text("ON")
                        .attr("opacity", 0.4)
                        .attr("font-family", "sans-serif")
                        .attr("font-size", "18px")
                        .attr("fill", "#808080");
        }

        on() { 
                d3.select("#"+this.name+"_ontext").attr("fill", colour.base);
                d3.select("#"+this.name+"_ledlight").attr("fill", colour.base); 
        }

        off() { 
                d3.select("#"+this.name+"_ontext").attr("fill", "#202020");
                d3.select("#"+this.name+"_ledlight").attr("fill", colour.env); 
        }

        remove() {
                d3.select("#"+this.name+"_ontext").remove();
                d3.select("#"+this.name+"_ledlight").remove(); 
        }

}
