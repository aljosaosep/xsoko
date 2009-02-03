/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package leveleditor;

/**
 *
 * @author jernej
 */
public class Field {
    
    public byte elemType, option;
    
    public Field(){
        elemType = 3;
        option = 0;
    }
    
    public Field(Field f){
        elemType = f.elemType;
        option = f.option;
    }
}
