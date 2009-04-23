/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package fontbuilder;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStream;

/**
 *
 * @author jernej
 */
public class RawPackets {

    private int count = 0;
    private ByteArrayOutputStream packet = new ByteArrayOutputStream();

    public void addPixel(int value) throws IOException{
        ++count;
        packet.write(new byte[] {(byte)value,(byte)(value >>> 8),
                                 (byte)(value >>> 16), (byte)(value >>> 24)});
    }

    public void writePacket(OutputStream out) throws IOException{
        byte[] data = packet.toByteArray();
        int offset=0;
        if(count>128){
            out.write(127);
            out.write(data, 0, 512);
            offset = 512;
            count -= 128;
        }
        out.write(count-1);
        out.write(data, offset, count<<2);
        packet.reset();
        count = 0;
    }
}
