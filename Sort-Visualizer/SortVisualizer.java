
import java.util.*;
import java.awt.*;
import java.awt.image.*;
import javax.swing.*;


/*
 * A program to visualize sorting algorithms.
 *
 * @Author: Glenn Wallace
 */
public class SortVisualizer extends JPanel {

	public static final int IMG_WIDTH = 240;
	public static final int IMG_HEIGHT = 320;

	private BufferedImage image;
	private Graphics2D g2d;

	public SortVisualizer() {
		super();
		image = new BufferedImage( IMG_WIDTH, IMG_HEIGHT, BufferedImage.TYPE_INT_RGB );
		g2d = image.createGraphics();
	}


	private void bubbleSort( ArrayList<Integer> array ) {
		boolean swapped = false;
		for( int i = 0; i < 40 && !swapped; i++ ) {
			swapped = false;
			for( int j = 39; j > i; j-- ) {
				updateVisualizer( array, i, j );
				if( array.get( j ) < array.get( j - 1 ) ) {
					Collections.swap( array, j, j - 1 );
					updateVisualizer( array, i, j );
					swapped = true;
				}
			}
		}
	}

	private void updateVisualizer(ArrayList<Integer> array, int index1, int index2 ) {

		int barHeight = (IMG_HEIGHT/40)-1;
		int barUnitLength = (IMG_WIDTH/40);
		
		/*clear back buffer*/
		g2d.setColor( Color.WHITE );
		g2d.fillRect( 0, 0, IMG_WIDTH, IMG_HEIGHT );

		/*draw the bars from the array list*/
		g2d.setColor( Color.BLACK );
		for( int i = 0; i < 40; i++ ) {
			int barLength = barUnitLength*array.get(i);
			int pos = (IMG_HEIGHT/40)*i;
			g2d.fillRect( 0, pos, barLength, barHeight );
		}
		
		/*draw the indices*/
		g2d.setColor( Color.RED );
		g2d.fillRect( 0, (IMG_HEIGHT/40)*(index1 + 1)-1, IMG_WIDTH, 1 );
		repaint();

	}

	@Override
	public void paintComponent( Graphics g ) {
		super.paintComponent(g);
		if( image != null ) {
			g.drawImage( image, 0, 0, null );
		}
	}

	public static void main( String[] argv ) {

		/*populate and randomize array*/
		ArrayList<Integer> array = new ArrayList<Integer>();
		for(int i = 1; i <= 40; i++ ) {
			array.add( i );
		}
		Collections.shuffle( array );

		/*initialize JFrame and graphics*/
		JFrame app = new JFrame();
		app.setDefaultCloseOperation( JFrame.DISPOSE_ON_CLOSE );
		app.pack();
		app.setResizable( false );
		app.setTitle( "Sort Visualizer" );
		app.setSize( 240, 320 );
		app.setVisible( true );

		/*initialize drawing objects*/
		SortVisualizer drawPanel = new SortVisualizer();
		app.add( drawPanel );
		drawPanel.updateVisualizer( array, 0, 0 );

		drawPanel.updateVisualizer( array, 1, 0 );

		/*initiate the sort!*/
		drawPanel.bubbleSort( array );
	}

}
