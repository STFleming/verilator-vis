// Wire 
// This is a wire class that can be enabled or disabled based on the data coming out of the
// hardware.
//
// author: stf

class wire{

    constructor(svg, colour, x1, y1, x2, y2, name, arrow=false){
        // hard coded parameters
        this.width = 1.0;

        this.svg = svg;
        this.colour = colour;
        this.x1 = x1;
        this.x2 = x2;
        this.y1 = y1;
        this.y2 = y2;
        this.name = name;

        this.arrow = arrow; // if true then we draw an arrow at the end 

        this.draw();
    }

    startx(pos) {
        d3.select("#"+this.name+"_wireinst").attr("x1", pos);
    }

    endx(pos) {
        d3.select("#"+this.name+"_wireinst").attr("x2", pos);
    }

    starty(pos) {
        d3.select("#"+this.name+"_wireinst").attr("y1", pos);
    }

    endy(pos) {
        d3.select("#"+this.name+"_wireinst").attr("y2", pos);
    }

    assert() {
        d3.selectAll("#"+this.name+"_wireinst").attr("stroke", colour.highlight);
        d3.selectAll("#"+this.name+"_wire_arrow").attr("stroke", colour.highlight);
        d3.selectAll("#"+this.name+"_wire_arrow").attr("fill", colour.highlight);
    }

    deassert() {
        d3.selectAll("#"+this.name+"_wireinst").attr("stroke", colour.base);
        d3.selectAll("#"+this.name+"_wire_arrow").attr("stroke", colour.base);
        d3.selectAll("#"+this.name+"_wire_arrow").attr("fill", colour.base);
    }

    draw() {
        
        if(this.arrow) {
                var arrowPoints = [[0, 0], [0, 10], [10, 5]];

                var markerBoxWidth = 10
                var markerBoxHeight = 10
                var refX = markerBoxWidth / 2
                var refY = markerBoxHeight / 2
                var markerWidth = markerBoxWidth / 2;
                var markerHeight = markerBoxHeight / 2;

                this.svg
                    .append('defs')
                    .append('marker')
                    .attr('id', this.name+'_wire_arrow')
                    .attr('viewBox', [0, 0, markerBoxWidth, markerBoxHeight])
                    .attr('refX', refX)
                    .attr('refY', refY)
                    .attr('markerWidth', markerBoxWidth)
                    .attr('markerHeight', markerBoxHeight)
                    .attr('orient', 'auto-start-reverse')
                    .append('path')
                    .attr('d', d3.line()(arrowPoints))
                    .attr("fill", this.colour.base)
                    .attr('stroke', this.colour.base);

             this.svg.append("line")
                     .attr("id", this.name+"_wireinst")
                     .attr("stroke", this.colour.base)
                     .attr("stroke-width", this.width)
                     .attr("marker-end", "url(#"+this.name+"_wire_arrow)")
                     .attr("x1", this.x1)
                     .attr("y1", this.y1)
                     .attr("x2", this.x2)
                     .attr("y2", this.y2);

        } else {
            this.svg.append("line")
                    .attr("id", this.name+"_wireinst")
                    .attr("stroke", this.colour.base)
                    .attr("stroke-width", this.width)
                    .attr("x1", this.x1)
                    .attr("y1", this.y1)
                    .attr("x2", this.x2)
                    .attr("y2", this.y2);
        }

    }

    remove(){
        d3.selectAll("#"+this.name+"_wireinst").remove();
    }
}
