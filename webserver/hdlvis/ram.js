// Library for visualising a RAM module in hdlvis
// Data is all stored in string format because it's primary purpose is for rendering visualisations of the
// underlying circuit
//
// author: stf

class hdlRAM {

    // svg - the drawing canvas
    // numAddr - the number of addresses
    // x - x location of the RAM
    // y - y location of the RAM
    // name - unique name given to the RAM
    constructor(svg, colour, numAddr, x, y, name) {
        this.colour = colour;

        // some set parameters (need to think of a nicer way to do this)
        this.itemHeight = 15; // height per RAM item
        this.ramWidth = 150; // total width of the ram
        this.portDist = 150;

        this.svg = svg;
        this.numAddr = numAddr;
        this.x = x;
        this.y = y;
        this.name = name;
        this.data = [];

        this.totalHeight = this.itemHeight * this.numAddr;

        // setup the data array
        for(var i=0; i<numAddr; i++){
            this.data.push("");
        }

        this.draw();
        this.populate();

        // -=-=-=-=-=-- The write port -=-=-=-=-=-=-=-=-=-
        this.prev_addr = 0;
        this.prev_data = "";
        this.prev_item = false; // there is an item to write from last cycle

        // Wires for the write port
        this.wrWire1 = new wire(this.svg, this.colour, this.x-this.portDist-5, this.y + this.totalHeight/2, 
                                                       this.x-(3*this.portDist)/4, this.y + this.totalHeight/2,
                               this.name+"_wrWire1");
            
        this.wrWire2 = new wire(this.svg, this.colour, this.x-(3*this.portDist)/4, this.y + this.totalHeight/2, 
                                                       this.x-(3*this.portDist)/4, this.y + this.itemHeight/2,
                               this.name+"_wrWire2");
        this.wrWire3 = new wire(this.svg, this.colour, this.x-(3*this.portDist)/4, this.y + this.itemHeight/2, 
                                                       this.x-this.portDist/4 - 15, this.y + this.itemHeight/2,
                               this.name+"_wrWire3", true);
        this.drawPort("wrport", this.getWrX(), this.getWrY()); // draws the write port for the RAM

        this.wrWires = new wireGroup(this.svg, this.colour, "wrWires");
        this.wrWires.append(this.wrWire1);
        this.wrWires.append(this.wrWire2);
        this.wrWires.append(this.wrWire3);
        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            
        // -=-=-=-=-=-- The read cmd port -=-=-=-=-=-=-=-=-=-
        this.rdCmdWire1 = new wire(this.svg, this.colour, this.x+this.ramWidth+this.portDist+5, this.y + this.totalHeight/2, 
                                                       this.x+this.ramWidth+(3*this.portDist)/4, this.y + this.totalHeight/2,
                               this.name+"_rdCmdWire1");
            
        this.rdCmdWire2 = new wire(this.svg, this.colour, this.x+this.ramWidth+(3*this.portDist)/4, this.y + this.totalHeight/2, 
                                                       this.x+this.ramWidth+(3*this.portDist)/4, this.y + this.itemHeight/2,
                               this.name+"_rdCmdWire2");
        this.rdCmdWire3 = new wire(this.svg, this.colour, this.x+this.ramWidth+(3*this.portDist)/4, this.y + this.itemHeight/2, 
                                                       this.x+this.ramWidth+this.portDist/4 - 15, this.y + this.itemHeight/2,
                               this.name+"_rdCmdWire3", true);
        this.drawPort("rdcmdport", this.getRdCmdX(), this.getRdCmdY()); // draws the read cmd port port for the RAM

        this.rdCmdWires = new wireGroup(this.svg, this.colour, "rdCmdWires");
        this.rdCmdWires.append(this.rdCmdWire1);
        this.rdCmdWires.append(this.rdCmdWire2);
        this.rdCmdWires.append(this.rdCmdWire3);
        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           
        // -=-=-=-=-=-- The read data port -=-=-=-=-=-=-=-=-=-
        this.rdDataWire = new wire(this.svg, this.colour, 
                                   this.x+this.ramWidth/2,
                                   this.y+this.totalHeight,
                                   this.x+this.ramWidth/2,
                                   this.y+this.totalHeight+this.portDist/2);
        this.drawPort("rddataport", this.getRdDataX(), this.getRdDataY()); 
        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            
    }
 
    // get the write port location
    getWrX() { return (this.x - this.portDist); }
    getWrY() { return (this.y + this.totalHeight/2); }
  
    // get rd_cmd port location
    getRdCmdX() { return this.x + this.portDist + this.ramWidth; }
    getRdCmdY() { return this.y + this.totalHeight/2; }

    // get rd_data port location
    getRdDataX() { return this.x + this.ramWidth/2; }
    getRdDataY() { return this.y + this.totalHeight + this.portDist/2; }

    assertPort(portname){
        d3.select("#"+this.name+"_"+portname).attr("stroke", this.colour.highlight);
    }

    deassertPort(portname){
        d3.select("#"+this.name+"_"+portname).attr("stroke", this.colour.base);
    }

    drawPort(portname, x, y) {
        console.log("Drawing a port at: "+x+","+y);
        this.svg.append("circle")
                .attr("id", this.name+"_"+portname)
                .attr("cx", x)
                .attr("cy", y)
                .attr("r", 5)
                .attr("stroke", this.colour.base)
                .attr("stroke-width", 1.0)
                .attr("fill", this.colour.env);
    }

