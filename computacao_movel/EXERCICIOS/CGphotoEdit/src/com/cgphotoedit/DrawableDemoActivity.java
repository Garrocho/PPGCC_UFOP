package com.cgphotoedit;

import android.app.Activity;
import android.graphics.Canvas;
import android.os.Bundle;
import android.widget.LinearLayout;

import com.cgphotoedit.TransformedViewWidget.Transformation;

public class DrawableDemoActivity extends Activity {
	
	private TransformedViewWidget widget1;
	private TransformedViewWidget widget2;
	private TransformedViewWidget widget3;
	private TransformedViewWidget widget4;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.drawarea);
		
		LinearLayout layout = (LinearLayout)findViewById(R.id.drawroot);
		
		widget1 = new TransformedViewWidget(this.getApplicationContext(), new TextDrawable(),
				new Transformation(){
			@Override
			public String describe(){
				return "translate(-50,-20),scale(2,1.2)";
			}
			
			@Override
			public void transform(Canvas canvas){
				canvas.translate(-50.0F, -20.0F);
				canvas.scale(2F, 1.2F);
			}
		});
		
		widget2 = new TransformedViewWidget(this.getApplicationContext(), new TextDrawable(),
				new Transformation(){
			@Override
			public String describe(){
				return "translate(-50,-20),scale(2,1.2)";
			}
			
			@Override
			public void transform(Canvas canvas){
				canvas.skew(0.1F, 0.3F);
			}
		});
		
		widget3 = new TransformedViewWidget(this.getApplicationContext(), new TextDrawable(),
				new Transformation(){
			@Override
			public String describe(){
				return "translate(-50,-20),scale(2,1.2)";
			}
			
			@Override
			public void transform(Canvas canvas){
				canvas.translate(-100.0F, -100.0F);
				canvas.scale(2.5F, 2F);
				canvas.skew(0.1F, 0.3F);
			}
		});
		
		widget4 = new TransformedViewWidget(this.getApplicationContext(), new TextDrawable(),
				new Transformation(){
			@Override
			public String describe(){
				return "translate(-50,-20),scale(2,1.2)";
			}
			
			@Override
			public void transform(Canvas canvas){
				canvas.translate(110.0F, -20.0F);
				canvas.rotate(85.0F);
			}
		});
		
		layout.addView(widget1, 0);
		layout.addView(widget2, 1);
		layout.addView(widget3, 2);
		layout.addView(widget4, 3);
		
		widget1.invalidate();
		widget2.invalidate();
		widget3.invalidate();
		widget4.invalidate();
	}
}