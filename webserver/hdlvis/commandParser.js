// commandParser 
// used to send commands to the simulation and for a textual
// exploration of the running hardware
//
// author: stf

class commandParser {


    constructor(svg, colour, socket) {
           this.svg = svg;
           this.colour = colour;
           this.socket = socket;

           this.cnt = 0;
           this.max = 0;
    }

    // =--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // Playback commands
    // =--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    playrun(){
        if(this.cnt == this.max){
            return;
        }

        this.cnt = this.cnt + 1;
        var run_json = "{\"cmd\":\"run\", \"steps\":1 }"; // advance the simulation by 1 cycle     
        socket.send(run_json);

        setTimeout( () => {   this.playrun();
        }, 1000);
    }

    // plays n cycles at a slower rate
    playcmd(arg) {
        if(isNaN(parseInt(arg))) {
            return false;
        }
        this.cnt = 0;
        this.max = parseInt(arg);
        
        this.playrun();

        return true;
    }
    // =--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    // steps through n cycles instantaneously
    runcmd(arg) {
        if(isNaN(parseInt(arg))) {
            return false;
        }
    
        var run_json = "{\"cmd\":\"run\", \"steps\":"+ parseInt(arg) +" }"; // advance the simulation by 1 cycle     
        socket.send(run_json);

        return true;
    }


    // ##################################
    // The Load command
    // runs the processor until the power
    // on switch is pressed (filling the 
    // instruction memory)
    // ##################################
    load() {
        var run_json = "{\"cmd\":\"load\"}"; // advance the simulation until the power on button is pressed     
        socket.send(run_json);

        return true;
    }
    // ##################################

    // \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
    // The end command -- ends the sim    
    // \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
    end() {
        var run_json = "{\"cmd\":\"end\"}"; // advance the simulation until the power on button is pressed     
        socket.send(run_json);
        return true;
    }
    // \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

    parse(input) {
        var cmd = input.split(" ");
        console.log(cmd);
        switch(cmd[0]) {
            case "step" :
                   return this.runcmd(cmd[1]); 
            case "s" :
                   return this.runcmd(cmd[1]); 
            case "play":
                return this.playcmd(cmd[1]);
            case "p":
                return this.playcmd(cmd[1]);
            case "load":
                return this.load();
            case "end":
                return this.end();

            default:
                return false;
        }
    }

}
