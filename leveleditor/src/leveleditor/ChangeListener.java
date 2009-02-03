/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package leveleditor;

import java.awt.Point;

/**
 *
 * @author jernej
 */
public interface ChangeListener {
    
    public void SelectedCell(Point cell);
    public void SizeChange(int cols, int rows);

}
