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
public class Options {

    private String[] names = {"Nič","Igralec","Kocka","Enosmerna kocka LEVO","Enosmerna kocka DESNO",
                              "Enosmerna kocka GOR","Enosmerna kocka DOL","Bomba","Prebojni zid"};
    private Image[] images = null;
    
    public Options(){
        images = new Image[names.length];
        images[0] = null;
        images[1] = Toolkit.getDefaultToolkit().getImage(Elements.class.getResource("resources/player.png"));
        images[2] = Toolkit.getDefaultToolkit().getImage(Elements.class.getResource("resources/cube.png"));
        images[3] = Toolkit.getDefaultToolkit().getImage(Elements.class.getResource("resources/onewaycubel.png"));
        images[4] = Toolkit.getDefaultToolkit().getImage(Elements.class.getResource("resources/onewaycuber.png"));
        images[5] = Toolkit.getDefaultToolkit().getImage(Elements.class.getResource("resources/onewaycubeu.png"));
        images[6] = Toolkit.getDefaultToolkit().getImage(Elements.class.getResource("resources/onewaycubed.png"));
        images[7] = Toolkit.getDefaultToolkit().getImage(Elements.class.getResource("resources/bomb.png"));
        images[8] = Toolkit.getDefaultToolkit().getImage(Elements.class.getResource("resources/unsolidwall.png"));
    }
    
    public String getName(byte id){
        return names[id];
    }
    public Image getImage(byte id){
        return images[id];
    }
    
    public int getOptionsCount(){
        return names.length;
    }
}
