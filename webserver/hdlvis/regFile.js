// register file visualiser
//
// author: stf


class regFile {

    constructor(svg, colour, x, y, name, num){
        // hard coded parameters
        this.reg_width = 20;
        this.reg_spacing = 10;
        this.reg_height = 80;
        this.port_dist = 80;
       
        this.svg = svg;
        this.colour = colour;
        this.x = x;
        this.y = y;
        this.name = name;
        this.num = num;

        this.reg_array = new regArray(this.svg, this.colour, this.x, this.y + this.port_dist, this.name+"_regarray", this.num); 

        this.draw();

    }

    drawPort(in_name, in_x, in_y) {
        this.svg.append("circle")
                .attr("id", in_name)
                .attr("cx", in_x) 
                .attr("cy", in_y)
                .attr("r", 5)
                .attr("stroke", this.colour.base)
                .attr("stroke-width", 1.5);
    }

    assertPort(name){
        d3.select("#"+name).attr("stroke", this.colour.highlight);
    }

    deassertPort(name){
        d3.select("#"+name).attr("stroke", this.colour.env);
    }

    drawWrWires(){
        this.wrWire1 = new wire(this.svg, this.colour, (this.x + (this.reg_width + this.reg_spacing)*this.num)/2, this.y + 5,
                                (this.x + (this.reg_width + this.reg_spacing)*this.num)/2, this.y + this.port_dist/2,
                                "wrport_wire1"
                                ); 
        this.wrWire2 = new wire(this.svg, this.colour, (this.x + (this.reg_width + this.reg_spacing)*this.num)/2, this.y + this.port_dist/2,
                                this.x + this.reg_width/2, this.y + this.port_dist/2,
                                "wrport_wire2"
                                ); 
        this.wrWire3 = new wire(this.svg, this.colour, this.x + this.reg_width/2, this.y + this.port_dist/2,
                                this.x + this.reg_width/2, this.y + this.port_dist - 10,
                                "wrport_wire3", true
                                ); 
        this.wrWires = new wireGroup(this.svg, this.colour, this.name+"_wrwires");
        this.wrWires.append(this.wrWire1);
        this.wrWires.append(this.wrWire2);
        this.wrWires.append(this.wrWire3);
    }

    drawSR0Wires(){
        this.sr0Wire1 = new wire(this.svg, this.colour, 
                                (this.x + (this.reg_width + this.reg_spacing)*this.num)/4, 
                                (this.y + (this.port_dist *2) + this.reg_height) - 5,
                                (this.x + (this.reg_width + this.reg_spacing)*this.num)/4, 
                                (this.y + (this.port_dist *2) + this.reg_height) - this.port_dist/2,
                                "sr0port_wire1"
                                ); 
        this.sr0Wire2 = new wire(this.svg, this.colour, 
                                (this.x + (this.reg_width + this.reg_spacing)*this.num)/4, 
                                (this.y + (this.port_dist *2) + this.reg_height) - this.port_dist/2,
                                (this.x + this.reg_width/2), 
                                (this.y + (this.port_dist *2) + this.reg_height) - this.port_dist/2,
                                "sr0port_wire2"
                                ); 
        this.sr0Wire3 = new wire(this.svg, this.colour,
                                (this.x + this.reg_width/2), 
                                (this.y + (this.port_dist*2) + this.reg_height) - this.port_dist/2,
                                (this.x + this.reg_width/2), 
                                (this.y + (this.port_dist *2) + this.reg_height) - this.port_dist + 10,
                                "sr0port_wire3", true
                                ); 
        this.sr0Wires = new wireGroup(this.svg, this.colour, this.name+"_sr0wires");
        this.sr0Wires.append(this.sr0Wire1);
        this.sr0Wires.append(this.sr0Wire2);
        this.sr0Wires.append(this.sr0Wire3);
    }

