package com.cgphotoedit;

import android.app.Activity;
import android.os.Bundle;
import android.widget.LinearLayout;

public class DrawAreaActivity extends Activity {
	
	private DrawView drawPad;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		// TODO Put your code here		
		setContentView(R.layout.drawarea);
		
		LinearLayout layout = (LinearLayout)findViewById(R.id.drawroot);
		drawPad = new DrawView(this.getApplicationContext(), "Galeria",
				250, 280);
		layout.addView(drawPad, 0);
		drawPad.invalidate();
	}
}