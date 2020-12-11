// fifo_fwft visualisation class
//
// author: stf


// The visualisation class
class fifo_fwft {

    constructor(svg, colour, x, y, name) {
        // hard coded parameters
        this.width = 250;
        this.height = 50;
        this.field_width = 20;

        this.svg = svg;
        this.colour = colour;
        this.x = x;
        this.y = y;
        this.name = name;

        this.data = [];
        this.uniqueid = 0;
        this.curr_disp = []; // list of the uniqueids currently on display

        this.draw();
    }

    // the write channel
    write(valid, item) {
        if(valid == 1)
            this.push(item);
    }

    read(valid) {
        if(valid == 1)
            this.pop();
    }

    pop() { 
        var poppeditem = this.curr_disp.shift();
        d3.select("#"+this.name+"_field_"+poppeditem)
          .transition()
          .attr("x", this.x + this.width + 75)
          .duration(500);

        d3.select("#"+this.name+"_field_text_"+poppeditem)
          .transition()
          .attr("x", this.x + this.width + 75)
          .duration(500);

        var that = this;
        setTimeout(function() {
             d3.select("#"+that.name+"_field_"+poppeditem).remove();
             d3.select("#"+that.name+"_field_text_"+poppeditem).remove();
        }, 500);
        
        var dat_last = this.data.shift(); 

        var new_item = this.curr_disp.length;
        // Shift everything in down by one and add the newest one 
        for(var i=0; i <this.curr_disp.length; i++) {
            d3.select("#"+this.name+"_field_"+this.curr_disp[i]).attr("x", this.x + this.width - (this.field_width*(i+1))); 
            d3.select("#"+this.name+"_field_text_"+this.curr_disp[i]).attr("x", this.x + this.width + 5 - (this.field_width*(i+1))); 
        }
    }

    // Adds an item to the fifo
    push(item) {
        this.data.push(item);
        this.uniqueid = this.uniqueid + 1;

        if( (this.width/this.field_width - this.data.length) > 1) {
            this.curr_disp.push(this.uniqueid);

            this.svg.append("rect")
                    .attr("id", this.name+"_field_"+this.uniqueid)
                    .attr("x", this.x - 75)
                    .attr("y", this.y)
                    .attr("width", this.field_width)
                    .attr("height", this.height)
                    .attr("stroke", this.colour.base)
                    .attr("stroke-width", 0.8)
                    .transition()
                    .attr("x", this.x + this.width - this.field_width*this.data.length)
                    .duration(500);

            // Add a text element for this node also 
            this.svg.append("text")
                    .attr("id", this.name+"_field_text_"+this.uniqueid)
                    .attr("x", this.x + 5 -75)
                    .attr("y", this.y + this.height/2)
                    .text(item)
                    .attr("font-family", "sans-serif")
                    .attr("font-size", "12px")
                    .attr("fill", this.colour.base)
                    .transition()
                    .attr("x", this.x + this.width + 5 - this.field_width*this.data.length)
                    .duration(500);
        } else {

            this.svg.append("rect")
                    .attr("id", this.name+"_temp_item")
                    .attr("x", this.x - 75)
                    .attr("y", this.y)
                    .attr("width", this.field_width)
                    .attr("height", this.height)
                    .attr("stroke", this.colour.base)
                    .attr("stroke-width", 0.8)
                    .transition()
                    .attr("x", this.x)
                    .duration(500);

            // Add a text element for this node also 
            this.svg.append("text")
                    .attr("id", this.name+"_temp_item")
                    .attr("x", this.x + 5 -75)
                    .attr("y", this.y + this.height/2)
                    .text(item)
                    .attr("font-family", "sans-serif")
                    .attr("font-size", "14px")
                    .attr("fill", this.colour.base)
                    .transition()
                    .attr("x", this.x + 5)
                    .duration(500);

            var that = this;
            setTimeout( function() {
                d3.selectAll("#"+that.name+"_temp_item").remove();
            }, 500);

           // draw three circles 
           for(var i=0; i<3; i++) {
               this.svg.append("circle")
                       .attr("id", this.name+"_cont_circle")
                       .attr("cx", this.x + 10 + i*5)
                       .attr("cy", this.y+this.height/2)
                       .attr("r", 1)
                       .attr("fill", this.colour.base)
                       .attr("stroke", this.colour.base);
           }

        }

    }

    draw() {
        this.svg.append("rect")
                .attr("id", this.name+"_fifobox")
                .attr("x", this.x)
                .attr("y", this.y)
                .attr("width", this.width)
                .attr("height", this.height)
                .attr("stroke", this.colour.base)
                .attr("stroke-width", 1.0);

        this.inwire = new wire(this.svg, this.colour, 
                               this.x - 75, 
                               this.y + this.height/2, 
                               this.x - 10, 
                               this.y + this.height/2, 
                               this.name+"_inwire", true);

        this.outwire = new wire(this.svg, this.colour, 
                               this.x + this.width+5, 
                               this.y + this.height/2, 
                               this.x + this.width+75, 
                               this.y + this.height/2, 
                               this.name+"_outwire", true);

    }

}