    drawSR1Wires(){
        this.sr1_offset = 10;
        this.sr1Wire1 = new wire(this.svg, this.colour, 
                                (this.x + 3*(this.reg_width + this.reg_spacing)*this.num)/4, 
                                (this.y + (this.port_dist *2) + this.reg_height) - 5,
                                (this.x + 3*(this.reg_width + this.reg_spacing)*this.num)/4, 
                                (this.y + (this.port_dist *2) + this.reg_height) - this.port_dist/2 - this.sr1_offset,
                                "sr1port_wire1"
                                ); 
        this.sr1Wire2 = new wire(this.svg, this.colour, 
                                (this.x + 3*(this.reg_width + this.reg_spacing)*this.num)/4, 
                                (this.y + (this.port_dist *2) + this.reg_height) - this.port_dist/2 - this.sr1_offset,
                                (this.x + this.reg_width/2), 
                                (this.y + (this.port_dist *2) + this.reg_height) - this.port_dist/2 - this.sr1_offset,
                                "sr1port_wire2"
                                ); 
        this.sr1Wire3 = new wire(this.svg, this.colour,
                                (this.x + this.reg_width/2), 
                                (this.y + (this.port_dist*2) + this.reg_height) - this.port_dist/2 - this.sr1_offset,
                                (this.x + this.reg_width/2), 
                                (this.y + (this.port_dist *2) + this.reg_height) - this.port_dist + 10,
                                "sr1port_wire3", true
                                ); 
        this.sr1Wires = new wireGroup(this.svg, this.colour, this.name+"_sr1wires");
        this.sr1Wires.append(this.sr1Wire1);
        this.sr1Wires.append(this.sr1Wire2);
        this.sr1Wires.append(this.sr1Wire3);
    }

    updateWrPos(reg) {
        this.wrWire2.endx(this.x + this.reg_width/2 + reg*(this.reg_width + this.reg_spacing));
        this.wrWire3.startx(this.x + this.reg_width/2 + reg*(this.reg_width + this.reg_spacing));
        this.wrWire3.endx(this.x + this.reg_width/2 + reg*(this.reg_width + this.reg_spacing));
    }

    assertWr(valid, reg){
       if(valid == 1) {
           this.assertPort(this.name+"_wrport");
           this.updateWrPos(reg);
           this.wrWires.assert();
       } else {
           this.deassertPort(this.name+"_wrport");
           this.wrWires.deassert();
       }
    }

    updateSR0(reg) {
        this.sr0Wire2.endx(this.x + this.reg_width/2 + reg*(this.reg_width + this.reg_spacing));
        this.sr0Wire3.startx(this.x + this.reg_width/2 + reg*(this.reg_width + this.reg_spacing));
        this.sr0Wire3.endx(this.x + this.reg_width/2 + reg*(this.reg_width + this.reg_spacing));
    }

    assertSR0(valid, reg) {
        if(valid == 1) {
            this.assertPort(this.name+"_sr0port");
            this.updateSR0(reg);
            this.sr0Wires.assert();
        } else {
            this.deassertPort(this.name+"_sr0port");
            this.sr0Wires.deassert();
        }
    }

    updateSR1(reg) {
        this.sr1Wire2.endx(this.x + this.reg_width/2 + reg*(this.reg_width + this.reg_spacing));
        this.sr1Wire3.startx(this.x + this.reg_width/2 + reg*(this.reg_width + this.reg_spacing));
        this.sr1Wire3.endx(this.x + this.reg_width/2 + reg*(this.reg_width + this.reg_spacing));
    }

    assertSR1(valid, reg) {
        if(valid == 1) {
            this.assertPort(this.name+"_sr1port");
            this.updateSR1(reg);
            this.sr1Wires.assert();
        } else {
            this.deassertPort(this.name+"_sr1port");
            this.sr1Wires.deassert();
        }
    }


    draw() {
        this.drawPort(this.name+"_wrport", (this.x + (this.reg_width + this.reg_spacing)*this.num)/2, this.y);
        this.drawWrWires();
        this.assertWr(1, 28);

        this.drawPort(this.name+"_sr0port", (this.x + (this.reg_width + this.reg_spacing)*this.num)/4, this.y + this.port_dist*2 + this.reg_height);
        this.drawSR0Wires();
        this.assertSR0(1, 13);

        this.drawPort(this.name+"_sr1port", (this.x + 3*(this.reg_width + this.reg_spacing)*this.num)/4, this.y + this.port_dist*2 + this.reg_height);
        this.drawSR1Wires();
    }


}
