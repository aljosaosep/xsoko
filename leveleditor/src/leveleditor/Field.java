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

    @Override
    public boolean equals(Object obj){
        if(obj instanceof Field){
            Field temp = (Field)obj;
            if (temp.elemType == elemType && temp.option == option)
                return true;
            else
                return false;
        } else
            return false;
    }

    @Override
    public int hashCode() {
        int hash = 5;
        hash = 43 * hash + this.elemType;
        hash = 43 * hash + this.option;
        return hash;
    }
}
