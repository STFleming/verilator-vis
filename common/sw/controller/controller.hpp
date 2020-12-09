// Controller
// Waits for commands from the webfrontend to control how the simulation should progress
//
// author: stf
#pragma once
#include <cstdint>
#include <string>
#include <cpprest/ws_client.h>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "visualiser.hpp"
#include <unistd.h>

class Controller {

    public:
        Controller(Visualiser *vis) {
            m_c = vis->ws_client();

            m_running = false;
            m_load = false;
            m_booted = false;
            m_finsig = false;

            m_cycle_count = 0;
            m_cycle_target = 0;
        }

        bool parse(std::string s) {
            rapidjson::Document json_i;
            json_i.Parse<0>(s.c_str());

            if(!json_i.IsObject()){
                return false;
            }

            if(!json_i.HasMember("cmd")){
                fprintf(stderr, "error: cmd field not found on input json");
                return false;
            }


            std::string commandstr = json_i["cmd"].GetString();

            // Parse the commands and apply them to the sim play controls
            if(commandstr == "run"){
                m_cycle_target = m_cycle_count + json_i["steps"].GetInt(); 
                if(m_cycle_target > m_cycle_count){
                    m_running = true;
                }
                return true;
            }

            // execute until the program is fully loaded
            if(commandstr == "load"){
                m_load = true;
                return true;
            }

            // we've got the command to end the simulation
            if(commandstr == "end") {
                m_finsig = true;
                return true;
            }

            return false;
        }

        // block until we get an instruction 
        void listen(){
            bool recvd = false;

            while(!recvd) { 
                usleep(250000);
                // try and receive a command
                m_c->receive().then([&recvd,this](web::websockets::client::websocket_incoming_message msg) mutable {
                    return msg.extract_string();
                }).then([&recvd,this](std::string body) mutable {
                    if(parse(body)) {
                        recvd = true; 
                    } else { 
                       fprintf(stderr, "%s\n", body.c_str());
                    }
                });
            }

        }

        // tick -- controls the simulation tick
        // if it returns true then we end the simulation
        bool tick() {
            // run until we boot
           if(m_load){
               if(m_booted){
                   m_load = false;
               }
           } else {
               if(!m_running) {
                    listen(); // blocks here until we have a command
                } else {
                    m_cycle_count++;
                    if(m_cycle_count >= m_cycle_target){
                        m_running = false;
                    }
               }
           }

           return m_finsig;
        }

        void booted(){
            m_booted = true;
        }

    private:
        uint64_t m_cycle_target; // the simulation will run until this target value
        uint64_t m_cycle_count;
        bool m_running;
        bool m_load;
        bool m_booted;
        bool m_finsig;
        web::websockets::client::websocket_client* m_c;

};
