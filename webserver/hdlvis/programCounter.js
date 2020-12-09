// class used to visualise the program counter
//
// author: stf

class programCounter {

    constructor(svg, colour, x, y, name, width, height) {
        this.svg = svg;
        this.x = x;
        this.y = y;
        this.name = name;
        this.width = width;
        this.height = height;
        
        this.colour = colour;
        
        this.value = 0; // The value currently stored in the programCounter

        this.draw();
    }

    draw() {
       this.svg.append("rect")
           .attr("id", this.name+"_box")                                
           .attr("x", this.x)
           .attr("y", this.y)
           .attr("fill", this.colour.env)
           .attr("stroke", this.colour.base)
           .attr("stroke-width", 1.5)
           .attr("width", this.width)
           .attr("height", this.height);

        this.svg.append("text")
                .attr("id", this.name+"_label")
                .attr("x", this.x - 15)
                .attr("y", this.y - 15)
                .text(this.name)
                .attr("font-family", "sans-serif")
                .attr("font-size", "18px")
                .attr("fill", this.colour.base);

        this.svg.append("text")
                .attr("id", this.name+"_data")
                .attr("x", this.x + - 35)
                .attr("y", this.y + this.height/2 - 10 )
                .text("0x"+this.value.toString(16))
                .attr("font-family", "sans-serif")
                .attr("font-size", "16px")
                .attr("fill", this.colour.base);

        // draw the increment input
        this.drawInc();

        // draw the output of the PC block
        this.drawOutput();
    }

    drawOutput(){
        this.outWire = new wire(this.svg, this.colour,
                                this.x,
                                this.y + this.height/2,
                                this.x - 35,
                                this.y + this.height/2,
                                this.name + "_outwire",
                                true);
    }

    drawInc(){
       this.svg.append("rect")
           .attr("id", this.name+"_incbox")                                
           .attr("x", this.x + 100)
           .attr("y", this.y + this.height/2 - 30)
           .attr("fill", this.colour.env)
           .attr("stroke", this.colour.base)
           .attr("stroke-width", 1.5)
           .attr("width", 30)
           .attr("height", 30);

        this.svg.append("line")
                .attr("id", this.name+"_inline")
                .attr("stroke", this.colour.base)
                .attr("stroke-width", 1.5)
                .attr("x1", this.x+100)
                .attr("y1", this.y + this.height/2 - 15)
                .attr("x2", this.x + this.width)
                .attr("y2", this.y + this.height/2 - 15);

        this.svg.append("text")
                .attr("id", this.name+"_incboxtext")
                .attr("x", this.x+100 + 5)
                .attr("y", this.y + this.height/2 - 10)
                .text("+1")
                .attr("font-family", "sans-serif")
                .attr("font-size", "18px")
                .attr("fill", this.colour.base);
    }

    getBiX() { return this.x + this.width; }
    getBiY() { return this.y + (3*this.height)/4;  }

    incActive(active_sig){
       if(active_sig == 1){
            d3.select("#"+this.name+"_incbox").attr("stroke", this.colour.highlight);
            d3.select("#"+this.name+"_inline").attr("stroke", this.colour.highlight);
            d3.select("#"+this.name+"_incboxtext").attr("fill", this.colour.highlight);
       } else {
            d3.select("#"+this.name+"_incbox").attr("stroke", this.colour.base);
            d3.select("#"+this.name+"_inline").attr("stroke", this.colour.base);
            d3.select("#"+this.name+"_incboxtext").attr("fill", this.colour.base);
       }
    }

    updateVal(value) {
        this.value = value;
        d3.select("#"+this.name+"_data").text("0x"+value.toString(16));
    }

    remove() {
        d3.select("#"+this.name+"_box").remove();
        d3.select("#"+this.name+"_label").remove();
        d3.select("#"+this.name+"_data").remove();
        d3.select("#"+this.name+"_incbox").remove();
        d3.select("#"+this.name+"_inline").remove();
        d3.select("#"+this.name+"_incboxtext").remove();
    }

}
