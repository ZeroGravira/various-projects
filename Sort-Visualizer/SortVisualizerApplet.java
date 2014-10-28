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

	@Override
	public void init() {
		image = new BufferedImage( IMG_WIDTH, IMG_HEIGHT, BufferedImage.TYPE_INT_RGB );
		g2d = image.createGraphics();
		setSize( IMG_WIDTH, IMG_HEIGHT );
	}

	@Override
	public void paint( Graphics g ) {

	}

	@Override
	public void update( Graphics g ) {

	}

	@Override
	public void start() {

		/*populate and randomize array*/
		ArrayList<Integer> array = new ArrayList<Integer>();
		for(int i = 1; i <= 40; i++ ) {
			array.add( i );
		}
		Collections.shuffle( array );

	}

	@Override
	public void stop() {

	}

	@Override
	public void run() {

	}
}
