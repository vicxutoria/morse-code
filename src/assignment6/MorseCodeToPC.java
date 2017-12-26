package assignment6;

import jssc.SerialPortException;
 
public class MorseCodeToPC {
	public static void main(String[] args) throws SerialPortException {		
		// TODO:  Complete program to show "training messages" and decoded Morse code
		String portName = "/dev/cu.usbserial-DN035ZEU";
		char hash = '#';
		
		SerialComm port = new SerialComm(portName);

		
		String charInput= "";
		char currentChar = ' ';
	
		while(true){
			if(port.available()){
				char c = (char)port.readByte();	
				if(c == hash){
					charInput= "";
					currentChar = (char)port.readByte();
					while (currentChar != hash) {
						charInput += currentChar;
						currentChar = (char)port.readByte();
					}
					System.out.println(charInput);
				}
			
			}
			
		}
	}

}
