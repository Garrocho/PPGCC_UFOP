package com.cgphotoedit;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.ColorFilter;
import android.graphics.Paint;
import android.graphics.PixelFormat;
import android.graphics.drawable.Drawable;

public class TextDrawable extends Drawable {

	private ColorFilter filter;
	private int opacity;
	
	public TextDrawable(){
		
	}
	
	@Override
	public void draw(Canvas canvas) {
		// TODO Auto-generated method stub
		Paint paint = new Paint();
		paint.setColorFilter(filter);
		paint.setAlpha(opacity);
		paint.setTextSize(12);
		paint.setColor(Color.GREEN);
		
		canvas.drawText("Hello", 40, 55, paint);
		paint.setTextSize(16);
		paint.setColor(Color.RED);
		canvas.drawText("Android", 35, 65, paint);
	}

	@Override
	public int getOpacity() {
		// TODO Auto-generated method stub
		return PixelFormat.TRANSLUCENT;
	}

	@Override
	public void setAlpha(int alpha) {
		// TODO Auto-generated method stub
		this.opacity = alpha;
	}

	@Override
	public void setColorFilter(ColorFilter cf) {
		// TODO Auto-generated method stub
		this.filter = cf;
	}

}