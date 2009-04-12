/*
 * LeveleditorView.java
 */

package leveleditor;

import java.awt.event.ItemEvent;
import java.io.IOException;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jdesktop.application.Action;
import org.jdesktop.application.SingleFrameApplication;
import org.jdesktop.application.FrameView;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;

/**
 * The application's main frame.
 */
public class LeveleditorView extends FrameView {

    private ArrayList<JRadioButton> options = null;
    private Hashtable<Byte,JRadioButton> types = null;
    private Table map = null;
    private Elements elem = new Elements();
    private Options opts = new Options();
    
    public LeveleditorView(SingleFrameApplication app) {
        super(app);
        initComponents();
        
        options = new ArrayList<JRadioButton>();
        for(byte i=0;i<opts.getOptionsCount();i++)
            addOption(opts,i);
        typePanel.setLayout(new BoxLayout(typePanel, BoxLayout.Y_AXIS));
        types = new Hashtable<Byte, JRadioButton>();
        for(byte i=0;i<elem.getNumElements();i++)
            addType(elem,i);
        typePanel.setVisible(false);
        map = new Table(elem,opts,10, 10);
        map.addSelectListener(new ChangeListener() {
            public void SelectedCell(/*Point selCell*/) {
                Field cell = map.getSelectedCellValue(); //map.getValue(selCell.x, selCell.y);
                typePanel.setVisible(true);
                if(jSplitPane1.getDividerLocation()<250){
                    jSplitPane1.setDividerLocation(250);
                }
                if(cell != null){
                    types.get(cell.elemType).setSelected(true);
                    options.get(cell.option).setSelected(true);
                } else {
                    typeGroup.clearSelection();
                    optionPanel.setVisible(false);
                }
            }

            public void SizeChange(int cols, int rows) {
                mwidth.setValue(cols);
                mheight.setValue(rows);
            }
        });
        optionPanel.setLayout(new BoxLayout(optionPanel,BoxLayout.Y_AXIS));
        jScrollPane1.getViewport().add(map);
    }
    
    private void addOption(Options opt, byte index){
        JRadioButton tempComp = new JRadioButton(opt.getName(index));
        if(options.size()==0)
            tempComp.setSelected(true);
            tempComp.addItemListener(new java.awt.event.ItemListener() {
            public void itemStateChanged(java.awt.event.ItemEvent evt) {
                if(evt.getStateChange() == ItemEvent.SELECTED){
                    map.setSelectedCellOption((byte)options.indexOf(evt.getSource()));
                    map.repaint();
                }
            }
        });
        optionGroup.add(tempComp);
        options.add(tempComp);
    }
    
    
    private void addType(final Elements el,final byte index){
        JRadioButton tempComp = new JRadioButton(el.getName(index));
        tempComp.addItemListener(new java.awt.event.ItemListener() {
            public void itemStateChanged(java.awt.event.ItemEvent evt) {
                if(evt.getStateChange() == ItemEvent.SELECTED){
                    map.setSelectedCellType(index);
                    map.repaint();
                    byte[] opt = el.getOptions(index);
                    optionPanel.removeAll();
                    options.get(map.getSelectedCellValue().option).setSelected(true);
                    if(opt!=null){
                        optionPanel.setVisible(true);
                        jSplitPane1.setDividerLocation(270);
                        for(int i=0;i<opt.length;i++){
                            optionPanel.add(options.get(opt[i]));
                        }
                    }
                    optionPanel.revalidate();
                    optionPanel.repaint();
                }
            }
        });
        typeGroup.add(tempComp);
        types.put(index,tempComp);
        typePanel.add(tempComp);
    }


    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        mainPanel = new javax.swing.JPanel();
        jToolBar1 = new javax.swing.JToolBar();
        jLabel1 = new javax.swing.JLabel();
        mwidth = new javax.swing.JSpinner();
        jLabel2 = new javax.swing.JLabel();
        mheight = new javax.swing.JSpinner();
        jPanel1 = new javax.swing.JPanel();
        jSplitPane1 = new javax.swing.JSplitPane();
        typePanel = new javax.swing.JPanel();
        optionPanel = new javax.swing.JPanel();
        jScrollPane1 = new javax.swing.JScrollPane();
        menuBar = new javax.swing.JMenuBar();
        javax.swing.JMenu fileMenu = new javax.swing.JMenu();
        jMenuItem1 = new javax.swing.JMenuItem();
        jMenuItem3 = new javax.swing.JMenuItem();
        javax.swing.JMenuItem exitMenuItem = new javax.swing.JMenuItem();
        jMenu1 = new javax.swing.JMenu();
        jMenuItem2 = new javax.swing.JMenuItem();
        typeGroup = new javax.swing.ButtonGroup();
        optionGroup = new javax.swing.ButtonGroup();

