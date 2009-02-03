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
public class TeleportTranslation {
    public Point src;
    public Point dest;

    public TeleportTranslation() {
    }

    public TeleportTranslation(Point src, Point dest) {
        this.src = src;
        this.dest = dest;
    }
}