    // clears the stored data in the RAM
    clearData(){
        for(var i=0; i<this.numAddr; i++) {
            this.data[i] = "";
            d3.selectAll("#"+this.name+"_datatext_"+String(i)).remove();
        }
    }

    // draws the RAM
    draw() {
        this.svg.append("text")
                .attr("id", this.name+"_ramlabel")
                .attr("x", this.x+10)
                .attr("y", this.y -10)
                .text(this.name)
                .attr("font-family", "sans-serif")
                .attr("font-size", "18px")
                .attr("fill", this.colour.base);

        this.svg.append("rect")
           .attr("id", this.name+"_membox")                                
           .attr("x", this.x)
           .attr("y", this.y)
           .attr("fill", this.colour.env)
           .attr("stroke", this.colour.base)
           .attr("stroke-width", 1.5)
           .attr("width", this.ramWidth)
           .attr("height", this.totalHeight);

        // Append all the lines
        for(var i=0; i<this.numAddr; i++){
            this.svg.append("rect")
               .attr("id", this.name+"_itembox_"+String(i))                                
               .attr("x", this.x)
               .attr("y", this.y + (i*this.itemHeight))
               .attr("fill", this.colour.env)
               .attr("stroke", this.colour.base)
               .attr("stroke-width", 0.5)
               .style("stroke-dasharray", ("3,3"))
               .attr("width", this.ramWidth)
               .attr("height", this.itemHeight);
        }

        // Append all the address labels
        for(var i=0; i<this.numAddr; i++) {
            var addr_str = "0x"+ i.toString(16);

            this.svg.append("text")
                    .attr("id", this.name+"_addrlabel_"+String(i))
                    .attr("x", this.x-30)
                    .attr("y", this.y + ((i+1)*this.itemHeight) - 3)
                    .text(addr_str)
                    .attr("font-family", "sans-serif")
                    .attr("font-size", "12px")
                    .attr("fill", this.colour.base);
        }

    }

    // removes the rendering of the RAM
    remove() {
        d3.selectAll("#"+this.name+"_membox").remove();
        d3.selectAll("#"+this.name+"_ramlabel").remove();
        for(var i=0; i<this.numAddr; i++) {
            d3.selectAll("#"+this.name+"_itembox_"+String(i)).remove();
            d3.selectAll("#"+this.name+"_datatext_"+String(i)).remove();
            d3.selectAll("#"+this.name+"_addrlabel_"+String(i)).remove();
        }
    }

    // populate -- draws the data currently stored in the RAM
    populate() {
        for(var i=0; i<this.numAddr; i++){
            this.svg.append("text")
                    .attr("id", this.name+"_datatext_"+String(i))
                    .attr("x", this.x+5)
                    .attr("y", this.y + ((i+1)*this.itemHeight) - 3)
                    .text(this.data[i])
                    .attr("font-family", "sans-serif")
                    .attr("font-size", "12px")
                    .attr("fill", this.colour.base);
        }
    }

    // write port TODO: Add addr bounds checks here 
    // It updates the item the call later
    write(write_enable, addr, data) {
        this.wrWires.deassert();
        this.deassertPort("wrport")
        for(var i=0; i<this.numAddr; i++) {
            d3.select("#"+this.name+"_itembox_"+String(i)).attr("fill", this.colour.env);
            d3.select("#"+this.name+"_itembox_"+String(addr)).attr("opacity", 1.0);
        }

        if(this.prev_item){
            d3.select("#"+this.name+"_itembox_"+String(this.prev_addr)).attr("fill", this.colour.highlight);
            d3.select("#"+this.name+"_itembox_"+String(this.prev_addr)).attr("opacity", 0.3);
            d3.select("#"+this.name+"_datatext_"+String(this.prev_addr)).remove();

            this.svg.append("text")
                    .attr("id", this.name+"_datatext_"+String(this.prev_addr))
                    .attr("x", this.x+5)
                    .attr("y", this.y + ((this.prev_addr+1)*this.itemHeight) - 3)
                    .text(this.prev_data)
                    .attr("font-family", "sans-serif")
                    .attr("font-size", "12px")
                    .attr("fill", this.colour.base);

            this.data[this.prev_addr] = this.prev_data;
        }

        if(write_enable == 1){
            // the write channel is active
            this.wrWires.assert();
            this.assertPort("wrport");
            this.wrWire2.endy(this.y + ((addr+1)*this.itemHeight) - this.itemHeight/2);
            this.wrWire3.starty(this.y + ((addr+1)*this.itemHeight) - this.itemHeight/2);
            this.wrWire3.endy(this.y + ((addr+1)*this.itemHeight) - this.itemHeight/2);
            
            this.prev_item = true;
            this.prev_addr = addr;
            this.prev_data = data;
        } else {
            this.prev_item = false;
        }
    }

    // Read command port, where are we fetching data from
    readCmd(valid, addr){
        this.rdCmdWires.deassert();
        this.deassertPort("rdcmdport");
        if(valid == 1) {
                this.assertPort("rdcmdport");
                this.rdCmdWires.assert();
                this.rdCmdWire2.endy(this.y + ((addr+1)*this.itemHeight) - this.itemHeight/2);
                this.rdCmdWire3.starty(this.y + ((addr+1)*this.itemHeight) - this.itemHeight/2);
                this.rdCmdWire3.endy(this.y + ((addr+1)*this.itemHeight) - this.itemHeight/2);
        }
    }

   // Read Data Port
   readData(valid, data) {
        this.rdDataWire.deassert();
        this.deassertPort("rddataport");
        if (valid == 1) {
             this.assertPort("rddataport");
             this.rdDataWire.assert();
        }
   }

}

