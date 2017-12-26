package assignment5;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import jssc.SerialPortException;

public class PCToMorseCode {
	public static void main(String[] args) throws SerialPortException, IOException {		
		// TODO:  Fix this: 
		//           a) Uncomment to create a SerialComm object
		//           b) Update the "the port" to refer to the serial port you're using
		//              (The port listed in the Arduino IDE Tools>Port menu.		
		//           c) Deal with the unresolved issue
		SerialComm port = new SerialComm("/dev/cu.usbserial-DN02BJDS");

		
		// TODO: Complete section 6 of the Studio (gather sanitized user input
		//       and send it to the Arduino)
		
		
		while(true){
			BufferedReader inn = new BufferedReader(new InputStreamReader(System.in));
			String s = inn.readLine();
			
			for(int i = 0; i < s.length(); ++i){
				port.writeByte((byte)(s.charAt(i)));
			}
		}
	}

}
