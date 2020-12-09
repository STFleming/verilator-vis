// Visualiser class
//
// Used to send visualisation information from the verilator simulation to the visualisation webserver  
#pragma once
#include <cstdint>
#include <cpprest/ws_client.h>
#include <string>

class Visualiser {
	public:
		Visualiser(std::string websocket_str) {
			m_websocket_str = websocket_str;
			const web::uri uri_server_addr = web::uri(m_websocket_str.c_str());
			auto contask = m_c.connect(uri_server_addr).then([](){});
			contask.wait();

			// Send a message to the frontend that a new simulation has started
            std::string start_cmd = "{ \"cmd\" : \"start\"}";
            send(start_cmd, false);
		}

		~Visualiser() {
            m_c.close().then([](){});
		}

        // sends the stop message to the frontend
        void halt(){
            std::string stop_cmd = "{ \"cmd\" : \"halt\" }"; // the command to tell the frontend that the simulation has completed
            send(stop_cmd, true);
        }

		// sends JSON to the visualiser
		void send(std::string s_msg, bool blocking=false){
		     web::websockets::client::websocket_outgoing_message msg;
		     msg.set_utf8_message(s_msg);
		     auto sendtask = m_c.send(msg).then([] {});

		     if(blocking) {
                          sendtask.wait();
		     }
		}

        // Get a reference to the websocket client -- this might not be the safest thing to do
        web::websockets::client::websocket_client * ws_client(){
            return &m_c;
        }   

	private:
		std::string m_websocket_str;
		web::websockets::client::websocket_client m_c;

};
