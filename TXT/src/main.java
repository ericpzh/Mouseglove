import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.InputEvent;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class main extends JFrame implements ActionListener {
    static Robot robot;
    static Point point;
    static boolean stop = false;
    private static main frm;
    private static JTextField txt;
    main()
    {
        setLocation(0, 0);
        setSize(200, 150);
    }
    public static void main(String[] args) throws InterruptedException, FileNotFoundException, AWTException {
        frm=new main();
        frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frm.setLayout(new FlowLayout());
        txt = new JTextField(12);
        txt.addActionListener(frm);
        frm.add(txt);
        frm.setVisible(true);
        int i = 0;
        int j = 110;
        int k = 110;
            while (!stop) {
                try {
                    Thread.sleep(15);
                    Scanner data = new Scanner(new FileReader("1.txt"));
                    String inputLine = data.nextLine();
                    robot = new Robot();
                    point = MouseInfo.getPointerInfo().getLocation();
                    int posX = (int) point.getX();
                    int posY = (int) point.getY();
                    int offset_x = 10;
                    int offset_y = 10;
                    System.out.println(inputLine);
                    try {
                        if (inputLine.charAt(0) == '1' && j != 0) {
                            robot.mousePress(InputEvent.BUTTON1_MASK);
                            j = 0;
                        }
                        if(inputLine.charAt(0) == '0' && j==0){
                           robot.mouseRelease(InputEvent.BUTTON1_MASK);
                           j++;
                        }
                        if (inputLine.charAt(1) == '2' && k != 0) {
                            //System.out.println("right click");
                            robot.mousePress(InputEvent.BUTTON3_MASK);
                            k = 0;
                        }
                        if(inputLine.charAt(1) == '0' && k==0){
                            robot.mouseRelease(InputEvent.BUTTON3_MASK);
                            k++;
                        }
                        //left
                        if (inputLine.charAt(2) == '3') {
                            //System.out.println("left");
                            robot.mouseMove(posX - offset_x, posY);

                        }
                        //right
                        if (inputLine.charAt(3) == '4') {
                            //System.out.println("right");
                            robot.mouseMove(offset_x + posX, posY);
                        }
                        //down
                        if (inputLine.charAt(5) == '6') {
                            robot.mouseMove(posX, offset_y + posY);
                        }
                        //up
                        if (inputLine.charAt(4) == '5') {
                            robot.mouseMove(posX, posY - offset_y);
                        }
                        i++;
                    } catch (IndexOutOfBoundsException e) {
                    }

                } catch (NoSuchElementException e) {
                }
            }
    }
    public void actionPerformed(ActionEvent e)
    {
        if(e.getSource()==txt)
        {
            stop = true;
        }
    }
}
