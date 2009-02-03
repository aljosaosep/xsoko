/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package leveleditor;

import java.awt.*;

/**
 *
 * @author jernej
 */

public class Elements{
    private String[] names = {"Tla","Neprebojni zid","Most","Nič/Prepad","Prostor za kocko","Enosmerna tla LEVO",
                              "Enosmerna tla DESNO","Enosmerna tla GOR","Enosmerna tla DOL","Teleport"};
    private byte[][] options = {{0,1,2,3,4,5,6,7,8},null,{0,1,2,3,4,5,6,7,8},null,{0,1,2,3,4,5,6,7,8},{0,1,2,3,4,5,6,7,8},
                                {0,1,2,3,4,5,6,7,8},{0,1,2,3,4,5,6,7,8},{0,1,2,3,4,5,6,7,8},null};
    private Image[] images = null;
    
    public Elements(){
        images = new Image[names.length];
        images[0] = Toolkit.getDefaultToolkit().getImage(Elements.class.getResource("resources/floor.png"));
        images[1] = Toolkit.getDefaultToolkit().getImage(Elements.class.getResource("resources/wall.png"));
        images[2] = Toolkit.getDefaultToolkit().getImage(Elements.class.getResource("resources/bridge.png"));
        images[3] = null;
        images[4] = Toolkit.getDefaultToolkit().getImage(Elements.class.getResource("resources/crate.png"));
        images[5] = Toolkit.getDefaultToolkit().getImage(Elements.class.getResource("resources/onewayfloorl.png"));
        images[6] = Toolkit.getDefaultToolkit().getImage(Elements.class.getResource("resources/onewayfloorr.png"));
        images[7] = Toolkit.getDefaultToolkit().getImage(Elements.class.getResource("resources/onewayflooru.png"));
        images[8] = Toolkit.getDefaultToolkit().getImage(Elements.class.getResource("resources/onewayfloord.png"));
        images[9] = Toolkit.getDefaultToolkit().getImage(Elements.class.getResource("resources/teleport.png"));
    }
    
    public String getName(byte id){
        return names[id];
    }
    
    public byte[] getOptions(byte id){
        return options[id];
    }
    
    public Image getImage(byte id){
        return images[id];
    }
    
    public int getNumElements(){
        return names.length;
    }
}
