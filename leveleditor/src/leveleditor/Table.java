/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package leveleditor;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.*;

/**
 *
 * @author jernej
 */
public class Table extends JComponent{
    
    private Hashtable<Integer,Hashtable<Integer,Field>> table = null;
    private int cols = 0;
    private int rows = 0;
    private Point selectedCell = null;
    private ArrayList<ChangeListener> listeners = null;
    private final int fieldSize = 64;
    private HashMap<Byte,Image> typeImages = null;
    private HashMap<Byte,Image> optImages = null;
    private ArrayList<TeleportTranslation> teleportsMapping = null;
    private ArrayList<Point> teleportList = null;
    
    public Table(Elements el,Options opt,int width, int height){
        this.cols = width;
        this.rows = height;
        listeners = new ArrayList<ChangeListener>();
        teleportsMapping = new ArrayList<TeleportTranslation>();
        teleportList = new ArrayList<Point>();
        table = new Hashtable<Integer, Hashtable<Integer, Field>>();
        for(int i=0;i<width;i++){
            Hashtable<Integer,Field> tempTable = new Hashtable<Integer,Field>();
            for(int j=0;j<height;j++){
                tempTable.put(j,new Field());
            }
            table.put(i,tempTable);
        }
        typeImages = new HashMap<Byte, Image>();
        for(byte i=0;i<el.getNumElements();i++){
            typeImages.put(i, el.getImage(i));
        }
        optImages = new HashMap<Byte, Image>();
        for(byte i=0;i<opt.getOptionsCount();i++){
            optImages.put(i, opt.getImage(i));
        }
        setSize(cols*fieldSize+1, rows*fieldSize+1);
        setFocusable(true);
        addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
               requestFocusInWindow();
               Point newSel = new Point();
               newSel.x = e.getPoint().x/fieldSize;
               newSel.y = e.getPoint().y/fieldSize;
               if(newSel.x < cols && newSel.y < rows){
                   selectedCell = newSel;
                   repaint();
                   for(int i=0;i<listeners.size();i++){
                       listeners.get(i).SelectedCell(selectedCell);
                   }
               }
            }
        });
        addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if(selectedCell== null)
                    return;
                boolean changed = false;
                if(e.getKeyCode()==KeyEvent.VK_DOWN && selectedCell.y<rows-1){
                    selectedCell.y++;
                    changed = true;
                }
                if(e.getKeyCode()==KeyEvent.VK_UP && selectedCell.y>0){
                    selectedCell.y--;
                    changed = true;
                }
                if(e.getKeyCode()==KeyEvent.VK_RIGHT && selectedCell.x<cols-1){
                    selectedCell.x++;
                    changed = true;
                }
                if(e.getKeyCode()==KeyEvent.VK_LEFT && selectedCell.x>0){
                    selectedCell.x--;
                    changed = true;
                }
                repaint();
                if(changed){
                    for(int i=0;i<listeners.size();i++){
                       listeners.get(i).SelectedCell(selectedCell);
                   }
                }
            }
        });
    }
    
    public void LoadFromFile(File file){
        try {
            selectedCell = null;
            teleportsMapping.clear();
            BufferedReader input = new BufferedReader(new FileReader(file));
            String line = input.readLine();
            StringTokenizer lineTokens = new StringTokenizer(line);
            cols = Integer.parseInt(lineTokens.nextToken());
            rows = Integer.parseInt(lineTokens.nextToken());
            for(int i=0;i<cols;i++){
                Hashtable<Integer,Field> tempTable = new Hashtable<Integer,Field>();
                for(int j=0;j<rows;j++){
                    tempTable.put(j,new Field());
                }
                table.put(i,tempTable);
            }
            for(int i=0;i<listeners.size();i++){
               listeners.get(i).SizeChange(cols, rows);
            }
            Hashtable<Byte,Point> mapping = new Hashtable<Byte, Point>();
            for(int i=0;i<rows;i++){
                line = input.readLine();
                lineTokens = new StringTokenizer(line);
                for(int j=0;j<cols;j++){
                    Byte elem = Byte.parseByte(lineTokens.nextToken());
                    if(elem>=9){
                        TeleportTranslation tel = new TeleportTranslation();
                        tel.src = new Point(j, i);
                        mapping.put(elem,tel.src);
                        teleportList.add(tel.src);
                        teleportsMapping.add(tel);
                        elem = 9;
                    }
                    table.get(j).get(i).elemType = elem;
                }
            }
            line = input.readLine();
            for(int i=0;i<rows;i++){
                line = input.readLine();
                lineTokens = new StringTokenizer(line);
                for(int j=0;j<cols;j++){
                    table.get(j).get(i).option = Byte.parseByte(lineTokens.nextToken());
                }
            }
            line = input.readLine();
            int telCount = Integer.parseInt(input.readLine());
            for(int i=0;i<telCount;i++){
                lineTokens = new StringTokenizer(input.readLine());
                byte srcID = Byte.parseByte(lineTokens.nextToken());
                byte destID = Byte.parseByte(lineTokens.nextToken());
                for(int j=0;j<teleportsMapping.size();j++){
                    if(mapping.get(srcID).equals(teleportsMapping.get(j).src)){
                        teleportsMapping.get(j).dest = mapping.get(destID);
                    }
                }
            }
        } catch (Exception ex) {
            Logger.getLogger(Table.class.getName()).log(Level.SEVERE, null, ex);
            ex.printStackTrace();
        }
        repaint();
    }
    
    public void addSelectListener(ChangeListener listener){
        listeners.add(listener);
    }
    
    public Field getSelectedCellValue(){
        if(selectedCell!=null){
            return new Field(table.get(selectedCell.x).get(selectedCell.y));
        } else {
            return null;
        }
    }
    
    public Field getValue(int x,int y){
        return new Field(table.get(x).get(y));
    }
    
    public void setSelectedCellOption(byte value){
        table.get(selectedCell.x).get(selectedCell.y).option = value;
        repaint();
    }
    
    public void setSelectedCellType(byte value){
        Field type = table.get(selectedCell.x).get(selectedCell.y);
        if(type.elemType == 9){
            teleportList.remove(selectedCell);
            for(int i=0;i<teleportsMapping.size();i++)
                if(teleportsMapping.get(i).src.equals(selectedCell) ||
                   teleportsMapping.get(i).dest.equals(selectedCell)){
                    teleportsMapping.remove(i);
                }
        }
        if(value == 9){
            teleportList.add(selectedCell);
        }
        type.elemType = value;
        repaint();
    }
    
    public void resizeWidth(int width){
        if(width<1) return;
        if(this.cols<width){
            for(int i=this.cols;i<width;i++){
                Hashtable<Integer,Field> list = new Hashtable<Integer, Field>();
                for(int j=0;j<rows;j++){
                    list.put(j,new Field());
                }
                table.put(i,list);
            }
        } else {
            for(int i=this.cols;i>width;i--){
                table.remove(i);
            }
        }
        this.cols = width;
        repaint();
    }
    
    public void resizeHeight(int height){
        if(height<1) return;
        if(this.rows<height){
            for(int i=0;i<cols;i++){
                Hashtable<Integer,Field> list = table.get(i);
                for(int j=this.rows;j<height;j++){
                    list.put(j,new Field());
                }
            }
        } else {
            for(int i=0;i<cols;i++){
                for(int j=this.rows;j>height;j--){
                    table.get(i).remove(j);
                    }
            }
        }
        this.rows = height;
        repaint();
    }
    
    @Override
    public void paintComponent(Graphics g){
        if(getWidth()<cols*fieldSize+1 || getHeight()<rows*fieldSize+1){
            setPreferredSize(new Dimension(cols*fieldSize+1, rows*fieldSize+1));
            setSize(cols*fieldSize+1, rows*fieldSize+1);
        }
        g.clearRect(0, 0, getWidth(), getHeight());
        for(int i=0;i<cols+1;i++){
            g.drawLine(i*fieldSize, 0, i*fieldSize, rows*fieldSize);
        }
        for(int i=0;i<rows+1;i++){
            g.drawLine(0, i*fieldSize,cols*fieldSize,i*fieldSize);
        }
        for(int i=0;i<cols;i++)
            for(int j=0;j<rows;j++){
                Image img = null;
                Field cell = table.get(i).get(j);
                if(cell.option>0)
                    img = optImages.get(cell.option);
                else
                    img = typeImages.get(cell.elemType);
                if(img!=null){
                    g.drawImage(img,i*fieldSize , j*fieldSize, this);
                }
            }
        if(selectedCell!=null){
           Graphics2D g2d = (Graphics2D) g;
           g2d.setColor(Color.BLUE); 
           g2d.setStroke(new BasicStroke(3)); 
           g2d.drawRect(selectedCell.x*fieldSize, selectedCell.y*fieldSize, fieldSize, fieldSize); 
           g2d.setColor(Color.BLACK); 
           g2d.setStroke(new BasicStroke(1));
        }
    }
    
    public void ShowTeleportManager(){
        if(teleportList.size() == 0){
            JOptionPane.showMessageDialog(null, "Nimate nobenega teleporta!");
            return;
        }
        if(teleportList.size() == 1){
            JOptionPane.showMessageDialog(null, "Imate samo en teleport! Dodajte še enega ali izbrišite obstoječega.");
            return;
        }
        if(teleportList.size() == 2){
            JOptionPane.showMessageDialog(null, "Teleporta sta lahko povezana samo med sabo!");
            if(teleportsMapping.size()!=2){
                teleportsMapping.clear();
                teleportsMapping.add(new TeleportTranslation(teleportList.get(0),teleportList.get(1)));
                teleportsMapping.add(new TeleportTranslation(teleportList.get(1),teleportList.get(0)));
            }
            return;
        }
        new TeleportManager(teleportsMapping, teleportList).setVisible(true);
    }
    
    public void SaveToFile(File file) throws IOException{
        if(teleportList.size() == 1){
            JOptionPane.showMessageDialog(null, "Shranjevanje neuspešno!\nImate samo en teleport; dodajte še enega ali izbrišite obstoječega.");
            return;
        }
        if(teleportList.size() == 2){
            if(teleportsMapping.size()!=2){
                teleportsMapping.clear();
                teleportsMapping.add(new TeleportTranslation(teleportList.get(0),teleportList.get(1)));
                teleportsMapping.add(new TeleportTranslation(teleportList.get(1),teleportList.get(0)));
            }
        }
        if(teleportList.size() != teleportsMapping.size()){
            new TeleportManager(teleportsMapping, teleportList).setVisible(true);
            if(teleportList.size() != teleportsMapping.size()){
                JOptionPane.showMessageDialog(null, "Shranjevanje neuspešno!\nTeleporti morajo imeti vsi nastavljene destinacije!");
                return;
            }
        }
        FileWriter writer = new FileWriter(file);
        writer.write(cols+" "+rows+"\n");
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                byte elem = table.get(j).get(i).elemType;
                if(elem == 9){
                    elem += teleportList.indexOf(new Point(j,i));
                }
                writer.write(Byte.toString(elem));
                if(j<cols-1)
                    writer.write(" ");
            }
            writer.write("\n");
        }
        writer.write("+\n");
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                writer.write(Byte.toString(table.get(j).get(i).option));
                if(j<cols-1)
                    writer.write(" ");
            }
            writer.write("\n");
        }
        writer.write("+\n"+teleportsMapping.size()+"\n");
        for(int i=0;i<teleportsMapping.size();i++){
            int src = 9 + teleportList.indexOf(teleportsMapping.get(i).src);
            int dest = 9 + teleportList.indexOf(teleportsMapping.get(i).dest);
            writer.write(src+" "+dest+"\n");
        }
        writer.close();
    }

}