        mainPanel.setName("mainPanel"); // NOI18N

        jToolBar1.setRollover(true);
        jToolBar1.setName("jToolBar1"); // NOI18N

        org.jdesktop.application.ResourceMap resourceMap = org.jdesktop.application.Application.getInstance(leveleditor.LeveleditorApp.class).getContext().getResourceMap(LeveleditorView.class);
        jLabel1.setText(resourceMap.getString("jLabel1.text")); // NOI18N
        jLabel1.setName("jLabel1"); // NOI18N
        jToolBar1.add(jLabel1);

        mwidth.setModel(new javax.swing.SpinnerNumberModel(Integer.valueOf(10), Integer.valueOf(5), null, Integer.valueOf(1)));
        mwidth.setName("mwidth"); // NOI18N
        mwidth.setPreferredSize(new java.awt.Dimension(75, 28));
        mwidth.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                mwidthStateChanged(evt);
            }
        });
        jToolBar1.add(mwidth);

        jLabel2.setText(resourceMap.getString("jLabel2.text")); // NOI18N
        jLabel2.setName("jLabel2"); // NOI18N
        jToolBar1.add(jLabel2);

        mheight.setModel(new javax.swing.SpinnerNumberModel(Integer.valueOf(10), Integer.valueOf(5), null, Integer.valueOf(1)));
        mheight.setName("mheight"); // NOI18N
        mheight.setPreferredSize(new java.awt.Dimension(75, 28));
        mheight.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                mheightStateChanged(evt);
            }
        });
        jToolBar1.add(mheight);

        jPanel1.setName("jPanel1"); // NOI18N

        jSplitPane1.setBorder(javax.swing.BorderFactory.createEtchedBorder());
        jSplitPane1.setDividerLocation(270);
        jSplitPane1.setOrientation(javax.swing.JSplitPane.VERTICAL_SPLIT);
        jSplitPane1.setName("jSplitPane1"); // NOI18N

        typePanel.setBorder(javax.swing.BorderFactory.createEtchedBorder(resourceMap.getColor("typePanel.border.highlightColor"), resourceMap.getColor("typePanel.border.shadowColor"))); // NOI18N
        typePanel.setName("typePanel"); // NOI18N
        typePanel.setPreferredSize(new java.awt.Dimension(204, 270));

        javax.swing.GroupLayout typePanelLayout = new javax.swing.GroupLayout(typePanel);
        typePanel.setLayout(typePanelLayout);
        typePanelLayout.setHorizontalGroup(
            typePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 200, Short.MAX_VALUE)
        );
        typePanelLayout.setVerticalGroup(
            typePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 264, Short.MAX_VALUE)
        );

        jSplitPane1.setTopComponent(typePanel);

        optionPanel.setBorder(javax.swing.BorderFactory.createEtchedBorder());
        optionPanel.setName("optionPanel"); // NOI18N

        javax.swing.GroupLayout optionPanelLayout = new javax.swing.GroupLayout(optionPanel);
        optionPanel.setLayout(optionPanelLayout);
        optionPanelLayout.setHorizontalGroup(
            optionPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 200, Short.MAX_VALUE)
        );
        optionPanelLayout.setVerticalGroup(
            optionPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 146, Short.MAX_VALUE)
        );

        jSplitPane1.setRightComponent(optionPanel);

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jSplitPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 208, javax.swing.GroupLayout.PREFERRED_SIZE)
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jSplitPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 432, Short.MAX_VALUE)
        );

        jScrollPane1.setName("jScrollPane1"); // NOI18N

        javax.swing.GroupLayout mainPanelLayout = new javax.swing.GroupLayout(mainPanel);
        mainPanel.setLayout(mainPanelLayout);
        mainPanelLayout.setHorizontalGroup(
            mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jToolBar1, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, 584, Short.MAX_VALUE)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, mainPanelLayout.createSequentialGroup()
                .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 370, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
        );
        mainPanelLayout.setVerticalGroup(
            mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, mainPanelLayout.createSequentialGroup()
                .addComponent(jToolBar1, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 432, Short.MAX_VALUE)
                    .addComponent(jPanel1, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
        );

        menuBar.setName("menuBar"); // NOI18N

        fileMenu.setText(resourceMap.getString("fileMenu.text")); // NOI18N
        fileMenu.setName("fileMenu"); // NOI18N

        javax.swing.ActionMap actionMap = org.jdesktop.application.Application.getInstance(leveleditor.LeveleditorApp.class).getContext().getActionMap(LeveleditorView.class, this);
        jMenuItem1.setAction(actionMap.get("MenuLoadLevel")); // NOI18N
        jMenuItem1.setText(resourceMap.getString("jMenuItem1.text")); // NOI18N
        jMenuItem1.setName("jMenuItem1"); // NOI18N
        fileMenu.add(jMenuItem1);

        jMenuItem3.setAction(actionMap.get("MenuSaveToFile")); // NOI18N
        jMenuItem3.setName("jMenuItem3"); // NOI18N
        fileMenu.add(jMenuItem3);

        exitMenuItem.setAction(actionMap.get("quit")); // NOI18N
        exitMenuItem.setName("exitMenuItem"); // NOI18N
        fileMenu.add(exitMenuItem);

        menuBar.add(fileMenu);

        jMenu1.setText(resourceMap.getString("jMenu1.text")); // NOI18N
        jMenu1.setName("jMenu1"); // NOI18N

        jMenuItem2.setAction(actionMap.get("OpenTeleportMngr")); // NOI18N
        jMenuItem2.setName("jMenuItem2"); // NOI18N
        jMenu1.add(jMenuItem2);

        menuBar.add(jMenu1);

        setComponent(mainPanel);
        setMenuBar(menuBar);
    }// </editor-fold>//GEN-END:initComponents
    
