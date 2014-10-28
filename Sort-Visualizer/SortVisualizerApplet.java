import java.util.*;
import java.awt.*;
import java.awt.image.*;
import javax.swing.*;
import java.applet.*;

public class SortVisualizerApplet extends Applet implements Runnable {

	public static final int IMG_WIDTH = 240;
	public static final int IMG_HEIGHT = 320;

	private BufferedImage image;
	private Graphics2D g2d;
	private Thread mainloop;


	@Override
	public void init() {
		image = new BufferedImage( IMG_WIDTH, IMG_HEIGHT, BufferedImage.TYPE_INT_RGB );
		g2d = image.createGraphics();
		setSize( IMG_WIDTH, IMG_HEIGHT );
	}

	@Override
	public void paint( Graphics g ) {
		g.drawImage( image, 0, 0, this );
	}

	@Override
	public void update( Graphics g ) {
		paint( g );
	}

	@Override
	public void start() {
		mainloop = new Thread( this );
		mainloop.start();
	}

	@Override
	public void stop() {

	}

	@Override
	public void run() {

		/*populate and randomize array*/
		ArrayList<Integer> array = new ArrayList<Integer>();
		for(int i = 1; i <= 40; i++ ) {
			array.add( i );
		}
		Collections.shuffle( array );

		updateVisualizer( array, 1, 2 );
		repaint();
		try {
			Thread.sleep( 2000 );
		} catch( Exception e ) {
			System.err.println( "error!" );
		}
		updateVisualizer( array, 3, 5 );
		try {
			Thread.sleep( 2000 );
		} catch( Exception e ) {
			System.err.println( "error!" );
		}
		updateVisualizer( array, 7, 10 );
		try {
			Thread.sleep( 2000 );
		} catch( Exception e ) {
			System.err.println( "error!" );
		}
	}

	public void updateVisualizer( ArrayList< Integer > array, int index1, int index2 ) {

		int barHeight = IMG_HEIGHT/40-1;
		int barUnitLength = (IMG_WIDTH/40);
		
		/*clear backbuffer*/
		g2d.setColor( Color.WHITE );
		g2d.fillRect( 0, 0, IMG_WIDTH, IMG_HEIGHT );

		/*draw bars from the array list*/
		g2d.setColor( Color.BLACK );
		for( int i = 0; i < 40; i++ ) {
			int barLength = barUnitLength*array.get(i);
			int pos = (IMG_HEIGHT/40)*i;
			g2d.fillRect( 0, pos, barLength, barHeight );
		}

		/*draw index lines*/
		g2d.setColor( Color.RED );
		g2d.fillRect( 0, (IMG_HEIGHT/40)*(index1+1)-1, IMG_WIDTH, 1 );
		g2d.setColor( Color.BLUE );
		g2d.fillRect( 0, (IMG_HEIGHT/40)*(index2+1)-1, IMG_WIDTH, 1 );
		repaint();
	}
}
