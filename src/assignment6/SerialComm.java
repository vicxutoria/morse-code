package assignment6;
 
import jssc.*;

public class SerialComm {

	SerialPort port;

	private boolean debug;  // Indicator of "debugging mode"
	
	// This function can be called to enable or disable "debugging mode"
	void setDebug(boolean mode) {
		debug = mode;
	}	
	

	// Constructor for the SerialComm class
	public SerialComm(String name) throws SerialPortException {
		port = new SerialPort(name);		
		port.openPort();
		port.setParams(SerialPort.BAUDRATE_9600,
			SerialPort.DATABITS_8,
			SerialPort.STOPBITS_1,
			SerialPort.PARITY_NONE);
		
		debug = false; // Default is to NOT be in debug mode
	}
		
	// TODO: Add writeByte() method that you created in Studio 5
	public void writeByte(byte b) throws SerialPortException {
		if (debug == true){
			port.writeByte(b);
			System.out.println("<0x" + String.format("%02x", b) + ">");
		}
	}
	// TODO: Add available() and readByte() that you created in Studio 6
	public boolean available() throws SerialPortException{
		if (port.getInputBufferBytesCount() > 0){
			return true;
		}
		else {
			return false;
		}
	}
	
	public byte readByte() throws SerialPortException {
		byte[] arr = port.readBytes(1);
		if(debug == false){
			return arr[0];
		}
		else{
			System.out.print("[0x" + String.format("%02x", arr[0]) + "]");
			return arr[0];
		}
	}
	
}