private void mwidthStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_mwidthStateChanged
    map.resizeWidth((Integer)mwidth.getValue());
}//GEN-LAST:event_mwidthStateChanged

private void mheightStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_mheightStateChanged
    map.resizeHeight((Integer)mheight.getValue());
}//GEN-LAST:event_mheightStateChanged

    @Action
    public void MenuLoadLevel() {
        JFileChooser fileDlg = new JFileChooser();
        fileDlg.addChoosableFileFilter(new FileNameExtensionFilter("xSoko level files", "lvl"));
        if(fileDlg.showOpenDialog(null)==JFileChooser.APPROVE_OPTION){
            map.LoadFromFile(fileDlg.getSelectedFile());
        }
    }

    @Action
    public void OpenTeleportMngr() {
        map.ShowTeleportManager();
    }

    @Action
    public void MenuSaveToFile() {
        JFileChooser fileDlg = new JFileChooser();
        fileDlg.addChoosableFileFilter(new FileNameExtensionFilter("xSoko level files", "lvl"));
        if(fileDlg.showSaveDialog(null)==JFileChooser.APPROVE_OPTION){
            try {
                map.SaveToFile(fileDlg.getSelectedFile());
            } catch (IOException ex) {
                Logger.getLogger(LeveleditorView.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    // <editor-fold defaultstate="collapsed" desc="Generated Variables">
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JMenu jMenu1;
    private javax.swing.JMenuItem jMenuItem1;
    private javax.swing.JMenuItem jMenuItem2;
    private javax.swing.JMenuItem jMenuItem3;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JSplitPane jSplitPane1;
    private javax.swing.JToolBar jToolBar1;
    private javax.swing.JPanel mainPanel;
    private javax.swing.JMenuBar menuBar;
    private javax.swing.JSpinner mheight;
    private javax.swing.JSpinner mwidth;
    private javax.swing.ButtonGroup optionGroup;
    private javax.swing.JPanel optionPanel;
    private javax.swing.ButtonGroup typeGroup;
    private javax.swing.JPanel typePanel;
    // End of variables declaration//GEN-END:variables
    // </editor-fold>
}
